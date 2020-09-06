from clang.cindex import *
import re

import sys, os
os.chdir(os.path.dirname(__file__))

if len(sys.argv) == 2:
    Config.set_library_path(sys.argv[1])

translation_unit = Index.create().parse(
    '../thirdparty/imgui/imgui.h', ['-x', 'c++-header', "-std=c++17", '-D IMGUI_DISABLE_OBSOLETE_FUNCTIONS'])

exclude_funcs = [
    "NewFrame", "EndFrame", "Render", "Combo"
]

enum_decl = ""
func_decl = ""
func_imp = ""
enum_cbg = ""
func_cbg = ""


def to_altseed2_return_type(_type):
    if _type == "int":
        return "int32_t"
    if _type == "ImVec2":
        return "Vector2F"
    if _type == "ImVec4":
        return "Vector4F"
    if _type == "const char *":
        return "const char16_t *"
    if _type == "ImU32":
        return "uint32_t"
    if _type == "float":
        return "float"
    if _type == "bool":
        return "bool"
    if _type == "void":
        return "void"
    if _type == "ImGuiID":
        return "uint32_t"

    if _type == "void *":
        raise

    raise


def to_altseed2_parameter_type(_type):
    if _type == "char *":
        raise
    if _type == "void *":
        raise
    if _type == "ImTextureID":
        raise
    if _type == "float &":
        raise
    if _type == "ImGuiStyle *":
        raise
    if _type == "ImGuiContext *":
        raise
    if _type == "ImGuiStorage *":
        raise

    if _type == "const char *":
        return "const char16_t *"
    if _type == "int":
        return "int32_t"
    if _type == "const ImVec2 &":
        return "Vector2F"
    if _type == "const ImVec4 &":
        return "Vector4F"
    if _type == "ImU32":
        return "uint32_t"
    if _type == "ImGuiID":
        return "uint32_t"
    if _type == "float":
        return "float"
    if _type == "bool":
        return "bool"
    if _type == "bool *":
        return "bool *"
    if _type == "int *":
        return "int32_t *"
    if _type == "float *":
        return "float *"

    if re.match(r"ImGui.*", _type):
        return "Tool" + re.sub(r"ImGui", "", _type)
    if re.match(r"int \[\d*\]", _type):
        return "std::shared_ptr<Int32Array>"
    if re.match(r"float \[\d*\]", _type):
        return "std::shared_ptr<FloatArray>"
    if re.match(r"bool \[\d*\]", _type):
        return "std::shared_ptr<BoolArray>"
    if re.match(r"const int \*", _type):
        return "int32_t *"
    if re.match(r"const float \*", _type):
        return "float *"
    if re.match(r"const bool \*", _type):
        return "bool *"

    raise


def to_imgui_parameter_type(name, _type):
    if _type == "char *":
        raise
    if _type == "void *":
        raise
    if _type == "ImTextureID":
        raise
    if _type == "float &":
        raise
    if _type == "ImGuiStyle *":
        raise
    if _type == "ImGuiStorage *":
        raise

    if name == "args":
        raise

    if _type == "const char16_t *":
        return f"utf16_to_utf8({name}).c_str()"
    if _type == "int32_t":
        return name
    if _type == "Vector2F":
        return f"toImVec2({name})"
    if _type == "Vector4F":
        return f"toImVec4({name})"
    if _type == "uint32_t":
        return name
    if _type == "float":
        return name
    if _type == "bool":
        return name
    if _type == "bool *":
        return name
    if _type == "int32_t *":
        return name
    if _type == "float *":
        return name

    if re.match(r"Tool.*", _type):
        cast = re.sub(r'Tool(.*)', r'ImGui\1', _type)
        return f"({cast}){name}"
    if re.match(r"std::shared_ptr<.*>", _type):
        return f"&{name}->GetVector()[0]"

    raise


