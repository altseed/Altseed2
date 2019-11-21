
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

    
extern "C" {

CBGEXPORT void CBGSTDCALL cbg_Window_Release(void* cbg_self) {
    auto cbg_self_ = (altseed::Window*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_CopyTo(void* cbg_self,void* array,int32_t size) {
    auto cbg_self_ = (altseed::Int8Array*)(cbg_self);

    std::shared_ptr<altseed::Int8Array> cbg_arg0 = altseed::CreateAndAddSharedPtr<altseed::Int8Array>((altseed::Int8Array*)array);
    int32_t cbg_arg1 = size;
    cbg_self_->CopyTo(cbg_arg0,cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_Release(void* cbg_self) {
    auto cbg_self_ = (altseed::Int8Array*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Resources_GetInstance() {
    std::shared_ptr<altseed::Resources> cbg_ret = altseed::Resources::GetInstance();
    return (void*)altseed::AddAndGetSharedPtr<altseed::Resources>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Resources_GetResourcesCount(void* cbg_self,int32_t type) {
    auto cbg_self_ = (altseed::Resources*)(cbg_self);

    altseed::ResourceType cbg_arg0 = (altseed::ResourceType)type;
    int32_t cbg_ret = cbg_self_->GetResourcesCount(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Resources_Clear(void* cbg_self) {
    auto cbg_self_ = (altseed::Resources*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT void CBGSTDCALL cbg_Resources_Reload(void* cbg_self) {
    auto cbg_self_ = (altseed::Resources*)(cbg_self);

    cbg_self_->Reload();
}

CBGEXPORT void CBGSTDCALL cbg_Resources_Release(void* cbg_self) {
    auto cbg_self_ = (altseed::Resources*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT bool CBGSTDCALL cbg_Keyboard_Initialize(void* cbg_self,void* window) {
    auto cbg_self_ = (altseed::Keyboard*)(cbg_self);

    std::shared_ptr<altseed::Window> cbg_arg0 = altseed::CreateAndAddSharedPtr<altseed::Window>((altseed::Window*)window);
    bool cbg_ret = cbg_self_->Initialize(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Keyboard_Terminate(void* cbg_self) {
    auto cbg_self_ = (altseed::Keyboard*)(cbg_self);

    cbg_self_->Terminate();
}

CBGEXPORT void* CBGSTDCALL cbg_Keyboard_GetInstance(void* cbg_self) {
    auto cbg_self_ = (altseed::Keyboard*)(cbg_self);

    std::shared_ptr<altseed::Keyboard> cbg_ret = cbg_self_->GetInstance();
    return (void*)altseed::AddAndGetSharedPtr<altseed::Keyboard>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Keyboard_RefleshKeyStates(void* cbg_self) {
    auto cbg_self_ = (altseed::Keyboard*)(cbg_self);

    cbg_self_->RefleshKeyStates();
}

CBGEXPORT int32_t CBGSTDCALL cbg_Keyboard_GetKeyState(void* cbg_self,int32_t key) {
    auto cbg_self_ = (altseed::Keyboard*)(cbg_self);

    altseed::Keys cbg_arg0 = (altseed::Keys)key;
    altseed::ButtonState cbg_ret = cbg_self_->GetKeyState(cbg_arg0);
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Keyboard_Release(void* cbg_self) {
    auto cbg_self_ = (altseed::Keyboard*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Graphics_GetInstance() {
    std::shared_ptr<altseed::Graphics> cbg_ret = altseed::Graphics::GetInstance();
    return (void*)altseed::AddAndGetSharedPtr<altseed::Graphics>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Graphics_Release(void* cbg_self) {
    auto cbg_self_ = (altseed::Graphics*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT bool CBGSTDCALL cbg_Texture2D_Reload(void* cbg_self) {
    auto cbg_self_ = (altseed::Texture2D*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
}

CBGEXPORT altseed::Vector2DI CBGSTDCALL cbg_Texture2D_GetSize(void* cbg_self) {
    auto cbg_self_ = (altseed::Texture2D*)(cbg_self);

    altseed::Vector2DI cbg_ret = cbg_self_->GetSize();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Texture2D_Release(void* cbg_self) {
    auto cbg_self_ = (altseed::Texture2D*)(cbg_self);

    cbg_self_->Release();
}


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

