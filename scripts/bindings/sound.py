from . import CppBindingGenerator as cbg
import ctypes

from .common import *

Sound = cbg.Class('Altseed', 'Sound')

with Sound as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '音源のクラス')
    with class_.add_property(float, 'LoopStartingPoint') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'ループ開始地点(秒)を取得または設定する')
        prop.has_getter = True
        prop.has_setter = True

    with class_.add_property(float, 'LoopEndPoint') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'ループ終了地点(秒)を取得または設定する')
        prop.has_getter = True
        prop.has_setter = True

    with class_.add_property(bool, 'IsLoopingMode') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', 'ループするかどうかを取得または設定する')
        prop.has_getter = True
        prop.has_setter = True

    with class_.add_property(float, 'Length') as prop:
        prop.brief = cbg.Description()
        prop.brief.add('ja', '音源の長さ(秒)を取得する')
        prop.has_getter = True

# SoundMixer = cbg.Class('Altseed', 'SoundMixier')

# with SoundMixer as class_:
    # coreでSoundが生ポインタになってる

    # with class_.add_func('CreateSound') as func_:
    #     func_.add_arg(ctypes.c_wchar_p, 'path')
    #     func_.add_arg(bool, 'isDecompressed')
    #     func_.return_value = Sound

    # with class_.add_func('Play') as func_:
    #     func_.add_arg(Sound, 'sound')
    #     func_.return_value = cbg.ReturnValue(int)

    # with class_.add_func('GetIsPlaying') as func_:
    #     func_.add_arg(int, 'id')
    #     func_.return_value = cbg.ReturnValue(bool)

    class_.add_func('StopAll')

    # 後回し

    # with class_.add_func('Stop') as func_:
    #     func_.add_arg(int, 'id')

    # with class_.add_func('Pause') as func_:
    #     func_.add_arg(int, 'id')

    # with class_.add_func('Resume') as func_:
    #     func_.add_arg(int, 'id')

    # with class_.add_func('Seek') as func_:
    #     func_.add_arg(int, 'id')
    #     func_.add_arg(float, 'position')

    # with class_.add_func('SetVolume') as func_:
    #     func_.add_arg(int, 'id')
    #     func_.add_arg(float, 'volume')

    # with class_.add_func('SetVolume') as func_:
    #     func_.add_arg(int, 'id')
    #     func_.add_arg(float, 'volume')