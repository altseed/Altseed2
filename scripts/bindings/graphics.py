from . import CppBindingGenerator as cbg
import ctypes

from .common import *
from .io import *

DeviceType = cbg.Enum('LLGI', 'DeviceType')

Graphics = cbg.Class('Altseed', 'Graphics')
with Graphics as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'グラフィックの制御を行うクラス')
    # with class_.add_func('Initialize') as func:
    #     # func.add_arg(DeviceType, 'deviceType')
    #     func.return_type = bool
    #     func.is_static = True

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
        func.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('EndFrame') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')

    # with class_.add_func('Terminate') as func:
    #     func.is_static = True
    
    # with class_.add_func('CreateDameyTexture') as func:
    #     func.add_arg(int, 'b')
    #     func.return_type = LlgiTexture

Texture2D = cbg.Class('Altseed', 'Texture2D')
with Texture2D as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '2Dテクスチャのクラス')
    # with class_.add_constructor() as ctor:
    #     ctor.add_arg(Resources, 'resources')
    #     ctor.add_arg(Int8Array, 'data')
    #     ctor.add_arg(int, 'width')
    #     ctor.add_arg(int, 'height')

    with class_.add_func('Reload') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '再読み込みを行う')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '再読み込みに成功したらtrue，外枠false')
    with class_.add_func('GetSize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'テクスチャの大きさ(ピクセル)を取得する')
        func.return_value.type_ = Vector2DI
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'テクスチャの大きさ(ピクセル)')

    # with class_.add_func('Load') as func:
    #     func.add_arg(ctypes.c_wchar_p, 'path')
    #     func.return_type = Texture2D
    #     func.is_static = True