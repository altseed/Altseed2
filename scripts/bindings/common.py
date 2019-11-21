from . import CppBindingGenerator as cbg

import ctypes

VoidPtr = cbg.Class('altseed', 'VoidPtr')

SeekOrigin = cbg.Enum('altseed', 'SeekOrigin')
with SeekOrigin as enum_:
    enum_.add('Begin')
    enum_.add('Current')
    enum_.add('End')

Int8Array = cbg.Class('altseed', 'Int8Array')
with Int8Array as class_:
    with class_.add_func("CopyTo") as func:
        func.add_arg(Int8Array, "array") # TODO:c_char_p使いたい
        func.add_arg(int, "size")

ResourceType = cbg.Enum('altseed', 'ResourceType')
with ResourceType as enum_:
    enum_.add('StaticFile')
    enum_.add('StreamFile')
    enum_.add('Texture2D')
    enum_.add('MAX')

Resources = cbg.Class('altseed', 'Resources')
with Resources as class_:
    with class_.add_func('GetInstance') as func:
        func.is_static = True
        func.return_type = Resources
    with class_.add_func('GetResourcesCount') as func:
        func.add_arg(ResourceType, 'type')
        func.return_type = int
    class_.add_func('Clear')
    class_.add_func('Reload')


Vector2DI = cbg.Struct('altseed', 'Vector2DI')
