from . import CppBindingGenerator as cbg
import ctypes

from .common import *
from .math import *
from .io import *

DeviceType = cbg.Enum('LLGI', 'DeviceType')

TextureBase = cbg.Class('Altseed', 'TextureBase',
                        cbg.CacheMode.ThreadSafeCache)
with TextureBase as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'テクスチャのベースクラス')
    class_.SerializeType = cbg.SerializeType.Interface
    class_.CallBackType = cbg.CallBackType.Enable

    with class_.add_property(Vector2I, 'Size') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'テクスチャの大きさ(ピクセル)を取得します。')
        prop.has_getter = True
        prop.serialized = True

    with class_.add_func('Save') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'png画像として保存します')
        func.is_public = True
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '成功したか否か')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '保存先')
            arg.nullable = False


Texture2D = cbg.Class('Altseed', 'Texture2D', cbg.CacheMode.ThreadSafeCache)
with Texture2D as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'テクスチャのクラス')
    class_.base_class = TextureBase
    class_.SerializeType = cbg.SerializeType.Interface
    class_.CallBackType = cbg.CallBackType.Enable
    class_.is_Sealed = True

    with class_.add_property(ctypes.c_wchar_p, 'Path') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '読み込んだファイルのパスを取得します。')
        prop.is_public = False
        prop.has_getter = True
        prop.serialized = True
        prop.null_deserialized = False

    with class_.add_func('Load') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定したファイルからテクスチャを読み込みます。')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルのパス')
            arg.nullable = False
        func.return_value.type_ = Texture2D
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'テクスチャ')
        func.is_static = True

    with class_.add_func('Reload') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '再読み込みを行います。')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '再読み込みに成功したら true。それ以外の場合は false')


RenderTexture = cbg.Class('Altseed', 'RenderTexture')
with RenderTexture as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'ポストエフェクトやカメラにおける描画先のクラス')
    class_.base_class = TextureBase
    class_.SerializeType = cbg.SerializeType.Interface_Usebase
    class_.is_Sealed = True
    class_.CallBackType = cbg.CallBackType.Enable_Usebase

    with class_.add_func('Create') as func:
        func.add_arg(Vector2I, 'size')
        func.is_static = True
        func.return_value.type_ = RenderTexture


ShaderStageType = cbg.Enum('Altseed', 'ShaderStageType')
with ShaderStageType as enum_:
    enum_.add('Vertex')
    enum_.add('Pixel')


Shader = cbg.Class('Altseed', 'Shader', cbg.CacheMode.Cache)
with Shader as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'シェーダ')
    class_.SerializeType = cbg.SerializeType.Interface
    class_.is_Sealed = True

    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'コードをコンパイルしてシェーダを生成する')
        with func.add_arg(ctypes.c_wchar_p, 'name') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'シェーダの名前')
            arg.nullable = False
        with func.add_arg(ctypes.c_wchar_p, 'code') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コンパイルするコード')
            arg.nullable = False
        with func.add_arg(ShaderStageType, 'shaderStage') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.return_value.type_ = Shader
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'コンパイルの結果生成されたシェーダ')
        func.is_static = True

    with class_.add_property(ShaderStageType, 'StageType') as prop_:
        prop_.has_getter = True
        prop_.has_setter = False
        prop_.serialized = True

    with class_.add_property(ctypes.c_wchar_p, 'Code') as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', 'インスタンス生成に使用したコードを取得します')
        prop_.has_getter = True
        prop_.has_setter = False
        prop_.serialized = True

    with class_.add_property(ctypes.c_wchar_p, 'Name') as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '名前を取得します')
        prop_.has_getter = True
        prop_.has_setter = False
        prop_.serialized = True

BuiltinShaderType = cbg.Enum('Altseed', 'BuiltinShaderType')
with BuiltinShaderType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'ビルド済みシェーダの種類を表します')
    enum_.add('SpriteUnlitVS')
    enum_.add('SpriteUnlitPS')
    enum_.add('FontUnlitPS')

