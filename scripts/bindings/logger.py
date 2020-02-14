from . import CppBindingGenerator as cbg
import ctypes
import sys

LogLevel = cbg.Enum('Altseed', 'LogLevel')
with LogLevel as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'ログレベルを表す')

    enum_.add('Trace', 0)
    enum_.add('Debug', 1)
    enum_.add('Information', 2)
    enum_.add('Warning', 3)
    enum_.add('Error', 4)
    enum_.add('Critical', 5)
    enum_.add('Off', 6)

LogCategory = cbg.Enum('Altseed', 'LogCategory')
with LogCategory as enum_:
    enum_.brief = cbg.Description()
    enum_.brief.add('ja', 'ログの範囲を表す')
    # Core用なので公開しない
    # enum_.add('Core', 0)
    enum_.add('Engine', 1)
    enum_.add('User', 2)

Log = cbg.Class('Altseed', 'Log')
with Log as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'ログを出力するクラス')

    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得する')
        func.return_value.type_ = Log
        func.is_static = True
        func.is_public = False

    with class_.add_func('Write') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ログを出力する')
        func.add_arg(LogCategory, 'category')
        func.add_arg(LogLevel, 'level')
        func.add_arg(ctypes.c_wchar_p, 'message')

    with class_.add_func('SetLevel') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'ログレベルを設定する')
        func.add_arg(LogCategory, 'category')
        func.add_arg(LogLevel, 'level')