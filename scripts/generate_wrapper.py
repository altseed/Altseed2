import cbg
import ctypes
import sys

from bindings import define

# generate
sharedObjectGenerator = cbg.SharedObjectGenerator(define)

sharedObjectGenerator.header = '''
// #include "wrapper.h"
'''

sharedObjectGenerator.func_name_create_and_add_shared_ptr = 'Altseed::CreateAndAddSharedPtr'
sharedObjectGenerator.func_name_add_and_get_shared_ptr = 'Altseed::AddAndGetSharedPtr'

sharedObjectGenerator.output_path = 'Wrapper.cpp'
sharedObjectGenerator.generate()