BuiltinShader = cbg.Class('Altseed', 'BuiltinShader')
with BuiltinShader as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '組み込みシェーダの取得を行うクラス')
    class_.is_Sealed = True

    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'シェーダを取得します。')
        func.return_value.type_ = Shader
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add(
            'ja', '<paramref name="type"/>に対応した種類の組み込みの<see cref="Shader"/>のインスタンス')
        with func.add_arg(BuiltinShaderType, 'type') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'シェーダの種類')
        func.is_public = True

    with class_.add_property(ctypes.c_wchar_p, 'DownsampleShader') as prop:
        prop.has_getter = True
        prop.has_setter = False
        prop.is_public = False

    with class_.add_property(ctypes.c_wchar_p, 'SepiaShader') as prop:
        prop.has_getter = True
        prop.has_setter = False
        prop.is_public = False

    with class_.add_property(ctypes.c_wchar_p, 'GrayScaleShader') as prop:
        prop.has_getter = True
        prop.has_setter = False
        prop.is_public = False

    with class_.add_property(ctypes.c_wchar_p, 'GaussianBlurShader') as prop:
        prop.has_getter = True
        prop.has_setter = False
        prop.is_public = False

    with class_.add_property(ctypes.c_wchar_p, 'LightBloomShader') as prop:
        prop.has_getter = True
        prop.has_setter = False
        prop.is_public = False


Material = cbg.Class('Altseed', 'Material', cbg.CacheMode.Cache)
with Material as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'マテリアル')
    class_.SerializeType = cbg.SerializeType.AttributeOnly
    class_.is_Sealed = True

    with class_.add_constructor() as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '新しいインスタンスを生成する')
        func.is_public = True

    with class_.add_func('GetVector4F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した名前を持つ<see cref="Vector4F"/>のインスタンスを取得する')
        func.return_value.type_ = Vector4F
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add(
            'ja', '<paramref name="key"/>を名前として持つ<see cref="Vector4F"/>のインスタンス')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索する<see cref="Vector4F"/>のインスタンスの名前')
            arg.nullable = False
        func.is_public = True

    with class_.add_func('SetVector4F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した名前を持つ<see cref="Vector4F"/>の値を設定する')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索する<see cref="Vector4F"/>のインスタンスの名前')
            arg.nullable = False
        with func.add_arg(Vector4F, 'value') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '設定する<see cref="Vector4F"/>のインスタンスの値')
        func.is_public = True

    with class_.add_func('GetMatrix44F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した名前を持つ<see cref="Matrix44F"/>のインスタンスを取得する')
        func.return_value.type_ = Matrix44F
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add(
            'ja', '<paramref name="key"/>を名前として持つ<see cref="Matrix44F"/>のインスタンス')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索する<see cref="Matrix44F"/>のインスタンスの名前')
            arg.nullable = False
        func.is_public = True

    with class_.add_func('SetMatrix44F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した名前を持つ<see cref="Matrix44F"/>の値を設定する')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索する<see cref="Matrix44F"/>のインスタンスの名前')
            arg.nullable = False
        with func.add_arg(Matrix44F, 'value') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '設定する<see cref="Matrix44F"/>のインスタンスの値')
        func.is_public = True

    with class_.add_func('GetTexture') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した名前を持つ<see cref="TextureBase"/>のインスタンスを取得する')
        func.return_value.type_ = TextureBase
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add(
            'ja', '<paramref name="key"/>を名前として持つ<see cref="TextureBase"/>のインスタンス')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索する<see cref="TextureBase"/>のインスタンスの名前')
            arg.nullable = False
        func.is_public = True

    with class_.add_func('SetTexture') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した名前を持つ<see cref="TextureBase"/>の値を設定する')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索する<see cref="TextureBase"/>のインスタンスの名前')
            arg.nullable = False
        with func.add_arg(TextureBase, 'value') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '設定する<see cref="TextureBase"/>のインスタンスの値')
        func.is_public = True

    with class_.add_func('GetShader') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した種類のシェーダを取得する')
        with func.add_arg(ShaderStageType, 'shaderStage') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索するシェーダのタイプ')
        func.return_value.type_ = Shader
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add(
            'ja', '<paramref name="shaderStage"/>に一致するタイプのシェーダ')

    with class_.add_func('SetShader') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'シェーダを設定する')
        with func.add_arg(Shader, 'shader') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '設定するシェーダ')


RenderPassParameter = cbg.Struct(
    'Altseed', 'RenderPassParameter_C', 'RenderPassParameter')

