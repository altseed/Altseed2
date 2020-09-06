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
from .tool import *
from .window import *
from .physics import *

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
define.enums.append(GraphicsDeviceType)
define.enums.append(CoreModules)
define.classes.append(Configuration)
define.enums.append(FramerateMode)
define.classes.append(Core)

# common
define.classes.append(Int8Array)
define.classes.append(Int32Array)
define.classes.append(VertexArray)
define.classes.append(FloatArray)
define.classes.append(Vector2FArray)

define.enums.append(ResourceType)
define.classes.append(Resources)

# input
define.enums.append(Key)
define.enums.append(ButtonState)
define.enums.append(MouseButton)
define.enums.append(CursorMode)
define.enums.append(JoystickType)
define.enums.append(JoystickButton)
define.enums.append(JoystickAxis)

define.classes.append(Cursor)
define.classes.append(Keyboard)
define.classes.append(Mouse)
define.classes.append(JoystickInfo)
define.classes.append(Joystick)

# graphics
define.enums.append(ShaderStageType)
define.enums.append(BuiltinShaderType)
define.enums.append(WritingDirection)
define.enums.append(TextureFilterType)
define.enums.append(TextureWrapMode)
define.enums.append(TextureFormatType)
define.enums.append(BlendEquationType)
define.enums.append(BlendFuncType)

define.structs.append(AlphaBlend)
define.structs.append(BatchVertex)
define.structs.append(Color)

define.classes.append(Graphics)
define.classes.append(TextureBase)
define.classes.append(Texture2D)
define.classes.append(RenderTexture)
define.classes.append(Material)
define.classes.append(Renderer)
define.structs.append(RenderPassParameter)
define.classes.append(CommandList)
define.classes.append(Rendered)
define.classes.append(RenderedSprite)
define.classes.append(RenderedText)
define.classes.append(RenderedPolygon)
define.classes.append(RenderedCamera)
define.classes.append(BuiltinShader)
define.classes.append(ShaderCompileResult)
define.classes.append(Shader)
define.classes.append(Glyph)
define.classes.append(Font)
define.classes.append(CullingSystem)

# tool
define.enums.append(ToolUsage)
define.enums.append(ToolGlyphRange)
define.enums.append(ToolWindowFlags)
define.enums.append(ToolInputTextFlags)
define.enums.append(ToolTreeNodeFlags)
define.enums.append(ToolSelectableFlags)
define.enums.append(ToolComboFlags)
define.enums.append(ToolTabBarFlags)
define.enums.append(ToolTabItemFlags)
define.enums.append(ToolFocusedFlags)
define.enums.append(ToolHoveredFlags)
define.enums.append(ToolDragDropFlags)
define.enums.append(ToolDataType)
define.enums.append(ToolDir)
define.enums.append(ToolKey)
define.enums.append(ToolKeyModFlags)
define.enums.append(ToolNavInput)
define.enums.append(ToolConfigFlags)
define.enums.append(ToolBackendFlags)
define.enums.append(ToolCol)
define.enums.append(ToolStyleVar)
define.enums.append(ToolColorEditFlags)
define.enums.append(ToolMouseButton)
define.enums.append(ToolMouseCursor)
define.enums.append(ToolCond)
define.enums.append(ToolDrawCornerFlags)
define.enums.append(ToolDrawListFlags)
define.enums.append(ToolFontAtlasFlags)
define.classes.append(Tool)

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

# Window
define.classes.append(Window)

# physics
define.classes.append(Collider)
define.classes.append(CircleCollider)
define.classes.append(EdgeCollider)
define.classes.append(ShapeCollider)
define.classes.append(PolygonCollider)
