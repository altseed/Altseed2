import ctypes
import sys
import os

from bindings import define
from bindings import auto_generate_define
from bindings import CppBindingGenerator as cbg

os.chdir(os.path.dirname(__file__))

if __name__ == '__main__':

    # generate
    sharedObjectGenerator = cbg.SharedObjectGenerator(define, [])

    sharedObjectGenerator.header = '''
#include "BaseObject.h"
#include "Common/Array.h"
#include "Common/Resource.h"
#include "Common/ResourceContainer.h"
#include "Common/Resources.h"
#include "Common/Profiler.h"
#include "Core.h"
#include "Graphics/BuiltinShader.h"
#include "Graphics/CommandList.h"
#include "Graphics/Font.h"
#include "Graphics/Graphics.h"
#include "Graphics/ImageFont.h"
#include "Graphics/Renderer/RenderedText.h"
#include "Graphics/Renderer/RenderedCamera.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/RenderedPolygon.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/RenderTexture.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"
#include "Graphics/Texture2D.h"
#include "IO/BaseFileReader.h"
#include "IO/File.h"
#include "IO/FileRoot.h"
#include "IO/PackFile.h"
#include "IO/PackFileReader.h"
#include "IO/StaticFile.h"
#include "IO/StreamFile.h"
#include "Input/ButtonState.h"
#include "Input/Joystick.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Logger/Log.h"
#include "Media/MediaPlayer.h"
#include "Physics/Collider/Collider.h"
#include "Physics/Collider/CircleCollider.h"
#include "Physics/Collider/EdgeCollider.h"
#include "Physics/Collider/PolygonCollider.h"
#include "Physics/Collider/ShapeCollider.h"
#include "Sound/Sound.h"
#include "Sound/SoundMixer.h"
#include "Tool/Tool.h"
#include "Window/Window.h"
    '''

    sharedObjectGenerator.func_name_create_and_add_shared_ptr = 'Altseed2::CreateAndAddSharedPtr'
    sharedObjectGenerator.func_name_add_and_get_shared_ptr = 'Altseed2::AddAndGetSharedPtr'

    sharedObjectGenerator.output_path = '../core/src/AutoGeneratedCoreWrapper.cpp'
    sharedObjectGenerator.generate()
