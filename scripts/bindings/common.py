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
    class_.brief = cbg.Description()
    class_.brief.add('ja', '8ビット整数の配列のクラス')
    with class_.add_func("CopyTo") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定したインスタンスにデータをコピーする')
        with func.add_arg(Int8Array, "array") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピー先のインスタンス')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーするデータ量')
    with class_.add_property(int, "Count") as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '格納されている要素の数を取得します。')
        prop_.has_getter = True
    # with class_.add_func("GetData") as func:
    #     func.return_value.type_ = VoidPtr
    # with class_.add_func("SetData") as func:
    #     with func.add_arg(VoidPtr, "ptr") as arg:
    #         arg.brief = cbg.Description()
    #         arg.brief.add('ja', 'コピーするデータの先頭のポインタ')
    #     with func.add_arg(int, "size") as arg:
    #         arg.brief = cbg.Description()
    #         arg.brief.add('ja', 'コピーするデータ量')
    #     func.return_value.type_ = VoidPtr

Int32Array = cbg.Class('Altseed', 'Int32Array')
with Int32Array as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '32ビット整数の配列のクラス')
    with class_.add_func("CopyTo") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定したインスタンスにデータをコピーする')
        with func.add_arg(Int32Array, "array") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピー先のインスタンス')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーするデータ量')
    with class_.add_property(int, "Count") as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '格納されている要素の数を取得します。')
        prop_.has_getter = True
    # with class_.add_func("GetData") as func:
    #     func.return_value.type_ = VoidPtr
    # with class_.add_func("SetData") as func:
    #     with func.add_arg(VoidPtr, "ptr") as arg:
    #         arg.brief = cbg.Description()
    #         arg.brief.add('ja', 'コピーするデータの先頭のポインタ')
    #     with func.add_arg(int, "size")as arg:
    #         arg.brief = cbg.Description()
    #         arg.brief.add('ja', 'コピーするデータ量')
    #     func.return_value.type_ = VoidPtr

# BatchVertexArray = cbg.Class('Altseed', 'BatchVertexArray')
# with BatchVertexArray as class_:
#     class_.brief = cbg.Description()
#     class_.brief.add('ja', 'BatchVertexの配列のクラス')
#     with class_.add_func("CopyTo") as func:
#         func.brief = cbg.Description()
#         func.brief.add('ja', '指定したインスタンスにデータをコピーする')
#         with func.add_arg(BatchVertexArray, "array") as arg:
#             arg.brief = cbg.Description()
#             arg.brief.add('ja', 'コピー先のインスタンス')
#         with func.add_arg(int, "size") as arg:
#             arg.brief = cbg.Description()
#             arg.brief.add('ja', 'コピーするデータ量')

ResourceType = cbg.Enum('Altseed', 'ResourceType')
with ResourceType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'リソースの種類を表す')
    enum_.add('StaticFile')
    enum_.add('StreamFile')
    enum_.add('Texture2D')
    enum_.add('Font')
    enum_.add('Sound')
    enum_.add('MAX')

Resources = cbg.Class('Altseed', 'Resources')
with Resources as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'リソースのクラス')
    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得する')
        func.is_public = False
        func.is_static = True
        func.return_value.type_ = Resources
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
    with class_.add_func('GetResourcesCount') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した種類のリソースの個数を返す')
        with func.add_arg(ResourceType, 'type') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '個数を検索するリソースの種類')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '指定した種類のリソースの個数')
    with class_.add_func('Clear') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '登録されたリソースをすべて削除する')
    with class_.add_func('Reload') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'リソースの再読み込みを行う')
