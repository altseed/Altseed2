from . import CppBindingGenerator as cbg
import ctypes

from .common import *
from .math import *
from .io import *

DeviceType = cbg.Enum('LLGI', 'DeviceType')

# BatchVertex = cbg.Struct('Altseed', 'BatchVertex')
Color = cbg.Struct('Altseed', 'Color')

CommandList = cbg.Class('Altseed', 'CommandList')
with CommandList as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'コマンドリストのクラス')
    with class_.add_func('SetRenderTargetWithScreen') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '？')
        func.is_public = True  # TODO：Engine側できちんと隠す

Graphics = cbg.Class('Altseed', 'Graphics')
with Graphics as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'グラフィックの制御を行うクラス')
    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得する')
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
        prop.brief.add('ja', 'コマンドリストを取得する')
        prop.has_getter = True  # TODO：Engine側できちんと隠す
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
        func.brief.add('ja', '再読み込みを行う')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '再読み込みに成功したら true。それ以外の場合は false')
    with class_.add_property(Vector2I, 'Size') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'テクスチャの大きさ(ピクセル)を取得する')
        prop.has_getter = True

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
        prop.brief.add('ja', 'テクスチャを取得または設定する')
        prop.has_getter = True
        prop.has_setter = True
    with class_.add_property(RectF, 'Src') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '描画範囲を取得または設定する')
        prop.has_getter = True
        prop.has_setter = True
    with class_.add_property(Matrix44F, 'Transform') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '変換行列を取得または設定します。')
        prop.has_getter = True
        prop.has_setter = True
    # with class_.add_property(Material, 'Material') as prop:
    #     prop.brief = cbg.Description()
    #     prop.brief.add('ja', 'マテリアルを取得または設定する')
    #     prop.has_getter = True
    #     prop.has_setter = True

RenderedCamera = cbg.Class('Altseed', 'RenderedCamera')
with RenderedCamera as class_:
    class_.base_class = Rendered
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'カメラのクラス')

Renderer = cbg.Class('Altseed', 'Renderer')
with Renderer as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'レンダラのクラス')
    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得する')
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

    # with class_.add_func('DrawPolygon') as func:
    #     func.brief = cbg.Description()
    #     func.brief.add('ja', 'ポリゴンを描画します')
    #     with func.add_arg(BatchVertexArray, 'vertexBuffer') as arg:
    #         arg.brief = cbg.Description()
    #         arg.brief.add('ja', '頂点バッファ')
    #     with func.add_arg(Int32Array, 'indexBuffer') as arg:
    #         arg.brief = cbg.Description()
    #         arg.brief.add('ja', 'インデックスバッファ')
    #     with func.add_arg(int, 'vertexBufferCount') as arg:
    #         arg.brief = cbg.Description()
    #         arg.brief.add('ja', '頂点バッファの要素数')
    #     with func.add_arg(int, 'indexBufferCount') as arg:
    #         arg.brief = cbg.Description()
    #         arg.brief.add('ja', '頂点バッファの要素数')
    #     with func.add_arg(Texture2D, 'texture') as arg:
    #         arg.brief = cbg.Description()
    #         arg.brief.add('ja', 'テクスチャ')
    #     func.is_public = True # TODO：Engine側できちんと隠す
