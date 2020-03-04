from . import CppBindingGenerator as cbg
import ctypes

from .common import *
from .math import *
from .io import *

DeviceType = cbg.Enum('LLGI', 'DeviceType')


CommandList = cbg.Class('Altseed', 'CommandList')
with CommandList as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'コマンドリストのクラス')
    with class_.add_func('SetRenderTargetWithScreen') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '？')
        func.is_public = True  # TODO：Engine側できちんと隠す

Shader = cbg.Class('Altseed', 'Shader', cbg.CacheMode.Cache)
with Shader as class_:
    class_.brief('ja', 'シェーダ')

BuiltinShaderType = cbg.Enum('Altseed', 'BuiltinShaderType')
with BuiltinShaderType as enum_:
    enum_.add('SpriteUnlitVS')
    enum_.add('SpriteUnlitPS')
    enum_.add('FontUnlitPS')

BuiltinShader = cbg.Class('Altseed', 'BuiltinShader')
with BuiltinShader as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'ビルド済みシェーダの取得を行うクラス')
    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'シェーダを取得します。')
        func.return_value.type_ = Shader
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'シェーダ')
        with func.add_arg(BuiltinShaderType, 'type') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'シェーダの種類')
        func.is_public = True

Graphics = cbg.Class('Altseed', 'Graphics')
with Graphics as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'グラフィックの制御を行うクラス')
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

Material = cbg.Class('Altseed', 'Material', cbg.CacheMode.Cache)
with Material as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'マテリアル')
    with class_.add_constructor() as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.is_public = True
    with class_.add_func('GetVector4F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = Vector4F
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.is_public = True
    with class_.add_func('SetVector4F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(Vector4F, 'value') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.is_public = True
    with class_.add_func('GetMatrix44F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = Matrix44F
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.is_public = True
    with class_.add_func('SetMatrix44F') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(Matrix44F, 'value') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.is_public = True
    with class_.add_func('GetTexture') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = Texture2D
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.is_public = True
    with class_.add_func('SetTexture') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'key') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(Texture2D, 'value') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.is_public = True
    with class_.add_property(Shader, 'Shader') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '')
        prop.has_getter = True
        prop.has_setter = True

Rendered = cbg.Class('Altseed', 'Rendered')
with Rendered as class_:
    class_.brief('ja', '描画されるオブジェクトの基本クラスを表します')
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
    with class_.add_property(Matrix44F, 'Transform') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '変換行列を取得または設定します。')
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

Renderer = cbg.Class('Altseed', 'Renderer')
with Renderer as class_:
    class_.is_public = True
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'レンダラのクラス')
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
        func.add_arg(RenderedSprite, 'sprite')
        func.is_public = True  # TODO：Engine側できちんと隠す
    with class_.add_func('Render') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'コマンドリストを描画します。')
        with func.add_arg(CommandList, 'commandList') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コマンドリスト')
        func.is_public = True  # TODO：Engine側できちんと隠す
    with class_.add_func('DrawPolygon') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ポリゴンを描画します')
        with func.add_arg(VertexArray, 'vertexBuffer') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '頂点バッファ')
        with func.add_arg(Int32Array, 'indexBuffer') as arg:
            arg.brief = cbg.Description()
        with func.add_arg(Texture2D, 'texture') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'テクスチャ')
        with func.add_arg(Material, 'material') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'マテリアル')

WritingDirection = cbg.Enum('Altseed', 'WritingDirection')
with WritingDirection as enum_:
    enum_.add('Vertical')
    enum_.add('Horizontal')

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
    with class_.add_property(Color, 'Color') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'フォントの色を取得する')
        prop.has_getter = True
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
        func.return_value.brief.add('ja', 'フォント')
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
        func.return_value.brief.add('ja', 'フォント')
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
