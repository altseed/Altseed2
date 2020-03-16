from . import CppBindingGenerator as cbg
import ctypes

from .common import *
from .math import *
from .io import *

DeviceType = cbg.Enum('LLGI', 'DeviceType')

Texture2D = cbg.Class('Altseed', 'Texture2D')
with Texture2D as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '2Dテクスチャのクラス')
    with class_.add_func('Load') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定したファイルからテクスチャを読み込みます。')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルのパス')
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
    with class_.add_property(Vector2I, 'Size') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'テクスチャの大きさ(ピクセル)を取得します。')
        prop.has_getter = True
    with class_.add_func('GetPath') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '読み込んだファイルのパスを取得します。')
        func.is_public = False
        func.return_value.type_ = ctypes.c_wchar_p
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込んだファイルのパス')

RenderTexture = cbg.Class('Altseed', 'RenderTexture')
with RenderTexture as class_:
    class_.base_class = Texture2D
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
    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'コードをコンパイルしてシェーダを生成する')
        with func.add_arg(ctypes.c_wchar_p, 'code') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コンパイルするコード')
        with func.add_arg(ctypes.c_wchar_p, 'name') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'シェーダの名前')
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
    with class_.add_property(ctypes.c_wchar_p, 'Code') as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', 'インスタンス生成に使用したコードを取得します')
        prop_.has_getter = True
        prop_.has_setter = False
    with class_.add_property(ctypes.c_wchar_p, 'Name') as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '名前を取得します')
        prop_.has_getter = True
        prop_.has_setter = False

BuiltinShaderType = cbg.Enum('Altseed', 'BuiltinShaderType')
with BuiltinShaderType as enum_:
    enum_.add('SpriteUnlitVS')
    enum_.add('SpriteUnlitPS')
    enum_.add('FontUnlitPS')

BuiltinShader = cbg.Class('Altseed', 'BuiltinShader')
with BuiltinShader as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '組み込みシェーダの取得を行うクラス')
    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'シェーダを取得します。')
        func.return_value.type_ = Shader
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '<paramref name="type"/>に対応した種類の組み込みの<see cref="Shader"/>のインスタンス')
        with func.add_arg(BuiltinShaderType, 'type') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'シェーダの種類')
        func.is_public = True


Material = cbg.Class('Altseed', 'Material', cbg.CacheMode.Cache)
with Material as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'マテリアル')
    with class_.add_constructor() as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '新しいインスタンスを生成する')
        func.is_public = True
    with class_.add_func('GetVector4F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した名前を持つ<see cref="Vector4F"/>のインスタンスを取得する')
        func.return_value.type_ = Vector4F
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '<paramref name="key"/>を名前として持つ<see cref="Vector4F"/>のインスタンス')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索する<see cref="Vector4F"/>のインスタンスの名前')
        func.is_public = True
    with class_.add_func('SetVector4F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した名前を持つ<see cref="Vector4F"/>の値を設定する')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索する<see cref="Vector4F"/>のインスタンスの名前')
        with func.add_arg(Vector4F, 'value') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '設定する<see cref="Vector4F"/>のインスタンスの値')
        func.is_public = True
    with class_.add_func('GetMatrix44F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した名前を持つ<see cref="Matrix44F"/>のインスタンスを取得する')
        func.return_value.type_ = Matrix44F
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '<paramref name="key"/>を名前として持つ<see cref="Matrix44F"/>のインスタンス')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索する<see cref="Matrix44F"/>のインスタンスの名前')
        func.is_public = True
    with class_.add_func('SetMatrix44F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した名前を持つ<see cref="Matrix44F"/>の値を設定する')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索する<see cref="Matrix44F"/>のインスタンスの名前')
        with func.add_arg(Matrix44F, 'value') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '設定する<see cref="Matrix44F"/>のインスタンスの値')
        func.is_public = True
    with class_.add_func('GetTexture') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した名前を持つ<see cref="Texture2D"/>のインスタンスを取得する')
        func.return_value.type_ = Texture2D
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '<paramref name="key"/>を名前として持つ<see cref="Texture2D"/>のインスタンス')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索する<see cref="Texture2D"/>のインスタンスの名前')
        func.is_public = True
    with class_.add_func('SetTexture') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した名前を持つ<see cref="Texture2D"/>の値を設定する')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '検索する<see cref="Texture2D"/>のインスタンスの名前')
        with func.add_arg(Texture2D, 'value') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '設定する<see cref="Texture2D"/>のインスタンスの値')
        func.is_public = True
    with class_.add_func('GetShader') as func:
        func.add_arg(ShaderStageType, 'shaderStage')
        func.return_value.type_ = Shader
    with class_.add_func('SetShader') as func:
        func.add_arg(Shader, 'shader')
    

CommandList = cbg.Class('Altseed', 'CommandList')
with CommandList as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'コマンドリストのクラス')
    with class_.add_func('SetRenderTargetWithScreen') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('ja', '？')
        func_.is_public = True  # TODO：Engine側できちんと隠す

    with class_.add_func('GetScreenTexture') as func_:
        func_.return_value.type_ = RenderTexture

    with class_.add_func('SetRenderTarget') as func_:
        func_.add_arg(RenderTexture, 'target')
        with func_.add_arg(RectI, 'viewport') as arg:
            arg.called_by = cbg.ArgCalledBy.Ref

    with class_.add_func('RenderToRenderTarget') as func_:
        func_.add_arg(Material, 'material')

