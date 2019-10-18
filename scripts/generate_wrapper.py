import ctypes, sys, os

repos = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.append(repos + '/scripts')
sys.path.append(repos + '/scripts/cbg')
os.chdir(repos)

import cbg
from bindings import define

# generate
sharedObjectGenerator = cbg.SharedObjectGenerator(define)

# TODO: add core header files
sharedObjectGenerator.header = '''
#include "wrapper.h"
'''

sharedObjectGenerator.func_name_create_and_add_shared_ptr = 'Altseed::CreateAndAddSharedPtr'
sharedObjectGenerator.func_name_add_and_get_shared_ptr = 'Altseed::AddAndGetSharedPtr'

sharedObjectGenerator.output_path = 'core/src/Wrapper.cpp'
sharedObjectGenerator.generate()