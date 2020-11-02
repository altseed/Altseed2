from . import CppBindingGenerator as cbg
from .math import *

import ctypes

VoidPtr = cbg.Class('Altseed2', 'VoidPtr')

Int8Array = cbg.Class('Altseed2', 'Int8Array')
with Int8Array as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '8ビット整数の配列のクラスを表します。')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface
    class_.is_Sealed = True

    with class_.add_func("Clear") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データをクリアします。')
        func.is_public = False

    with class_.add_property(int, "Count") as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '格納されている要素の数を取得します。')
        prop_.has_getter = True
        prop_.serialized = True
        prop_.is_public = True  # to implement IArray<T>

    with class_.add_func('Resize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'サイズを変更します。')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func("GetData") as func:
        func.return_value.type_ = ctypes.c_void_p
        func.is_public = False

    with class_.add_func("Assign") as func:
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーするデータの先頭のポインタ')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーする要素の個数')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func('CopyTo') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データを指定したポインタにコピーします。')
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ポインタ')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func('GetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        func.return_value.type_ = ctypes.c_byte
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        func.is_public = False

    with class_.add_func('SetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        with func.add_arg(ctypes.c_byte, "value") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '値')
        func.is_public = False

    with class_.add_func("Create") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを作成します。')
        func.return_value.type_ = class_
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_static = True
        func.is_public = False

Int32Array = cbg.Class('Altseed2', 'Int32Array')
with Int32Array as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '32ビット整数の配列のクラスを表します。')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface
    class_.is_Sealed = True

    with class_.add_func("Clear") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データをクリアします。')
        func.is_public = False

    with class_.add_property(int, "Count") as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '格納されている要素の数を取得します。')
        prop_.has_getter = True
        prop_.serialized = True
        prop_.is_public = True  # to implement IArray<T>

    with class_.add_func('Resize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'サイズを変更します。')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func("GetData") as func:
        func.return_value.type_ = ctypes.c_void_p
        func.is_public = False

    with class_.add_func("Assign") as func:
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーするデータの先頭のポインタ')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーする要素の個数')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func('CopyTo') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データを指定したポインタにコピーします。')
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ポインタ')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func('GetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        func.return_value.type_ = int
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        func.is_public = False

    with class_.add_func('SetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        with func.add_arg(int, "value") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '値')
        func.is_public = False

    with class_.add_func("Create") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを作成します。')
        func.return_value.type_ = class_
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_static = True
        func.is_public = False

VertexArray = cbg.Class('Altseed2', 'VertexArray')
with VertexArray as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '頂点データの配列のクラスを表します。')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface
    class_.is_Sealed = True

    with class_.add_func("Clear") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データをクリアします。')
        func.is_public = False

    with class_.add_property(int, "Count") as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '格納されている要素の数を取得します。')
        prop_.has_getter = True
        prop_.serialized = True
        prop_.is_public = True  # to implement IArray<T>

    with class_.add_func('Resize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'サイズを変更します。')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func("GetData") as func:
        func.return_value.type_ = ctypes.c_void_p
        func.is_public = False

    with class_.add_func("Assign") as func:
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーするデータの先頭のポインタ')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーする要素の個数')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func('CopyTo') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データを指定したポインタにコピーします。')
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ポインタ')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func('GetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        func.return_value.type_ = BatchVertex
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        func.is_public = False

    with class_.add_func('SetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        with func.add_arg(BatchVertex, "value") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '値')
        func.is_public = False

    with class_.add_func("Create") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを作成します。')
        func.return_value.type_ = class_
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_static = True
        func.is_public = False

FloatArray = cbg.Class('Altseed2', 'FloatArray')
with FloatArray as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '浮動小数点数の配列のクラスを表します。')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface
    class_.is_Sealed = True

    with class_.add_func("Clear") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データをクリアします。')
        func.is_public = False

    with class_.add_property(int, "Count") as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '格納されている要素の数を取得します。')
        prop_.has_getter = True
        prop_.serialized = True
        prop_.is_public = True  # to implement IArray<T>

    with class_.add_func('Resize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'サイズを変更します。')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func("GetData") as func:
        func.return_value.type_ = ctypes.c_void_p
        func.is_public = False

    with class_.add_func("Assign") as func:
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーするデータの先頭のポインタ')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーする要素の個数')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func('CopyTo') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データを指定したポインタにコピーします。')
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ポインタ')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func('GetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        func.return_value.type_ = float
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        func.is_public = False

    with class_.add_func('SetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        with func.add_arg(float, "value") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '値')
        func.is_public = False

    with class_.add_func("Create") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを作成します。')
        func.return_value.type_ = class_
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_static = True
        func.is_public = False

Vector2FArray = cbg.Class('Altseed2', 'Vector2FArray')
with Vector2FArray as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '2次元ベクトルの配列のクラスを表します。')
    class_.is_public = False
    class_.SerializeType = cbg.SerializeType.Interface
    class_.is_Sealed = True

    with class_.add_func("Clear") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データをクリアします。')
        func.is_public = False

    with class_.add_property(int, "Count") as prop_:
        prop_.brief = cbg.Description()
        prop_.brief.add('ja', '格納されている要素の数を取得します。')
        prop_.has_getter = True
        prop_.serialized = True
        prop_.is_public = True  # to implement IArray<T>

    with class_.add_func('Resize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'サイズを変更します。')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func("GetData") as func:
        func.return_value.type_ = ctypes.c_void_p
        func.is_public = False

    with class_.add_func("Assign") as func:
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーするデータの先頭のポインタ')
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'コピーする要素の個数')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func('CopyTo') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'データを指定したポインタにコピーします。')
        with func.add_arg(ctypes.c_void_p, "ptr") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ポインタ')
        func.is_public = True  # to implement IArray<T>

    with class_.add_func('GetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        func.return_value.type_ = Vector2F
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        func.is_public = False

    with class_.add_func('SetAt') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インデックスアクセス')
        with func.add_arg(int, "index") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'インデックス')
        with func.add_arg(Vector2F, "value") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '値')
        func.is_public = False

    with class_.add_func("Create") as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを作成します。')
        func.return_value.type_ = class_
        with func.add_arg(int, "size") as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '要素数')
        func.is_static = True
        func.is_public = False
