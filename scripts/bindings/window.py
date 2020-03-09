from . import CppBindingGenerator as cbg
import ctypes
import sys

Window = cbg.Class('Altseed', 'Window')
with Window as class_:
    class_.is_public=False

    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得します。')
        func.return_value.type_ = Window
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
        func.is_public = False
        func.is_static = True

    with class_.add_property(ctypes.c_wchar_p, 'Title') as prop:
        prop.has_getter = True
        prop.has_setter = True
