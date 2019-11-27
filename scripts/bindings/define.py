from . import CppBindingGenerator as cbg
import ctypes
import sys

from .io import *
from .input import *
from .graphics import *
from .core import *

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

define.structs.append(Vector2DI)

# core
define.structs.append(CoreOption)
define.classes.append(Core)

# window
define.classes.append(Window)

# common
define.classes.append(Int8Array)
define.enums.append(ResourceType)
define.classes.append(Resources)

# input
define.enums.append(Keys)
define.enums.append(ButtonState)
define.classes.append(Keyboard)

# graphics
define.enums.append(DeviceType)
define.classes.append(Graphics)
define.classes.append(Texture2D)

# io
#define.classes.append(StreamFile)
#define.classes.append(StaticFile)
#define.classes.append(File)
