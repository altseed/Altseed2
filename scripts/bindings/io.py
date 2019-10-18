from . import CppBindingGenerator as cbg
import ctypes
import sys

from .common import *

BaseFileReader = cbg.Class('altseed', 'BaseFileReader')
with BaseFileReader as class_:
    with class_.add_constructor() as ctor:
        ctor.add_arg(ctypes.c_wchar_p, 'path')
    with class_.add_func('GetPosition') as func:
        func.return_type = int
    with class_.add_func('GetFullPath') as func:
        func.return_type = ctypes.c_wchar_p
    with class_.add_func('GetSize') as func:
        func.return_type = int
    with class_.add_func('ReadBytes') as func:
        func.add_arg(Bytes, 'buffer')
        func.add_arg(int, 'count')
    with class_.add_func('ReadUInt32') as func:
        func.return_type = int
    with class_.add_func('ReadUInt64') as func:
        func.return_type = int
    with class_.add_func('ReadAllBytes') as func:
        func.add_arg(Bytes, 'buffer')
    with class_.add_func('Seek') as func:
        func.add_arg(int, 'offset')
        func.add_arg(SeekOrigin, 'origin')
    with class_.add_func('GetIsInPackage') as func:
        func.return_type = bool

StaticFile = cbg.Class('altseed', 'StaticFile')
with StaticFile as class_:
    with class_.add_constructor() as ctor:
        ctor.add_arg(BaseFileReader, 'reader')
    with class_.add_func('GetBuffer') as func:
        func.return_type = Bytes
    with class_.add_func('GetPath') as func:
        func.return_type = ctypes.c_wchar_p
    with class_.add_func('GetData') as func:
        func.return_type = VoidPtr
    with class_.add_func('GetSize') as func:
        func.return_type = int
    with class_.add_func('GetIsInPackage') as func:
        func.return_type = bool
    with class_.add_func('Reload') as func:
        func.return_type = bool

StreamFile = cbg.Class('altseed', 'StreamFile')
with StreamFile as class_:
    with class_.add_constructor() as ctor:
        ctor.add_arg(BaseFileReader, 'reader')
    with class_.add_func('GetSize') as func:
        func.return_type = int
    with class_.add_func('GetCurrentPosition') as func:
        func.return_type = int
    with class_.add_func('Read') as func:
        func.add_arg(int, 'size')
        func.return_type = int
    with class_.add_func('GetTempBuffer') as func:
        func.return_type = Bytes
    with class_.add_func('GetTempBufferSize') as func:
        func.return_type = int
    with class_.add_func('GetIsInPackage') as func:
        func.return_type = bool
    with class_.add_func('Reload') as func:
        func.return_type = bool

File = cbg.Class('altseed', 'File')
with File as class_:
    with class_.add_func('Initialize') as func:
        func.add_arg(Resources, 'resources')
        func.return_type = bool
    class_.add_func('Terminate')
    with class_.add_func('GetInstance') as func:
        func.return_type = File
    with class_.add_func('CreateStaticFile') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = StaticFile
    with class_.add_func('CreateStreamFile') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = StreamFile
    with class_.add_func('AddRootDirectory') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = bool
    with class_.add_func('AddRootPackageWithPassword') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.add_arg(ctypes.c_wchar_p, 'password')
        func.return_type = bool
    with class_.add_func('AddRootPackage') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = bool
    class_.add_func('ClearRootDirectories')
    with class_.add_func('Exists') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = bool
    with class_.add_func('Pack') as func:
        func.add_arg(ctypes.c_wchar_p, 'srcPath')
        func.add_arg(ctypes.c_wchar_p, 'dstPath')
        func.return_type = bool
    with class_.add_func('Pack') as func:
        func.add_arg(ctypes.c_wchar_p, 'srcPath')
        func.add_arg(ctypes.c_wchar_p, 'dstPath')
        func.add_arg(ctypes.c_wchar_p, 'password')
        func.return_type = bool

ZipPtr = cbg.Class('altseed', 'ZipPtr')
ZipFilePtr = cbg.Class('altseed', 'ZipFilePtr')
ZipStatPtr = cbg.Class('altseed', 'ZipStatPtr')

PackFile = cbg.Class('altseed', 'PackFile')
with PackFile as class_:
    with class_.add_constructor() as ctor:
        ctor.add_arg(ZipPtr, 'zipPtr')
        ctor.add_arg(bool, 'isUsePassword')
    with class_.add_func('Load') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = ZipFilePtr
    with class_.add_func('Exists') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = bool
    with class_.add_func('GetZipStat') as func:
        func.add_arg(ctypes.c_wchar_p, 'path')
        func.return_type = ZipStatPtr
    with class_.add_func('GetIsUsePassword') as func:
        func.return_type = bool

FileRoot = cbg.Class('altseed', 'FileRoot')
with FileRoot as class_:
    with class_.add_constructor() as ctor:
        ctor.add_arg(ctypes.c_wchar_p, 'path')
    with class_.add_constructor() as ctor:
        ctor.add_arg(ctypes.c_wchar_p, 'path')
        ctor.add_arg(PackFile, 'packFile')
    with class_.add_func('GetPath') as func:
        func.return_type = ctypes.c_wchar_p
    with class_.add_func('GetPackFile') as func:
        func.return_type = PackFile
    with class_.add_func('IsPack') as func:
        func.return_type = bool

PackFileReader = cbg.Class('altseed', 'PackFileReader')
with PackFileReader as class_:
    with class_.add_constructor() as ctor:
        ctor.add_arg(ZipFilePtr, 'zipFile')
        ctor.add_arg(ctypes.c_wchar_p, 'path')
        ctor.add_arg(ZipStatPtr, 'stat')
    with class_.add_func('GetSize') as func:
        func.return_type = int
    with class_.add_func('ReadBytes') as func:
        func.add_arg(Bytes, 'buffer')
        func.add_arg(int, 'count')
    with class_.add_func('Seek') as func:
        func.add_arg(int, 'offset')
        func.add_arg(SeekOrigin, 'origin')
    with class_.add_func('GetIsInPackage') as func:
        func.return_type = bool