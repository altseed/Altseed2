from . import CppBindingGenerator as cbg
import ctypes
import sys

from .common import *

CoreOption = cbg.Struct('Altseed', 'CoreOption')
# with CoreOption as struct_:

Core = cbg.Class('Altseed', 'Core')
with Core as class_:
    with class_.add_func('Initialize') as func:
        func.add_arg(ctypes.c_wchar_p, 'title')
        func.add_arg(int, 'width')
        func.add_arg(int, 'height')
        func.add_arg(CoreOption, 'option')
        func.return_value.type_ = bool
        func.is_static = True

    with class_.add_func('DoEvent') as func:
        func.return_value.type_ = bool

    with class_.add_func('Terminate') as func:
        func.is_static = True

    with class_.add_func('GetInstance') as func:
        func.return_value.type_ = Core
        func.is_static = True