def to_cbg_parameter_type(_type):
    if _type == "const char16_t *":
        return "ctypes.c_wchar_p"
    if _type == "int32_t":
        return "int"
    if _type == "uint32_t":
        return "int"
    if _type == "float":
        return "float"
    if _type == "bool":
        return "bool"
    if _type == "bool *":
        return "bool"
    if _type == "int32_t *":
        return "int"
    if _type == "float *":
        return "float"
    if _type == "Vector2F":
        return "Vector2F"
    if _type == "Vector4F":
        return "Vector4F"

    if re.match(r"Tool[a-zA-Z]*", _type):
        return _type
    if re.match(r"std::shared_ptr<.*>", _type):
        return re.sub(r"std::shared_ptr<(.*)>", r"\1", _type)

    raise _type


def parameter_default_value(cursor):
    if re.match(r".* \[\d*\]", cursor.type.spelling):
        return ""

    for child in cursor.get_children():
        if child.kind.name == 'TYPE_REF':
            continue
        tokens = []
        for token in child.get_tokens():
            tokens.append(token.spelling)
        if len(tokens) > 0:
            temp = " ".join(tokens)
            temp = temp.replace("ImVec2", "Vector2F")
            temp = temp.replace("=", "nullptr")
            if cursor.type.spelling == "const char *" and temp != "nullptr":
                temp = "u" + temp
            if re.match(r"ImGui.*", cursor.type.spelling):
                cast = to_altseed2_parameter_type(cursor.type.spelling)
                temp = f"({cast})" + temp

            return " = " + temp
    return ""


def make_function_declaration(cursor):
    if cursor.kind.name != "FUNCTION_DECL":
        return ""

    if cursor.spelling in exclude_funcs:
        return ""

    try:
        res = "    "

        _type = cursor.type.spelling.split('(')[0].strip()
        res += to_altseed2_return_type(_type)

        res += f" {cursor.spelling }("

        params = []
        for child in cursor.get_children():
            if child.kind.name != "PARM_DECL":
                continue

            param_type = to_altseed2_parameter_type(child.type.spelling)

            params.append(
                f"{param_type} {child.spelling}{parameter_default_value(child)}")

        res += ", ".join(params) + ");\n\n"

    except Exception as e:
        return f"    // {cursor.type.spelling} {cursor.spelling}\n\n"

    return res


