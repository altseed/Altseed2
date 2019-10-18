import cbg
import ctypes
import sys

from bindings.io import *
from bindings.input import *
from bindings.graphics import *

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
define.classes.append(BaseFileReader)
define.classes.append(StreamFile)
define.classes.append(StaticFile)
define.classes.append(File)
define.classes.append(PackFile)
define.classes.append(FileRoot)
define.classes.append(PackFileReader)
define.classes.append(Bytes)
define.classes.append(Resources)
define.classes.append(ZipPtr)
define.classes.append(ZipFilePtr)
define.classes.append(ZipStatPtr)

define.enums.append(SeekOrigin)
define.enums.append(ResourceType)