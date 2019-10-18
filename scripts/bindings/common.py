from . import CppBindingGenerator as cbg

VoidPtr = cbg.Class('altseed', 'VoidPtr')

SeekOrigin = cbg.Enum('altseed', 'SeekOrigin')
with SeekOrigin as enum_:
    enum_.add('Begin')
    enum_.add('Current')
    enum_.add('End')

Bytes = cbg.Class('altseed', 'ByteBuffer')

ResourceType = cbg.Enum('altseed', 'ResourceType')
with ResourceType as enum_:
    enum_.add('StaticFile')
    enum_.add('StreamFile')
    enum_.add('Texture2D')
    enum_.add('MAX')

ResourceContainer = cbg.Class('altseed', 'ResourceContainer')

Resources = cbg.Class('altseed', 'Resources')
with Resources as class_:
    with class_.add_func('Initialize') as func:
        func.is_static = True
        func.return_type = bool
    with class_.add_func('Terminate') as func:
        func.is_static = True
    with class_.add_func('GetInstance') as func:
        func.is_static = True
        func.return_type = Resources
    with class_.add_func('GetResourceContainer') as func:
        func.add_arg(ResourceType, 'type')
        func.return_type = ResourceContainer
    with class_.add_func('GetResourcesCount') as func:
        func.add_arg(ResourceType, 'type')
        func.return_type = int
    class_.add_func('Clear')
    class_.add_func('Reload')