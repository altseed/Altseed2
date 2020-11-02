from . import CppBindingGenerator as cbg
import ctypes
import sys

from .graphics import *
from .sound import *
from .math import *
from .logger import *

# サポートされない型
# u16string は const char16_t* として扱われることになる
# int64_t, int8_t などは int32_t として扱われることになる
# int8_t*, vector<int8_t> に対しては仮に Bytes クラスとおいている
# void* に対しては仮に VoidPtr クラスとおいている
# double; Mouse; floatとして扱われる
# double& 引数; Mouse
# std::function<void(double, double)>; Mouse
# フィールドはサポートされない; Graphics
# std::vector<std::shared_ptr<Sprite>>; Graphics
# LLGI::DeviceType; Graphics
# std::array<LLGI::Vec2F, 4>; Sprite
# LLGI::Vec2F; Sprite
# std::tuple<int32_t, int32_t>; Texture2D
# shared_ptrを使わずポインタで直接インスタンスを受け渡している場所

# define
define = cbg.Define()

# math
define.structs.append(Vector2I)
define.structs.append(Vector2F)
define.structs.append(Vector3I)
define.structs.append(Vector3F)
define.structs.append(Vector4I)
define.structs.append(Vector4F)
define.structs.append(RectI)
define.structs.append(RectF)
define.structs.append(Matrix44I)
define.structs.append(Matrix44F)

# common
define.classes.append(Int8Array)
define.classes.append(Int32Array)
define.classes.append(VertexArray)
define.classes.append(FloatArray)
define.classes.append(Vector2FArray)

# graphics

define.structs.append(AlphaBlend)
define.structs.append(BatchVertex)
define.structs.append(Color)

define.structs.append(RenderPassParameter)

# sound
define.enums.append(FFTWindow)

# Logger
define.enums.append(LogLevel)
define.enums.append(LogCategory)
define.classes.append(Log)
