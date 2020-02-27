from . import CppBindingGenerator as cbg
import ctypes
import sys

from .io import *
from .input import *
from .graphics import *
from .core import *
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

# core
define.classes.append(Configuration)
define.classes.append(Core)

# common
define.classes.append(Int8Array)
define.classes.append(Int32Array)
define.classes.append(VertexArray)
define.classes.append(FloatArray)

define.enums.append(ResourceType)
define.classes.append(Resources)

# input
define.enums.append(Keys)
define.enums.append(ButtonState)
define.enums.append(MouseButtons)
define.enums.append(CursorMode)
define.enums.append(JoystickType)
define.enums.append(JoystickButtonType)
define.enums.append(JoystickAxisType)

define.classes.append(Keyboard)
define.classes.append(Mouse)
define.classes.append(Joystick)

# graphics
define.enums.append(DeviceType)
define.enums.append(BuildinShaderType)
define.enums.append(WritingDirection)

# define.structs.append(BatchVertex)
define.structs.append(Color)

define.classes.append(Graphics)
define.classes.append(Texture2D)
define.classes.append(Material)
define.classes.append(Renderer)
define.classes.append(CommandList)
define.classes.append(Rendered)
define.classes.append(RenderedSprite)
define.classes.append(RenderedCamera)
define.classes.append(BuildinShader)
define.classes.append(Shader)
define.classes.append(Glyph)
define.classes.append(Font)

# io
define.classes.append(StreamFile)
define.classes.append(StaticFile)
define.classes.append(File)

# sound
define.enums.append(FFTWindow)
define.classes.append(Sound)
define.classes.append(SoundMixer)

# Logger
define.enums.append(LogLevel)
define.enums.append(LogCategory)
define.classes.append(Log)
