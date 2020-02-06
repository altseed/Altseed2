from . import CppBindingGenerator as cbg
import ctypes
import sys

# from .common import *

EasingType = cbg.Enum('Altseed', 'EasingType')
with EasingType as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', 'イージングの種類を表す')
    enum.add('Linear')
    enum.add('InSine')
    enum.add('OutSine')
    enum.add('InOutSine')
    enum.add('InQuad')
    enum.add('OutQuad')
    enum.add('InOutQuad')
    enum.add('InCubic')
    enum.add('OutCubic')
    enum.add('InOutCubic')
    enum.add('InQuart')
    enum.add('OutQuart')
    enum.add('InOutQuart')
    enum.add('InQuint')
    enum.add('OutQuint')
    enum.add('InOutQuint')
    enum.add('InExpo')
    enum.add('OutExpo')
    enum.add('InOutExpo')
    enum.add('InCirc')
    enum.add('OutCirc')
    enum.add('InOutCirc')
    enum.add('InBack')
    enum.add('OutBack')
    enum.add('InOutBack')
    enum.add('InElastic')
    enum.add('OutElastic')
    enum.add('InOutElastic')
    enum.add('InBounce')
    enum.add('OutBounce')
    enum.add('InOutBounce')

Easing = cbg.Class('Altseed', 'Easing')
with Easing as class_:
    with class_.add_func('GetEasing') as func_:
        func_.brief = cbg.Description()
        func_.brief.add('ja', '')
        with func_.add_arg(EasingType, 'easing') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        with func_.add_arg(float, 't') as arg:
            arg.brief = cbg.Description()
            arg.brief.add('ja', '')
        func_.is_static = True

