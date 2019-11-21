import ctypes, sys, os

from bindings import define
from bindings import CppBindingGenerator as cbg

if __name__ == '__main__':
    # generate
    sharedObjectGenerator = cbg.SharedObjectGenerator(define)

    sharedObjectGenerator.header = '''
#include "Core.h"
#include "BaseObject.h"

#include "Common/Int8Array.h"
#include "Common/ResourceContainer.h"
#include "Common/Resource.h"
#include "Common/Resources.h"

#include "Window/Window.h"

#include "Input/Keyboard.h"

#include "Graphics/Graphics.h"
#include "Graphics/Texture2D.h"

#include "IO/File.h"
#include "IO/PackFile.h"
#include "IO/StaticFile.h"
#include "IO/StreamFile.h"
#include "IO/FileRoot.h"
#include "IO/BaseFileReader.h"
#include "IO/PackFileReader.h"

    '''

    sharedObjectGenerator.func_name_create_and_add_shared_ptr = 'altseed::CreateAndAddSharedPtr'
    sharedObjectGenerator.func_name_add_and_get_shared_ptr = 'altseed::AddAndGetSharedPtr'

    sharedObjectGenerator.output_path = '../core/src/Wrapper.cpp'
    sharedObjectGenerator.generate()