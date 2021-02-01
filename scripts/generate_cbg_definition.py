from clang.cindex import *
from bindings import define
from bindings import CppBindingGenerator as cbg
import re
import pprint
import sys
import os
import copy
import json
import argparse
import platform

current_dir = os.path.dirname(__file__)
if current_dir != '':
    os.chdir(current_dir)


def merge_list(a, b):
    m = copy.copy(a)
    for i, value in enumerate(b):
        if i >= len(a):
            m.append(value)
        if isinstance(value, dict):
            m[i] = merge_dict(a[i], b[i])
        elif isinstance(value, list):
            m[i] = merge_list(a[i], b[i])
        else:
            m.append(value)
    return m


def merge_dict(a, b):
    m = copy.copy(a)
    if type(m) is list:
        return m

    for item in b:
        if not item in a:
            m[item] = b[item]
        elif isinstance(b[item], dict):
            m[item] = merge_dict(a[item], b[item])
        elif isinstance(b[item], list):
            m[item] = merge_list(a[item], b[item])
        else:
            m[item] = b[item]
    return m


def dump(cursor, indent=0, altseed=False):
    if cursor.kind.name == "NAMESPACE":
        if cursor.spelling == "Altseed2":
            altseed = True
        else:
            return
    text = cursor.kind.name

    # 名前
    text += ' 名前[' + cursor.spelling + ']'

    # 型
    text += ' 型[' + cursor.type.spelling + ']'

    # 元の型
    if cursor.type.spelling != cursor.type.get_canonical().spelling:
        text += ' 元型[' + cursor.type.get_canonical().spelling + ']'

    for child in cursor.get_children():
        dump(child, indent + 1, altseed)


