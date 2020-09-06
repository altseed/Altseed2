from . import CppBindingGenerator as cbg
import ctypes
import sys

# from .common import *

Vector2I = cbg.Struct('Altseed2', 'Vector2I_C', 'Vector2I')
Vector2F = cbg.Struct('Altseed2', 'Vector2F_C', 'Vector2F')
Vector3I = cbg.Struct('Altseed2', 'Vector3I_C', 'Vector3I')
Vector3F = cbg.Struct('Altseed2', 'Vector3F_C', 'Vector3F')
Vector4I = cbg.Struct('Altseed2', 'Vector4I_C', 'Vector4I')
Vector4F = cbg.Struct('Altseed2', 'Vector4F_C', 'Vector4F')
RectI = cbg.Struct('Altseed2', 'RectI_C', 'RectI')
RectF = cbg.Struct('Altseed2', 'RectF_C', 'RectF')
Matrix44I = cbg.Struct('Altseed2', 'Matrix44I_C', 'Matrix44I')
Matrix44F = cbg.Struct('Altseed2', 'Matrix44F_C', 'Matrix44F')
BatchVertex = cbg.Struct('Altseed2', 'BatchVertex', 'Vertex')
Color = cbg.Struct('Altseed2', 'Color_C', 'Color')