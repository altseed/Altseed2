from . import CppBindingGenerator as cbg
import ctypes
import sys

from .common import *

CoreOption = cbg.Struct('Altseed', 'CoreOption')
# with CoreOption as struct_:

Core = cbg.Class('Altseed', 'Core')
with Core as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', 'C++のCoreとの仲介を担うクラス')
    with class_.add_func('Initialize') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '初期化処理を行う')
        with func.add_arg(ctypes.c_wchar_p, 'title') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ウィンドウの左上に表示されるウィンドウん名')
        with func.add_arg(int, 'width') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ウィンドウの横幅')
        with func.add_arg(int, 'height') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', 'ウィンドウの縦幅')
        with func.add_arg(CoreOption, 'option') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '使用するコアのオプション')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '初期化処理がうまくいったらtrue，それ以外でfalse')
        func.is_static = True

    with class_.add_func('DoEvent') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'イベントを実行する')
        func.return_value.type_ = bool
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', 'イベントが進行出来たらtrue，それ以外でfalse')

    with class_.add_func('Terminate') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', '終了処理を行う')
        func.is_static = True

    with class_.add_func('GetInstance') as func:
        func.brief = cbg.Description()
        func.brief.add('ja', 'インスタンスを取得する')
        func.return_value.type_ = Core
        func.return_value.brief = cbg.Description()
        func.return_value.brief.add('ja', '使用するインスタンス')
        func.is_public = False
        func.is_static = True
