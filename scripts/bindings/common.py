from . import CppBindingGenerator as cbg

import ctypes

VoidPtr = cbg.Class('Altseed', 'VoidPtr')

SeekOrigin = cbg.Enum('Altseed', 'SeekOrigin')
with SeekOrigin as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', '')
    enum_.add('Begin')
    enum_.add('Current')
    enum_.add('End')

Int8Array = cbg.Class('Altseed', 'Int8Array')
with Int8Array as class_:
    with class_.add_func("CopyTo") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定したインスタンスにデータをコピーする')
        with func.add_arg(Int8Array, "array") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピー先のインスタンス')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーするデータ量')

ResourceType = cbg.Enum('Altseed', 'ResourceType')
with ResourceType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'リソースのタイプを表す')
    enum_.add('StaticFile')
    enum_.add('StreamFile')
    enum_.add('Texture2D')
    enum_.add('Font')
    enum_.add('MAX')

Resources = cbg.Class('Altseed', 'Resources')
with Resources as class_:
    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        func.is_static = True
        func.return_value.type_ = Resources
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    with class_.add_func('GetResourcesCount') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
        with func.add_arg(ResourceType, 'type') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '')
    class_.add_func('Clear')
    class_.add_func('Reload')


Vector2DI = cbg.Struct('Altseed', 'Vector2DI')
Vector2DF = cbg.Struct('Altseed', 'Vector2DF')
