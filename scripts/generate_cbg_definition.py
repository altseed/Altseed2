from clang.cindex import *
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
        self.enums = {}

    def cbg_definition(self):
        pass

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
                if token.spelling in enum_dic:
                    token_str = f"({enum_dic[token.spelling]})"
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
                    "type": self.to_cbg_parameter_type(child.type.spelling)
                }

        if re.match(r"Get.*", cursor.spelling) and len(params) == 0:
            name = re.sub(r"Get(.*)", r"\1", cursor.spelling)
            if not name in class_def["properties"]:
                class_def["properties"][name] = {}
            prop = class_def["properties"][name]
            prop["type"] = self.to_cbg_parameter_type(
                cursor.type.spelling.split('(')[0].strip())
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
                "return_type": self.to_cbg_parameter_type(cursor.type.spelling.split('(')[0].strip()),
                "params": params
            }

    def to_cbg_parameter_type(self, _type):
        if re.match(r"const .*", _type):
            _type = re.sub(r"const (.*)", r"\1", _type)

        if _type == "const char16_t *":
            return "ctypes.c_wchar_p"
        if _type == "int32_t":
            return "int"
        if _type == "uint32_t":
            return "int"
        if _type == "bool *":
            return "bool"
        if _type == "int32_t *":
            return "int"
        if _type == "float *":
            return "float"

        if re.match(r"std::shared_ptr<.*>.*", _type):
            return re.sub(r"std::shared_ptr<(.*)>.*", r"\1", _type)

        return _type


source_path = '../core/src/'
headers = ['Core.h', 'Input/Keyboard.h']
parser = Parser()

if len(sys.argv) == 2:
    Config.set_library_path(sys.argv[1])

for header in headers:
    with open(source_path + header, encoding="utf-8-sig") as f:
        data_lines = f.read()

    with open("temp.h", mode="w", encoding="utf-8-sig") as f:
        f.write(data_lines)

    translation_unit = Index.create().parse(
        "temp.h", ['-x', 'c++-header', "-std=c++17"], None, TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)

    # dump(translation_unit.cursor)
    parser.parse(translation_unit.cursor)

pprint.pprint(parser.classes)
pprint.pprint(parser.enums)
