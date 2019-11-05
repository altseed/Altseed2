import ctypes, sys, os

from bindings import define
from bindings import CppBindingGenerator as cbg

if __name__ == '__main__':
    # generate
    sharedObjectGenerator = cbg.SharedObjectGenerator(define)

    sharedObjectGenerator.header = '''
#include "Input/Keyboard.h"
#include "Graphics/Graphics.h"
#include "Graphics/Texture2D.h"

    '''

    sharedObjectGenerator.func_name_create_and_add_shared_ptr = 'altseed::CreateAndAddSharedPtr'
    sharedObjectGenerator.func_name_add_and_get_shared_ptr = 'altseed::AddAndGetSharedPtr'

    sharedObjectGenerator.output_path = '../core/src/Wrapper.cpp'
    sharedObjectGenerator.generate()