class Parser:

    def __init__(self):
        self.classes = {}
        self.structs = {}
        self.enums = {}

    def cbg_method_definition(self, method_name, method, overload=False):
        try:
            method_code = f'''\
    with class_.add_func('{method_name}') as func_:
'''
            is_pass = True
            if method["return_type"] != "void":
                type_ = self.to_cbg_parameter_type(
                    method["return_type"])
                method_code += f'''\
        func_.return_value.type_ = {type_}
'''
                is_pass = False

            if "is_static" in method:
                method_code += f'''\
        func_.is_static = {method["is_static"]}
'''
                is_pass = False

            if "is_public" in method:
                method_code += f'''\
        func_.is_public = {method["is_public"]}
'''
                is_pass = False

            if overload:
                method_code += f'''\
        func_.is_overload = True
'''
                is_pass = False

            if "onlyExtern" in method:
                method_code += f'''\
        func_.onlyExtern = {method["onlyExtern"]}
'''
                is_pass = False

            for param_name, param in method["params"].items():
                type_ = self.to_cbg_parameter_type(param["type"])
                is_pass = False
                is_arg_pass = True

                if param_name == "in":
                    param_name += "_"

                method_code += f'''\
        with func_.add_arg({type_}, '{param_name}') as arg:
'''
                if "called_by" in param:
                    for called_by in cbg.ArgCalledBy:
                        if param["called_by"] == called_by.name:
                            method_code += f'''\
            arg.called_by = cbg.ArgCalledBy.{param["called_by"]}
'''
                            is_arg_pass = False
                            break

                if "nullable" in param:
                    method_code += f'''\
            arg.nullable = {param["nullable"]}
'''
                    is_arg_pass = False

                if is_arg_pass:
                    method_code += f'''\
            pass
'''

            if is_pass:
                method_code += f'''\
        pass
'''
        except Exception as e:
            method_code = f'''\
# {e}
    """
{method_code}
    """
'''

        return method_code

    def cbg_definition(self):
        code = '''\
from . import CppBindingGenerator as cbg
from .define import *
import ctypes
import sys

'''
        for name, enum in self.enums.items():
            code += f'''\
{name} = cbg.Enum('Altseed2', '{name}')
with {name} as enum_:
'''

            if "isFlag" in enum:
                code += f'''\
    enum_.isFlag = {enum["isFlag"]}
'''

            if "alias" in enum:
                code += f'''\
    enum_.alias = "{enum["alias"]}"
'''

            for key, value in sorted(enum["values"].items(), key=lambda x: eval(x[1])):
                code += f'''\
    enum_.add('{key}', {value})
'''
            code += f'''\
define.enums.append({name})

'''

        for name, _class in self.classes.items():
            code += f'''\
{name} = cbg.Class('Altseed2', '{name}')
'''
        code += '\n'

        for name, _class in self.classes.items():
            if len(_class["methods"]) == 0 and len(_class["properties"]) == 0:
                continue

            code += f'''\
with {name} as class_:
'''

            if "base_class" in _class and _class["base_class"] in self.classes.keys():
                code += f'''\
    class_.base_class = {_class["base_class"]}
'''

            if "is_public" in _class:
                code += f'''\
    class_.is_public = {_class["is_public"]}
'''

            if "SerializeType" in _class:
                for serializeType in cbg.SerializeType:
                    if _class["SerializeType"] == serializeType.name:
                        code += f'''\
    class_.SerializeType = cbg.SerializeType.{_class["SerializeType"]}
'''
                        break

            if "CallBackType" in _class:
                for callBackType in cbg.CallBackType:
                    if _class["CallBackType"] == callBackType.name:
                        code += f'''\
    class_.CallBackType = cbg.CallBackType.{_class["CallBackType"]}
'''
                        break

            if "cache_mode" in _class:
                for cache_mode in cbg.CacheMode:
                    if _class["cache_mode"] == cache_mode.name:
                        code += f'''\
    class_.cache_mode = cbg.CacheMode.{_class["cache_mode"]}
'''
                        break

            if "is_Sealed" in _class:
                code += f'''\
    class_.is_Sealed = {_class["is_Sealed"]}
'''

            if "handleCache" in _class:
                code += f'''\
    class_.handleCache = {_class["handleCache"]}
'''

            for method_name, method in _class["methods"].items():
                if type(method) is dict:
                    code += self.cbg_method_definition(method_name, method)
                    code += '\n'
                elif type(method) is list:
                    for m in method:
                        code += self.cbg_method_definition(
                            method_name, m, True)
                        code += '\n'

            for property_name, prop in _class["properties"].items():
                try:
                    type_ = self.to_cbg_parameter_type(prop["type"])
                    code += f'''\
    with class_.add_property({type_}, '{property_name}') as prop_:
        prop_.has_getter = {prop["get"] if "get" in prop else False}
        prop_.has_setter = {prop["set"] if "set" in prop else False}
'''
                    if "onlyExtern" in prop:
                        code += f'''\
        prop_.onlyExtern = {prop["onlyExtern"]}
'''

                    if "nullable" in prop:
                        code += f'''\
        prop_.nullable = {prop["nullable"]}
'''

                    if "null_deserialized" in prop:
                        code += f'''\
        prop_.null_deserialized = {prop["null_deserialized"]}
'''

                    if "is_public" in prop:
                        code += f'''\
        prop_.is_public = {prop["is_public"]}
'''

                    if "is_static" in prop:
                        code += f'''\
        prop_.is_static = {prop["is_static"]}
'''

                    if "serialized" in prop:
                        code += f'''\
        prop_.serialized = {prop["serialized"]}
'''

                    if "cache_set_value" in prop:
                        code += f'''\
        prop_.cache_set_value = {prop["cache_set_value"]}
'''

                except:
                    type_ = prop["type"] if "type" in prop else "not found"
                    code += f'''\
    # class_.add_property({type_}, '{property_name}')
'''

            code += f'''\
define.classes.append({name})

'''
        return code

    def parse(self, cursor, tool_mode=False):
        self.tool_mode = tool_mode

        if cursor.kind.name == "NAMESPACE":
            if cursor.spelling == "Altseed2":
                self.namespace(cursor)
            return

        for child in cursor.get_children():
            self.parse(child, self.tool_mode)

    def namespace(self, cursor):
        for child in cursor.get_children():
            if child.kind.name == 'CLASS_DECL':
                self._class(child)
            elif child.kind.name == 'ENUM_DECL':
                self.enum(child)

    def enum(self, cursor):
        enum = {
            "values": {}
        }
        if cursor.spelling in self.enums:
            enum = self.enums[cursor.spelling]

        count = 0
        for child in cursor.get_children():
            if child.kind.name == 'ENUM_CONSTANT_DECL':
                self.enum_constant(child, enum["values"], count)
                count += 1
        self.enums[cursor.spelling] = enum

    def enum_constant(self, cursor, enum_dic, count):
        value = ""
        for child in cursor.get_children():
            tokens = []
            for token in child.get_tokens():
                token_str = token.spelling
                if token_str in enum_dic:
                    token_str = f"({enum_dic[token_str]})"
                tokens.append(token_str)
            if len(tokens) > 0:
                value = " ".join(tokens)
        if value == "":
            value = str(count)
        enum_dic[cursor.spelling] = value

    def _class(self, cursor):
        class_def = {
            "methods": {},
            "properties": {}
        }
        if cursor.spelling in self.classes:
            class_def = self.classes[cursor.spelling]

        if self.tool_mode and cursor.spelling == "Tool":
            class_def["is_Sealed"] = True
            class_def["is_tool"] = True

        is_public = False
        for child in cursor.get_children():
            if child.kind.name == 'CXX_ACCESS_SPEC_DECL':
                for token in child.get_tokens():
                    if token.spelling == "public":
                        is_public = True
                    elif token.spelling == "private" or token.spelling == "protected":
                        is_publuc = False

            if child.kind.name == 'CXX_METHOD' and is_public:
                self.method(child, class_def)
        self.classes[cursor.spelling] = class_def

    def method(self, cursor, class_def):
        # params
        params = {}
        for child in cursor.get_children():
            if child.kind.name == 'PARM_DECL':
                params[child.spelling] = {
                    "type": child.type.spelling
                }

                if self.tool_mode:
                    type_ = params[child.spelling]["type"]
                    if type_ == "int32_t *" or type_ == "bool *" or type_ == "float *":
                        params[child.spelling]["called_by"] = "Ref"
                    if type_ == "const char16_t *":
                        params[child.spelling]["nullable"] = False

        if re.match(r"Get.*", cursor.spelling) and len(params) == 0 and cursor.spelling != "GetInstance" and \
                (not "is_tool" in class_def or cursor.spelling in ["GetToolUsage"]):
            name = re.sub(r"Get(.*)", r"\1", cursor.spelling)
            if not name in class_def["properties"]:
                class_def["properties"][name] = {}
            prop = class_def["properties"][name]
            prop["type"] = cursor.type.spelling.split('(')[0].strip()
            prop["get"] = True
        elif re.match(r"Set.*", cursor.spelling) and len(params) == 1 and \
                (not "is_tool" in class_def or cursor.spelling in ["SetToolUsage"]):
            name = re.sub(r"Set(.*)", r"\1", cursor.spelling)
            if not name in class_def["properties"]:
                class_def["properties"][name] = {}
            prop = class_def["properties"][name]
            prop["type"] = list(params.values())[0]["type"]
            prop["set"] = True
        else:
            params_digest = ''.join(map(lambda p: p["type"], params.values()))
            method = {
                "return_type": cursor.type.spelling.split('(')[0].strip(),
                "params": params,
                "params_digest": params_digest
            }

            if "is_tool" in class_def and any([re.match(r".*Array", param["type"]) for param in params.values()]):
                method["is_public"] = False

            if "is_tool" in class_def and cursor.spelling == "GetInstance":
                method["is_static"] = True
                method["is_public"] = False

            if cursor.spelling in class_def["methods"] and \
                    type(class_def["methods"][cursor.spelling]) is dict and \
                    class_def["methods"][cursor.spelling]["params_digest"] != params_digest:
                class_def["methods"][cursor.spelling] = [
                    class_def["methods"][cursor.spelling],
                    method
                ]
                print(cursor.spelling)
            elif cursor.spelling in class_def["methods"] and \
                    type(class_def["methods"][cursor.spelling]) is list and \
                    all([m["params_digest"] != params_digest for m in class_def["methods"][cursor.spelling]]):
                class_def["methods"][cursor.spelling].append(method)
                print(cursor.spelling)
            else:
                class_def["methods"][cursor.spelling] = method

    def to_cbg_parameter_type(self, _type):
        if re.match(r"const .*", _type):
            _type = re.sub(r"const (.*)", r"\1", _type)

        if re.match(r"Altseed2::.*", _type):
            _type = re.sub(r"Altseed2::(.*)", r"\1", _type)

        if re.match(r".* &", _type):
            _type = re.sub(r"(.*) &", r"\1", _type)

        if _type == "char16_t *":
            return "ctypes.c_wchar_p"

        if _type == "int":
            return "int"
        if _type == "int32_t":
            return "int"
        if _type == "uint32_t":
            return "int"
        if _type == "int32_t *":
            return "int"

        if _type == "bool":
            return "bool"
        if _type == "bool *":
            return "bool"

        if _type == "float":
            return "float"
        if _type == "float *":
            return "float"

        if re.match(r"std::shared_ptr<.*>.*", _type):
            _type = re.sub(r"std::shared_ptr<(.*)>.*", r"\1", _type)

        if _type in self.enums:
            return _type

        if _type in self.classes:
            return _type

        if any([struct.alias == _type for struct in define.structs]):
            return _type

        if any([_class.name == _type for _class in define.classes]):
            return _type

        if any([enum.name == _type for enum in define.enums]):
            return _type

        raise Exception(_type)

    def add_definition_option(self, option):
        if 'enums' in option:
            for k, v in option['enums'].items():
                if k in self.enums:
                    v = merge_dict(v, self.enums[k])
                self.enums[k] = v

        if 'classes' in option:
            for k, v in option['classes'].items():
                if k in self.classes:
                    v = merge_dict(self.classes[k], v)
                self.classes[k] = v


