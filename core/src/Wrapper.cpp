
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
#include "Graphics/Renderer/RenderedCamera.h"

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

    
extern "C" {

CBGEXPORT void CBGSTDCALL cbg_Easing_GetEasing(int32_t easing, float t) {
    Altseed::EasingType cbg_arg0 = (Altseed::EasingType)easing;
    float cbg_arg1 = t;
    Altseed::Easing::GetEasing(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Easing_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Easing*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Configuration_Constructor_0() {
    return new Altseed::Configuration();
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetIsFullscreenMode(void* cbg_self) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsFullscreenMode();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetIsFullscreenMode(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetIsFullscreenMode(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetIsResizable(void* cbg_self) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsResizable();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetIsResizable(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetIsResizable(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetEnabledConsoleLogging(void* cbg_self) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetEnabledConsoleLogging();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetEnabledConsoleLogging(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetEnabledConsoleLogging(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetEnabledFileLogging(void* cbg_self) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetEnabledFileLogging();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetEnabledFileLogging(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetEnabledFileLogging(cbg_arg0);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Configuration_GetLogFilename(void* cbg_self) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetLogFilename();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetLogFilename(void* cbg_self, const char16_t* value) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    const char16_t* cbg_arg0 = value;
    cbg_self_->SetLogFilename(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT bool CBGSTDCALL cbg_Core_Initialize(const char16_t* title, int32_t width, int32_t height, void* config) {
    const char16_t* cbg_arg0 = title;
    int32_t cbg_arg1 = width;
    int32_t cbg_arg2 = height;
    std::shared_ptr<Altseed::Configuration> cbg_arg3 = Altseed::CreateAndAddSharedPtr<Altseed::Configuration>((Altseed::Configuration*)config);
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

CBGEXPORT void CBGSTDCALL cbg_Int32Array_CopyTo(void* cbg_self, void* array, int32_t size) {
    auto cbg_self_ = (Altseed::Int32Array*)(cbg_self);

    std::shared_ptr<Altseed::Int32Array> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::Int32Array>((Altseed::Int32Array*)array);
    int32_t cbg_arg1 = size;
    cbg_self_->CopyTo(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Int32Array*)(cbg_self);

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

CBGEXPORT void* CBGSTDCALL cbg_Mouse_GetInstance() {
    std::shared_ptr<Altseed::Mouse> cbg_ret = Altseed::Mouse::GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Mouse>(cbg_ret);
}

CBGEXPORT float CBGSTDCALL cbg_Mouse_GetWheel(void* cbg_self) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    float cbg_ret = cbg_self_->GetWheel();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Mouse_GetMouseButtonState(void* cbg_self, int32_t button) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    Altseed::MouseButtons cbg_arg0 = (Altseed::MouseButtons)button;
    Altseed::ButtonState cbg_ret = cbg_self_->GetMouseButtonState(cbg_arg0);
    return (int32_t)cbg_ret;
}

CBGEXPORT Altseed::Vector2F CBGSTDCALL cbg_Mouse_GetPosition(void* cbg_self) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    Altseed::Vector2F cbg_ret = cbg_self_->GetPosition();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_SetPosition(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    Altseed::Vector2F cbg_arg0 = (*((Altseed::Vector2F*)value));
    cbg_self_->SetPosition(cbg_arg0);
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

CBGEXPORT bool CBGSTDCALL cbg_Joystick_IsPresent(void* cbg_self, int32_t joystickIndex) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    int32_t cbg_arg0 = joystickIndex;
    bool cbg_ret = cbg_self_->IsPresent(cbg_arg0);
    return cbg_ret;
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

CBGEXPORT bool CBGSTDCALL cbg_Graphics_DoEvents(void* cbg_self) {
    auto cbg_self_ = (Altseed::Graphics*)(cbg_self);

    bool cbg_ret = cbg_self_->DoEvents();
    return cbg_ret;
}

CBGEXPORT void* CBGSTDCALL cbg_Graphics_GetCommandList(void* cbg_self) {
    auto cbg_self_ = (Altseed::Graphics*)(cbg_self);

    std::shared_ptr<Altseed::CommandList> cbg_ret = cbg_self_->GetCommandList();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::CommandList>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Graphics_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Graphics*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Texture2D_Load(const char16_t* path) {
    const char16_t* cbg_arg0 = path;
    std::shared_ptr<Altseed::Texture2D> cbg_ret = Altseed::Texture2D::Load(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Texture2D>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Texture2D_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed::Texture2D*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
}

CBGEXPORT Altseed::Vector2I CBGSTDCALL cbg_Texture2D_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed::Texture2D*)(cbg_self);

    Altseed::Vector2I cbg_ret = cbg_self_->GetSize();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Texture2D_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Texture2D*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Renderer_GetInstance() {
    std::shared_ptr<Altseed::Renderer> cbg_ret = Altseed::Renderer::GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Renderer>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_DrawSprite(void* cbg_self, void* sprite) {
    auto cbg_self_ = (Altseed::Renderer*)(cbg_self);

    std::shared_ptr<Altseed::RenderedSprite> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::RenderedSprite>((Altseed::RenderedSprite*)sprite);
    cbg_self_->DrawSprite(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_Render(void* cbg_self, void* commandList) {
    auto cbg_self_ = (Altseed::Renderer*)(cbg_self);

    std::shared_ptr<Altseed::CommandList> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::CommandList>((Altseed::CommandList*)commandList);
    cbg_self_->Render(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Renderer*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_SetRenderTargetWithScreen(void* cbg_self) {
    auto cbg_self_ = (Altseed::CommandList*)(cbg_self);

    cbg_self_->SetRenderTargetWithScreen();
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::CommandList*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_Rendered_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Rendered*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedSprite_Create() {
    std::shared_ptr<Altseed::RenderedSprite> cbg_ret = Altseed::RenderedSprite::Create();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::RenderedSprite>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedSprite_GetTexture(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedSprite*)(cbg_self);

    std::shared_ptr<Altseed::Texture2D> cbg_ret = cbg_self_->GetTexture();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Texture2D>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_SetTexture(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed::RenderedSprite*)(cbg_self);

    std::shared_ptr<Altseed::Texture2D> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::Texture2D>((Altseed::Texture2D*)value);
    cbg_self_->SetTexture(cbg_arg0);
}

CBGEXPORT Altseed::RectF CBGSTDCALL cbg_RenderedSprite_GetSrc(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedSprite*)(cbg_self);

    Altseed::RectF cbg_ret = cbg_self_->GetSrc();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_SetSrc(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed::RenderedSprite*)(cbg_self);

    Altseed::RectF cbg_arg0 = (*((Altseed::RectF*)value));
    cbg_self_->SetSrc(cbg_arg0);
}

CBGEXPORT Altseed::Matrix44F CBGSTDCALL cbg_RenderedSprite_GetTransform(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedSprite*)(cbg_self);

    Altseed::Matrix44F cbg_ret = cbg_self_->GetTransform();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_SetTransform(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed::RenderedSprite*)(cbg_self);

    Altseed::Matrix44F cbg_arg0 = (*((Altseed::Matrix44F*)value));
    cbg_self_->SetTransform(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedSprite*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_RenderedCamera_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedCamera*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_StreamFile_Create(const char16_t* path) {
    const char16_t* cbg_arg0 = path;
    std::shared_ptr<Altseed::StreamFile> cbg_ret = Altseed::StreamFile::Create(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::StreamFile>(cbg_ret);
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

CBGEXPORT bool CBGSTDCALL cbg_StreamFile_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed::StreamFile*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
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

CBGEXPORT void CBGSTDCALL cbg_StreamFile_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::StreamFile*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_StaticFile_Create(const char16_t* path) {
    const char16_t* cbg_arg0 = path;
    std::shared_ptr<Altseed::StaticFile> cbg_ret = Altseed::StaticFile::Create(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::StaticFile>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_StaticFile_GetBuffer(void* cbg_self) {
    auto cbg_self_ = (Altseed::StaticFile*)(cbg_self);

    std::shared_ptr<Altseed::Int8Array> cbg_ret = cbg_self_->GetBuffer();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Int8Array>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_StaticFile_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed::StaticFile*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
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

CBGEXPORT void CBGSTDCALL cbg_StaticFile_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::StaticFile*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_File_GetInstance() {
    std::shared_ptr<Altseed::File> cbg_ret = Altseed::File::GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::File>(cbg_ret);
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

CBGEXPORT float CBGSTDCALL cbg_Sound_GetLoopStartingPoint(void* cbg_self) {
    auto cbg_self_ = (Altseed::Sound*)(cbg_self);

    float cbg_ret = cbg_self_->GetLoopStartingPoint();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Sound_SetLoopStartingPoint(void* cbg_self, float value) {
    auto cbg_self_ = (Altseed::Sound*)(cbg_self);

    float cbg_arg0 = value;
    cbg_self_->SetLoopStartingPoint(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_Sound_GetLoopEndPoint(void* cbg_self) {
    auto cbg_self_ = (Altseed::Sound*)(cbg_self);

    float cbg_ret = cbg_self_->GetLoopEndPoint();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Sound_SetLoopEndPoint(void* cbg_self, float value) {
    auto cbg_self_ = (Altseed::Sound*)(cbg_self);

    float cbg_arg0 = value;
    cbg_self_->SetLoopEndPoint(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Sound_GetIsLoopingMode(void* cbg_self) {
    auto cbg_self_ = (Altseed::Sound*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsLoopingMode();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Sound_SetIsLoopingMode(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed::Sound*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetIsLoopingMode(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_Sound_GetLength(void* cbg_self) {
    auto cbg_self_ = (Altseed::Sound*)(cbg_self);

    float cbg_ret = cbg_self_->GetLength();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Sound_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Sound*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_SoundMixer_GetInstance() {
    std::shared_ptr<Altseed::SoundMixer> cbg_ret = Altseed::SoundMixer::GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::SoundMixer>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_SoundMixer_Load(void* cbg_self, const char16_t* path, bool isDecompressed) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    bool cbg_arg1 = isDecompressed;
    std::shared_ptr<Altseed::Sound> cbg_ret = cbg_self_->Load(cbg_arg0, cbg_arg1);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Sound>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_SoundMixer_Play(void* cbg_self, void* sound) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    std::shared_ptr<Altseed::Sound> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::Sound>((Altseed::Sound*)sound);
    int32_t cbg_ret = cbg_self_->Play(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_SoundMixer_GetIsPlaying(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    bool cbg_ret = cbg_self_->GetIsPlaying(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_StopAll(void* cbg_self) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    cbg_self_->StopAll();
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_Stop(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    cbg_self_->Stop(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_Pause(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    cbg_self_->Pause(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_Resume(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    cbg_self_->Resume(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_Seek(void* cbg_self, int32_t id, float position) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = position;
    cbg_self_->Seek(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_SetVolume(void* cbg_self, int32_t id, float volume) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = volume;
    cbg_self_->SetVolume(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_FadeIn(void* cbg_self, int32_t id, float second) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = second;
    cbg_self_->FadeIn(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_FadeOut(void* cbg_self, int32_t id, float second) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = second;
    cbg_self_->FadeOut(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_Fade(void* cbg_self, int32_t id, float second, float targetedVolume) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = second;
    float cbg_arg2 = targetedVolume;
    cbg_self_->Fade(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT bool CBGSTDCALL cbg_SoundMixer_GetIsPlaybackSpeedEnabled(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    bool cbg_ret = cbg_self_->GetIsPlaybackSpeedEnabled(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_SetIsPlaybackSpeedEnabled(void* cbg_self, int32_t id, bool isPlaybackSpeedEnabled) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    bool cbg_arg1 = isPlaybackSpeedEnabled;
    cbg_self_->SetIsPlaybackSpeedEnabled(cbg_arg0, cbg_arg1);
}

CBGEXPORT float CBGSTDCALL cbg_SoundMixer_GetPlaybackSpeed(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_ret = cbg_self_->GetPlaybackSpeed(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_SetPlaybackSpeed(void* cbg_self, int32_t id, float playbackSpeed) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = playbackSpeed;
    cbg_self_->SetPlaybackSpeed(cbg_arg0, cbg_arg1);
}

CBGEXPORT float CBGSTDCALL cbg_SoundMixer_GetPanningPosition(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_ret = cbg_self_->GetPanningPosition(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_SetPanningPosition(void* cbg_self, int32_t id, float panningPosition) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = panningPosition;
    cbg_self_->SetPanningPosition(cbg_arg0, cbg_arg1);
}

CBGEXPORT float CBGSTDCALL cbg_SoundMixer_GetPlaybackPercent(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_ret = cbg_self_->GetPlaybackPercent(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Log_GetInstance() {
    std::shared_ptr<Altseed::Log> cbg_ret = Altseed::Log::GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Log>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Write(void* cbg_self, int32_t category, int32_t level, const char16_t* message) {
    auto cbg_self_ = (Altseed::Log*)(cbg_self);

    Altseed::LogCategory cbg_arg0 = (Altseed::LogCategory)category;
    Altseed::LogLevel cbg_arg1 = (Altseed::LogLevel)level;
    const char16_t* cbg_arg2 = message;
    cbg_self_->Write(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Trace(void* cbg_self, int32_t category, const char16_t* message) {
    auto cbg_self_ = (Altseed::Log*)(cbg_self);

    Altseed::LogCategory cbg_arg0 = (Altseed::LogCategory)category;
    const char16_t* cbg_arg1 = message;
    cbg_self_->Trace(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Debug(void* cbg_self, int32_t category, const char16_t* message) {
    auto cbg_self_ = (Altseed::Log*)(cbg_self);

    Altseed::LogCategory cbg_arg0 = (Altseed::LogCategory)category;
    const char16_t* cbg_arg1 = message;
    cbg_self_->Debug(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Info(void* cbg_self, int32_t category, const char16_t* message) {
    auto cbg_self_ = (Altseed::Log*)(cbg_self);

    Altseed::LogCategory cbg_arg0 = (Altseed::LogCategory)category;
    const char16_t* cbg_arg1 = message;
    cbg_self_->Info(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Warn(void* cbg_self, int32_t category, const char16_t* message) {
    auto cbg_self_ = (Altseed::Log*)(cbg_self);

    Altseed::LogCategory cbg_arg0 = (Altseed::LogCategory)category;
    const char16_t* cbg_arg1 = message;
    cbg_self_->Warn(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Error(void* cbg_self, int32_t category, const char16_t* message) {
    auto cbg_self_ = (Altseed::Log*)(cbg_self);

    Altseed::LogCategory cbg_arg0 = (Altseed::LogCategory)category;
    const char16_t* cbg_arg1 = message;
    cbg_self_->Error(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Critical(void* cbg_self, int32_t category, const char16_t* message) {
    auto cbg_self_ = (Altseed::Log*)(cbg_self);

    Altseed::LogCategory cbg_arg0 = (Altseed::LogCategory)category;
    const char16_t* cbg_arg1 = message;
    cbg_self_->Critical(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_SetLevel(void* cbg_self, int32_t category, int32_t level) {
    auto cbg_self_ = (Altseed::Log*)(cbg_self);

    Altseed::LogCategory cbg_arg0 = (Altseed::LogCategory)category;
    Altseed::LogLevel cbg_arg1 = (Altseed::LogLevel)level;
    cbg_self_->SetLevel(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Log*)(cbg_self);

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

