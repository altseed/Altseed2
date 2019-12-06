
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

CBGEXPORT bool CBGSTDCALL cbg_Core_Initialize(const char16_t* title,int32_t width,int32_t height,void* option) {
    const char16_t* cbg_arg0 = title;
    int32_t cbg_arg1 = width;
    int32_t cbg_arg2 = height;
    altseed::CoreOption cbg_arg3 = (*((altseed::CoreOption*)option));
    bool cbg_ret = altseed::Core::Initialize(cbg_arg0,cbg_arg1,cbg_arg2,cbg_arg3);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Core_DoEvent(void* cbg_self) {
    auto cbg_self_ = (altseed::Core*)(cbg_self);

    bool cbg_ret = cbg_self_->DoEvent();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Core_Terminate() {
    altseed::Core::Terminate();
}

CBGEXPORT void* CBGSTDCALL cbg_Core_GetInstance() {
    std::shared_ptr<altseed::Core> cbg_ret = altseed::Core::GetInstance();
    return (void*)altseed::AddAndGetSharedPtr<altseed::Core>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Core_Release(void* cbg_self) {
    auto cbg_self_ = (altseed::Core*)(cbg_self);

    cbg_self_->Release();
}

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

CBGEXPORT void* CBGSTDCALL cbg_Keyboard_GetInstance() {
    std::shared_ptr<altseed::Keyboard> cbg_ret = altseed::Keyboard::GetInstance();
    return (void*)altseed::AddAndGetSharedPtr<altseed::Keyboard>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Keyboard_Release(void* cbg_self) {
    auto cbg_self_ = (altseed::Keyboard*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Graphics_GetInstance() {
    std::shared_ptr<altseed::Graphics> cbg_ret = altseed::Graphics::GetInstance();
    return (void*)altseed::AddAndGetSharedPtr<altseed::Graphics>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Graphics_Update(void* cbg_self) {
    auto cbg_self_ = (altseed::Graphics*)(cbg_self);

    bool cbg_ret = cbg_self_->Update();
    return cbg_ret;
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

CBGEXPORT int32_t CBGSTDCALL cbg_StreamFile_GetSize(void* cbg_self) {
    auto cbg_self_ = (altseed::StreamFile*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetSize();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_StreamFile_GetCurrentPosition(void* cbg_self) {
    auto cbg_self_ = (altseed::StreamFile*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCurrentPosition();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_StreamFile_Read(void* cbg_self,int32_t size) {
    auto cbg_self_ = (altseed::StreamFile*)(cbg_self);

    int32_t cbg_arg0 = size;
    int32_t cbg_ret = cbg_self_->Read(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void* CBGSTDCALL cbg_StreamFile_GetTempBuffer(void* cbg_self) {
    auto cbg_self_ = (altseed::StreamFile*)(cbg_self);

    std::shared_ptr<altseed::Int8Array> cbg_ret = cbg_self_->GetTempBuffer();
    return (void*)altseed::AddAndGetSharedPtr<altseed::Int8Array>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_StreamFile_GetTempBufferSize(void* cbg_self) {
    auto cbg_self_ = (altseed::StreamFile*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetTempBufferSize();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_StreamFile_GetIsInPackage(void* cbg_self) {
    auto cbg_self_ = (altseed::StreamFile*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsInPackage();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_StreamFile_Reload(void* cbg_self) {
    auto cbg_self_ = (altseed::StreamFile*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_StreamFile_Release(void* cbg_self) {
    auto cbg_self_ = (altseed::StreamFile*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_StaticFile_GetBuffer(void* cbg_self) {
    auto cbg_self_ = (altseed::StaticFile*)(cbg_self);

    std::shared_ptr<altseed::Int8Array> cbg_ret = cbg_self_->GetBuffer();
    return (void*)altseed::AddAndGetSharedPtr<altseed::Int8Array>(cbg_ret);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_StaticFile_GetPath(void* cbg_self) {
    auto cbg_self_ = (altseed::StaticFile*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetPath();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_StaticFile_GetSize(void* cbg_self) {
    auto cbg_self_ = (altseed::StaticFile*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetSize();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_StaticFile_GetIsInPackage(void* cbg_self) {
    auto cbg_self_ = (altseed::StaticFile*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsInPackage();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_StaticFile_Reload(void* cbg_self) {
    auto cbg_self_ = (altseed::StaticFile*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_StaticFile_Release(void* cbg_self) {
    auto cbg_self_ = (altseed::StaticFile*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_File_GetInstance() {
    std::shared_ptr<altseed::File> cbg_ret = altseed::File::GetInstance();
    return (void*)altseed::AddAndGetSharedPtr<altseed::File>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_File_CreateStaticFile(void* cbg_self,const char16_t* path) {
    auto cbg_self_ = (altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    std::shared_ptr<altseed::StaticFile> cbg_ret = cbg_self_->CreateStaticFile(cbg_arg0);
    return (void*)altseed::AddAndGetSharedPtr<altseed::StaticFile>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_File_CreateStreamFile(void* cbg_self,const char16_t* path) {
    auto cbg_self_ = (altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    std::shared_ptr<altseed::StreamFile> cbg_ret = cbg_self_->CreateStreamFile(cbg_arg0);
    return (void*)altseed::AddAndGetSharedPtr<altseed::StreamFile>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_File_AddRootDirectory(void* cbg_self,const char16_t* path) {
    auto cbg_self_ = (altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    bool cbg_ret = cbg_self_->AddRootDirectory(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_File_AddRootPackageWithPassword(void* cbg_self,const char16_t* path,const char16_t* password) {
    auto cbg_self_ = (altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    const char16_t* cbg_arg1 = password;
    bool cbg_ret = cbg_self_->AddRootPackageWithPassword(cbg_arg0,cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_File_AddRootPackage(void* cbg_self,const char16_t* path) {
    auto cbg_self_ = (altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    bool cbg_ret = cbg_self_->AddRootPackage(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_File_ClearRootDirectories(void* cbg_self) {
    auto cbg_self_ = (altseed::File*)(cbg_self);

    cbg_self_->ClearRootDirectories();
}

CBGEXPORT bool CBGSTDCALL cbg_File_Exists(void* cbg_self,const char16_t* path) {
    auto cbg_self_ = (altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    bool cbg_ret = cbg_self_->Exists(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_File_Pack(void* cbg_self,const char16_t* srcPath,const char16_t* dstPath) {
    auto cbg_self_ = (altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = srcPath;
    const char16_t* cbg_arg1 = dstPath;
    bool cbg_ret = cbg_self_->Pack(cbg_arg0,cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_File_PackWithPassword(void* cbg_self,const char16_t* srcPath,const char16_t* dstPath,const char16_t* password) {
    auto cbg_self_ = (altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = srcPath;
    const char16_t* cbg_arg1 = dstPath;
    const char16_t* cbg_arg2 = password;
    bool cbg_ret = cbg_self_->PackWithPassword(cbg_arg0,cbg_arg1,cbg_arg2);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_File_Release(void* cbg_self) {
    auto cbg_self_ = (altseed::File*)(cbg_self);

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

