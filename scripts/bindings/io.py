from . import CppBindingGenerator as cbg
import ctypes
import sys

from .common import *

StaticFile = cbg.Class('Altseed', 'StaticFile')
with StaticFile as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '一度でファイルを読み取るクラス')
    with class_.add_func('GetBuffer') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '読み込んだファイルのデータを取得する')
        func.return_value.type_ = Int8Array
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込んだファイルのデータ')
    with class_.add_func('GetPath') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '読み込んだファイルのパスを取得する')
        func.return_value.type_ = ctypes.c_wchar_p
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込んだファイルのパス')
    with class_.add_func('GetSize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '読み込んだファイルのデータサイズを取得する')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込んだファイルのデータサイズ')
    with class_.add_func('GetIsInPackage') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '読み込んだファイルがファイルパッケージ内に格納されているかどうかを取得する')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込んだファイルがファイルパッケージ内に格納されていたらtrue，それ以外でfalse')
    with class_.add_func('Reload') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '再読み込みを行う')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '再読み込み処理がうまくいったらtrue，それ以外でfalse')

StreamFile = cbg.Class('Altseed', 'StreamFile')
with StreamFile as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '段階的にファイルを読み取るクラス')
    with class_.add_func('GetSize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '読み込むファイルのデータサイズを取得する')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込むファイルのデータサイズ')
    with class_.add_func('GetCurrentPosition') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '現在読み込んでいるファイル上の位置を取得する')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '現在読み込んでいるファイル上の位置')
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
        func.brief = cbg.Description()
        func.brief.add('ja', '現在読み込んでいるファイルのデータを取得する')
        func.return_value.type_ = Int8Array
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '現在読み込んでいるファイルのデータ')
    with class_.add_func('GetTempBufferSize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '現在読み込んでいるファイルのデータサイズを取得する')
        func.return_value.type_ = int
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '現在読み込んでいるファイルのデータサイズ')
    with class_.add_func('GetIsInPackage') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '読み込むファイルがファイルパッケージ内に格納されているかどうかを取得する')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込むファイルがファイルパッケージ内に格納されていたらtrue，それ以外でfalse')
    with class_.add_func('Reload') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '再読み込みを行う')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '再読み込み処理がうまくいったらtrue，それ以外でfalse')

File = cbg.Class('Altseed', 'File')
with File as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'ファイル制御を行うクラス')
    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得する')
        func.is_public = False
        func.is_static = True
        func.return_value.type_ = File
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
    with class_.add_func('CreateStaticFile') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定ファイルを読み込んだStaticFileの新しいインスタンスを生成する')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルのパス')
        func.is_public = False
        func.return_value.type_ = StaticFile
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'pathで読み込んだファイルを格納するStaticFileの新しいインスタンスを生成する')
    with class_.add_func('CreateStreamFile') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定ファイルを読み込むStreamFileの新しいインスタンスを生成する')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルのパス')
        func.is_public = False
        func.return_value.type_ = StreamFile
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'pathで読み込むファイルを格納するStreamFileの新しいインスタンスを生成する')
    with class_.add_func('AddRootDirectory') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ファイル読み込み時に自動的に保管されるディレクトリを追加する')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '追加するディレクトリ')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '追加処理がうまくいったらtrue，それ以外でfalse')
    with class_.add_func('AddRootPackageWithPassword') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ファイルパッケージをパスワード有りで読み込む')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルパッケージのパス')
        with func.add_arg(ctypes.c_wchar_p, 'password') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルパッケージのパスワード')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込み処理がうまくいったらtrue，それ以外でfalse')
    with class_.add_func('AddRootPackage') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ファイルパッケージをパスワード無しで読み込む')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '読み込むファイルパッケージのパス')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '読み込み処理がうまくいったらtrue，それ以外でfalse')
    with class_.add_func('ClearRootDirectories') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '追加されたディレクトリやファイルパッケージをすべて削除する')
    with class_.add_func('Exists') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '指定したファイルが存在するかどうかを検索する')
        with func.add_arg(ctypes.c_wchar_p, 'path') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '存在を確認するファイルのパス')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'pathの示すファイルが存在していたらtrue，それ以外でfalse')
    with class_.add_func('Pack') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '')
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
        