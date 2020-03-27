from . import CppBindingGenerator as cbg
from .math import *

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
    class_.brief.add('ja', '8ビット整数の配列のクラスを表します。')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface
    class_.is_Sealed = True

    with class_.add_func("Clear") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データをクリアします。')

    with class_.add_property(int, "Count") as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '格納されている要素の数を取得します。')
        prop_.has_getter = True
        prop_.serialized = True

    with class_.add_func('Resize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'サイズを変更します。')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')

    with class_.add_func("GetData") as func:
        func.return_value.type_ = ctypes.c_void_p

    with class_.add_func("Assign") as func:
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーするデータの先頭のポインタ')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーする要素の個数')

    with class_.add_func('CopyTo') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データを指定したポインタにコピーします。')
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ポインタ')

    with class_.add_func('GetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        func.return_value.type_ = ctypes.c_byte
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')

    with class_.add_func('SetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        with func.add_arg(ctypes.c_byte, "value") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '値')

    with class_.add_func("Create") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを作成します。')
        func.return_value.type_ = class_
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_static = True


Int32Array = cbg.Class('Altseed', 'Int32Array')
with Int32Array as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '32ビット整数の配列のクラスを表します。')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface
    class_.is_Sealed = True

    with class_.add_func("Clear") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データをクリアします。')

    with class_.add_property(int, "Count") as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '格納されている要素の数を取得します。')
        prop_.has_getter = True
        prop_.serialized = True

    with class_.add_func('Resize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'サイズを変更します。')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')

    with class_.add_func("GetData") as func:
        func.return_value.type_ = ctypes.c_void_p

    with class_.add_func("Assign") as func:
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーするデータの先頭のポインタ')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーする要素の個数')

    with class_.add_func('CopyTo') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データを指定したポインタにコピーします。')
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ポインタ')

    with class_.add_func('GetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        func.return_value.type_ = int
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')

    with class_.add_func('SetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        with func.add_arg(int, "value") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '値')

    with class_.add_func("Create") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを作成します。')
        func.return_value.type_ = class_
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_static = True

VertexArray = cbg.Class('Altseed', 'VertexArray')
with VertexArray as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '頂点データの配列のクラスを表します。')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface
    class_.is_Sealed = True

    with class_.add_func("Clear") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データをクリアします。')

    with class_.add_property(int, "Count") as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '格納されている要素の数を取得します。')
        prop_.has_getter = True
        prop_.serialized = True

    with class_.add_func('Resize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'サイズを変更します。')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')

    with class_.add_func("GetData") as func:
        func.return_value.type_ = ctypes.c_void_p

    with class_.add_func("Assign") as func:
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーするデータの先頭のポインタ')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーする要素の個数')

    with class_.add_func('CopyTo') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データを指定したポインタにコピーします。')
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ポインタ')

    with class_.add_func('GetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        func.return_value.type_ = BatchVertex
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')

    with class_.add_func('SetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        with func.add_arg(BatchVertex, "value") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '値')

    with class_.add_func("Create") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを作成します。')
        func.return_value.type_ = class_
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_static = True

FloatArray = cbg.Class('Altseed', 'FloatArray')
with FloatArray as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '浮動小数点数の配列のクラスを表します。')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface
    class_.is_Sealed = True

    with class_.add_func("Clear") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データをクリアします。')

    with class_.add_property(int, "Count") as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '格納されている要素の数を取得します。')
        prop_.has_getter = True
        prop_.serialized = True

    with class_.add_func('Resize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'サイズを変更します。')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')

    with class_.add_func("GetData") as func:
        func.return_value.type_ = ctypes.c_void_p

    with class_.add_func("Assign") as func:
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーするデータの先頭のポインタ')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーする要素の個数')

    with class_.add_func('CopyTo') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データを指定したポインタにコピーします。')
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ポインタ')

    with class_.add_func('GetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        func.return_value.type_ = float
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')

    with class_.add_func('SetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        with func.add_arg(float, "value") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '値')

    with class_.add_func("Create") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを作成します。')
        func.return_value.type_ = class_
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_static = True

Vector2FArray = cbg.Class('Altseed', 'Vector2FArray')
with Vector2FArray as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '2次元ベクトルの配列のクラスを表します。')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface
    class_.is_Sealed = True

    with class_.add_func("Clear") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データをクリアします。')

    with class_.add_property(int, "Count") as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '格納されている要素の数を取得します。')
        prop_.has_getter = True
        prop_.serialized = True

    with class_.add_func('Resize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'サイズを変更します。')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')

    with class_.add_func("GetData") as func:
        func.return_value.type_ = ctypes.c_void_p

    with class_.add_func("Assign") as func:
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーするデータの先頭のポインタ')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーする要素の個数')

    with class_.add_func('CopyTo') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データを指定したポインタにコピーします。')
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ポインタ')

    with class_.add_func('GetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        func.return_value.type_ = Vector2F
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')

    with class_.add_func('SetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        with func.add_arg(Vector2F, "value") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '値')

    with class_.add_func("Create") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを作成します。')
        func.return_value.type_ = class_
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_static = True

ResourceType = cbg.Enum('Altseed', 'ResourceType')
with ResourceType as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'リソースの種類を表します。')
    with enum_.add('StaticFile') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '<see cref="Altseed.StaticFile"/>を表す')
    with enum_.add('StreamFile') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '<see cref="Altseed.StreamFile"/>を表す')
    with enum_.add('Texture2D') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '<see cref="Altseed.Texture2D"/>を表す')
    with enum_.add('Font') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '<see cref="Altseed.Font"/>を表す')
    with enum_.add('Sound') as v:
        v.brief = cbg.Description()
        v.brief.add('ja', '<see cref="Altseed.Sound"/>を表す')
    enum_.add('MAX')

Resources = cbg.Class('Altseed', 'Resources')
with Resources as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'リソースのクラスを表します。')
    class_.is_public=False
    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得します。')
        func.is_public = False
        func.is_static = True
        func.return_value.type_ = Resources
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
    with class_.add_func('GetResourcesCount') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した種類のリソースの個数を返します。')
        with func.add_arg(ResourceType, 'type') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '個数を検索するリソースの種類')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '指定した種類のリソースの個数')
    with class_.add_func('Clear') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '登録されたリソースをすべて削除します。')
    with class_.add_func('Reload') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'リソースの再読み込みを行います。')
