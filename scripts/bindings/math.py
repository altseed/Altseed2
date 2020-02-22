from . import CppBindingGenerator as cbg
import ctypes
import sys

# from .common import *

Vector2I = cbg.Struct('Altseed', 'Vector2I', 'Vector2I')
Vector2F = cbg.Struct('Altseed', 'Vector2F_C', 'Vector2F')
Vector3F = cbg.Struct('Altseed', 'Vector3F', 'Vector3F')
RectF = cbg.Struct('Altseed', 'RectF', 'RectF')
Matrix44F = cbg.Struct('Altseed', 'Matrix44F', 'Matrix44F')