def make_class_decl(cursor):
    if cursor.kind.name != "NAMESPACE":
        return ""

    code = """class Tool : public BaseObject {
private:
    static std::shared_ptr<Tool> instance_;
    std::shared_ptr<ImguiPlatform> platform_;

    //! to hold graphics device
    std::shared_ptr<Graphics> graphics_;

    ToolUsage toolUsageMode_ = ToolUsage::Overwrapped;

    std::mutex terminatingMtx_;

    void Dispose();

public:
    static std::shared_ptr<Tool>& GetInstance();

    static bool Initialize(std::shared_ptr<Graphics> graphics);

    static void Terminate();

    Tool(std::shared_ptr<Graphics> graphics);

    virtual ~Tool();

    void OnTerminating() override;

    ToolUsage GetToolUsage() const;

    void SetToolUsage(ToolUsage toolUsage);

    void NewFrame();

    void Render();

    bool AddFontFromFileTTF(const char16_t* path, float sizePixels, ToolGlyphRange ranges);

    bool ListBox(const char16_t* label, int32_t* current, const char16_t* items_separated_by_tabs, int32_t popup_max_height_in_items = -1);

    const char16_t* InputText(const char16_t* label, const char16_t* input, int32_t max_length, ToolInputTextFlags flags = ToolInputTextFlags::None);

    const char16_t* InputTextWithHint(
            const char16_t* label,
            const char16_t* hint,
            const char16_t* input,
            int32_t max_length,
            ToolInputTextFlags flags = ToolInputTextFlags::None);

    const char16_t* InputTextMultiline(
            const char16_t* label, const char16_t* input, int32_t max_length, Vector2F size, ToolInputTextFlags flags = ToolInputTextFlags::None);

    bool ColorEdit3(const char16_t* label, Color* color, ToolColorEditFlags flags = ToolColorEditFlags::None);

    bool ColorEdit4(const char16_t* label, Color* color, ToolColorEditFlags flags = ToolColorEditFlags::None);

    void Image(
            std::shared_ptr<TextureBase> texture,
            Vector2F size,
            Vector2F uv0 = Vector2F(0, 0),
            Vector2F uv1 = Vector2F(1, 1),
            Color tint_col = Color(255, 255, 255, 255),
            Color border_col = Color(0, 0, 0, 0));

    bool ImageButton(
            std::shared_ptr<TextureBase> texture,
            Vector2F size,
            Vector2F uv0 = Vector2F(0, 0),
            Vector2F uv1 = Vector2F(1, 1),
            int32_t frame_padding = -1,
            Color bg_col = Color(0, 0, 0, 0),
            Color tint_col = Color(255, 255, 255, 255));

    bool Combo(
            const char16_t* label, int32_t* current_item, const char16_t* items_separated_by_tabs, int32_t popup_max_height_in_items = -1);

    bool ColorButton(const char16_t* desc_id, Color* col, ToolColorEditFlags flags = ToolColorEditFlags::None, Vector2F size = Vector2F(0, 0));

    void PlotLines(
            const char16_t* label,
            std::shared_ptr<FloatArray> values,
            int32_t values_count,
            int32_t values_offset = 0,
            const char16_t* overlay_text = NULL,
            float scale_min = FLT_MAX,
            float scale_max = FLT_MAX,
            Vector2F graph_size = Vector2F(0, 0),
            int32_t stride = sizeof(float));

    void PlotHistogram(
            const char16_t* label,
            std::shared_ptr<FloatArray> values,
            int32_t values_count,
            int32_t values_offset = 0,
            const char16_t* overlay_text = NULL,
            float scale_min = FLT_MAX,
            float scale_max = FLT_MAX,
            Vector2F graph_size = Vector2F(0, 0),
            int32_t stride = sizeof(float));

    float GetTime();

    const char16_t* OpenDialog(const char16_t* filter, const char16_t* defaultPath);

    const char16_t* OpenDialogMultiple(const char16_t* filter, const char16_t* defaultPath);

    const char16_t* SaveDialog(const char16_t* filter, const char16_t* defaultPath);

    const char16_t* PickFolder(const char16_t* defaultPath);
	"""

    for child in cursor.get_children():
        if child.kind.name == 'FUNCTION_DECL':
            code += make_function_declaration(child)

    code += "};\n\n"

    return code


def make_enum_constant(cursor):
    if cursor.kind.name == 'ENUM_CONSTANT_DECL':
        name = re.sub(r"ImGui.*_", "", cursor.spelling)
        name = re.sub(r"Im.*_", "", name)
        if name == "":
            return ""

        res = f"    {name}"
        for child in cursor.get_children():
            tokens = []
            for token in child.get_tokens():
                name = re.sub(r"ImGui.*_", "", token.spelling)
                name = re.sub(r"Im.*_", "", name)
                tokens.append(name)
            if len(tokens) > 0:
                res += " = " + " ".join(tokens)
        return res + ",\n"


def make_enum_decl(cursor):
    if cursor.kind.name != "ENUM_DECL":
        return ""
    name = re.sub(r"(ImGui|Im)(.*)_", r"Tool\2", cursor.spelling)
    code = f"enum class {name} : int32_t " + "{\n"

    for child in cursor.get_children():
        code += make_enum_constant(child)
    code += "};\n\n"

    return code


def make_imgui_call_func(_type, call):
    if _type == "Vector2F":
        return f"    return toVector2F({call});\n"
    if _type == "Vector4F":
        return f"    return toVector4F({call});\n"
    if _type == "const char16_t *":
        return f"    returnStr = utf8_to_utf16({call});\n    return returnStr.c_str();\n"
    if _type == "void":
        return f"    {call};\n"

    return f"    return {call};\n"


def make_return_if_null(param, return_type):
    if return_type == "bool":
        return f"    RETURN_IF_NULL({param}, false);\n"
    if return_type == "void":
        return f"    RETURN_IF_NULL({param}, );\n"
    if return_type == "const char16_t *":
        return f"    RETURN_IF_NULL({param}, nullptr);\n"

    return ""


