from . import CppBindingGenerator as cbg
import ctypes

from .common import *
from .math import *

AlphaBlend = cbg.Struct('Altseed2', 'AlphaBlend_C', 'AlphaBlend')

RenderPassParameter = cbg.Struct(
    'Altseed2', 'RenderPassParameter_C', 'RenderPassParameter')