CommandList = cbg.Class('Altseed', 'CommandList')
with CommandList as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'コマンドリストのクラス')
    class_.is_Sealed = True

    with class_.add_func('GetScreenTexture') as func_:
        func_.return_value.type_ = RenderTexture

    with class_.add_func('SetRenderTarget') as func_:
        func_.add_arg(RenderTexture, 'target')
        with func_.add_arg(RenderPassParameter, 'renderPassParameter') as arg:
            arg.brief = cbg.Description()

    with class_.add_func('RenderToRenderTexture') as func_:
        func_.add_arg(Material, 'material')
        func_.add_arg(RenderTexture, 'target')
        func_.add_arg(RenderPassParameter, 'renderPassparameter')

    with class_.add_func('RenderToRenderTarget') as func_:
        func_.add_arg(Material, 'material')

    with class_.add_func('CopyTexture') as func_:
        with func_.add_arg(RenderTexture, 'src') as arg_:
            arg_.nullable = False
        with func_.add_arg(RenderTexture, 'dst') as arg_:
            arg_.nullable = False


Graphics = cbg.Class('Altseed', 'Graphics')
with Graphics as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'グラフィックの制御を行うクラス')
    class_.is_Sealed = True

    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得します。')
        func.return_value.type_ = Graphics
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
        func.is_public = False
        func.is_static = True

    with class_.add_func('BeginFrame') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '描画を開始します。')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '正常に開始した場合は　true 。それ以外の場合は false。')
        func.add_arg(RenderPassParameter, 'renderPassParmeter')
        func.is_public = False

    with class_.add_func('EndFrame') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '描画を終了します。')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '正常に終了した場合は　true 。それ以外の場合は false。')
        func.is_public = False

    with class_.add_property(CommandList, 'CommandList') as prop:
        prop.has_getter = True
        prop.has_setter = False

    with class_.add_property(BuiltinShader, 'BuiltinShader') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '組み込みのシェーダを取得します。')
        prop.has_getter = True
        prop.is_public = False

    with class_.add_func('DoEvents') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'イベントを処理します。')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '正常に処理した場合は　true 。それ以外の場合は false。')
        func.is_public = False


WritingDirection = cbg.Enum('Altseed', 'WritingDirection')
with WritingDirection as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'テキストの描画方向')
    with enum_.add('Vertical') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '縦書き')
    with enum_.add('Horizontal') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '横書き')


Glyph = cbg.Class('Altseed', 'Glyph', cbg.CacheMode.ThreadSafeCache)
with Glyph as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '文字情報')
    class_.is_Sealed = True

    with class_.add_property(Vector2I, 'TextureSize') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '文字テクスチャのサイズを取得する')
        prop.has_getter = True

    with class_.add_property(int, 'TextureIndex') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '文字テクスチャのインデックスを取得する')
        prop.has_getter = True

    with class_.add_property(Vector2I, 'Position') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '文字の座標を取得する')
        prop.has_getter = True

    with class_.add_property(Vector2I, 'Size') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '文字のサイズを取得する')
        prop.has_getter = True

    with class_.add_property(Vector2I, 'Offset') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '文字のオフセットを取得する')
        prop.has_getter = True

    with class_.add_property(int, 'GlyphWidth') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '文字の幅を取得する')
        prop.has_getter = True