def make_function_imp(cursor):
    if cursor.kind.name != "FUNCTION_DECL":
        return ""

    if cursor.spelling in exclude_funcs:
        return ""
    
    try:
        res = ""

        _type = to_altseed2_return_type(
            cursor.type.spelling.split('(')[0].strip())
        res += _type

        res += f" Tool::{cursor.spelling }("

        params = []
        params_string = []
        for child in cursor.get_children():
            if child.kind.name != "PARM_DECL":
                continue

            param_type = to_altseed2_parameter_type(child.type.spelling)

            params_string.append(
                f"{param_type} {child.spelling}")
            params.append([child.spelling, param_type,
                           parameter_default_value(child)])

        res += ", ".join(params_string) + ") {\n"

        for param_name, param_type, default_value in params:
            if default_value == " = nullptr":
                continue

            if re.match(r"std::shared_ptr<.*>", param_type):
                res += make_return_if_null(param_name, _type)
            elif re.match(r".* \*", param_type):
                res += make_return_if_null(param_name, _type)

        res += make_imgui_call_func(
            _type, f"ImGui::{cursor.spelling}({', '.join(map(lambda k: to_imgui_parameter_type(k[0], k[1]), params))})")
        res += "}\n\n"

    except Exception as e:
        return f"// {cursor.type.spelling} {cursor.spelling}\n\n"

    return res


def make_class_imp(cursor):
    code = ""
    for child in cursor.get_children():
        if child.kind.name == 'FUNCTION_DECL':
            code += make_function_imp(child)
    return code


def make_function_cbg(cursor):
    if cursor.kind.name != "FUNCTION_DECL":
        return ""
    
    if cursor.spelling in exclude_funcs:
        return ""

    try:
        res = f"""
    with class_.add_func('{cursor.spelling}') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
"""

        _type = to_altseed2_return_type(
            cursor.type.spelling.split('(')[0].strip())

        params = []
        for child in cursor.get_children():
            if child.kind.name != "PARM_DECL":
                continue

            param_type = to_altseed2_parameter_type(child.type.spelling)

            params.append([child.spelling, param_type,
                           parameter_default_value(child)])

        for param_name, param_type, default_value in params:
            res += f"        with func_.add_arg({to_cbg_parameter_type(param_type)}, '{param_name}') as arg:\n"
            if param_type == "bool *" or param_type == "int32_t *" or param_type == "float *":
                res += "            arg.called_by = cbg.ArgCalledBy.Ref\n"
            else:
                res += "            pass\n"

        if _type != "void":
            res += f"""        func_.return_value.type_ = {to_cbg_parameter_type(_type)}
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '')
"""

        res += "\n"

    except Exception as e:
        return f"    # {cursor.type.spelling} {cursor.spelling}\n\n"

    return res


