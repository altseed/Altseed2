from . import CppBindingGenerator as cbg
import ctypes
import sys

from .common import *

StaticFile = cbg.Class('Altseed2', 'StaticFile', cbg.CacheMode.ThreadSafeCache)
with StaticFile as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '一度でファイルを読み取るクラス')
    class_.SerializeType = cbg.SerializeType.Interface
    class_.is_Sealed = True
    
    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定ファイルを読み込んだ<see cref="StaticFile"/>の新しいインスタンスを生成します。')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルのパス')
            arg.nullable = False
        func.is_static = True
        func.return_value.type_ = StaticFile
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add(
            'ja', 'pathで読み込んだファイルを格納する<see cref="StaticFile"/>の新しいインスタンスを生成します。')

    with class_.add_func('GetBuffer') as func:
        func.is_public = False
        func.brief = cbg.Description()
        func.brief.add('ja', '読み込んだファイルのデータを取得します。')
        func.return_value.type_ = Int8Array
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込んだファイルのデータ')

    with class_.add_property(ctypes.c_wchar_p, 'Path') as prop:

        prop.brief = cbg.Description()
        prop.brief.add('ja', '読み込んだファイルのパスを取得します。')
        prop.has_getter = True
        prop.serialized = True

    with class_.add_property(int, 'Size') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '読み込んだファイルのデータサイズを取得します。')
        prop.has_getter = True

    with class_.add_property(bool, 'IsInPackage') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '読み込んだファイルがファイルパッケージ内に格納されているかどうかを取得します。')
        prop.has_getter = True

    with class_.add_func('Reload') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '再読み込みを行います。')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '再読み込み処理がうまくいったらtrue，それ以外でfalse')

StreamFile = cbg.Class('Altseed2', 'StreamFile', cbg.CacheMode.ThreadSafeCache)
with StreamFile as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '段階的にファイルを読み取るクラス')
    class_.SerializeType = cbg.SerializeType.Interface
    class_.is_Sealed = True
    class_.CallBackType = cbg.CallBackType.Enable

    with class_.add_func('Create') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定ファイルを読み込む<see cref="StreamFile"/>の新しいインスタンスを生成します。')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルのパス')
            arg.nullable = False
        func.is_static = True
        func.return_value.type_ = StreamFile
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add(
            'ja', 'pathで読み込むファイルを格納する<see cref="StreamFile"/>の新しいインスタンスを生成します。')

    with class_.add_property(int, 'Size') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '読み込むファイルのデータサイズを取得します。')
        prop.has_getter = True

    with class_.add_property(int, 'CurrentPosition') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '現在読み込んでいるファイル上の位置を取得します。')
        prop.has_getter = True
        prop.serialized = True

    with class_.add_func('Read') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定した分ファイルを読み込む')
        with func.add_arg(int, 'size') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'この処理で読み込むデータサイズ')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込まれたデータサイズ')

    with class_.add_func('GetTempBuffer') as func:
        func.is_public = False
        func.brief = cbg.Description()
        func.brief.add('ja', '現在読み込んでいるファイルのデータを取得します。')
        func.return_value.type_ = Int8Array
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '現在読み込んでいるファイルのデータ')
        
    with class_.add_property(int, 'TempBufferSize') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '現在読み込んでいるファイルのデータサイズを取得します。')
        prop.has_getter = True

    with class_.add_property(bool, 'IsInPackage') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '読み込むファイルがファイルパッケージ内に格納されているかどうかを取得します。')
        prop.has_getter = True

    with class_.add_property(ctypes.c_wchar_p, 'Path') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '読み込んだファイルのパスを取得します。')
        prop.is_public = False
        prop.has_getter = True
        prop.serialized = True

    with class_.add_func('Reload') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '再読み込みを行います。')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '再読み込み処理がうまくいったらtrue，それ以外でfalse')

File = cbg.Class('Altseed2', 'File')
with File as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'ファイル制御を行うクラス')
    class_.is_Sealed = True
    
    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得します。')
        func.is_public = False
        func.is_static = True
        func.return_value.type_ = File
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
    with class_.add_func('AddRootDirectory') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ファイル読み込み時に自動的に保管されるディレクトリを追加します。')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '追加するディレクトリ')
            arg.nullable = False
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '追加処理がうまくいったらtrue，それ以外でfalse')
    with class_.add_func('AddRootPackageWithPassword') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ファイルパッケージをパスワード有りで読み込む')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルパッケージのパス')
            arg.nullable = False
        with func.add_arg(ctypes.c_wchar_p, 'password') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルパッケージのパスワード')
            arg.nullable = False
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込み処理がうまくいったらtrue，それ以外でfalse')
    with class_.add_func('AddRootPackage') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ファイルパッケージをパスワード無しで読み込む')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルパッケージのパス')
            arg.nullable = False
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込み処理がうまくいったらtrue，それ以外でfalse')
    with class_.add_func('ClearRootDirectories') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '追加されたディレクトリやファイルパッケージをすべて削除します。')
    with class_.add_func('Exists') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定したファイルが存在するかどうかを検索します。')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '存在を確認するファイルのパス')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'pathの示すファイルが存在していたらtrue，それ以外でfalse')
    with class_.add_func('Pack') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定したディレクトリのファイルをパックする')
        with func.add_arg(ctypes.c_wchar_p, 'srcPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'パックするファイルのディレクトリ')
            arg.nullable = False
        with func.add_arg(ctypes.c_wchar_p, 'dstPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'パックされたファイル名')
            arg.nullable = False
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'パック処理がうまくいったらtrue，それ以外でfalse')
    with class_.add_func('PackWithPassword') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定したディレクトリのファイルをパスワード付きでパックする')
        with func.add_arg(ctypes.c_wchar_p, 'srcPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'パックするファイルのディレクトリ')
            arg.nullable = False
        with func.add_arg(ctypes.c_wchar_p, 'dstPath') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'パックされたファイル名')
            arg.nullable = False
        with func.add_arg(ctypes.c_wchar_p, 'password') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'かけるパスワード')
            arg.nullable = False
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'パック処理がうまくいったらtrue，それ以外でfalse')
