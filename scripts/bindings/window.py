from . import CppBindingGenerator as cbg
from .math import Vector2I
import ctypes
import sys

Window = cbg.Class('Altseed2', 'Window')
with Window as class_:
    class_.is_public = False
    class_.is_Sealed = True

    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得します。')
        func.return_value.type_ = Window
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
        func.is_public = False
        func.is_static = True

    with class_.add_property(ctypes.c_wchar_p, 'Title') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'ウィンドウに表示するタイトルを取得または設定します')
        prop.has_getter = True
        prop.has_setter = True
        prop.nullable = False

    with class_.add_property(Vector2I, "Size") as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'ウィンドウサイズを取得します')
        prop.has_getter = True
        prop.has_setter = True
        
