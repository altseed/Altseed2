from . import CppBindingGenerator as cbg
import ctypes
import sys

# from .common import *

Vector2I = cbg.Struct('Altseed', 'Vector2I_C', 'Vector2I')
Vector2F = cbg.Struct('Altseed', 'Vector2F_C', 'Vector2F')
Vector3I = cbg.Struct('Altseed', 'Vector3F_C', 'Vector3F')
Vector3F = cbg.Struct('Altseed', 'Vector3F_C', 'Vector3F')
Vector4I = cbg.Struct('Altseed', 'Vector4F_C', 'Vector4F')
Vector4F = cbg.Struct('Altseed', 'Vector4F_C', 'Vector4F')
RectI = cbg.Struct('Altseed', 'RectI_C', 'RectI')
RectF = cbg.Struct('Altseed', 'RectF_C', 'RectF')
Matrix44I = cbg.Struct('Altseed', 'Matrix44I_C', 'Matrix44I')
Matrix44F = cbg.Struct('Altseed', 'Matrix44F_C', 'Matrix44F')
BatchVertex = cbg.Struct('Altseed', 'BatchVertex', 'Vertex')
Color = cbg.Struct('Altseed', 'Color_C', 'Color')