def make_class_cbg(cursor):
    code = """Tool = cbg.Class('Altseed2', 'Tool')
with Tool as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'imguiのツール処理を行うクラス')
    class_.is_Sealed = True

    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得します。')
        func.is_static = True
        func.is_public = False
        func.return_value.type_ = Tool

    with class_.add_property(ToolUsage, 'ToolUsage') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'ツールの使用方法を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True

    with class_.add_func('AddFontFromFileTTF') as func_:
        func_.brief = cbg.Description()
        func_.brief.add(
            'en', 'Load font from path. Packed files are not supported.')
        func_.brief.add('ja', 'パスからフォントを読み込みます。パックされたファイルは非対応です。')
        func_.add_arg(ctypes.c_wchar_p, 'path')
        func_.add_arg(float, 'sizePixels')
        func_.add_arg(ToolGlyphRange, 'ranges')
        func_.return_value.type_ = bool

    with class_.add_func('ListBox') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', 'リストボックスを生成します。')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '横に表示するラベルのテキスト')
            arg.nullable = False
        with func_.add_arg(int, 'current') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '選択中のアイテムのインデックス -1で選択無し')
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(ctypes.c_wchar_p, 'items') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'タブ文字を用いて分割したアイテム')
        with func_.add_arg(int, 'popupMaxHeightInItems') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '一度に表示されるアイテムの個数')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', 'アイテムがクリックされたらtrue，それ以外でfalse')

    with class_.add_func('InputText') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', 'テキストを入力するボックスを生成します。')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '横に表示するラベルのテキスト')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'input') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '入力するテキスト')
            arg.nullable = False
        with func_.add_arg(int, 'maxLength') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '処理するテキストの最大長')
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '適用する設定')
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '入力されたテキスト')

    with class_.add_func('InputTextWithHint') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', 'ヒント付きのテキスト入力ボックスを生成します。')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '横に表示するラベルのテキスト')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'hint') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インプットされている文字列長が0の時に表示されるヒント')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'input') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '入力するテキスト')
            arg.nullable = False
        with func_.add_arg(int, 'maxLength') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '処理するテキストの最大長')
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '適用する設定')
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '入力されたテキスト')

    with class_.add_func('InputTextMultiline') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '複数行のテキストが入力可能なボックスを生成します。')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '横に表示するラベルのテキスト')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'input') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '入力するテキスト')
            arg.nullable = False
        with func_.add_arg(int, 'maxLength') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '処理するテキストの最大長')
        with func_.add_arg(Vector2F, 'size') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'サイズ')
        with func_.add_arg(ToolInputTextFlags, 'flags') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '適用する設定')
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '入力されたテキスト')

    with class_.add_func('ColorEdit3') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '色を入力するツールを生成します。')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '横に表示するラベルのテキスト')
            arg.nullable = False
        with func_.add_arg(Color, 'color') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '扱う色')
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(ToolColorEditFlags, 'flags') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '適用する設定')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '入力が決定されたらtrue，それ以外でfalse')

    with class_.add_func('ColorEdit4') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '色を入力するツールを生成します。')
        with func_.add_arg(ctypes.c_wchar_p, 'label') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '横に表示するラベルのテキスト')
            arg.nullable = False
        with func_.add_arg(Color, 'color') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '扱う色')
            arg.called_by = cbg.ArgCalledBy.Ref
        with func_.add_arg(ToolColorEditFlags, 'flags') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '適用する設定')
        func_.return_value.type_ = bool
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '入力が決定されたらtrue，それ以外でfalse')

    with class_.add_func('Image') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '画像表示ボックスを生成します。')
        with func_.add_arg(TextureBase, 'texture') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '表示するテクスチャ')
        with func_.add_arg(Vector2F, 'size') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'サイズ')
        with func_.add_arg(Vector2F, 'uv0') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャのUV値(0~1)')
        with func_.add_arg(Vector2F, 'uv1') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャのUV値(0~1)')
        with func_.add_arg(Color, 'tintColor') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャの色')
        with func_.add_arg(Color, 'borderColor') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '縁の色')

    with class_.add_func('ImageButton') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', 'ボタンとして機能する画像表示ボックスを生成します。')
        with func_.add_arg(TextureBase, 'texture') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '表示するテクスチャ')
        with func_.add_arg(Vector2F, 'size') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'サイズ')
        with func_.add_arg(Vector2F, 'uv0') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャのUV値(0~1)')
        with func_.add_arg(Vector2F, 'uv1') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャのUV値(0~1)')
        with func_.add_arg(int, 'framePadding') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '縁の太さ')
        with func_.add_arg(Color, 'tintColor') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャの色')
        with func_.add_arg(Color, 'borderColor') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '縁の色')
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', 'クリックされたらtrue，それ以外でfalse')
        func_.return_value.type_ = bool

    with class_.add_func('PlotLines') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'values')
        func_.add_arg(int, 'valuesCount')
        func_.add_arg(int, 'valuesOffset')
        func_.add_arg(ctypes.c_wchar_p, 'overlayText')
        func_.add_arg(float, 'scaleMin')
        func_.add_arg(float, 'scaleMax')
        func_.add_arg(Vector2F, 'graphSize')
        func_.add_arg(int, 'stride')
        func_.is_public = False

    with class_.add_func('PlotHistogram') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.add_arg(ctypes.c_wchar_p, 'label')
        func_.add_arg(FloatArray, 'values')
        func_.add_arg(int, 'valuesCount')
        func_.add_arg(int, 'valuesOffset')
        func_.add_arg(ctypes.c_wchar_p, 'overlayText')
        func_.add_arg(float, 'scaleMin')
        func_.add_arg(float, 'scaleMax')
        func_.add_arg(Vector2F, 'graphSize')
        func_.add_arg(int, 'stride')
        func_.is_public = False

    with class_.add_func('GetTime') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '')
        func_.return_value.type_ = float

    with class_.add_func('OpenDialog') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '1つの開くファイルを選択するダイアログを開きます。')
        with func_.add_arg(ctypes.c_wchar_p, 'filter') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルの拡張子のフィルタ')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'defaultPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ファイルダイアログの初期位置のパス')
            arg.nullable = False
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '読み込むファイルのパス')

    with class_.add_func('OpenDialogMultiple') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '複数の開くファイルを選択するダイアログを開きます。')
        with func_.add_arg(ctypes.c_wchar_p, 'filter') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルの拡張子のフィルタ')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'defaultPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ファイルダイアログの初期位置のパス')
            arg.nullable = False
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '読み込むファイルのパス')

    with class_.add_func('SaveDialog') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', '保存するファイルを選択するダイアログを開きます。')
        with func_.add_arg(ctypes.c_wchar_p, 'filter') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '保存するファイルの拡張子のフィルタ')
            arg.nullable = False
        with func_.add_arg(ctypes.c_wchar_p, 'defaultPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ファイルダイアログの初期位置のパス')
            arg.nullable = False
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '保存するファイルのパス')

    with class_.add_func('PickFolder') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('en', '')
        func_.brief.add('ja', 'フォルダを選択するダイアログを開きます。')
        with func_.add_arg(ctypes.c_wchar_p, 'defaultPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ファイルダイアログの初期位置のパス')
            arg.nullable = False
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.type_ = ctypes.c_wchar_p
        func_.return_value.brief = cbg.Description()
        func_.return_value.brief.add('ja', '選択するフォルダのパス')

"""
    for child in cursor.get_children():
        if child.kind.name == 'FUNCTION_DECL':
            code += make_function_cbg(child)
    return code


