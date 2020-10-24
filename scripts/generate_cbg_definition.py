from clang.cindex import *
from bindings import define
import re
import pprint

import sys
import os
os.chdir(os.path.dirname(__file__))


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

    if altseed:
        print('\t' * indent + text)

    for child in cursor.get_children():
        dump(child, indent + 1, altseed)


class Parser:

    def __init__(self):
        self.classes = {}
        self.structs = {}
        self.enums = {}

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
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
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
            for method_name, method in _class["methods"].items():
                try:
                    method_code = f'''\
    with class_.add_func('{method_name}') as func_:
'''
                    if method["return_type"] != "void":
                        type_ = self.to_cbg_parameter_type(
                            method["return_type"])
                        method_code += f'''\
        func_.return_value.type_ = {type_}
'''
                    elif len(method["params"]) == 0:
                        method_code += f'''\
        pass
'''

                    for param_name, param in method["params"].items():
                        type_ = self.to_cbg_parameter_type(param["type"])
                        method_code += f'''\
        func_.add_arg({type_}, '{param_name}')
'''
                except Exception as e:
                    method_code = f'''\
# {e}
    """
{method_code}
    """
'''

                code += method_code
                code += '\n'

            for property_name, prop in _class["properties"].items():
                try:
                    type_ = self.to_cbg_parameter_type(prop["type"])
                    code += f'''\
    with class_.add_property({type_}, '{property_name}') as prop_:
        prop_.has_getter = {prop["get"] if "get" in prop else False}
        prop_.has_setter = {prop["set"] if "set" in prop else False}
'''
                except:
                    code += f'''\
    # class_.add_property({prop["type"]}, '{property_name}')
'''

            code += f'''\
define.classes.append({name})

'''
        return code

    def parse(self, cursor):
        if cursor.kind.name == "NAMESPACE":
            if cursor.spelling == "Altseed2":
                self.namespace(cursor)
            return

        for child in cursor.get_children():
            self.parse(child)

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
        for child in cursor.get_children():
            if child.kind.name == 'ENUM_CONSTANT_DECL':
                self.enum_constant(child, enum["values"])
        self.enums[cursor.spelling] = enum

    def enum_constant(self, cursor, enum_dic):
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
            value = str(len(enum_dic))
        enum_dic[cursor.spelling] = value

    def _class(self, cursor):
        class_def = {
            "methods": {},
            "properties": {}
        }
        for child in cursor.get_children():
            if child.kind.name == 'CXX_METHOD':
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

        if re.match(r"Get.*", cursor.spelling) and len(params) == 0:
            name = re.sub(r"Get(.*)", r"\1", cursor.spelling)
            if not name in class_def["properties"]:
                class_def["properties"][name] = {}
            prop = class_def["properties"][name]
            prop["type"] = cursor.type.spelling.split('(')[0].strip()
            prop["get"] = True
        elif re.match(r"Set.*", cursor.spelling) and len(params) == 1:
            name = re.sub(r"Set(.*)", r"\1", cursor.spelling)
            if not name in class_def["properties"]:
                class_def["properties"][name] = {}
            prop = class_def["properties"][name]
            prop["type"] = list(params.values())[0]["type"]
            prop["set"] = True
        else:
            class_def["methods"][cursor.spelling] = {
                "return_type": cursor.type.spelling.split('(')[0].strip(),
                "params": params
            }

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
            return re.sub(r"std::shared_ptr<(.*)>.*", r"\1", _type)

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
    'Physics/Collider/RectangleCollider.h',
    'Physics/Collider/PolygonCollider.h',
    'Platform/FileSystem.h',
    'Sound/Sound.h',
    'Sound/SoundMixer.h',
    'Tool/Tool.h',
    'Window/Window.h',
    'System/SynchronizationContext.h',
]
parser = Parser()

if len(sys.argv) == 2:
    Config.set_library_path(sys.argv[1])

for header in headers:
    print(header)

    translation_unit = Index.create().parse(
        source_path + header, ['-x', 'c++-header', "-std=c++17", "-DUSE_CBG"], None, TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)

    # dump(translation_unit.cursor)
    parser.parse(translation_unit.cursor)

with open("bindings/auto_generate_define.py", mode="w", encoding="utf-8-sig") as f:
    f.write(parser.cbg_definition())
