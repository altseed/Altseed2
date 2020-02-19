import ctypes, sys, os

from bindings import define
from bindings import CppBindingGenerator as cbg

if __name__ == '__main__':
    
    # os.chdir(os.path.dirname(__file__))

    # generate
    sharedObjectGenerator = cbg.SharedObjectGenerator(define)

    sharedObjectGenerator.header = '''
#include "Core.h"
#include "BaseObject.h"

#include "Common/Array.h"
#include "Common/ResourceContainer.h"
#include "Common/Resource.h"
#include "Common/Resources.h"

#include "Window/Window.h"

#include "Input/ButtonState.h"
#include "Input/Joystick.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"

#include "Graphics/Graphics.h"
#include "Graphics/CommandList.h"
#include "Graphics/Texture2D.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Renderer/RenderedSprite.h"

#include "IO/File.h"
#include "IO/PackFile.h"
#include "IO/StaticFile.h"
#include "IO/StreamFile.h"
#include "IO/FileRoot.h"
#include "IO/BaseFileReader.h"
#include "IO/PackFileReader.h"

#include "Sound/Sound.h"
#include "Sound/SoundMixer.h"

#include "Math/Easing.h"

#include "Logger/Log.h"

    '''

    sharedObjectGenerator.func_name_create_and_add_shared_ptr = 'Altseed::CreateAndAddSharedPtr'
    sharedObjectGenerator.func_name_add_and_get_shared_ptr = 'Altseed::AddAndGetSharedPtr'

    sharedObjectGenerator.output_path = '../core/src/Wrapper.cpp'
    sharedObjectGenerator.generate()