def make_enum_constant_cbg(cursor, enum_dic):
    if cursor.kind.name == 'ENUM_CONSTANT_DECL':
        name = re.sub(r"ImGui.*_", "", cursor.spelling)
        name = re.sub(r"Im.*_", "", name)
        if name == "":
            return ""

        value = ""
        for child in cursor.get_children():
            tokens = []
            for token in child.get_tokens():
                token_str = re.sub(r"ImGui.*_", "", token.spelling)
                token_str = re.sub(r"Im.*_", "", token_str)
                if token_str in enum_dic:
                    token_str = f"({enum_dic[token_str]})"
                tokens.append(token_str)
            if len(tokens) > 0:
                value = " ".join(tokens)
        if value == "":
            value = str(len(enum_dic))
        enum_dic[name] = value
        res = f"    enum_.add('{name}', {value})\n"
        return res


def make_enum_cbg(cursor):
    if cursor.kind.name != "ENUM_DECL":
        return ""

    name = re.sub(r"(ImGui|Im)(.*)_", r"Tool\2", cursor.spelling)
    code = f"""{name} = cbg.Enum('Altseed2', '{name}')
with {name} as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.isFlag = True
"""
    enum_dic = {}
    for child in cursor.get_children():
        code += make_enum_constant_cbg(child, enum_dic)

    code += '\n'
    return code


def parse(cursor):
    global enum_decl, func_decl, func_imp, func_cbg, enum_cbg
    if cursor.kind.name == 'NAMESPACE':
        func_decl = make_class_decl(cursor)
        func_imp = make_class_imp(cursor)
        func_cbg = make_class_cbg(cursor)

    if cursor.kind.name == 'ENUM_DECL':
        enum_decl += make_enum_decl(cursor)
        enum_cbg += make_enum_cbg(cursor)

    for child in cursor.get_children():
        parse(child)


