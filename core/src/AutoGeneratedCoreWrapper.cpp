// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//   このファイルは自動生成されました。
//   このファイルへの変更は消失することがあります。
//
//   THIS FILE IS AUTO GENERATED.
//   YOUR COMMITMENT ON THIS FILE WILL BE WIPED. 
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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
#include "Graphics/RenderTexture.h"
#include "Graphics/Font.h"
#include "Graphics/ImageFont.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/RenderedText.h"
#include "Graphics/Renderer/RenderedPolygon.h"
#include "Graphics/Renderer/RenderedCamera.h"
#include "Graphics/BuiltinShader.h"

#include "Tool/Tool.h"

#include "IO/File.h"
#include "IO/PackFile.h"
#include "IO/StaticFile.h"
#include "IO/StreamFile.h"
#include "IO/FileRoot.h"
#include "IO/BaseFileReader.h"
#include "IO/PackFileReader.h"

#include "Sound/Sound.h"
#include "Sound/SoundMixer.h"

#include "Logger/Log.h"

    
extern "C" {

CBGEXPORT void* CBGSTDCALL cbg_Configuration_Constructor_0() {
    return new Altseed::Configuration();
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetIsFullscreen(void* cbg_self) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsFullscreen();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetIsFullscreen(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetIsFullscreen(cbg_arg0);
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

CBGEXPORT int32_t CBGSTDCALL cbg_Configuration_GetDeviceType(void* cbg_self) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    Altseed::GraphicsDeviceType cbg_ret = cbg_self_->GetDeviceType();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetDeviceType(void* cbg_self, int32_t value) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    Altseed::GraphicsDeviceType cbg_arg0 = (Altseed::GraphicsDeviceType)value;
    cbg_self_->SetDeviceType(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetWaitVSync(void* cbg_self) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetWaitVSync();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetWaitVSync(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetWaitVSync(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetConsoleLoggingEnabled(void* cbg_self) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetConsoleLoggingEnabled();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetConsoleLoggingEnabled(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetConsoleLoggingEnabled(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetFileLoggingEnabled(void* cbg_self) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetFileLoggingEnabled();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetFileLoggingEnabled(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetFileLoggingEnabled(cbg_arg0);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Configuration_GetLogFileName(void* cbg_self) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetLogFileName();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetLogFileName(void* cbg_self, const char16_t* value) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    const char16_t* cbg_arg0 = value;
    cbg_self_->SetLogFileName(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetToolEnabled(void* cbg_self) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetToolEnabled();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetToolEnabled(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetToolEnabled(cbg_arg0);
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

CBGEXPORT float CBGSTDCALL cbg_Core_GetDeltaSecond(void* cbg_self) {
    auto cbg_self_ = (Altseed::Core*)(cbg_self);

    float cbg_ret = cbg_self_->GetDeltaSecond();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Core_GetCurrentFPS(void* cbg_self) {
    auto cbg_self_ = (Altseed::Core*)(cbg_self);

    float cbg_ret = cbg_self_->GetCurrentFPS();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Core_GetTargetFPS(void* cbg_self) {
    auto cbg_self_ = (Altseed::Core*)(cbg_self);

    float cbg_ret = cbg_self_->GetTargetFPS();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Core_SetTargetFPS(void* cbg_self, float value) {
    auto cbg_self_ = (Altseed::Core*)(cbg_self);

    float cbg_arg0 = value;
    cbg_self_->SetTargetFPS(cbg_arg0);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Core_GetFramerateMode(void* cbg_self) {
    auto cbg_self_ = (Altseed::Core*)(cbg_self);

    Altseed::FramerateMode cbg_ret = cbg_self_->GetFramerateMode();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Core_SetFramerateMode(void* cbg_self, int32_t value) {
    auto cbg_self_ = (Altseed::Core*)(cbg_self);

    Altseed::FramerateMode cbg_arg0 = (Altseed::FramerateMode)value;
    cbg_self_->SetFramerateMode(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Core_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Core*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_Clear(void* cbg_self) {
    auto cbg_self_ = (Altseed::Int8Array*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_Resize(void* cbg_self, int32_t size) {
    auto cbg_self_ = (Altseed::Int8Array*)(cbg_self);

    int32_t cbg_arg0 = size;
    cbg_self_->Resize(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_Int8Array_GetData(void* cbg_self) {
    auto cbg_self_ = (Altseed::Int8Array*)(cbg_self);

    void* cbg_ret = cbg_self_->GetData();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_Assign(void* cbg_self, void* ptr, int32_t size) {
    auto cbg_self_ = (Altseed::Int8Array*)(cbg_self);

    void* cbg_arg0 = ptr;
    int32_t cbg_arg1 = size;
    cbg_self_->Assign(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_CopyTo(void* cbg_self, void* ptr) {
    auto cbg_self_ = (Altseed::Int8Array*)(cbg_self);

    void* cbg_arg0 = ptr;
    cbg_self_->CopyTo(cbg_arg0);
}

CBGEXPORT int8_t CBGSTDCALL cbg_Int8Array_GetAt(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed::Int8Array*)(cbg_self);

    int32_t cbg_arg0 = index;
    int8_t cbg_ret = cbg_self_->GetAt(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_SetAt(void* cbg_self, int32_t index, int8_t value) {
    auto cbg_self_ = (Altseed::Int8Array*)(cbg_self);

    int32_t cbg_arg0 = index;
    int8_t cbg_arg1 = value;
    cbg_self_->SetAt(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_Int8Array_Create(int32_t size) {
    int32_t cbg_arg0 = size;
    std::shared_ptr<Altseed::Int8Array> cbg_ret = Altseed::Int8Array::Create(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Int8Array>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Int8Array_GetCount(void* cbg_self) {
    auto cbg_self_ = (Altseed::Int8Array*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCount();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Int8Array*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_Clear(void* cbg_self) {
    auto cbg_self_ = (Altseed::Int32Array*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_Resize(void* cbg_self, int32_t size) {
    auto cbg_self_ = (Altseed::Int32Array*)(cbg_self);

    int32_t cbg_arg0 = size;
    cbg_self_->Resize(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_Int32Array_GetData(void* cbg_self) {
    auto cbg_self_ = (Altseed::Int32Array*)(cbg_self);

    void* cbg_ret = cbg_self_->GetData();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_Assign(void* cbg_self, void* ptr, int32_t size) {
    auto cbg_self_ = (Altseed::Int32Array*)(cbg_self);

    void* cbg_arg0 = ptr;
    int32_t cbg_arg1 = size;
    cbg_self_->Assign(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_CopyTo(void* cbg_self, void* ptr) {
    auto cbg_self_ = (Altseed::Int32Array*)(cbg_self);

    void* cbg_arg0 = ptr;
    cbg_self_->CopyTo(cbg_arg0);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Int32Array_GetAt(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed::Int32Array*)(cbg_self);

    int32_t cbg_arg0 = index;
    int32_t cbg_ret = cbg_self_->GetAt(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_SetAt(void* cbg_self, int32_t index, int32_t value) {
    auto cbg_self_ = (Altseed::Int32Array*)(cbg_self);

    int32_t cbg_arg0 = index;
    int32_t cbg_arg1 = value;
    cbg_self_->SetAt(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_Int32Array_Create(int32_t size) {
    int32_t cbg_arg0 = size;
    std::shared_ptr<Altseed::Int32Array> cbg_ret = Altseed::Int32Array::Create(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Int32Array>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Int32Array_GetCount(void* cbg_self) {
    auto cbg_self_ = (Altseed::Int32Array*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCount();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Int32Array*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_VertexArray_Clear(void* cbg_self) {
    auto cbg_self_ = (Altseed::VertexArray*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT void CBGSTDCALL cbg_VertexArray_Resize(void* cbg_self, int32_t size) {
    auto cbg_self_ = (Altseed::VertexArray*)(cbg_self);

    int32_t cbg_arg0 = size;
    cbg_self_->Resize(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_VertexArray_GetData(void* cbg_self) {
    auto cbg_self_ = (Altseed::VertexArray*)(cbg_self);

    void* cbg_ret = cbg_self_->GetData();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_VertexArray_Assign(void* cbg_self, void* ptr, int32_t size) {
    auto cbg_self_ = (Altseed::VertexArray*)(cbg_self);

    void* cbg_arg0 = ptr;
    int32_t cbg_arg1 = size;
    cbg_self_->Assign(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_VertexArray_CopyTo(void* cbg_self, void* ptr) {
    auto cbg_self_ = (Altseed::VertexArray*)(cbg_self);

    void* cbg_arg0 = ptr;
    cbg_self_->CopyTo(cbg_arg0);
}

CBGEXPORT Altseed::BatchVertex CBGSTDCALL cbg_VertexArray_GetAt(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed::VertexArray*)(cbg_self);

    int32_t cbg_arg0 = index;
    Altseed::BatchVertex cbg_ret = cbg_self_->GetAt(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_VertexArray_SetAt(void* cbg_self, int32_t index, Altseed::BatchVertex value) {
    auto cbg_self_ = (Altseed::VertexArray*)(cbg_self);

    int32_t cbg_arg0 = index;
    Altseed::BatchVertex cbg_arg1 = value;
    cbg_self_->SetAt(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_VertexArray_Create(int32_t size) {
    int32_t cbg_arg0 = size;
    std::shared_ptr<Altseed::VertexArray> cbg_ret = Altseed::VertexArray::Create(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::VertexArray>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_VertexArray_GetCount(void* cbg_self) {
    auto cbg_self_ = (Altseed::VertexArray*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCount();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_VertexArray_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::VertexArray*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_FloatArray_Clear(void* cbg_self) {
    auto cbg_self_ = (Altseed::FloatArray*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT void CBGSTDCALL cbg_FloatArray_Resize(void* cbg_self, int32_t size) {
    auto cbg_self_ = (Altseed::FloatArray*)(cbg_self);

    int32_t cbg_arg0 = size;
    cbg_self_->Resize(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_FloatArray_GetData(void* cbg_self) {
    auto cbg_self_ = (Altseed::FloatArray*)(cbg_self);

    void* cbg_ret = cbg_self_->GetData();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_FloatArray_Assign(void* cbg_self, void* ptr, int32_t size) {
    auto cbg_self_ = (Altseed::FloatArray*)(cbg_self);

    void* cbg_arg0 = ptr;
    int32_t cbg_arg1 = size;
    cbg_self_->Assign(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_FloatArray_CopyTo(void* cbg_self, void* ptr) {
    auto cbg_self_ = (Altseed::FloatArray*)(cbg_self);

    void* cbg_arg0 = ptr;
    cbg_self_->CopyTo(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_FloatArray_GetAt(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed::FloatArray*)(cbg_self);

    int32_t cbg_arg0 = index;
    float cbg_ret = cbg_self_->GetAt(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_FloatArray_SetAt(void* cbg_self, int32_t index, float value) {
    auto cbg_self_ = (Altseed::FloatArray*)(cbg_self);

    int32_t cbg_arg0 = index;
    float cbg_arg1 = value;
    cbg_self_->SetAt(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_FloatArray_Create(int32_t size) {
    int32_t cbg_arg0 = size;
    std::shared_ptr<Altseed::FloatArray> cbg_ret = Altseed::FloatArray::Create(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::FloatArray>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_FloatArray_GetCount(void* cbg_self) {
    auto cbg_self_ = (Altseed::FloatArray*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCount();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_FloatArray_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::FloatArray*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_Vector2FArray_Clear(void* cbg_self) {
    auto cbg_self_ = (Altseed::Vector2FArray*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT void CBGSTDCALL cbg_Vector2FArray_Resize(void* cbg_self, int32_t size) {
    auto cbg_self_ = (Altseed::Vector2FArray*)(cbg_self);

    int32_t cbg_arg0 = size;
    cbg_self_->Resize(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_Vector2FArray_GetData(void* cbg_self) {
    auto cbg_self_ = (Altseed::Vector2FArray*)(cbg_self);

    void* cbg_ret = cbg_self_->GetData();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Vector2FArray_Assign(void* cbg_self, void* ptr, int32_t size) {
    auto cbg_self_ = (Altseed::Vector2FArray*)(cbg_self);

    void* cbg_arg0 = ptr;
    int32_t cbg_arg1 = size;
    cbg_self_->Assign(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Vector2FArray_CopyTo(void* cbg_self, void* ptr) {
    auto cbg_self_ = (Altseed::Vector2FArray*)(cbg_self);

    void* cbg_arg0 = ptr;
    cbg_self_->CopyTo(cbg_arg0);
}

CBGEXPORT Altseed::Vector2F_C CBGSTDCALL cbg_Vector2FArray_GetAt(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed::Vector2FArray*)(cbg_self);

    int32_t cbg_arg0 = index;
    Altseed::Vector2F_C cbg_ret = cbg_self_->GetAt(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Vector2FArray_SetAt(void* cbg_self, int32_t index, Altseed::Vector2F_C value) {
    auto cbg_self_ = (Altseed::Vector2FArray*)(cbg_self);

    int32_t cbg_arg0 = index;
    Altseed::Vector2F_C cbg_arg1 = value;
    cbg_self_->SetAt(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_Vector2FArray_Create(int32_t size) {
    int32_t cbg_arg0 = size;
    std::shared_ptr<Altseed::Vector2FArray> cbg_ret = Altseed::Vector2FArray::Create(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Vector2FArray>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Vector2FArray_GetCount(void* cbg_self) {
    auto cbg_self_ = (Altseed::Vector2FArray*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCount();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Vector2FArray_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Vector2FArray*)(cbg_self);

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

CBGEXPORT int32_t CBGSTDCALL cbg_Mouse_GetMouseButtonState(void* cbg_self, int32_t button) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    Altseed::MouseButtons cbg_arg0 = (Altseed::MouseButtons)button;
    Altseed::ButtonState cbg_ret = cbg_self_->GetMouseButtonState(cbg_arg0);
    return (int32_t)cbg_ret;
}

CBGEXPORT Altseed::Vector2F_C CBGSTDCALL cbg_Mouse_GetPosition(void* cbg_self) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    Altseed::Vector2F_C cbg_ret = cbg_self_->GetPosition();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_SetPosition(void* cbg_self, Altseed::Vector2F_C value) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    Altseed::Vector2F_C cbg_arg0 = value;
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

CBGEXPORT float CBGSTDCALL cbg_Mouse_GetWheel(void* cbg_self) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    float cbg_ret = cbg_self_->GetWheel();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Mouse*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Joystick_GetInstance() {
    std::shared_ptr<Altseed::Joystick> cbg_ret = Altseed::Joystick::GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Joystick>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Joystick_IsPresent(void* cbg_self, int32_t joystickIndex) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    int32_t cbg_arg0 = joystickIndex;
    bool cbg_ret = cbg_self_->IsPresent(cbg_arg0);
    return cbg_ret;
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

CBGEXPORT void CBGSTDCALL cbg_Joystick_Vibrate(void* cbg_self, int32_t index, float frequency, float amplitude) {
    auto cbg_self_ = (Altseed::Joystick*)(cbg_self);

    int32_t cbg_arg0 = index;
    float cbg_arg1 = frequency;
    float cbg_arg2 = amplitude;
    cbg_self_->Vibrate(cbg_arg0, cbg_arg1, cbg_arg2);
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

CBGEXPORT void* CBGSTDCALL cbg_Graphics_GetBuiltinShader(void* cbg_self) {
    auto cbg_self_ = (Altseed::Graphics*)(cbg_self);

    std::shared_ptr<Altseed::BuiltinShader> cbg_ret = cbg_self_->GetBuiltinShader();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::BuiltinShader>(cbg_ret);
}

CBGEXPORT Altseed::Color_C CBGSTDCALL cbg_Graphics_GetClearColor(void* cbg_self) {
    auto cbg_self_ = (Altseed::Graphics*)(cbg_self);

    Altseed::Color_C cbg_ret = cbg_self_->GetClearColor();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Graphics_SetClearColor(void* cbg_self, Altseed::Color_C value) {
    auto cbg_self_ = (Altseed::Graphics*)(cbg_self);

    Altseed::Color_C cbg_arg0 = value;
    cbg_self_->SetClearColor(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Graphics_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Graphics*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT bool CBGSTDCALL cbg_TextureBase_Save(void* cbg_self, const char16_t* path) {
    auto cbg_self_ = (Altseed::TextureBase*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    bool cbg_ret = cbg_self_->Save(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT Altseed::Vector2I_C CBGSTDCALL cbg_TextureBase_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed::TextureBase*)(cbg_self);

    Altseed::Vector2I_C cbg_ret = cbg_self_->GetSize();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_TextureBase_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::TextureBase*)(cbg_self);

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

CBGEXPORT const char16_t* CBGSTDCALL cbg_Texture2D_GetPath(void* cbg_self) {
    auto cbg_self_ = (Altseed::Texture2D*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetPath();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Texture2D_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Texture2D*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_RenderTexture_Create(Altseed::Vector2I_C size) {
    Altseed::Vector2I_C cbg_arg0 = size;
    std::shared_ptr<Altseed::RenderTexture> cbg_ret = Altseed::RenderTexture::Create(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::RenderTexture>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderTexture_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderTexture*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Material_Constructor_0() {
    return new Altseed::Material();
}

CBGEXPORT Altseed::Vector4F_C CBGSTDCALL cbg_Material_GetVector4F(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed::Material*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed::Vector4F_C cbg_ret = cbg_self_->GetVector4F(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Material_SetVector4F(void* cbg_self, const char16_t* key, Altseed::Vector4F_C value) {
    auto cbg_self_ = (Altseed::Material*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed::Vector4F_C cbg_arg1 = value;
    cbg_self_->SetVector4F(cbg_arg0, cbg_arg1);
}

CBGEXPORT Altseed::Matrix44F_C CBGSTDCALL cbg_Material_GetMatrix44F(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed::Material*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed::Matrix44F_C cbg_ret = cbg_self_->GetMatrix44F(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Material_SetMatrix44F(void* cbg_self, const char16_t* key, Altseed::Matrix44F_C value) {
    auto cbg_self_ = (Altseed::Material*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed::Matrix44F_C cbg_arg1 = value;
    cbg_self_->SetMatrix44F(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_Material_GetTexture(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed::Material*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    std::shared_ptr<Altseed::TextureBase> cbg_ret = cbg_self_->GetTexture(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::TextureBase>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Material_SetTexture(void* cbg_self, const char16_t* key, void* value) {
    auto cbg_self_ = (Altseed::Material*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    std::shared_ptr<Altseed::TextureBase> cbg_arg1 = Altseed::CreateAndAddSharedPtr<Altseed::TextureBase>((Altseed::TextureBase*)value);
    cbg_self_->SetTexture(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_Material_GetShader(void* cbg_self, int32_t shaderStage) {
    auto cbg_self_ = (Altseed::Material*)(cbg_self);

    Altseed::ShaderStageType cbg_arg0 = (Altseed::ShaderStageType)shaderStage;
    std::shared_ptr<Altseed::Shader> cbg_ret = cbg_self_->GetShader(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Shader>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Material_SetShader(void* cbg_self, void* shader) {
    auto cbg_self_ = (Altseed::Material*)(cbg_self);

    std::shared_ptr<Altseed::Shader> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::Shader>((Altseed::Shader*)shader);
    cbg_self_->SetShader(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Material_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Material*)(cbg_self);

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

CBGEXPORT void CBGSTDCALL cbg_Renderer_DrawText(void* cbg_self, void* text) {
    auto cbg_self_ = (Altseed::Renderer*)(cbg_self);

    std::shared_ptr<Altseed::RenderedText> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::RenderedText>((Altseed::RenderedText*)text);
    cbg_self_->DrawText(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_DrawPolygon(void* cbg_self, void* polygon) {
    auto cbg_self_ = (Altseed::Renderer*)(cbg_self);

    std::shared_ptr<Altseed::RenderedPolygon> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::RenderedPolygon>((Altseed::RenderedPolygon*)polygon);
    cbg_self_->DrawPolygon(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_Render(void* cbg_self) {
    auto cbg_self_ = (Altseed::Renderer*)(cbg_self);

    cbg_self_->Render();
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_SetCamera(void* cbg_self, void* commandList) {
    auto cbg_self_ = (Altseed::Renderer*)(cbg_self);

    std::shared_ptr<Altseed::RenderedCamera> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::RenderedCamera>((Altseed::RenderedCamera*)commandList);
    cbg_self_->SetCamera(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_ResetCamera(void* cbg_self) {
    auto cbg_self_ = (Altseed::Renderer*)(cbg_self);

    cbg_self_->ResetCamera();
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Renderer*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_SetRenderTargetWithScreen(void* cbg_self) {
    auto cbg_self_ = (Altseed::CommandList*)(cbg_self);

    cbg_self_->SetRenderTargetWithScreen();
}

CBGEXPORT void* CBGSTDCALL cbg_CommandList_GetScreenTexture(void* cbg_self) {
    auto cbg_self_ = (Altseed::CommandList*)(cbg_self);

    std::shared_ptr<Altseed::RenderTexture> cbg_ret = cbg_self_->GetScreenTexture();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::RenderTexture>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_SetRenderTarget(void* cbg_self, void* target, Altseed::RenderPassParameter_C renderPassParameter) {
    auto cbg_self_ = (Altseed::CommandList*)(cbg_self);

    std::shared_ptr<Altseed::RenderTexture> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::RenderTexture>((Altseed::RenderTexture*)target);
    Altseed::RenderPassParameter_C cbg_arg1 = renderPassParameter;
    cbg_self_->SetRenderTarget(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_RenderToRenderTarget(void* cbg_self, void* material) {
    auto cbg_self_ = (Altseed::CommandList*)(cbg_self);

    std::shared_ptr<Altseed::Material> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::Material>((Altseed::Material*)material);
    cbg_self_->RenderToRenderTarget(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::CommandList*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT Altseed::Matrix44F_C CBGSTDCALL cbg_Rendered_GetTransform(void* cbg_self) {
    auto cbg_self_ = (Altseed::Rendered*)(cbg_self);

    Altseed::Matrix44F_C cbg_ret = cbg_self_->GetTransform();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Rendered_SetTransform(void* cbg_self, Altseed::Matrix44F_C value) {
    auto cbg_self_ = (Altseed::Rendered*)(cbg_self);

    Altseed::Matrix44F_C cbg_arg0 = value;
    cbg_self_->SetTransform(cbg_arg0);
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

    std::shared_ptr<Altseed::TextureBase> cbg_ret = cbg_self_->GetTexture();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::TextureBase>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_SetTexture(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed::RenderedSprite*)(cbg_self);

    std::shared_ptr<Altseed::TextureBase> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::TextureBase>((Altseed::TextureBase*)value);
    cbg_self_->SetTexture(cbg_arg0);
}

CBGEXPORT Altseed::RectF_C CBGSTDCALL cbg_RenderedSprite_GetSrc(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedSprite*)(cbg_self);

    Altseed::RectF_C cbg_ret = cbg_self_->GetSrc();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_SetSrc(void* cbg_self, Altseed::RectF_C value) {
    auto cbg_self_ = (Altseed::RenderedSprite*)(cbg_self);

    Altseed::RectF_C cbg_arg0 = value;
    cbg_self_->SetSrc(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedSprite_GetMaterial(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedSprite*)(cbg_self);

    std::shared_ptr<Altseed::Material> cbg_ret = cbg_self_->GetMaterial();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Material>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_SetMaterial(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed::RenderedSprite*)(cbg_self);

    std::shared_ptr<Altseed::Material> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::Material>((Altseed::Material*)value);
    cbg_self_->SetMaterial(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedSprite*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedText_Create() {
    std::shared_ptr<Altseed::RenderedText> cbg_ret = Altseed::RenderedText::Create();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::RenderedText>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedText_GetMaterial(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedText*)(cbg_self);

    std::shared_ptr<Altseed::Material> cbg_ret = cbg_self_->GetMaterial();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Material>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetMaterial(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed::RenderedText*)(cbg_self);

    std::shared_ptr<Altseed::Material> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::Material>((Altseed::Material*)value);
    cbg_self_->SetMaterial(cbg_arg0);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_RenderedText_GetText(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedText*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetText();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetText(void* cbg_self, const char16_t* value) {
    auto cbg_self_ = (Altseed::RenderedText*)(cbg_self);

    const char16_t* cbg_arg0 = value;
    cbg_self_->SetText(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedText_GetFont(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedText*)(cbg_self);

    std::shared_ptr<Altseed::Font> cbg_ret = cbg_self_->GetFont();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Font>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetFont(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed::RenderedText*)(cbg_self);

    std::shared_ptr<Altseed::Font> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::Font>((Altseed::Font*)value);
    cbg_self_->SetFont(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_RenderedText_GetWeight(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedText*)(cbg_self);

    float cbg_ret = cbg_self_->GetWeight();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetWeight(void* cbg_self, float value) {
    auto cbg_self_ = (Altseed::RenderedText*)(cbg_self);

    float cbg_arg0 = value;
    cbg_self_->SetWeight(cbg_arg0);
}

CBGEXPORT Altseed::Color_C CBGSTDCALL cbg_RenderedText_GetColor(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedText*)(cbg_self);

    Altseed::Color_C cbg_ret = cbg_self_->GetColor();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetColor(void* cbg_self, Altseed::Color_C value) {
    auto cbg_self_ = (Altseed::RenderedText*)(cbg_self);

    Altseed::Color_C cbg_arg0 = value;
    cbg_self_->SetColor(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedText*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedPolygon_Create() {
    std::shared_ptr<Altseed::RenderedPolygon> cbg_ret = Altseed::RenderedPolygon::Create();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::RenderedPolygon>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_SetVertexesByVector2F(void* cbg_self, void* vertexes) {
    auto cbg_self_ = (Altseed::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed::Vector2FArray> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::Vector2FArray>((Altseed::Vector2FArray*)vertexes);
    cbg_self_->SetVertexesByVector2F(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedPolygon_GetVertexes(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed::VertexArray> cbg_ret = cbg_self_->GetVertexes();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::VertexArray>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_SetVertexes(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed::VertexArray> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::VertexArray>((Altseed::VertexArray*)value);
    cbg_self_->SetVertexes(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedPolygon_GetTexture(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed::Texture2D> cbg_ret = cbg_self_->GetTexture();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Texture2D>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_SetTexture(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed::Texture2D> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::Texture2D>((Altseed::Texture2D*)value);
    cbg_self_->SetTexture(cbg_arg0);
}

CBGEXPORT Altseed::RectF_C CBGSTDCALL cbg_RenderedPolygon_GetSrc(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedPolygon*)(cbg_self);

    Altseed::RectF_C cbg_ret = cbg_self_->GetSrc();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_SetSrc(void* cbg_self, Altseed::RectF_C value) {
    auto cbg_self_ = (Altseed::RenderedPolygon*)(cbg_self);

    Altseed::RectF_C cbg_arg0 = value;
    cbg_self_->SetSrc(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedPolygon_GetMaterial(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed::Material> cbg_ret = cbg_self_->GetMaterial();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Material>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_SetMaterial(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed::Material> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::Material>((Altseed::Material*)value);
    cbg_self_->SetMaterial(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedPolygon*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedCamera_Create() {
    std::shared_ptr<Altseed::RenderedCamera> cbg_ret = Altseed::RenderedCamera::Create();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::RenderedCamera>(cbg_ret);
}

CBGEXPORT Altseed::Vector2F_C CBGSTDCALL cbg_RenderedCamera_GetCenterOffset(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedCamera*)(cbg_self);

    Altseed::Vector2F_C cbg_ret = cbg_self_->GetCenterOffset();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedCamera_SetCenterOffset(void* cbg_self, Altseed::Vector2F_C value) {
    auto cbg_self_ = (Altseed::RenderedCamera*)(cbg_self);

    Altseed::Vector2F_C cbg_arg0 = value;
    cbg_self_->SetCenterOffset(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedCamera_GetTargetTexture(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedCamera*)(cbg_self);

    std::shared_ptr<Altseed::RenderTexture> cbg_ret = cbg_self_->GetTargetTexture();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::RenderTexture>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedCamera_SetTargetTexture(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed::RenderedCamera*)(cbg_self);

    std::shared_ptr<Altseed::RenderTexture> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::RenderTexture>((Altseed::RenderTexture*)value);
    cbg_self_->SetTargetTexture(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedCamera_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::RenderedCamera*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_BuiltinShader_Create(void* cbg_self, int32_t type) {
    auto cbg_self_ = (Altseed::BuiltinShader*)(cbg_self);

    Altseed::BuiltinShaderType cbg_arg0 = (Altseed::BuiltinShaderType)type;
    std::shared_ptr<Altseed::Shader> cbg_ret = cbg_self_->Create(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Shader>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_BuiltinShader_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::BuiltinShader*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Shader_Create(const char16_t* name, const char16_t* code, int32_t shaderStage) {
    const char16_t* cbg_arg0 = name;
    const char16_t* cbg_arg1 = code;
    Altseed::ShaderStageType cbg_arg2 = (Altseed::ShaderStageType)shaderStage;
    std::shared_ptr<Altseed::Shader> cbg_ret = Altseed::Shader::Create(cbg_arg0, cbg_arg1, cbg_arg2);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Shader>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Shader_GetStageType(void* cbg_self) {
    auto cbg_self_ = (Altseed::Shader*)(cbg_self);

    Altseed::ShaderStageType cbg_ret = cbg_self_->GetStageType();
    return (int32_t)cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Shader_GetCode(void* cbg_self) {
    auto cbg_self_ = (Altseed::Shader*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetCode();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Shader_GetName(void* cbg_self) {
    auto cbg_self_ = (Altseed::Shader*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetName();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Shader_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Shader*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT Altseed::Vector2I_C CBGSTDCALL cbg_Glyph_GetTextureSize(void* cbg_self) {
    auto cbg_self_ = (Altseed::Glyph*)(cbg_self);

    Altseed::Vector2I_C cbg_ret = cbg_self_->GetTextureSize();
    return (cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Glyph_GetTextureIndex(void* cbg_self) {
    auto cbg_self_ = (Altseed::Glyph*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetTextureIndex();
    return cbg_ret;
}

CBGEXPORT Altseed::Vector2I_C CBGSTDCALL cbg_Glyph_GetPosition(void* cbg_self) {
    auto cbg_self_ = (Altseed::Glyph*)(cbg_self);

    Altseed::Vector2I_C cbg_ret = cbg_self_->GetPosition();
    return (cbg_ret);
}

CBGEXPORT Altseed::Vector2I_C CBGSTDCALL cbg_Glyph_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed::Glyph*)(cbg_self);

    Altseed::Vector2I_C cbg_ret = cbg_self_->GetSize();
    return (cbg_ret);
}

CBGEXPORT Altseed::Vector2I_C CBGSTDCALL cbg_Glyph_GetOffset(void* cbg_self) {
    auto cbg_self_ = (Altseed::Glyph*)(cbg_self);

    Altseed::Vector2I_C cbg_ret = cbg_self_->GetOffset();
    return (cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Glyph_GetGlyphWidth(void* cbg_self) {
    auto cbg_self_ = (Altseed::Glyph*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetGlyphWidth();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Glyph_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Glyph*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Font_LoadDynamicFont(const char16_t* path, int32_t size) {
    const char16_t* cbg_arg0 = path;
    int32_t cbg_arg1 = size;
    std::shared_ptr<Altseed::Font> cbg_ret = Altseed::Font::LoadDynamicFont(cbg_arg0, cbg_arg1);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Font>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_Font_LoadStaticFont(const char16_t* path) {
    const char16_t* cbg_arg0 = path;
    std::shared_ptr<Altseed::Font> cbg_ret = Altseed::Font::LoadStaticFont(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Font>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Font_GenerateFontFile(const char16_t* dynamicFontPath, const char16_t* staticFontPath, int32_t size, const char16_t* characters) {
    const char16_t* cbg_arg0 = dynamicFontPath;
    const char16_t* cbg_arg1 = staticFontPath;
    int32_t cbg_arg2 = size;
    const char16_t* cbg_arg3 = characters;
    bool cbg_ret = Altseed::Font::GenerateFontFile(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT void* CBGSTDCALL cbg_Font_GetGlyph(void* cbg_self, int32_t character) {
    auto cbg_self_ = (Altseed::Font*)(cbg_self);

    int32_t cbg_arg0 = character;
    std::shared_ptr<Altseed::Glyph> cbg_ret = cbg_self_->GetGlyph(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Glyph>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_Font_GetFontTexture(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed::Font*)(cbg_self);

    int32_t cbg_arg0 = index;
    std::shared_ptr<Altseed::Texture2D> cbg_ret = cbg_self_->GetFontTexture(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Texture2D>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Font_GetKerning(void* cbg_self, int32_t c1, int32_t c2) {
    auto cbg_self_ = (Altseed::Font*)(cbg_self);

    int32_t cbg_arg0 = c1;
    int32_t cbg_arg1 = c2;
    int32_t cbg_ret = cbg_self_->GetKerning(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT Altseed::Vector2I_C CBGSTDCALL cbg_Font_CalcTextureSize(void* cbg_self, const char16_t* text, int32_t direction, bool isEnableKerning) {
    auto cbg_self_ = (Altseed::Font*)(cbg_self);

    const char16_t* cbg_arg0 = text;
    Altseed::WritingDirection cbg_arg1 = (Altseed::WritingDirection)direction;
    bool cbg_arg2 = isEnableKerning;
    Altseed::Vector2I_C cbg_ret = cbg_self_->CalcTextureSize(cbg_arg0, cbg_arg1, cbg_arg2);
    return (cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_Font_CreateImageFont(void* baseFont) {
    std::shared_ptr<Altseed::Font> cbg_arg0 = Altseed::CreateAndAddSharedPtr<Altseed::Font>((Altseed::Font*)baseFont);
    std::shared_ptr<Altseed::Font> cbg_ret = Altseed::Font::CreateImageFont(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Font>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Font_AddImageGlyph(void* cbg_self, int32_t character, void* texture) {
    auto cbg_self_ = (Altseed::Font*)(cbg_self);

    int32_t cbg_arg0 = character;
    std::shared_ptr<Altseed::Texture2D> cbg_arg1 = Altseed::CreateAndAddSharedPtr<Altseed::Texture2D>((Altseed::Texture2D*)texture);
    cbg_self_->AddImageGlyph(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_Font_GetImageGlyph(void* cbg_self, int32_t character) {
    auto cbg_self_ = (Altseed::Font*)(cbg_self);

    int32_t cbg_arg0 = character;
    std::shared_ptr<Altseed::Texture2D> cbg_ret = cbg_self_->GetImageGlyph(cbg_arg0);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Texture2D>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Font_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed::Font*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetSize();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Font_GetAscent(void* cbg_self) {
    auto cbg_self_ = (Altseed::Font*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetAscent();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Font_GetDescent(void* cbg_self) {
    auto cbg_self_ = (Altseed::Font*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetDescent();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Font_GetLineGap(void* cbg_self) {
    auto cbg_self_ = (Altseed::Font*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetLineGap();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Font_GetIsStaticFont(void* cbg_self) {
    auto cbg_self_ = (Altseed::Font*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsStaticFont();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Font_GetPath(void* cbg_self) {
    auto cbg_self_ = (Altseed::Font*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetPath();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Font_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Font*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Tool_GetInstance() {
    std::shared_ptr<Altseed::Tool> cbg_ret = Altseed::Tool::GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Tool>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_Begin(void* cbg_self, const char16_t* name, int32_t flags) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = name;
    Altseed::ToolWindow cbg_arg1 = (Altseed::ToolWindow)flags;
    bool cbg_ret = cbg_self_->Begin(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_End(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->End();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_NewFrame(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->NewFrame();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Render(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->Render();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Dummy(void* cbg_self, Altseed::Vector2F_C size) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    Altseed::Vector2F_C cbg_arg0 = size;
    cbg_self_->Dummy(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Text(void* cbg_self, const char16_t* text) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = text;
    cbg_self_->Text(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_TextUnformatted(void* cbg_self, const char16_t* text) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = text;
    cbg_self_->TextUnformatted(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_TextWrapped(void* cbg_self, const char16_t* text) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = text;
    cbg_self_->TextWrapped(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_TextColored(void* cbg_self, Altseed::Vector4F_C color, const char16_t* text) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    Altseed::Vector4F_C cbg_arg0 = color;
    const char16_t* cbg_arg1 = text;
    cbg_self_->TextColored(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_TextDisabled(void* cbg_self, const char16_t* text) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = text;
    cbg_self_->TextDisabled(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_BulletText(void* cbg_self, const char16_t* text) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = text;
    cbg_self_->BulletText(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_LabelText(void* cbg_self, const char16_t* label, const char16_t* text) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    const char16_t* cbg_arg1 = text;
    cbg_self_->LabelText(cbg_arg0, cbg_arg1);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_CollapsingHeader(void* cbg_self, const char16_t* label, int32_t flags) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed::ToolTreeNode cbg_arg1 = (Altseed::ToolTreeNode)flags;
    bool cbg_ret = cbg_self_->CollapsingHeader(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_TreeNode(void* cbg_self, const char16_t* label) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool cbg_ret = cbg_self_->TreeNode(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_TreeNodeEx(void* cbg_self, const char16_t* label, int32_t flags) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed::ToolTreeNode cbg_arg1 = (Altseed::ToolTreeNode)flags;
    bool cbg_ret = cbg_self_->TreeNodeEx(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_TreePop(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->TreePop();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextItemOpen(void* cbg_self, bool isOpen, int32_t cond) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    bool cbg_arg0 = isOpen;
    Altseed::ToolCond cbg_arg1 = (Altseed::ToolCond)cond;
    cbg_self_->SetNextItemOpen(cbg_arg0, cbg_arg1);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_Button(void* cbg_self, const char16_t* label, Altseed::Vector2F_C size) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed::Vector2F_C cbg_arg1 = size;
    bool cbg_ret = cbg_self_->Button(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_CheckBox(void* cbg_self, const char16_t* label, bool * isOpen) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool* cbg_arg1 = isOpen;
    bool cbg_ret = cbg_self_->CheckBox(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_RadioButton(void* cbg_self, const char16_t* label, bool active) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool cbg_arg1 = active;
    bool cbg_ret = cbg_self_->RadioButton(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_ArrowButton(void* cbg_self, const char16_t* label, int32_t dir) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed::ToolDir cbg_arg1 = (Altseed::ToolDir)dir;
    bool cbg_ret = cbg_self_->ArrowButton(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_InvisibleButton(void* cbg_self, const char16_t* label, Altseed::Vector2F_C size) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed::Vector2F_C cbg_arg1 = size;
    bool cbg_ret = cbg_self_->InvisibleButton(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_Selectable(void* cbg_self, const char16_t* label, bool * selected, int32_t flags) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool* cbg_arg1 = selected;
    Altseed::ToolSelectable cbg_arg2 = (Altseed::ToolSelectable)flags;
    bool cbg_ret = cbg_self_->Selectable(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_InputInt(void* cbg_self, const char16_t* label, int32_t * value) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    int32_t* cbg_arg1 = value;
    bool cbg_ret = cbg_self_->InputInt(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_InputFloat(void* cbg_self, const char16_t* label, float * value) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    float* cbg_arg1 = value;
    bool cbg_ret = cbg_self_->InputFloat(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SliderInt(void* cbg_self, const char16_t* label, int32_t * value, float speed, int32_t valueMin, int32_t valueMax) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    int32_t* cbg_arg1 = value;
    float cbg_arg2 = speed;
    int32_t cbg_arg3 = valueMin;
    int32_t cbg_arg4 = valueMax;
    bool cbg_ret = cbg_self_->SliderInt(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SliderFloat(void* cbg_self, const char16_t* label, float * value, float speed, float valueMin, float valueMax) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    float* cbg_arg1 = value;
    float cbg_arg2 = speed;
    float cbg_arg3 = valueMin;
    float cbg_arg4 = valueMax;
    bool cbg_ret = cbg_self_->SliderFloat(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SliderAngle(void* cbg_self, const char16_t* label, float * angle) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    float* cbg_arg1 = angle;
    bool cbg_ret = cbg_self_->SliderAngle(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_VSliderInt(void* cbg_self, const char16_t* label, Altseed::Vector2F_C size, int32_t * value, int32_t valueMin, int32_t valueMax) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed::Vector2F_C cbg_arg1 = size;
    int32_t* cbg_arg2 = value;
    int32_t cbg_arg3 = valueMin;
    int32_t cbg_arg4 = valueMax;
    bool cbg_ret = cbg_self_->VSliderInt(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_VSliderFloat(void* cbg_self, const char16_t* label, Altseed::Vector2F_C size, float * value, float valueMin, float valueMax) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed::Vector2F_C cbg_arg1 = size;
    float* cbg_arg2 = value;
    float cbg_arg3 = valueMin;
    float cbg_arg4 = valueMax;
    bool cbg_ret = cbg_self_->VSliderFloat(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_DragInt(void* cbg_self, const char16_t* label, int32_t * value, float speed, int32_t valueMin, int32_t valueMax) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    int32_t* cbg_arg1 = value;
    float cbg_arg2 = speed;
    int32_t cbg_arg3 = valueMin;
    int32_t cbg_arg4 = valueMax;
    bool cbg_ret = cbg_self_->DragInt(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_DragFloat(void* cbg_self, const char16_t* label, float * value, float speed, float valueMin, float valueMax) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    float* cbg_arg1 = value;
    float cbg_arg2 = speed;
    float cbg_arg3 = valueMin;
    float cbg_arg4 = valueMax;
    bool cbg_ret = cbg_self_->DragFloat(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_OpenPopup(void* cbg_self, const char16_t* label) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    cbg_self_->OpenPopup(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginPopup(void* cbg_self, const char16_t* label) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool cbg_ret = cbg_self_->BeginPopup(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginPopupModal(void* cbg_self, const char16_t* label) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool cbg_ret = cbg_self_->BeginPopupModal(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndPopup(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->EndPopup();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginChild(void* cbg_self, const char16_t* label, Altseed::Vector2F_C size, bool border, int32_t flags) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed::Vector2F_C cbg_arg1 = size;
    bool cbg_arg2 = border;
    Altseed::ToolWindow cbg_arg3 = (Altseed::ToolWindow)flags;
    bool cbg_ret = cbg_self_->BeginChild(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndChild(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->EndChild();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginMenuBar(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->BeginMenuBar();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndMenuBar(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->EndMenuBar();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginMenu(void* cbg_self, const char16_t* label, bool enabled) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool cbg_arg1 = enabled;
    bool cbg_ret = cbg_self_->BeginMenu(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndMenu(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->EndMenu();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_MenuItem(void* cbg_self, const char16_t* label, const char16_t* shortcut, bool selected, bool enabled) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    const char16_t* cbg_arg1 = shortcut;
    bool cbg_arg2 = selected;
    bool cbg_arg3 = enabled;
    bool cbg_ret = cbg_self_->MenuItem(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginTabBar(void* cbg_self, const char16_t* label, int32_t flags) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed::ToolTabBar cbg_arg1 = (Altseed::ToolTabBar)flags;
    bool cbg_ret = cbg_self_->BeginTabBar(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndTabBar(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->EndTabBar();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginTabItem(void* cbg_self, const char16_t* label) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool cbg_ret = cbg_self_->BeginTabItem(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndTabItem(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->EndTabItem();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Indent(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->Indent();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Unindent(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->Unindent();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Separator(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->Separator();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetTooltip(void* cbg_self, const char16_t* text) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = text;
    cbg_self_->SetTooltip(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_BeginTooltip(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->BeginTooltip();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndTooltip(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->EndTooltip();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_NewLine(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->NewLine();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SameLine(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->SameLine();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushTextWrapPos(void* cbg_self, float wrapLocalPosX) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    float cbg_arg0 = wrapLocalPosX;
    cbg_self_->PushTextWrapPos(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PopTextWrapPos(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->PopTextWrapPos();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextItemWidth(void* cbg_self, float width) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    float cbg_arg0 = width;
    cbg_self_->SetNextItemWidth(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushItemWidth(void* cbg_self, float width) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    float cbg_arg0 = width;
    cbg_self_->PushItemWidth(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PopItemWidth(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->PopItemWidth();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushButtonRepeat(void* cbg_self, bool repeat) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    bool cbg_arg0 = repeat;
    cbg_self_->PushButtonRepeat(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PopButtonRepeat(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->PopButtonRepeat();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Columns(void* cbg_self, int32_t count, bool border) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    int32_t cbg_arg0 = count;
    bool cbg_arg1 = border;
    cbg_self_->Columns(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_NextColumn(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->NextColumn();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushID(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    int32_t cbg_arg0 = id;
    cbg_self_->PushID(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PopID(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->PopID();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsItemActive(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsItemActive();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsItemHovered(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsItemHovered();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetScrollHere(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->SetScrollHere();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetScrollHereX(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->SetScrollHereX();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetScrollHereY(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    cbg_self_->SetScrollHereY();
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetTextLineHeight(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetTextLineHeight();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetFontSize(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetFontSize();
    return cbg_ret;
}

CBGEXPORT Altseed::Vector2F_C CBGSTDCALL cbg_Tool_GetWindowSize(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    Altseed::Vector2F_C cbg_ret = cbg_self_->GetWindowSize();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetWindowSize(void* cbg_self, Altseed::Vector2F_C size) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    Altseed::Vector2F_C cbg_arg0 = size;
    cbg_self_->SetWindowSize(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsMousePosValid(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsMousePosValid();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsMouseDragging(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsMouseDragging();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsMouseDoubleClicked(void* cbg_self, int32_t button) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    int32_t cbg_arg0 = button;
    bool cbg_ret = cbg_self_->IsMouseDoubleClicked(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT Altseed::Vector2F_C CBGSTDCALL cbg_Tool_GetMouseDragDelta(void* cbg_self, int32_t button) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    int32_t cbg_arg0 = button;
    Altseed::Vector2F_C cbg_ret = cbg_self_->GetMouseDragDelta(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_ResetMouseDragDelta(void* cbg_self, int32_t button) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    int32_t cbg_arg0 = button;
    cbg_self_->ResetMouseDragDelta(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextWindowContentSize(void* cbg_self, Altseed::Vector2F_C size) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    Altseed::Vector2F_C cbg_arg0 = size;
    cbg_self_->SetNextWindowContentSize(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextWindowSize(void* cbg_self, Altseed::Vector2F_C size) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    Altseed::Vector2F_C cbg_arg0 = size;
    cbg_self_->SetNextWindowSize(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextWindowPos(void* cbg_self, Altseed::Vector2F_C pos) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

    Altseed::Vector2F_C cbg_arg0 = pos;
    cbg_self_->SetNextWindowPos(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Tool*)(cbg_self);

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

CBGEXPORT const char16_t* CBGSTDCALL cbg_StreamFile_GetPath(void* cbg_self) {
    auto cbg_self_ = (Altseed::StreamFile*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetPath();
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

CBGEXPORT void* CBGSTDCALL cbg_Sound_Load(const char16_t* path, bool isDecompressed) {
    const char16_t* cbg_arg0 = path;
    bool cbg_arg1 = isDecompressed;
    std::shared_ptr<Altseed::Sound> cbg_ret = Altseed::Sound::Load(cbg_arg0, cbg_arg1);
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Sound>(cbg_ret);
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

CBGEXPORT const char16_t* CBGSTDCALL cbg_Sound_GetPath(void* cbg_self) {
    auto cbg_self_ = (Altseed::Sound*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetPath();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Sound_GetIsDecompressed(void* cbg_self) {
    auto cbg_self_ = (Altseed::Sound*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsDecompressed();
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

CBGEXPORT float CBGSTDCALL cbg_SoundMixer_GetPlaybackPosition(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_ret = cbg_self_->GetPlaybackPosition(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_SetPlaybackPosition(void* cbg_self, int32_t id, float position) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = position;
    cbg_self_->SetPlaybackPosition(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_GetSpectrumData(void* cbg_self, int32_t id, void* spectrums, int32_t window) {
    auto cbg_self_ = (Altseed::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    std::shared_ptr<Altseed::FloatArray> cbg_arg1 = Altseed::CreateAndAddSharedPtr<Altseed::FloatArray>((Altseed::FloatArray*)spectrums);
    Altseed::FFTWindow cbg_arg2 = (Altseed::FFTWindow)window;
    cbg_self_->GetSpectrumData(cbg_arg0, cbg_arg1, cbg_arg2);
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

CBGEXPORT void* CBGSTDCALL cbg_Window_GetInstance() {
    std::shared_ptr<Altseed::Window> cbg_ret = Altseed::Window::GetInstance();
    return (void*)Altseed::AddAndGetSharedPtr<Altseed::Window>(cbg_ret);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Window_GetTitle(void* cbg_self) {
    auto cbg_self_ = (Altseed::Window*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetTitle();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Window_SetTitle(void* cbg_self, const char16_t* value) {
    auto cbg_self_ = (Altseed::Window*)(cbg_self);

    const char16_t* cbg_arg0 = value;
    cbg_self_->SetTitle(cbg_arg0);
}

CBGEXPORT Altseed::Vector2I_C CBGSTDCALL cbg_Window_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed::Window*)(cbg_self);

    Altseed::Vector2I_C cbg_ret = cbg_self_->GetSize();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Window_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed::Window*)(cbg_self);

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