Graphics = cbg.Class('Altseed', 'Graphics')
with Graphics as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'グラフィックの制御を行うクラス')
    class_.is_public = False
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
        func.is_public = True  # TODO：Engine側できちんと隠す
    with class_.add_func('EndFrame') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '描画を終了します。')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '正常に終了した場合は　true 。それ以外の場合は false。')
        func.is_public = True  # TODO：Engine側できちんと隠す
    with class_.add_property(CommandList, 'CommandList') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'コマンドリストを取得します。')
        prop.has_getter = True  # TODO：Engine側できちんと隠す
    with class_.add_property(BuiltinShader, 'BuiltinShader') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '組み込みのシェーダを取得します。')
        prop.has_getter = True
    with class_.add_func('DoEvents') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'イベントを処理します。')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '正常に処理した場合は　true 。それ以外の場合は false。')
        # func.is_public = False

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
    with class_.add_property(int, 'Size') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'フォントのサイズを取得する')
        prop.has_getter = True
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
    with class_.add_func('LoadDynamicFont') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '動的にフォントを生成します')
        func.return_value.type_ = Font
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '<paramref name="path"/>の指定するファイルから生成されたフォント')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むフォントのパス')
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
        func.return_value.brief.add('ja', '<paramref name="path"/>の指定するファイルから生成されたフォント')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むフォントのパス')
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
    with class_.add_func('GetPath') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '読み込んだファイルのパスを取得します。')
        func.is_public = False
        func.return_value.type_ = ctypes.c_wchar_p
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込んだファイルのパス')
    with class_.add_func('CalcTextureSize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'テキストを描画したときのサイズを取得します')
        func.return_value.type_ = Vector2I
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'サイズ')
        with func.add_arg(ctypes.c_wchar_p, 'text') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テキスト')
        with func.add_arg(WritingDirection, 'direction') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '文字列の方向')
        with func.add_arg(bool, 'isEnableKerning') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'カーニングの有無')
        func.is_public = True
    with class_.add_func('CreateImageFont') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'テクスチャ追加対応フォントを生成します')
        func.return_value.type_ = Font
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'テクスチャ追加対応フォント')
        with func.add_arg(Font, 'baseFont') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ベースとなるフォント')
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
    with class_.add_property(Matrix44F, 'Transform') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '変換行列を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True

RenderedSprite = cbg.Class('Altseed', 'RenderedSprite')
with RenderedSprite as class_:
    class_.base_class = Rendered
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'スプライトのクラス')
    class_.is_public = False
    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'スプライトを作成します。')
        func.return_value.type_ = RenderedSprite
        func.is_static = True
    with class_.add_property(Texture2D, 'Texture') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'テクスチャを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
    with class_.add_property(RectF, 'Src') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '描画範囲を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
    with class_.add_property(Material, 'Material') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'マテリアルを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True

RenderedText = cbg.Class('Altseed', 'RenderedText')
with RenderedText as class_:
    class_.base_class = Rendered
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'テキストのクラス')
    class_.is_public = False

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

    with class_.add_property(ctypes.c_wchar_p, 'Text') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'テキストを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True

    with class_.add_property(Font, 'Font') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'フォントを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True

    with class_.add_property(float, 'Weight') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '文字の太さを取得または設定します。(0 ~ 255)')
        prop.has_getter = True
        prop.has_setter = True

    with class_.add_property(Color, 'Color') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '色を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True

RenderedPolygon = cbg.Class('Altseed', 'RenderedPolygon')
with RenderedPolygon as class_:
    class_.base_class = Rendered
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'ポリゴンのクラス')
    class_.is_public = False
    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ポリゴンを作成します。')
        func.return_value.type_ = RenderedPolygon
        func.is_static = True
    with class_.add_func('SetVertexesByVector2F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '頂点情報を設定します。')
        with func.add_arg(Vector2FArray, 'vertexes') as arg:
            func.brief = cbg.Description()
            func.brief.add('ja', '頂点情報')
    with class_.add_property(VertexArray, 'Vertexes') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '頂点情報を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
    with class_.add_property(Texture2D, 'Texture') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'テクスチャを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
    with class_.add_property(RectF, 'Src') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '描画範囲を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
    with class_.add_property(Material, 'Material') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'マテリアルを取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True

RenderedCamera = cbg.Class('Altseed', 'RenderedCamera')
with RenderedCamera as class_:
    class_.base_class = Rendered
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'カメラのクラス')
    class_.is_public = False

Renderer = cbg.Class('Altseed', 'Renderer')
with Renderer as class_:
    class_.is_public = True
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'レンダラのクラス')
    class_.is_public = False
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
        func.is_public = True  # TODO：Engine側できちんと隠す
    with class_.add_func('DrawText') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'テキストを描画します。')
        with func.add_arg(RenderedText, 'text') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '描画する<see cref="RenderedText"/>のインスタンス')
        func.is_public = True  # TODO：Engine側できちんと隠す
    with class_.add_func('DrawPolygon') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ポリゴンを描画します。')
        with func.add_arg(RenderedPolygon, 'polygon') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '描画する<see cref="RenderedPolygon"/>のインスタンス')
        func.is_public = True  # TODO：Engine側できちんと隠す
    with class_.add_func('Render') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'コマンドリストを描画します。')
        with func.add_arg(CommandList, 'commandList') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '描画するコマンドリスト')
        func.is_public = True  # TODO：Engine側できちんと隠す