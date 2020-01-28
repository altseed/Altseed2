
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

#include "Input/ButtonState.h"
#include "Input/Joystick.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"

#include "Graphics/Graphics.h"
#include "Graphics/Texture2D.h"

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

    
extern "C" {

CBGEXPORT bool CBGSTDCALL cbg_Core_Initialize(const char16_t* title, int32_t width, int32_t height, void* option) {
    const char16_t* cbg_arg0 = title;
    int32_t cbg_arg1 = width;
    int32_t cbg_arg2 = height;
    Altseed::CoreOption cbg_arg3 = (*((Altseed::CoreOption*)option));
    bool cbg_ret = Altseed::Core::Initialize(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Core_DoEvent(void* cbg_self) {
    auto cbg_self_ = (Altseed::Core*)(cbg_self);

    bool cbg_ret = cbg_self_->DoEvent();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Core_Terminate() {
    Altseed::Core::Terminate();
}

CBGEXPORT void* CBGSTDCALL cbg_Core_GetInstance() {
    std::shared_ptr<Altseed::Core> cbg_ret = Altseed::Core::GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Core>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Core_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Core*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_CopyTo(void* cbg_self, void* array, int32_t size) {
    auto cbg_self_ = (Altseed::Int8Array*)(cbg_self);

    std::shared_ptr<Altseed::Int8Array> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::Int8Array>((Altseed::Int8Array*)array);
    int32_t cbg_arg1 = size;
    cbg_self_->CopyTo(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Int8Array*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Resources_GetInstance() {
    std::shared_ptr<Altseed::Resources> cbg_ret = Altseed::Resources::GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Resources>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Resources_GetResourcesCount(void* cbg_self, int32_t type) {
    auto cbg_self_ = (Altseed::Resources*)(cbg_self);

    Altseed::ResourceType cbg_arg0 = (Altseed::ResourceType)type;
    int32_t cbg_ret = cbg_self_->GetResourcesCount(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Resources_Clear(void* cbg_self) {
    auto cbg_self_ = (Altseed::Resources*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT void CBGSTDCALL cbg_Resources_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed::Resources*)(cbg_self);

    cbg_self_->Reload();
}

CBGEXPORT void CBGSTDCALL cbg_Resources_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Resources*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT int32_t CBGSTDCALL cbg_Keyboard_GetKeyState(void* cbg_self, int32_t key) {
    auto cbg_self_ = (Altseed::Keyboard*)(cbg_self);

    Altseed::Keys cbg_arg0 = (Altseed::Keys)key;
    Altseed::ButtonState cbg_ret = cbg_self_->GetKeyState(cbg_arg0);
    return (int32_t)cbg_ret;
}

CBGEXPORT void* CBGSTDCALL cbg_Keyboard_GetInstance() {
    std::shared_ptr<Altseed::Keyboard> cbg_ret = Altseed::Keyboard::GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Keyboard>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Keyboard_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Keyboard*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Mouse_GetInstance(void* cbg_self) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    std::shared_ptr<Altseed::Mouse> cbg_ret = cbg_self_->GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Mouse>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_RefreshInputState(void* cbg_self) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    cbg_self_->RefreshInputState();
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_SetPosition(void* cbg_self, void* vec) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    Altseed::Vector2DF cbg_arg0 = (*((Altseed::Vector2DF*)vec));
    cbg_self_->SetPosition(cbg_arg0);
}

CBGEXPORT Altseed::Vector2DF CBGSTDCALL cbg_Mouse_GetPosition(void* cbg_self) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    Altseed::Vector2DF cbg_ret = cbg_self_->GetPosition();
    return (cbg_ret);
}

CBGEXPORT float CBGSTDCALL cbg_Mouse_GetWheel(void* cbg_self) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    float cbg_ret = cbg_self_->GetWheel();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_GetMouseButtonState(void* cbg_self, int32_t button) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    Altseed::MouseButtons cbg_arg0 = (Altseed::MouseButtons)button;
    cbg_self_->GetMouseButtonState(cbg_arg0);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Mouse_GetCursorMode(void* cbg_self) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    Altseed::CursorMode cbg_ret = cbg_self_->GetCursorMode();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_SetCursorMode(void* cbg_self, int32_t value) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    Altseed::CursorMode cbg_arg0 = (Altseed::CursorMode)value;
    cbg_self_->SetCursorMode(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_Joystick_IsPresent(void* cbg_self, int32_t joystickIndex) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    int32_t cbg_arg0 = joystickIndex;
    cbg_self_->IsPresent(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Joystick_RefreshInputState(void* cbg_self) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    cbg_self_->RefreshInputState();
}

CBGEXPORT void CBGSTDCALL cbg_Joystick_RefreshConnectedState(void* cbg_self) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    cbg_self_->RefreshConnectedState();
}

CBGEXPORT int32_t CBGSTDCALL cbg_Joystick_GetButtonStateByIndex(void* cbg_self, int32_t joystickIndex, int32_t buttonIndex) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    int32_t cbg_arg0 = joystickIndex;
    int32_t cbg_arg1 = buttonIndex;
    Altseed::ButtonState cbg_ret = cbg_self_->GetButtonStateByIndex(cbg_arg0, cbg_arg1);
    return (int32_t)cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Joystick_GetButtonStateByType(void* cbg_self, int32_t joystickIndex, int32_t type) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    int32_t cbg_arg0 = joystickIndex;
    Altseed::JoystickButtonType cbg_arg1 = (Altseed::JoystickButtonType)type;
    Altseed::ButtonState cbg_ret = cbg_self_->GetButtonStateByType(cbg_arg0, cbg_arg1);
    return (int32_t)cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Joystick_GetJoystickType(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    int32_t cbg_arg0 = index;
    Altseed::JoystickType cbg_ret = cbg_self_->GetJoystickType(cbg_arg0);
    return (int32_t)cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Joystick_GetAxisStateByIndex(void* cbg_self, int32_t joystickIndex, int32_t axisIndex) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    int32_t cbg_arg0 = joystickIndex;
    int32_t cbg_arg1 = axisIndex;
    float cbg_ret = cbg_self_->GetAxisStateByIndex(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Joystick_GetAxisStateByType(void* cbg_self, int32_t joystickIndex, int32_t type) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    int32_t cbg_arg0 = joystickIndex;
    Altseed::JoystickAxisType cbg_arg1 = (Altseed::JoystickAxisType)type;
    float cbg_ret = cbg_self_->GetAxisStateByType(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Joystick_GetJoystickName(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    int32_t cbg_arg0 = index;
    const char16_t* cbg_ret = cbg_self_->GetJoystickName(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Joystick_RefreshVibrateState(void* cbg_self) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    cbg_self_->RefreshVibrateState();
}

CBGEXPORT void CBGSTDCALL cbg_Joystick_SetVibration(void* cbg_self, int32_t index, float high_freq, float low_freq, float high_amp, float low_amp, int32_t life_time) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    int32_t cbg_arg0 = index;
    float cbg_arg1 = high_freq;
    float cbg_arg2 = low_freq;
    float cbg_arg3 = high_amp;
    float cbg_arg4 = low_amp;
    int32_t cbg_arg5 = life_time;
    cbg_self_->SetVibration(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5);
}

CBGEXPORT void CBGSTDCALL cbg_Joystick_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Graphics_GetInstance() {
    std::shared_ptr<Altseed::Graphics> cbg_ret = Altseed::Graphics::GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Graphics>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Graphics_BeginFrame(void* cbg_self) {
    auto cbg_self_ = (Altseed::Graphics*)(cbg_self);

    bool cbg_ret = cbg_self_->BeginFrame();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Graphics_EndFrame(void* cbg_self) {
    auto cbg_self_ = (Altseed::Graphics*)(cbg_self);

    bool cbg_ret = cbg_self_->EndFrame();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Graphics_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Graphics*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT bool CBGSTDCALL cbg_Texture2D_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed::Texture2D*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
}

CBGEXPORT Altseed::Vector2DI CBGSTDCALL cbg_Texture2D_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed::Texture2D*)(cbg_self);

    Altseed::Vector2DI cbg_ret = cbg_self_->GetSize();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Texture2D_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Texture2D*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT int32_t CBGSTDCALL cbg_StreamFile_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed::StreamFile*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetSize();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_StreamFile_GetCurrentPosition(void* cbg_self) {
    auto cbg_self_ = (Altseed::StreamFile*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCurrentPosition();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_StreamFile_Read(void* cbg_self, int32_t size) {
    auto cbg_self_ = (Altseed::StreamFile*)(cbg_self);

    int32_t cbg_arg0 = size;
    int32_t cbg_ret = cbg_self_->Read(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void* CBGSTDCALL cbg_StreamFile_GetTempBuffer(void* cbg_self) {
    auto cbg_self_ = (Altseed::StreamFile*)(cbg_self);

    std::shared_ptr<Altseed::Int8Array> cbg_ret = cbg_self_->GetTempBuffer();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Int8Array>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_StreamFile_GetTempBufferSize(void* cbg_self) {
    auto cbg_self_ = (Altseed::StreamFile*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetTempBufferSize();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_StreamFile_GetIsInPackage(void* cbg_self) {
    auto cbg_self_ = (Altseed::StreamFile*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsInPackage();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_StreamFile_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed::StreamFile*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_StreamFile_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::StreamFile*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_StaticFile_GetBuffer(void* cbg_self) {
    auto cbg_self_ = (Altseed::StaticFile*)(cbg_self);

    std::shared_ptr<Altseed::Int8Array> cbg_ret = cbg_self_->GetBuffer();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Int8Array>(cbg_ret);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_StaticFile_GetPath(void* cbg_self) {
    auto cbg_self_ = (Altseed::StaticFile*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetPath();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_StaticFile_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed::StaticFile*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetSize();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_StaticFile_GetIsInPackage(void* cbg_self) {
    auto cbg_self_ = (Altseed::StaticFile*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsInPackage();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_StaticFile_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed::StaticFile*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_StaticFile_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::StaticFile*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_File_GetInstance() {
    std::shared_ptr<Altseed::File> cbg_ret = Altseed::File::GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::File>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_File_CreateStaticFile(void* cbg_self, const char16_t* path) {
    auto cbg_self_ = (Altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    std::shared_ptr<Altseed::StaticFile> cbg_ret = cbg_self_->CreateStaticFile(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::StaticFile>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_File_CreateStreamFile(void* cbg_self, const char16_t* path) {
    auto cbg_self_ = (Altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    std::shared_ptr<Altseed::StreamFile> cbg_ret = cbg_self_->CreateStreamFile(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::StreamFile>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_File_AddRootDirectory(void* cbg_self, const char16_t* path) {
    auto cbg_self_ = (Altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    bool cbg_ret = cbg_self_->AddRootDirectory(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_File_AddRootPackageWithPassword(void* cbg_self, const char16_t* path, const char16_t* password) {
    auto cbg_self_ = (Altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    const char16_t* cbg_arg1 = password;
    bool cbg_ret = cbg_self_->AddRootPackageWithPassword(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_File_AddRootPackage(void* cbg_self, const char16_t* path) {
    auto cbg_self_ = (Altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    bool cbg_ret = cbg_self_->AddRootPackage(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_File_ClearRootDirectories(void* cbg_self) {
    auto cbg_self_ = (Altseed::File*)(cbg_self);

    cbg_self_->ClearRootDirectories();
}

CBGEXPORT bool CBGSTDCALL cbg_File_Exists(void* cbg_self, const char16_t* path) {
    auto cbg_self_ = (Altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    bool cbg_ret = cbg_self_->Exists(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_File_Pack(void* cbg_self, const char16_t* srcPath, const char16_t* dstPath) {
    auto cbg_self_ = (Altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = srcPath;
    const char16_t* cbg_arg1 = dstPath;
    bool cbg_ret = cbg_self_->Pack(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_File_PackWithPassword(void* cbg_self, const char16_t* srcPath, const char16_t* dstPath, const char16_t* password) {
    auto cbg_self_ = (Altseed::File*)(cbg_self);

    const char16_t* cbg_arg0 = srcPath;
    const char16_t* cbg_arg1 = dstPath;
    const char16_t* cbg_arg2 = password;
    bool cbg_ret = cbg_self_->PackWithPassword(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_File_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::File*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_Easing_GetEasing(int32_t easing,float t) {
    Altseed::EasingType cbg_arg0 = (Altseed::EasingType)easing;
    float cbg_arg1 = t;
    Altseed::Easing::GetEasing(cbg_arg0,cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Easing_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Easing*)(cbg_self);

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

