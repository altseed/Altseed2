from . import CppBindingGenerator as cbg
import ctypes

from .common import *

FFTWindow = cbg.Enum('Altseed2', 'FFTWindow')
with FFTWindow as enum:
    enum.brief = cbg.Description()
    enum.brief.add('ja', '音のスペクトル解析に使用する窓関数')
    enum.add('Rectangular')
    enum.add('Triangle')
    enum.add('Hamming')
    enum.add('Hanning')
    enum.add('Blackman')
    enum.add('BlackmanHarris')
