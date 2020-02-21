from . import CppBindingGenerator as cbg
import ctypes

from .common import *

Sound = cbg.Class('Altseed', 'Sound')

with Sound as class_:
    class_.brief = cbg.Description()
    class_.brief.add('ja', '音源のクラス')

    with class_.add_func('Load') as func_:
        func_.is_static = True
        func_.add_arg(ctypes.c_wchar_p, 'path')
        func_.add_arg(bool, 'isDecompressed')
        func_.return_value.type_ = Sound

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

SoundMixer = cbg.Class('Altseed', 'SoundMixer')

with SoundMixer as class_:

    with class_.add_func('GetInstance') as func_:
        func_.is_static = True
        func_.is_public = False
        func_.return_value.type_ = SoundMixer

    with class_.add_func('Play') as func_:
        func_.add_arg(Sound, 'sound')
        func_.return_value.type_ = int

    with class_.add_func('GetIsPlaying') as func_:
        func_.add_arg(int, 'id')
        func_.return_value.type_ = bool

    class_.add_func('StopAll')

    with class_.add_func('Stop') as func_:
        func_.add_arg(int, 'id')

    with class_.add_func('Pause') as func_:
        func_.add_arg(int, 'id')

    with class_.add_func('Resume') as func_:
        func_.add_arg(int, 'id')

    with class_.add_func('Seek') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'position')

    with class_.add_func('SetVolume') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'volume')

    with class_.add_func('FadeIn') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'second')

    with class_.add_func('FadeOut') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'second')

    with class_.add_func('Fade') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'second')
        func_.add_arg(float, 'targetedVolume')

    with class_.add_func('GetIsPlaybackSpeedEnabled') as func_:
        func_.add_arg(int, 'id')
        func_.return_value.type_ = bool

    with class_.add_func('SetIsPlaybackSpeedEnabled') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(bool, 'isPlaybackSpeedEnabled')

    with class_.add_func('GetPlaybackSpeed') as func_:
        func_.add_arg(int, 'id')
        func_.return_value.type_ = float

    with class_.add_func('SetPlaybackSpeed') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'playbackSpeed')

    with class_.add_func('GetPanningPosition') as func_:
        func_.add_arg(int, 'id')
        func_.return_value.type_ = float

    with class_.add_func('SetPanningPosition') as func_:
        func_.add_arg(int, 'id')
        func_.add_arg(float, 'panningPosition')

    with class_.add_func('GetPlaybackPercent') as func_:
        func_.add_arg(int, 'id')
        func_.return_value.type_ = float