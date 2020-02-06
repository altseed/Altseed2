from . import CppBindingGenerator as cbg
import ctypes
import sys

from .common import *

CoreOption = cbg.Struct('Altseed', 'CoreOption')
# with CoreOption as struct_:

Core = cbg.Class('Altseed', 'Core')
with Core as class_:
    with class_.add_func('Initialize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'title') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(int, 'width') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(int, 'height') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(CoreOption, 'option') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
        func.is_static = True

    with class_.add_func('DoEvent') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')

    with class_.add_func('Terminate') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.is_static = True

    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = Core
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
        func.is_static = True