source_path = '../core/src/'
headers = [
    'BaseObject.h',
    'Configuration.h',
    'Core.h',
    'FPS.h',
    'Common/Array.h',
    'Common/Resource.h',
    'Common/ResourceContainer.h',
    'Common/Resources.h',
    'Common/StringHelper.h',
    'Common/Assertion.h',
    'Common/ThreadSafeMap.h',
    'Common/BinaryWriter.h',
    'Common/BinaryReader.h',
    'Common/HashHelper.h',
    'Graphics/BatchRenderer.h',
    'Graphics/BuiltinShader.h',
    'Graphics/Color.h',
    'Graphics/CommandList.h',
    'Graphics/Font.h',
    'Graphics/FrameDebugger.h',
    'Graphics/ImageFont.h',
    'Graphics/Graphics.h',
    'Graphics/LLGIWindow.h',
    'Graphics/Material.h',
    'Graphics/RenderTexture.h',
    'Graphics/Renderer/Rendered.h',
    'Graphics/Renderer/RenderedCamera.h',
    'Graphics/Renderer/RenderedSprite.h',
    'Graphics/Renderer/RenderedText.h',
    'Graphics/Renderer/RenderedPolygon.h',
    'Graphics/Renderer/Renderer.h',
    'Graphics/Renderer/CullingSystem.h',
    'Graphics/Shader.h',
    'Graphics/ShaderCompiler/ShaderCompiler.h',
    'Graphics/Texture2D.h',
    'Graphics/TextureBase.h',
    'IO/BaseFileReader.h',
    'IO/File.h',
    'IO/FileRoot.h',
    'IO/PackFile.h',
    'IO/PackFileReader.h',
    'IO/StaticFile.h',
    'IO/StreamFile.h',
    'Input/ButtonState.h',
    'Input/Cursor.h',
    'Input/Joystick.h',
    'Input/Keyboard.h',
    'Input/Mouse.h',
    'Logger/Log.h',
    'Math/Easing.h',
    'Math/MathTemplate.h',
    'Math/Matrix33F.h',
    'Math/Matrix33I.h',
    'Math/Matrix44F.h',
    'Math/Matrix44I.h',
    'Math/RectF.h',
    'Math/RectI.h',
    'Math/Vector2F.h',
    'Math/Vector2I.h',
    'Math/Vector3F.h',
    'Math/Vector3I.h',
    'Math/Vector4F.h',
    'Math/Vector4I.h',
    'Physics/Collider/Box2DHelper.h',
    'Physics/Collider/Collider.h',
    'Physics/Collider/CircleCollider.h',
    'Physics/Collider/PolygonCollider.h',
    'Physics/Collider/EdgeCollider.h',
    'Platform/FileSystem.h',
    'Sound/Sound.h',
    'Sound/SoundMixer.h',
    'Tool/Tool.h',
    'Window/Window.h',
    'System/SynchronizationContext.h',
]
jsons = [
    "bindings/common.json",
    "bindings/core.json",
    "bindings/graphics.json",
    "bindings/input.json",
    "bindings/io.json",
    "bindings/logger.json",
    "bindings/physics.json",
    "bindings/sound.json",
    "bindings/window.json",
]

