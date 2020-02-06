from . import CppBindingGenerator as cbg
import ctypes
import sys

from .common import *

StaticFile = cbg.Class('Altseed', 'StaticFile')
with StaticFile as class_:
    with class_.add_func('GetBuffer') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = Int8Array
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('GetPath') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = ctypes.c_wchar_p
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('GetSize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('GetIsInPackage') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('Reload') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')

StreamFile = cbg.Class('Altseed', 'StreamFile')
with StreamFile as class_:
    with class_.add_func('GetSize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('GetCurrentPosition') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('Read') as func:
        with func.add_arg(int, 'size') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('GetTempBuffer') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = Int8Array
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('GetTempBufferSize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('GetIsInPackage') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('Reload') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')

File = cbg.Class('Altseed', 'File')
with File as class_:
    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.is_static = True
        func.return_value.type_ = File
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('CreateStaticFile') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.return_value.type_ = StaticFile
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('CreateStreamFile') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.return_value.type_ = StreamFile
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('AddRootDirectory') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('AddRootPackageWithPassword') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'password') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('AddRootPackage') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('ClearRootDirectories') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
    with class_.add_func('Exists') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('Pack') as func:
        with func.add_arg(ctypes.c_wchar_p, 'srcPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'dstPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('PackWithPassword') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'srcPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'dstPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func.add_arg(ctypes.c_wchar_p, 'password') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
        