Font = cbg.Class('Altseed', 'Font', cbg.CacheMode.ThreadSafeCache)
with Font as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'フォント')
    class_.SerializeType = cbg.SerializeType.Interface
    class_.CallBackType = cbg.CallBackType.Enable
    class_.is_Sealed = True

    with class_.add_property(int, 'Size') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'フォントのサイズを取得する')
        prop.has_getter = True
        prop.serialized = True

    with class_.add_property(int, 'Ascent') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'フォントのベースラインからトップラインまでの距離を取得する')
        prop.has_getter = True

    with class_.add_property(int, 'Descent') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'フォントのベースラインからボトムラインまでの距離を取得する')
        prop.has_getter = True

    with class_.add_property(int, 'LineGap') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'フォントの行間の距離を取得する')
        prop.has_getter = True

    with class_.add_property(bool, 'IsStaticFont') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'StaticFontか否か')
        prop.has_getter = True
        prop.serialized = True

    with class_.add_func('LoadDynamicFont') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '動的にフォントを生成します')
        func.return_value.type_ = Font
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add(
            'ja', '<paramref name="path"/>の指定するファイルから生成されたフォント')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むフォントのパス')
            arg.nullable = False
        with func.add_arg(int, 'size') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'フォントのサイズ')
        func.is_public = True
        func.is_static = True

    with class_.add_func('LoadStaticFont') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '静的にフォントを生成します')
        func.return_value.type_ = Font
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add(
            'ja', '<paramref name="path"/>の指定するファイルから生成されたフォント')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むフォントのパス')
            arg.nullable = False
        func.is_public = True
        func.is_static = True

    with class_.add_func('GenerateFontFile') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'a2fフォントを生成します')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '生成できたか否か')
        with func.add_arg(ctypes.c_wchar_p, 'dynamicFontPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むtruetypeフォントのパス')
            arg.nullable = False
        with func.add_arg(ctypes.c_wchar_p, 'staticFontPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '生成するa2fフォントのパス')
            arg.nullable = False
        with func.add_arg(int, 'size') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'フォントのサイズ')
        with func.add_arg(ctypes.c_wchar_p, 'characters') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'フォント化させる文字列')
        func.is_public = True
        func.is_static = True

    with class_.add_func('GetGlyph') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '文字情報を取得する')
        func.return_value.type_ = Glyph
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '文字')
        with func.add_arg(int, 'character') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '文字')
        func.is_public = True

    with class_.add_func('GetFontTexture') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '文字列テクスチャを得る')
        func.return_value.type_ = Texture2D
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'テクスチャ')
        with func.add_arg(int, 'index') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        func.is_public = True

    with class_.add_func('GetKerning') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'カーニングを得る')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'カーニング')
        with func.add_arg(int, 'c1') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '文字1')
        with func.add_arg(int, 'c2') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '文字2')
        func.is_public = True

    with class_.add_property(ctypes.c_wchar_p, 'Path') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '読み込んだファイルのパスを取得します。')
        prop.has_getter = True
        prop.serialized = True
        prop.null_deserialized = False

    with class_.add_func('CreateImageFont') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'テクスチャ追加対応フォントを生成します')
        func.return_value.type_ = Font
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'テクスチャ追加対応フォント')
        with func.add_arg(Font, 'baseFont') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ベースとなるフォント')
            arg.nullable = False
        func.is_public = True
        func.is_static = True

    with class_.add_func('AddImageGlyph') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'テクスチャ文字を追加する')
        with func.add_arg(int, 'character') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '文字')
        with func.add_arg(Texture2D, 'texture') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャ')
        func.is_public = False

    with class_.add_func('GetImageGlyph') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'テクスチャ文字を取得する')
        func.return_value.type_ = Texture2D
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'テクスチャ文字')
        with func.add_arg(int, 'character') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '文字')
        func.is_public = True


Rendered = cbg.Class('Altseed', 'Rendered')
with Rendered as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '描画されるオブジェクトの基本クラスを表します')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface

    with class_.add_property(Matrix44F, 'Transform') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '変換行列を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(int, 'Id') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'BaseObjectのIdを取得します')
        prop.has_getter = True

RenderedSprite = cbg.Class('Altseed', 'RenderedSprite')
with RenderedSprite as class_:
    class_.base_class = Rendered
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'スプライトのクラス')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface_Usebase
    class_.is_Sealed = True

    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'スプライトを作成します。')
        func.return_value.type_ = RenderedSprite
        func.is_static = True

    with class_.add_property(TextureBase, 'Texture') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'テクスチャを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(RectF, 'Src') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '描画範囲を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(Material, 'Material') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'マテリアルを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(Color, 'Color') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '色を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