aparser = argparse.ArgumentParser()
aparser.add_argument('--clang', default='./', help='a path to a directory which contains libclang.dll (Windows, Linux)')
aparser.add_argument('--xcode', default='/Applications/Xcode.app/', help='a path to a directory which contains xcode like /Applications/Xcode.app/ (MacOSX)')
args = aparser.parse_args()

options = ['-x', 'c++-header', "-std=c++17", "-DUSE_CBG"]

pf = platform.system()

if pf == 'Darwin':
    xcode_path = args.xcode + 'Contents/Frameworks/'
    xcode_include_path = args.xcode + 'Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/'
    if not os.path.exists(xcode_path):
        print(f'Not found {xcode_path}')
        sys.exit(1)

    if not os.path.exists(xcode_include_path):
        print(f'Not found {xcode_include_path}')
        sys.exit(1)

    Config.set_library_path(xcode_path)
    options.extend(['-I', xcode_include_path])

else:
    Config.set_library_path(args.clang)

parser = Parser()

for header in headers:
    print(header)

    translation_unit = Index.create().parse(
        source_path + header, options, None, TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)

    # dump(translation_unit.cursor)
    parser.parse(translation_unit.cursor, header == "Tool/Tool.h")

for json_ in jsons:
    with open(json_) as f:
        option = json.load(f)
        parser.add_definition_option(option)

dst_path = "bindings/auto_generate_define.py"

with open(dst_path, mode="w", encoding="utf-8-sig") as f:
    f.write(parser.cbg_definition())
    print(f'export {dst_path}')