def make_tool_header():
    global enum_decl, func_decl
    with open("../core/src/Tool/Tool.h", mode="w", encoding="utf-8-sig", newline="\n") as f:

        code = """#pragma once
# include <cfloat>

# include "../Common/Array.h"
# include "../Graphics/Graphics.h"
# include "../Math/Vector2F.h"
# include "../Math/Vector4F.h"

class ImguiPlatform;

namespace Altseed2 {

class Graphics;

enum class ToolGlyphRange : int32_t {
    Default,
    // キリル文字
    Cyrillic,
    Japanese,
    ChineseFull,
    ChineseSimplifiedCommon,
    Korean,
    Thai,
};

enum class ToolUsage {
    Overwrapped,
    Main,
};
"""
        f.write(code)

        f.write(enum_decl)
        f.write(func_decl)

        f.write("}")


def make_tool_source():
    global func_imp
    with open("../core/src/Tool/AutoGenerateTool.cpp", mode="w", encoding="utf-8-sig", newline="\n") as f:

        code = """#include "Tool.h"

#include <nfd.h>

#include "../Common/StringHelper.h"
#include "Platform/ImGuiPlatform.h"
#ifdef _WIN32
#include "Platform/ImGuiPlatformDX12.h"
#elif __APPLE__
#include "Platform/ImGuiPlatformMetal.h"
#endif

#ifdef ENABLE_VULKAN
#include "Platform/ImGuiPlatformVulkan.h"
#endif

#include <imgui_impl_glfw.h>

#include "../Graphics/CommandList.h"
#include "../Graphics/Graphics.h"
#include "../IO/File.h"
#include "../IO/StaticFile.h"
#include "../Logger/Log.h"
#include "../System/SynchronizationContext.h"
#include "../Math/Vector4F.h"

namespace Altseed2 {

static std::u16string returnStr;

inline ImVec2 toImVec2(const Vector2F& v) { return ImVec2(v.X, v.Y); }

inline ImVec4 toImVec4(const Vector4F& v) { return ImVec4(v.X, v.Y, v.Z, v.W); }

inline ImVec4 toImVec4(const Color& v) { return ImVec4(v.R / 255.0f, v.G / 255.0f, v.B / 255.0f, v.A / 255.0f); }

inline Vector2F toVector2F(const ImVec2& v) { return Vector2F(v.x, v.y); }

inline Vector4F toVector4F(const ImVec4& v) { return Vector4F(v.x, v.y, v.z, v.w); }

inline Color toColor(const ImVec4& v) { return Color(v.x * 255, v.y * 255, v.z * 255, v.w * 255); }
"""

        f.write(code)

        f.write(func_imp)

        f.write("}")


def make_tool_cbg():
    global enum_cbg, func_cbg
    with open("bindings/tool.py", mode="w", encoding="utf-8") as f:

        code = """from . import CppBindingGenerator as cbg
import ctypes
from .math import Vector2F, Vector4F
from .common import *
from .graphics import *

ToolUsage = cbg.Enum('Altseed2', 'ToolUsage')
with ToolUsage as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'ツール機能の使用方法(描画位置)')

    with enum_.add('Overwrapped', 0) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '画面の上に表示')
    with enum_.add('Main', 1) as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '画面を表示せずにツールのみ表示')

ToolGlyphRange = cbg.Enum('Altseed2', 'ToolGlyphRange')
with ToolGlyphRange as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('en', 'Don\\'t bit operation')
    enum_.brief.add('ja', 'ツール機能を使ってフォントを読み込む際の範囲を指定します。ビット演算は行わないでください。')

    enum_.add('Default')

    with enum_.add('Cyrillic') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'キリル文字')

    with enum_.add('Japanese') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '日本語')
    with enum_.add('ChineseFull') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '繁体字中国語')
    with enum_.add('ChineseSimplifiedCommon') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '簡体字中国語')
    with enum_.add('Korean') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '韓国語')
    with enum_.add('Thai') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', 'タイ語')

"""

        f.write(code)

        f.write(enum_cbg)
        f.write(func_cbg)


parse(translation_unit.cursor)

make_tool_header()
make_tool_source()
make_tool_cbg()
