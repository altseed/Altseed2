
#include <stdio.h>
#include <stdint.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
  #include <Windows.h>
#endif

#ifndef CBGEXPORT
#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
  #define CBGEXPORT __declspec(dllexport)
#else
  #define CBGEXPORT
#endif
#endif

#ifndef CBGSTDCALL
#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
  #define CBGSTDCALL __stdcall
#else
  #define CBGSTDCALL
#endif
#endif


    #include "Input/Keyboard.h"
    
extern "C" {


}

#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	bool res = true;
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		break;
	case DLL_PROCESS_DETACH:
		CoUninitialize();
		break;
	case DLL_THREAD_ATTACH:
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		break;
	case DLL_THREAD_DETACH:
		CoUninitialize();
		break;
	default:
		break;
	}
	return res;
}

#endif