RenderedText = cbg.Class('Altseed', 'RenderedText')
with RenderedText as class_:
    class_.base_class = Rendered
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'テキストのクラス')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface_Usebase
    class_.is_Sealed = True

    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'テキストを作成します。')
        func.return_value.type_ = RenderedText
        func.is_static = True

    with class_.add_property(Material, 'Material') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'マテリアルを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(ctypes.c_wchar_p, 'Text') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'テキストを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(Font, 'Font') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'フォントを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(float, 'Weight') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '文字の太さを取得または設定します。(0 ~ 255)')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(bool, 'IsEnableKerning') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'カーニングの有無を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(WritingDirection, 'WritingDirection') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '行の方向を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(float, 'CharacterSpace') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '字間をピクセル単位で取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True
    
    with class_.add_property(float, 'LineGap') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '行間をピクセル単位で取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(Vector2F, 'TextureSize') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'テキストを描画したときのサイズを取得します')
        prop.has_getter = True

    with class_.add_property(Color, 'Color') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '色を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

RenderedPolygon = cbg.Class('Altseed', 'RenderedPolygon')
with RenderedPolygon as class_:
    class_.base_class = Rendered
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'ポリゴンのクラス')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface_Usebase
    class_.is_Sealed = True

    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ポリゴンを作成します。')
        func.return_value.type_ = RenderedPolygon
        func.is_static = True

    with class_.add_func('CreateVertexesByVector2F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '頂点情報を設定します。')
        with func.add_arg(Vector2FArray, 'vertexes') as arg:
            func.brief = cbg.Description()
            func.brief.add('ja', '頂点情報')

    with class_.add_func('OverwriteVertexesColor') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '頂点の色情報を上書きします。')
        with func.add_arg(Color, 'color') as arg:
            func.brief = cbg.Description()
            func.brief.add('ja', '頂点情報')

    with class_.add_property(VertexArray, 'Vertexes') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '頂点情報を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(TextureBase, 'Texture') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'テクスチャを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(RectF, 'Src') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '描画範囲を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(Material, 'Material') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'マテリアルを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

RenderedCamera = cbg.Class('Altseed', 'RenderedCamera')
with RenderedCamera as class_:
    class_.base_class = Rendered
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'カメラのクラス')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface_Usebase
    class_.is_Sealed = True

    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'RenderedCameraを作成します。')
        func.return_value.type_ = RenderedCamera
        func.is_static = True

    with class_.add_property(Vector2F, 'CenterOffset') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'CenterOffsetを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

    with class_.add_property(RenderTexture, 'TargetTexture') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'TargetTextureを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True
    
    with class_.add_property(RenderPassParameter,'RenderPassParameter') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'RenderPassParameterを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
        prop.serialized = True

Renderer = cbg.Class('Altseed', 'Renderer')
with Renderer as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'レンダラのクラス')
    class_.is_public = False
    class_.is_Sealed = True

    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得します。')
        func.return_value.type_ = Renderer
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
        func.is_public = False
        func.is_static = True

    with class_.add_func('DrawSprite') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'スプライトを描画します。')
        with func.add_arg(RenderedSprite, 'sprite') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '描画する<see cref="RenderedSprite"/>のインスタンス')
        func.is_public = False

    with class_.add_func('DrawText') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'テキストを描画します。')
        with func.add_arg(RenderedText, 'text') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '描画する<see cref="RenderedText"/>のインスタンス')
        func.is_public = False

    with class_.add_func('DrawPolygon') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ポリゴンを描画します。')
        with func.add_arg(RenderedPolygon, 'polygon') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '描画する<see cref="RenderedPolygon"/>のインスタンス')
        func.is_public = False

    with class_.add_func('Render') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'コマンドリストを描画します。')

    with class_.add_func('SetCamera') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '使用するカメラを設定します。')
        with func.add_arg(RenderedCamera, 'camera') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '描画するカメラ')
        func.is_public = False

    with class_.add_func('ResetCamera') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '使用するカメラの設定をリセットします。')

CullingSystem = cbg.Class('Altseed', 'CullingSystem')
with CullingSystem as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'カリングのクラス')
    class_.is_public = False
    class_.is_Sealed = True

    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得します。')
        func.return_value.type_ = CullingSystem
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
        func.is_public = False
        func.is_static = True

    with class_.add_func('UpdateAABB') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'RenderedのAABBを更新します')
        func.is_public = False

    with class_.add_property(int, 'DrawingRenderedCount') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '描画されているRenderedの個数を取得する')
        prop.has_getter = True

    with class_.add_property(Int32Array, 'DrawingRenderedIds') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '描画されているRenderedのIdの配列を取得する')
        prop.has_getter = True
