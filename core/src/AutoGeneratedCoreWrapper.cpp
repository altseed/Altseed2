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

#include <stdint.h>
#include <stdio.h>

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


#include "BaseObject.h"
#include "Common/Array.h"
#include "Common/Resource.h"
#include "Common/ResourceContainer.h"
#include "Common/Resources.h"
#include "Common/Profiler.h"
#include "Core.h"
#include "Graphics/BuiltinShader.h"
#include "Graphics/CommandList.h"
#include "Graphics/Font.h"
#include "Graphics/Graphics.h"
#include "Graphics/ImageFont.h"
#include "Graphics/Renderer/RenderedText.h"
#include "Graphics/Renderer/RenderedCamera.h"
#include "Graphics/Renderer/RenderedSprite.h"
#include "Graphics/Renderer/RenderedPolygon.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/RenderTexture.h"
#include "Graphics/ShaderCompiler/ShaderCompiler.h"
#include "Graphics/Texture2D.h"
#include "IO/BaseFileReader.h"
#include "IO/File.h"
#include "IO/FileRoot.h"
#include "IO/PackFile.h"
#include "IO/PackFileReader.h"
#include "IO/StaticFile.h"
#include "IO/StreamFile.h"
#include "Input/ButtonState.h"
#include "Input/Joystick.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Logger/Log.h"
#include "Media/MediaPlayer.h"
#include "Physics/Collider/Collider.h"
#include "Physics/Collider/CircleCollider.h"
#include "Physics/Collider/EdgeCollider.h"
#include "Physics/Collider/PolygonCollider.h"
#include "Physics/Collider/ShapeCollider.h"
#include "Sound/Sound.h"
#include "Sound/SoundMixer.h"
#include "Tool/Tool.h"
#include "Window/Window.h"
    
extern "C" {

CBGEXPORT void CBGSTDCALL cbg_Int8Array_Clear(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Int8Array*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_Resize(void* cbg_self, int32_t size) {
    auto cbg_self_ = (Altseed2::Int8Array*)(cbg_self);

    int32_t cbg_arg0 = size;
    cbg_self_->Resize(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_Int8Array_GetData(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Int8Array*)(cbg_self);

    void* cbg_ret = cbg_self_->GetData();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_Assign(void* cbg_self, void* ptr, int32_t size) {
    auto cbg_self_ = (Altseed2::Int8Array*)(cbg_self);

    void* cbg_arg0 = ptr;
    int32_t cbg_arg1 = size;
    cbg_self_->Assign(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_CopyTo(void* cbg_self, void* ptr) {
    auto cbg_self_ = (Altseed2::Int8Array*)(cbg_self);

    void* cbg_arg0 = ptr;
    cbg_self_->CopyTo(cbg_arg0);
}

CBGEXPORT int8_t CBGSTDCALL cbg_Int8Array_GetAt(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed2::Int8Array*)(cbg_self);

    int32_t cbg_arg0 = index;
    int8_t cbg_ret = cbg_self_->GetAt(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_SetAt(void* cbg_self, int32_t index, int8_t value) {
    auto cbg_self_ = (Altseed2::Int8Array*)(cbg_self);

    int32_t cbg_arg0 = index;
    int8_t cbg_arg1 = value;
    cbg_self_->SetAt(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_Int8Array_Create(int32_t size) {
    int32_t cbg_arg0 = size;
    std::shared_ptr<Altseed2::Int8Array> cbg_ret = Altseed2::Int8Array::Create(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Int8Array>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Int8Array_GetCount(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Int8Array*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCount();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Int8Array*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Int8Array_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Int8Array*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_Clear(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Int32Array*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_Resize(void* cbg_self, int32_t size) {
    auto cbg_self_ = (Altseed2::Int32Array*)(cbg_self);

    int32_t cbg_arg0 = size;
    cbg_self_->Resize(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_Int32Array_GetData(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Int32Array*)(cbg_self);

    void* cbg_ret = cbg_self_->GetData();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_Assign(void* cbg_self, void* ptr, int32_t size) {
    auto cbg_self_ = (Altseed2::Int32Array*)(cbg_self);

    void* cbg_arg0 = ptr;
    int32_t cbg_arg1 = size;
    cbg_self_->Assign(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_CopyTo(void* cbg_self, void* ptr) {
    auto cbg_self_ = (Altseed2::Int32Array*)(cbg_self);

    void* cbg_arg0 = ptr;
    cbg_self_->CopyTo(cbg_arg0);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Int32Array_GetAt(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed2::Int32Array*)(cbg_self);

    int32_t cbg_arg0 = index;
    int32_t cbg_ret = cbg_self_->GetAt(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_SetAt(void* cbg_self, int32_t index, int32_t value) {
    auto cbg_self_ = (Altseed2::Int32Array*)(cbg_self);

    int32_t cbg_arg0 = index;
    int32_t cbg_arg1 = value;
    cbg_self_->SetAt(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_Int32Array_Create(int32_t size) {
    int32_t cbg_arg0 = size;
    std::shared_ptr<Altseed2::Int32Array> cbg_ret = Altseed2::Int32Array::Create(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Int32Array>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Int32Array_GetCount(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Int32Array*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCount();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Int32Array*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Int32Array_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Int32Array*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_VertexArray_Clear(void* cbg_self) {
    auto cbg_self_ = (Altseed2::VertexArray*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT void CBGSTDCALL cbg_VertexArray_Resize(void* cbg_self, int32_t size) {
    auto cbg_self_ = (Altseed2::VertexArray*)(cbg_self);

    int32_t cbg_arg0 = size;
    cbg_self_->Resize(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_VertexArray_GetData(void* cbg_self) {
    auto cbg_self_ = (Altseed2::VertexArray*)(cbg_self);

    void* cbg_ret = cbg_self_->GetData();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_VertexArray_Assign(void* cbg_self, void* ptr, int32_t size) {
    auto cbg_self_ = (Altseed2::VertexArray*)(cbg_self);

    void* cbg_arg0 = ptr;
    int32_t cbg_arg1 = size;
    cbg_self_->Assign(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_VertexArray_CopyTo(void* cbg_self, void* ptr) {
    auto cbg_self_ = (Altseed2::VertexArray*)(cbg_self);

    void* cbg_arg0 = ptr;
    cbg_self_->CopyTo(cbg_arg0);
}

CBGEXPORT Altseed2::BatchVertex CBGSTDCALL cbg_VertexArray_GetAt(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed2::VertexArray*)(cbg_self);

    int32_t cbg_arg0 = index;
    Altseed2::BatchVertex cbg_ret = cbg_self_->GetAt(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_VertexArray_SetAt(void* cbg_self, int32_t index, Altseed2::BatchVertex value) {
    auto cbg_self_ = (Altseed2::VertexArray*)(cbg_self);

    int32_t cbg_arg0 = index;
    Altseed2::BatchVertex cbg_arg1 = value;
    cbg_self_->SetAt(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_VertexArray_Create(int32_t size) {
    int32_t cbg_arg0 = size;
    std::shared_ptr<Altseed2::VertexArray> cbg_ret = Altseed2::VertexArray::Create(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::VertexArray>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_VertexArray_GetCount(void* cbg_self) {
    auto cbg_self_ = (Altseed2::VertexArray*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCount();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_VertexArray_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::VertexArray*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_VertexArray_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::VertexArray*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_FloatArray_Clear(void* cbg_self) {
    auto cbg_self_ = (Altseed2::FloatArray*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT void CBGSTDCALL cbg_FloatArray_Resize(void* cbg_self, int32_t size) {
    auto cbg_self_ = (Altseed2::FloatArray*)(cbg_self);

    int32_t cbg_arg0 = size;
    cbg_self_->Resize(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_FloatArray_GetData(void* cbg_self) {
    auto cbg_self_ = (Altseed2::FloatArray*)(cbg_self);

    void* cbg_ret = cbg_self_->GetData();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_FloatArray_Assign(void* cbg_self, void* ptr, int32_t size) {
    auto cbg_self_ = (Altseed2::FloatArray*)(cbg_self);

    void* cbg_arg0 = ptr;
    int32_t cbg_arg1 = size;
    cbg_self_->Assign(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_FloatArray_CopyTo(void* cbg_self, void* ptr) {
    auto cbg_self_ = (Altseed2::FloatArray*)(cbg_self);

    void* cbg_arg0 = ptr;
    cbg_self_->CopyTo(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_FloatArray_GetAt(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed2::FloatArray*)(cbg_self);

    int32_t cbg_arg0 = index;
    float cbg_ret = cbg_self_->GetAt(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_FloatArray_SetAt(void* cbg_self, int32_t index, float value) {
    auto cbg_self_ = (Altseed2::FloatArray*)(cbg_self);

    int32_t cbg_arg0 = index;
    float cbg_arg1 = value;
    cbg_self_->SetAt(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_FloatArray_Create(int32_t size) {
    int32_t cbg_arg0 = size;
    std::shared_ptr<Altseed2::FloatArray> cbg_ret = Altseed2::FloatArray::Create(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::FloatArray>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_FloatArray_GetCount(void* cbg_self) {
    auto cbg_self_ = (Altseed2::FloatArray*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCount();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_FloatArray_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::FloatArray*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_FloatArray_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::FloatArray*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_Vector2FArray_Clear(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Vector2FArray*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT void CBGSTDCALL cbg_Vector2FArray_Resize(void* cbg_self, int32_t size) {
    auto cbg_self_ = (Altseed2::Vector2FArray*)(cbg_self);

    int32_t cbg_arg0 = size;
    cbg_self_->Resize(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_Vector2FArray_GetData(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Vector2FArray*)(cbg_self);

    void* cbg_ret = cbg_self_->GetData();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Vector2FArray_Assign(void* cbg_self, void* ptr, int32_t size) {
    auto cbg_self_ = (Altseed2::Vector2FArray*)(cbg_self);

    void* cbg_arg0 = ptr;
    int32_t cbg_arg1 = size;
    cbg_self_->Assign(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Vector2FArray_CopyTo(void* cbg_self, void* ptr) {
    auto cbg_self_ = (Altseed2::Vector2FArray*)(cbg_self);

    void* cbg_arg0 = ptr;
    cbg_self_->CopyTo(cbg_arg0);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Vector2FArray_GetAt(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed2::Vector2FArray*)(cbg_self);

    int32_t cbg_arg0 = index;
    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetAt(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Vector2FArray_SetAt(void* cbg_self, int32_t index, Altseed2::Vector2F_C value) {
    auto cbg_self_ = (Altseed2::Vector2FArray*)(cbg_self);

    int32_t cbg_arg0 = index;
    Altseed2::Vector2F_C cbg_arg1 = value;
    cbg_self_->SetAt(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_Vector2FArray_Create(int32_t size) {
    int32_t cbg_arg0 = size;
    std::shared_ptr<Altseed2::Vector2FArray> cbg_ret = Altseed2::Vector2FArray::Create(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Vector2FArray>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Vector2FArray_GetCount(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Vector2FArray*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCount();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Vector2FArray_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Vector2FArray*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Vector2FArray_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Vector2FArray*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Log_GetInstance() {
    std::shared_ptr<Altseed2::Log> cbg_ret = Altseed2::Log::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Log>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Write(void* cbg_self, int32_t category, int32_t level, const char16_t* message) {
    auto cbg_self_ = (Altseed2::Log*)(cbg_self);

    Altseed2::LogCategory cbg_arg0 = (Altseed2::LogCategory)category;
    Altseed2::LogLevel cbg_arg1 = (Altseed2::LogLevel)level;
    const char16_t* cbg_arg2 = message;
    cbg_self_->Write(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Trace(void* cbg_self, int32_t category, const char16_t* message) {
    auto cbg_self_ = (Altseed2::Log*)(cbg_self);

    Altseed2::LogCategory cbg_arg0 = (Altseed2::LogCategory)category;
    const char16_t* cbg_arg1 = message;
    cbg_self_->Trace(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Debug(void* cbg_self, int32_t category, const char16_t* message) {
    auto cbg_self_ = (Altseed2::Log*)(cbg_self);

    Altseed2::LogCategory cbg_arg0 = (Altseed2::LogCategory)category;
    const char16_t* cbg_arg1 = message;
    cbg_self_->Debug(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Info(void* cbg_self, int32_t category, const char16_t* message) {
    auto cbg_self_ = (Altseed2::Log*)(cbg_self);

    Altseed2::LogCategory cbg_arg0 = (Altseed2::LogCategory)category;
    const char16_t* cbg_arg1 = message;
    cbg_self_->Info(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Warn(void* cbg_self, int32_t category, const char16_t* message) {
    auto cbg_self_ = (Altseed2::Log*)(cbg_self);

    Altseed2::LogCategory cbg_arg0 = (Altseed2::LogCategory)category;
    const char16_t* cbg_arg1 = message;
    cbg_self_->Warn(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Error(void* cbg_self, int32_t category, const char16_t* message) {
    auto cbg_self_ = (Altseed2::Log*)(cbg_self);

    Altseed2::LogCategory cbg_arg0 = (Altseed2::LogCategory)category;
    const char16_t* cbg_arg1 = message;
    cbg_self_->Error(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_Critical(void* cbg_self, int32_t category, const char16_t* message) {
    auto cbg_self_ = (Altseed2::Log*)(cbg_self);

    Altseed2::LogCategory cbg_arg0 = (Altseed2::LogCategory)category;
    const char16_t* cbg_arg1 = message;
    cbg_self_->Critical(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_SetLevel(void* cbg_self, int32_t category, int32_t level) {
    auto cbg_self_ = (Altseed2::Log*)(cbg_self);

    Altseed2::LogCategory cbg_arg0 = (Altseed2::LogCategory)category;
    Altseed2::LogLevel cbg_arg1 = (Altseed2::LogLevel)level;
    cbg_self_->SetLevel(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Log_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Log*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Log_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Log*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_Core_PrintAllBaseObjectName(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Core*)(cbg_self);

    cbg_self_->PrintAllBaseObjectName();
}

CBGEXPORT bool CBGSTDCALL cbg_Core_Initialize(const char16_t* title, int32_t width, int32_t height, void* config) {
    const char16_t* cbg_arg0 = title;
    int32_t cbg_arg1 = width;
    int32_t cbg_arg2 = height;
    std::shared_ptr<Altseed2::Configuration> cbg_arg3 = Altseed2::CreateAndAddSharedPtr<Altseed2::Configuration>((Altseed2::Configuration*)config);
    bool cbg_ret = Altseed2::Core::Initialize(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Core_Terminate() {
    Altseed2::Core::Terminate();
}

CBGEXPORT void* CBGSTDCALL cbg_Core_GetInstance() {
    std::shared_ptr<Altseed2::Core> cbg_ret = Altseed2::Core::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Core>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Core_DoEvent(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Core*)(cbg_self);

    bool cbg_ret = cbg_self_->DoEvent();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Core_GetBaseObjectCount(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Core*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetBaseObjectCount();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Core_GetDeltaSecond(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Core*)(cbg_self);

    float cbg_ret = cbg_self_->GetDeltaSecond();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Core_GetCurrentFPS(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Core*)(cbg_self);

    float cbg_ret = cbg_self_->GetCurrentFPS();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Core_GetTargetFPS(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Core*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetTargetFPS();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Core_SetTargetFPS(void* cbg_self, int32_t value) {
    auto cbg_self_ = (Altseed2::Core*)(cbg_self);

    int32_t cbg_arg0 = value;
    cbg_self_->SetTargetFPS(cbg_arg0);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Core_GetFramerateMode(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Core*)(cbg_self);

    Altseed2::FramerateMode cbg_ret = cbg_self_->GetFramerateMode();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Core_SetFramerateMode(void* cbg_self, int32_t value) {
    auto cbg_self_ = (Altseed2::Core*)(cbg_self);

    Altseed2::FramerateMode cbg_arg0 = (Altseed2::FramerateMode)value;
    cbg_self_->SetFramerateMode(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Core_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Core*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Core_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Core*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Window_GetInstance() {
    std::shared_ptr<Altseed2::Window> cbg_ret = Altseed2::Window::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Window>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Window_DoEvent(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Window*)(cbg_self);

    bool cbg_ret = cbg_self_->DoEvent();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Window_GetTitle(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Window*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetTitle();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Window_SetTitle(void* cbg_self, const char16_t* value) {
    auto cbg_self_ = (Altseed2::Window*)(cbg_self);

    const char16_t* cbg_arg0 = value;
    cbg_self_->SetTitle(cbg_arg0);
}

CBGEXPORT Altseed2::Vector2I_C CBGSTDCALL cbg_Window_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Window*)(cbg_self);

    Altseed2::Vector2I_C cbg_ret = cbg_self_->GetSize();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Window_SetSize(void* cbg_self, Altseed2::Vector2I_C value) {
    auto cbg_self_ = (Altseed2::Window*)(cbg_self);

    Altseed2::Vector2I_C cbg_arg0 = value;
    cbg_self_->SetSize(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Window_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Window*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Window_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Window*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Buffer_Create(int32_t usage, int32_t size) {
    Altseed2::BufferUsageType cbg_arg0 = (Altseed2::BufferUsageType)usage;
    int32_t cbg_arg1 = size;
    std::shared_ptr<Altseed2::Buffer> cbg_ret = Altseed2::Buffer::Create(cbg_arg0, cbg_arg1);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Buffer>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_Buffer_Lock(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Buffer*)(cbg_self);

    void* cbg_ret = cbg_self_->Lock();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Buffer_Unlock(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Buffer*)(cbg_self);

    cbg_self_->Unlock();
}

CBGEXPORT int32_t CBGSTDCALL cbg_Buffer_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Buffer*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetSize();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Buffer_GetBufferUsage(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Buffer*)(cbg_self);

    Altseed2::BufferUsageType cbg_ret = cbg_self_->GetBufferUsage();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Buffer_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Buffer*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Buffer_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Buffer*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_ShaderCompileResult_GetValue(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ShaderCompileResult*)(cbg_self);

    std::shared_ptr<Altseed2::Shader> cbg_ret = cbg_self_->GetValue();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Shader>(cbg_ret);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_ShaderCompileResult_GetMessage(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ShaderCompileResult*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetMessage();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_ShaderCompileResult_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ShaderCompileResult*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_ShaderCompileResult_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ShaderCompileResult*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Shader_Compile(const char16_t* name, const char16_t* code, int32_t shaderStage) {
    const char16_t* cbg_arg0 = name;
    const char16_t* cbg_arg1 = code;
    Altseed2::ShaderStageType cbg_arg2 = (Altseed2::ShaderStageType)shaderStage;
    std::shared_ptr<Altseed2::ShaderCompileResult> cbg_ret = Altseed2::Shader::Compile(cbg_arg0, cbg_arg1, cbg_arg2);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::ShaderCompileResult>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_Shader_CompileFromFile(const char16_t* name, const char16_t* path, int32_t shaderStage) {
    const char16_t* cbg_arg0 = name;
    const char16_t* cbg_arg1 = path;
    Altseed2::ShaderStageType cbg_arg2 = (Altseed2::ShaderStageType)shaderStage;
    std::shared_ptr<Altseed2::ShaderCompileResult> cbg_ret = Altseed2::Shader::CompileFromFile(cbg_arg0, cbg_arg1, cbg_arg2);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::ShaderCompileResult>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Shader_GetUniformSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Shader*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetUniformSize();
    return cbg_ret;
}

CBGEXPORT Altseed2::Vector3I_C CBGSTDCALL cbg_Shader_GetNumThreads(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Shader*)(cbg_self);

    Altseed2::Vector3I_C cbg_ret = cbg_self_->GetNumThreads();
    return (cbg_ret);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Shader_GetCode(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Shader*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetCode();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Shader_GetName(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Shader*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetName();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Shader_GetStageType(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Shader*)(cbg_self);

    Altseed2::ShaderStageType cbg_ret = cbg_self_->GetStageType();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Shader_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Shader*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Shader_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Shader*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Resources_GetInstance() {
    std::shared_ptr<Altseed2::Resources> cbg_ret = Altseed2::Resources::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Resources>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Resources_GetResourcesCount(void* cbg_self, int32_t type) {
    auto cbg_self_ = (Altseed2::Resources*)(cbg_self);

    Altseed2::ResourceType cbg_arg0 = (Altseed2::ResourceType)type;
    int32_t cbg_ret = cbg_self_->GetResourcesCount(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Resources_Clear(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Resources*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT void CBGSTDCALL cbg_Resources_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Resources*)(cbg_self);

    cbg_self_->Reload();
}

CBGEXPORT void CBGSTDCALL cbg_Resources_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Resources*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Resources_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Resources*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT bool CBGSTDCALL cbg_TextureBase_Save(void* cbg_self, const char16_t* path) {
    auto cbg_self_ = (Altseed2::TextureBase*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    bool cbg_ret = cbg_self_->Save(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT Altseed2::Vector2I_C CBGSTDCALL cbg_TextureBase_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::TextureBase*)(cbg_self);

    Altseed2::Vector2I_C cbg_ret = cbg_self_->GetSize();
    return (cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_TextureBase_GetWrapMode(void* cbg_self) {
    auto cbg_self_ = (Altseed2::TextureBase*)(cbg_self);

    Altseed2::TextureWrapMode cbg_ret = cbg_self_->GetWrapMode();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_TextureBase_SetWrapMode(void* cbg_self, int32_t value) {
    auto cbg_self_ = (Altseed2::TextureBase*)(cbg_self);

    Altseed2::TextureWrapMode cbg_arg0 = (Altseed2::TextureWrapMode)value;
    cbg_self_->SetWrapMode(cbg_arg0);
}

CBGEXPORT int32_t CBGSTDCALL cbg_TextureBase_GetFilterType(void* cbg_self) {
    auto cbg_self_ = (Altseed2::TextureBase*)(cbg_self);

    Altseed2::TextureFilterType cbg_ret = cbg_self_->GetFilterType();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_TextureBase_SetFilterType(void* cbg_self, int32_t value) {
    auto cbg_self_ = (Altseed2::TextureBase*)(cbg_self);

    Altseed2::TextureFilterType cbg_arg0 = (Altseed2::TextureFilterType)value;
    cbg_self_->SetFilterType(cbg_arg0);
}

CBGEXPORT int32_t CBGSTDCALL cbg_TextureBase_GetFormat(void* cbg_self) {
    auto cbg_self_ = (Altseed2::TextureBase*)(cbg_self);

    Altseed2::TextureFormatType cbg_ret = cbg_self_->GetFormat();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_TextureBase_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::TextureBase*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_TextureBase_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::TextureBase*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT Altseed2::Vector4F_C CBGSTDCALL cbg_MaterialPropertyBlock_GetVector4F(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlock*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Vector4F_C cbg_ret = cbg_self_->GetVector4F(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_MaterialPropertyBlock_SetVector4F(void* cbg_self, const char16_t* key, Altseed2::Vector4F_C value) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlock*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Vector4F_C cbg_arg1 = value;
    cbg_self_->SetVector4F(cbg_arg0, cbg_arg1);
}

CBGEXPORT Altseed2::Matrix44F_C CBGSTDCALL cbg_MaterialPropertyBlock_GetMatrix44F(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlock*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Matrix44F_C cbg_ret = cbg_self_->GetMatrix44F(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_MaterialPropertyBlock_SetMatrix44F(void* cbg_self, const char16_t* key, Altseed2::Matrix44F_C value) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlock*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Matrix44F_C cbg_arg1 = value;
    cbg_self_->SetMatrix44F(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_MaterialPropertyBlock_GetTexture(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlock*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    std::shared_ptr<Altseed2::TextureBase> cbg_ret = cbg_self_->GetTexture(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::TextureBase>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_MaterialPropertyBlock_SetTexture(void* cbg_self, const char16_t* key, void* value) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlock*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    std::shared_ptr<Altseed2::TextureBase> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::TextureBase>((Altseed2::TextureBase*)value);
    cbg_self_->SetTexture(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_MaterialPropertyBlock_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlock*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_MaterialPropertyBlock_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlock*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void CBGSTDCALL cbg_MaterialPropertyBlockCollection_Add(void* cbg_self, void* block) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlockCollection*)(cbg_self);

    std::shared_ptr<Altseed2::MaterialPropertyBlock> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::MaterialPropertyBlock>((Altseed2::MaterialPropertyBlock*)block);
    cbg_self_->Add(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_MaterialPropertyBlockCollection_Clear(void* cbg_self) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlockCollection*)(cbg_self);

    cbg_self_->Clear();
}

CBGEXPORT Altseed2::Vector4F_C CBGSTDCALL cbg_MaterialPropertyBlockCollection_GetVector4F(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlockCollection*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Vector4F_C cbg_ret = cbg_self_->GetVector4F(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT Altseed2::Matrix44F_C CBGSTDCALL cbg_MaterialPropertyBlockCollection_GetMatrix44F(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlockCollection*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Matrix44F_C cbg_ret = cbg_self_->GetMatrix44F(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_MaterialPropertyBlockCollection_GetTexture(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlockCollection*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    std::shared_ptr<Altseed2::TextureBase> cbg_ret = cbg_self_->GetTexture(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::TextureBase>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_MaterialPropertyBlockCollection_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlockCollection*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_MaterialPropertyBlockCollection_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::MaterialPropertyBlockCollection*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Material_Create() {
    std::shared_ptr<Altseed2::Material> cbg_ret = Altseed2::Material::Create();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Material>(cbg_ret);
}

CBGEXPORT Altseed2::Vector4F_C CBGSTDCALL cbg_Material_GetVector4F(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed2::Material*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Vector4F_C cbg_ret = cbg_self_->GetVector4F(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Material_SetVector4F(void* cbg_self, const char16_t* key, Altseed2::Vector4F_C value) {
    auto cbg_self_ = (Altseed2::Material*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Vector4F_C cbg_arg1 = value;
    cbg_self_->SetVector4F(cbg_arg0, cbg_arg1);
}

CBGEXPORT Altseed2::Matrix44F_C CBGSTDCALL cbg_Material_GetMatrix44F(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed2::Material*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Matrix44F_C cbg_ret = cbg_self_->GetMatrix44F(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Material_SetMatrix44F(void* cbg_self, const char16_t* key, Altseed2::Matrix44F_C value) {
    auto cbg_self_ = (Altseed2::Material*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Matrix44F_C cbg_arg1 = value;
    cbg_self_->SetMatrix44F(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_Material_GetTexture(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed2::Material*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    std::shared_ptr<Altseed2::TextureBase> cbg_ret = cbg_self_->GetTexture(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::TextureBase>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Material_SetTexture(void* cbg_self, const char16_t* key, void* value) {
    auto cbg_self_ = (Altseed2::Material*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    std::shared_ptr<Altseed2::TextureBase> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::TextureBase>((Altseed2::TextureBase*)value);
    cbg_self_->SetTexture(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_Material_GetShader(void* cbg_self, int32_t shaderStage) {
    auto cbg_self_ = (Altseed2::Material*)(cbg_self);

    Altseed2::ShaderStageType cbg_arg0 = (Altseed2::ShaderStageType)shaderStage;
    std::shared_ptr<Altseed2::Shader> cbg_ret = cbg_self_->GetShader(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Shader>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Material_SetShader(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::Material*)(cbg_self);

    std::shared_ptr<Altseed2::Shader> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Shader>((Altseed2::Shader*)value);
    cbg_self_->SetShader(cbg_arg0);
}

CBGEXPORT Altseed2::AlphaBlend_C CBGSTDCALL cbg_Material_GetAlphaBlend(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Material*)(cbg_self);

    Altseed2::AlphaBlend_C cbg_ret = cbg_self_->GetAlphaBlend();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Material_SetAlphaBlend(void* cbg_self, Altseed2::AlphaBlend_C value) {
    auto cbg_self_ = (Altseed2::Material*)(cbg_self);

    Altseed2::AlphaBlend_C cbg_arg0 = value;
    cbg_self_->SetAlphaBlend(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_Material_GetPropertyBlock(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Material*)(cbg_self);

    std::shared_ptr<Altseed2::MaterialPropertyBlock> cbg_ret = cbg_self_->GetPropertyBlock();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::MaterialPropertyBlock>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Material_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Material*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Material_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Material*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT bool CBGSTDCALL cbg_Texture2D_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Texture2D*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
}

CBGEXPORT void* CBGSTDCALL cbg_Texture2D_Load(const char16_t* path) {
    const char16_t* cbg_arg0 = path;
    std::shared_ptr<Altseed2::Texture2D> cbg_ret = Altseed2::Texture2D::Load(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Texture2D>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_Texture2D_Create(Altseed2::Vector2I_C size) {
    Altseed2::Vector2I_C cbg_arg0 = size;
    std::shared_ptr<Altseed2::Texture2D> cbg_ret = Altseed2::Texture2D::Create(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Texture2D>(cbg_ret);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Texture2D_GetPath(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Texture2D*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetPath();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Texture2D_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Texture2D*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Texture2D_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Texture2D*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_BuiltinShader_Create(void* cbg_self, int32_t type) {
    auto cbg_self_ = (Altseed2::BuiltinShader*)(cbg_self);

    Altseed2::BuiltinShaderType cbg_arg0 = (Altseed2::BuiltinShaderType)type;
    std::shared_ptr<Altseed2::Shader> cbg_ret = cbg_self_->Create(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Shader>(cbg_ret);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_BuiltinShader_GetDownsampleShader(void* cbg_self) {
    auto cbg_self_ = (Altseed2::BuiltinShader*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetDownsampleShader();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_BuiltinShader_GetSepiaShader(void* cbg_self) {
    auto cbg_self_ = (Altseed2::BuiltinShader*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetSepiaShader();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_BuiltinShader_GetGrayScaleShader(void* cbg_self) {
    auto cbg_self_ = (Altseed2::BuiltinShader*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetGrayScaleShader();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_BuiltinShader_GetGaussianBlurShader(void* cbg_self) {
    auto cbg_self_ = (Altseed2::BuiltinShader*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetGaussianBlurShader();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_BuiltinShader_GetHighLuminanceShader(void* cbg_self) {
    auto cbg_self_ = (Altseed2::BuiltinShader*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetHighLuminanceShader();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_BuiltinShader_GetLightBloomShader(void* cbg_self) {
    auto cbg_self_ = (Altseed2::BuiltinShader*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetLightBloomShader();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_BuiltinShader_GetTextureMixShader(void* cbg_self) {
    auto cbg_self_ = (Altseed2::BuiltinShader*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetTextureMixShader();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_BuiltinShader_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::BuiltinShader*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_BuiltinShader_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::BuiltinShader*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_CommandList_Create() {
    std::shared_ptr<Altseed2::CommandList> cbg_ret = Altseed2::CommandList::Create();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::CommandList>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_Begin(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    cbg_self_->Begin();
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_End(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    cbg_self_->End();
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_EndRenderPass(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    cbg_self_->EndRenderPass();
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_PauseRenderPass(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    cbg_self_->PauseRenderPass();
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_ResumeRenderPass(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    cbg_self_->ResumeRenderPass();
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_UploadBuffer(void* cbg_self, void* buffer) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    std::shared_ptr<Altseed2::Buffer> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Buffer>((Altseed2::Buffer*)buffer);
    cbg_self_->UploadBuffer(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_ReadbackBuffer(void* cbg_self, void* buffer) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    std::shared_ptr<Altseed2::Buffer> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Buffer>((Altseed2::Buffer*)buffer);
    cbg_self_->ReadbackBuffer(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_CopyBuffer(void* cbg_self, void* src, void* dst) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    std::shared_ptr<Altseed2::Buffer> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Buffer>((Altseed2::Buffer*)src);
    std::shared_ptr<Altseed2::Buffer> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::Buffer>((Altseed2::Buffer*)dst);
    cbg_self_->CopyBuffer(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_SetRenderTarget(void* cbg_self, void* target, Altseed2::RenderPassParameter_C renderPassParameter) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    std::shared_ptr<Altseed2::RenderTexture> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::RenderTexture>((Altseed2::RenderTexture*)target);
    Altseed2::RenderPassParameter_C cbg_arg1 = renderPassParameter;
    cbg_self_->SetRenderTarget(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_RenderToRenderTexture(void* cbg_self, void* material, void* target, Altseed2::RenderPassParameter_C renderPassParameter) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    std::shared_ptr<Altseed2::Material> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Material>((Altseed2::Material*)material);
    std::shared_ptr<Altseed2::RenderTexture> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::RenderTexture>((Altseed2::RenderTexture*)target);
    Altseed2::RenderPassParameter_C cbg_arg2 = renderPassParameter;
    cbg_self_->RenderToRenderTexture(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_RenderToRenderTarget(void* cbg_self, void* material) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    std::shared_ptr<Altseed2::Material> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Material>((Altseed2::Material*)material);
    cbg_self_->RenderToRenderTarget(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_Draw(void* cbg_self, int32_t instanceCount) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    int32_t cbg_arg0 = instanceCount;
    cbg_self_->Draw(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_SetVertexBuffer(void* cbg_self, void* vb, int32_t stride, int32_t offset) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    std::shared_ptr<Altseed2::Buffer> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Buffer>((Altseed2::Buffer*)vb);
    int32_t cbg_arg1 = stride;
    int32_t cbg_arg2 = offset;
    cbg_self_->SetVertexBuffer(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_SetIndexBuffer(void* cbg_self, void* ib, int32_t stride, int32_t offset) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    std::shared_ptr<Altseed2::Buffer> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Buffer>((Altseed2::Buffer*)ib);
    int32_t cbg_arg1 = stride;
    int32_t cbg_arg2 = offset;
    cbg_self_->SetIndexBuffer(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_BeginComputePass(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    cbg_self_->BeginComputePass();
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_EndComputePass(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    cbg_self_->EndComputePass();
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_SetComputeBuffer(void* cbg_self, void* buffer, int32_t stride, int32_t unit) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    std::shared_ptr<Altseed2::Buffer> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Buffer>((Altseed2::Buffer*)buffer);
    int32_t cbg_arg1 = stride;
    int32_t cbg_arg2 = unit;
    cbg_self_->SetComputeBuffer(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_Dispatch(void* cbg_self, int32_t x, int32_t y, int32_t z) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    int32_t cbg_arg0 = x;
    int32_t cbg_arg1 = y;
    int32_t cbg_arg2 = z;
    cbg_self_->Dispatch(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_CopyTexture(void* cbg_self, void* src, void* dst) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    std::shared_ptr<Altseed2::RenderTexture> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::RenderTexture>((Altseed2::RenderTexture*)src);
    std::shared_ptr<Altseed2::RenderTexture> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::RenderTexture>((Altseed2::RenderTexture*)dst);
    cbg_self_->CopyTexture(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_ResetTextures(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    cbg_self_->ResetTextures();
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_ResetComputeBuffers(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    cbg_self_->ResetComputeBuffers();
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_SaveRenderTexture(void* cbg_self, const char16_t* path, void* texture) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    std::shared_ptr<Altseed2::RenderTexture> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::RenderTexture>((Altseed2::RenderTexture*)texture);
    cbg_self_->SaveRenderTexture(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_CommandList_GetScreenTexture(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    std::shared_ptr<Altseed2::RenderTexture> cbg_ret = cbg_self_->GetScreenTexture();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::RenderTexture>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_SetScissor(void* cbg_self, Altseed2::RectI_C value) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    Altseed2::RectI_C cbg_arg0 = value;
    cbg_self_->SetScissor(cbg_arg0);
}

CBGEXPORT int32_t CBGSTDCALL cbg_CommandList_GetScreenTextureFormat(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    Altseed2::TextureFormatType cbg_ret = cbg_self_->GetScreenTextureFormat();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_SetScreenTextureFormat(void* cbg_self, int32_t value) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    Altseed2::TextureFormatType cbg_arg0 = (Altseed2::TextureFormatType)value;
    cbg_self_->SetScreenTextureFormat(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_SetMaterial(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    std::shared_ptr<Altseed2::Material> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Material>((Altseed2::Material*)value);
    cbg_self_->SetMaterial(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_SetComputePipelineState(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    std::shared_ptr<Altseed2::ComputePipelineState> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::ComputePipelineState>((Altseed2::ComputePipelineState*)value);
    cbg_self_->SetComputePipelineState(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_CommandList_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CommandList*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Graphics_GetInstance() {
    std::shared_ptr<Altseed2::Graphics> cbg_ret = Altseed2::Graphics::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Graphics>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Graphics_BeginFrame(void* cbg_self, Altseed2::RenderPassParameter_C renderPassParameter) {
    auto cbg_self_ = (Altseed2::Graphics*)(cbg_self);

    Altseed2::RenderPassParameter_C cbg_arg0 = renderPassParameter;
    bool cbg_ret = cbg_self_->BeginFrame(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Graphics_EndFrame(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Graphics*)(cbg_self);

    bool cbg_ret = cbg_self_->EndFrame();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Graphics_DoEvents(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Graphics*)(cbg_self);

    bool cbg_ret = cbg_self_->DoEvents();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Graphics_Terminate() {
    Altseed2::Graphics::Terminate();
}

CBGEXPORT void CBGSTDCALL cbg_Graphics_ExecuteCommandList(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Graphics*)(cbg_self);

    cbg_self_->ExecuteCommandList();
}

CBGEXPORT void CBGSTDCALL cbg_Graphics_WaitFinish(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Graphics*)(cbg_self);

    cbg_self_->WaitFinish();
}

CBGEXPORT void CBGSTDCALL cbg_Graphics_SaveScreenshot(void* cbg_self, const char16_t* path) {
    auto cbg_self_ = (Altseed2::Graphics*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    cbg_self_->SaveScreenshot(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_Graphics_GetCommandList(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Graphics*)(cbg_self);

    std::shared_ptr<Altseed2::CommandList> cbg_ret = cbg_self_->GetCommandList();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::CommandList>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_Graphics_GetBuiltinShader(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Graphics*)(cbg_self);

    std::shared_ptr<Altseed2::BuiltinShader> cbg_ret = cbg_self_->GetBuiltinShader();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::BuiltinShader>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Graphics_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Graphics*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Graphics_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Graphics*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Configuration_Create() {
    std::shared_ptr<Altseed2::Configuration> cbg_ret = Altseed2::Configuration::Create();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Configuration>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetIsFullscreen(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsFullscreen();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetIsFullscreen(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetIsFullscreen(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetIsResizable(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsResizable();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetIsResizable(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetIsResizable(cbg_arg0);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Configuration_GetDeviceType(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    Altseed2::GraphicsDeviceType cbg_ret = cbg_self_->GetDeviceType();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetDeviceType(void* cbg_self, int32_t value) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    Altseed2::GraphicsDeviceType cbg_arg0 = (Altseed2::GraphicsDeviceType)value;
    cbg_self_->SetDeviceType(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetWaitVSync(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetWaitVSync();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetWaitVSync(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetWaitVSync(cbg_arg0);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Configuration_GetEnabledCoreModules(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    Altseed2::CoreModules cbg_ret = cbg_self_->GetEnabledCoreModules();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetEnabledCoreModules(void* cbg_self, int32_t value) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    Altseed2::CoreModules cbg_arg0 = (Altseed2::CoreModules)value;
    cbg_self_->SetEnabledCoreModules(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetConsoleLoggingEnabled(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetConsoleLoggingEnabled();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetConsoleLoggingEnabled(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetConsoleLoggingEnabled(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Configuration_GetFileLoggingEnabled(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    bool cbg_ret = cbg_self_->GetFileLoggingEnabled();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetFileLoggingEnabled(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetFileLoggingEnabled(cbg_arg0);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Configuration_GetLogFileName(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetLogFileName();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetLogFileName(void* cbg_self, const char16_t* value) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    const char16_t* cbg_arg0 = value;
    cbg_self_->SetLogFileName(cbg_arg0);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Configuration_GetToolSettingFileName(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetToolSettingFileName();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_SetToolSettingFileName(void* cbg_self, const char16_t* value) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    const char16_t* cbg_arg0 = value;
    cbg_self_->SetToolSettingFileName(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Configuration_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Configuration*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_File_GetInstance() {
    std::shared_ptr<Altseed2::File> cbg_ret = Altseed2::File::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::File>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_File_AddRootDirectory(void* cbg_self, const char16_t* path) {
    auto cbg_self_ = (Altseed2::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    bool cbg_ret = cbg_self_->AddRootDirectory(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_File_AddRootPackageWithPassword(void* cbg_self, const char16_t* path, const char16_t* password) {
    auto cbg_self_ = (Altseed2::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    const char16_t* cbg_arg1 = password;
    bool cbg_ret = cbg_self_->AddRootPackageWithPassword(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_File_AddRootPackage(void* cbg_self, const char16_t* path) {
    auto cbg_self_ = (Altseed2::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    bool cbg_ret = cbg_self_->AddRootPackage(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_File_ClearRootDirectories(void* cbg_self) {
    auto cbg_self_ = (Altseed2::File*)(cbg_self);

    cbg_self_->ClearRootDirectories();
}

CBGEXPORT bool CBGSTDCALL cbg_File_Exists(void* cbg_self, const char16_t* path) {
    auto cbg_self_ = (Altseed2::File*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    bool cbg_ret = cbg_self_->Exists(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_File_Pack(void* cbg_self, const char16_t* srcPath, const char16_t* dstPath) {
    auto cbg_self_ = (Altseed2::File*)(cbg_self);

    const char16_t* cbg_arg0 = srcPath;
    const char16_t* cbg_arg1 = dstPath;
    bool cbg_ret = cbg_self_->Pack(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_File_PackWithPassword(void* cbg_self, const char16_t* srcPath, const char16_t* dstPath, const char16_t* password) {
    auto cbg_self_ = (Altseed2::File*)(cbg_self);

    const char16_t* cbg_arg0 = srcPath;
    const char16_t* cbg_arg1 = dstPath;
    const char16_t* cbg_arg2 = password;
    bool cbg_ret = cbg_self_->PackWithPassword(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_File_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::File*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_File_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::File*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_StaticFile_Create(const char16_t* path) {
    const char16_t* cbg_arg0 = path;
    std::shared_ptr<Altseed2::StaticFile> cbg_ret = Altseed2::StaticFile::Create(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::StaticFile>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_StaticFile_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StaticFile*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
}

CBGEXPORT void* CBGSTDCALL cbg_StaticFile_GetInt8ArrayBuffer(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StaticFile*)(cbg_self);

    std::shared_ptr<Altseed2::Int8Array> cbg_ret = cbg_self_->GetInt8ArrayBuffer();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Int8Array>(cbg_ret);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_StaticFile_GetPath(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StaticFile*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetPath();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_StaticFile_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StaticFile*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetSize();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_StaticFile_GetIsInPackage(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StaticFile*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsInPackage();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_StaticFile_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StaticFile*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_StaticFile_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StaticFile*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Profiler_GetInstance() {
    std::shared_ptr<Altseed2::Profiler> cbg_ret = Altseed2::Profiler::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Profiler>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Profiler_BeginBlock(void* cbg_self, const char16_t* name, const char16_t* _filename, int32_t _line, Altseed2::Color_C color) {
    auto cbg_self_ = (Altseed2::Profiler*)(cbg_self);

    const char16_t* cbg_arg0 = name;
    const char16_t* cbg_arg1 = _filename;
    int32_t cbg_arg2 = _line;
    Altseed2::Color_C cbg_arg3 = color;
    cbg_self_->BeginBlock(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
}

CBGEXPORT void CBGSTDCALL cbg_Profiler_EndBlock(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Profiler*)(cbg_self);

    cbg_self_->EndBlock();
}

CBGEXPORT void CBGSTDCALL cbg_Profiler_StartCapture(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Profiler*)(cbg_self);

    cbg_self_->StartCapture();
}

CBGEXPORT void CBGSTDCALL cbg_Profiler_StopCapture(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Profiler*)(cbg_self);

    cbg_self_->StopCapture();
}

CBGEXPORT void CBGSTDCALL cbg_Profiler_StartListen(void* cbg_self, int32_t port) {
    auto cbg_self_ = (Altseed2::Profiler*)(cbg_self);

    int32_t cbg_arg0 = port;
    cbg_self_->StartListen(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Profiler_DumpToFileAndStopCapture(void* cbg_self, const char16_t* path) {
    auto cbg_self_ = (Altseed2::Profiler*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    cbg_self_->DumpToFileAndStopCapture(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Profiler_GetIsProfilerRunning(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Profiler*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsProfilerRunning();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Profiler_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Profiler*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Profiler_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Profiler*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_ComputePipelineState_Create() {
    std::shared_ptr<Altseed2::ComputePipelineState> cbg_ret = Altseed2::ComputePipelineState::Create();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::ComputePipelineState>(cbg_ret);
}

CBGEXPORT Altseed2::Vector4F_C CBGSTDCALL cbg_ComputePipelineState_GetVector4F(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed2::ComputePipelineState*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Vector4F_C cbg_ret = cbg_self_->GetVector4F(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_ComputePipelineState_SetVector4F(void* cbg_self, const char16_t* key, Altseed2::Vector4F_C value) {
    auto cbg_self_ = (Altseed2::ComputePipelineState*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Vector4F_C cbg_arg1 = value;
    cbg_self_->SetVector4F(cbg_arg0, cbg_arg1);
}

CBGEXPORT Altseed2::Matrix44F_C CBGSTDCALL cbg_ComputePipelineState_GetMatrix44F(void* cbg_self, const char16_t* key) {
    auto cbg_self_ = (Altseed2::ComputePipelineState*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Matrix44F_C cbg_ret = cbg_self_->GetMatrix44F(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_ComputePipelineState_SetMatrix44F(void* cbg_self, const char16_t* key, Altseed2::Matrix44F_C value) {
    auto cbg_self_ = (Altseed2::ComputePipelineState*)(cbg_self);

    const char16_t* cbg_arg0 = key;
    Altseed2::Matrix44F_C cbg_arg1 = value;
    cbg_self_->SetMatrix44F(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_ComputePipelineState_GetShader(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ComputePipelineState*)(cbg_self);

    std::shared_ptr<Altseed2::Shader> cbg_ret = cbg_self_->GetShader();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Shader>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_ComputePipelineState_SetShader(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::ComputePipelineState*)(cbg_self);

    std::shared_ptr<Altseed2::Shader> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Shader>((Altseed2::Shader*)value);
    cbg_self_->SetShader(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_ComputePipelineState_GetPropertyBlock(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ComputePipelineState*)(cbg_self);

    std::shared_ptr<Altseed2::MaterialPropertyBlock> cbg_ret = cbg_self_->GetPropertyBlock();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::MaterialPropertyBlock>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_ComputePipelineState_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ComputePipelineState*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_ComputePipelineState_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ComputePipelineState*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_RenderTexture_Create(Altseed2::Vector2I_C size, int32_t format) {
    Altseed2::Vector2I_C cbg_arg0 = size;
    Altseed2::TextureFormatType cbg_arg1 = (Altseed2::TextureFormatType)format;
    std::shared_ptr<Altseed2::RenderTexture> cbg_ret = Altseed2::RenderTexture::Create(cbg_arg0, cbg_arg1);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::RenderTexture>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_RenderTexture_Save(void* cbg_self, const char16_t* path) {
    auto cbg_self_ = (Altseed2::RenderTexture*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    bool cbg_ret = cbg_self_->Save(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_RenderTexture_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderTexture*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_RenderTexture_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderTexture*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_RenderTexture_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderTexture*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT Altseed2::Vector2I_C CBGSTDCALL cbg_Glyph_GetTextureSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Glyph*)(cbg_self);

    Altseed2::Vector2I_C cbg_ret = cbg_self_->GetTextureSize();
    return (cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Glyph_GetTextureIndex(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Glyph*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetTextureIndex();
    return cbg_ret;
}

CBGEXPORT Altseed2::Vector2I_C CBGSTDCALL cbg_Glyph_GetPosition(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Glyph*)(cbg_self);

    Altseed2::Vector2I_C cbg_ret = cbg_self_->GetPosition();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector2I_C CBGSTDCALL cbg_Glyph_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Glyph*)(cbg_self);

    Altseed2::Vector2I_C cbg_ret = cbg_self_->GetSize();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Glyph_GetOffset(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Glyph*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetOffset();
    return (cbg_ret);
}

CBGEXPORT float CBGSTDCALL cbg_Glyph_GetAdvance(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Glyph*)(cbg_self);

    float cbg_ret = cbg_self_->GetAdvance();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Glyph_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Glyph*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Glyph_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Glyph*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Font_GetGlyph(void* cbg_self, int32_t character) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    int32_t cbg_arg0 = character;
    std::shared_ptr<Altseed2::Glyph> cbg_ret = cbg_self_->GetGlyph(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Glyph>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_Font_GetFontTexture(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    int32_t cbg_arg0 = index;
    std::shared_ptr<Altseed2::Texture2D> cbg_ret = cbg_self_->GetFontTexture(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Texture2D>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Font_GetKerning(void* cbg_self, int32_t c1, int32_t c2) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    int32_t cbg_arg0 = c1;
    int32_t cbg_arg1 = c2;
    int32_t cbg_ret = cbg_self_->GetKerning(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void* CBGSTDCALL cbg_Font_LoadDynamicFont(const char16_t* path, int32_t samplingSize) {
    const char16_t* cbg_arg0 = path;
    int32_t cbg_arg1 = samplingSize;
    std::shared_ptr<Altseed2::Font> cbg_ret = Altseed2::Font::LoadDynamicFont(cbg_arg0, cbg_arg1);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Font>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_Font_LoadStaticFont(const char16_t* path) {
    const char16_t* cbg_arg0 = path;
    std::shared_ptr<Altseed2::Font> cbg_ret = Altseed2::Font::LoadStaticFont(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Font>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_Font_CreateImageFont(void* baseFont) {
    std::shared_ptr<Altseed2::Font> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Font>((Altseed2::Font*)baseFont);
    std::shared_ptr<Altseed2::Font> cbg_ret = Altseed2::Font::CreateImageFont(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Font>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Font_GenerateFontFile(const char16_t* dynamicFontPath, const char16_t* staticFontPath, int32_t samplingSize, const char16_t* characters) {
    const char16_t* cbg_arg0 = dynamicFontPath;
    const char16_t* cbg_arg1 = staticFontPath;
    int32_t cbg_arg2 = samplingSize;
    const char16_t* cbg_arg3 = characters;
    bool cbg_ret = Altseed2::Font::GenerateFontFile(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Font_AddImageGlyph(void* cbg_self, int32_t character, void* texture) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    int32_t cbg_arg0 = character;
    std::shared_ptr<Altseed2::TextureBase> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::TextureBase>((Altseed2::TextureBase*)texture);
    cbg_self_->AddImageGlyph(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_Font_GetImageGlyph(void* cbg_self, int32_t character) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    int32_t cbg_arg0 = character;
    std::shared_ptr<Altseed2::TextureBase> cbg_ret = cbg_self_->GetImageGlyph(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::TextureBase>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Font_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Font_GetSamplingSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetSamplingSize();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Font_GetAscent(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    float cbg_ret = cbg_self_->GetAscent();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Font_GetDescent(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    float cbg_ret = cbg_self_->GetDescent();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Font_GetLineGap(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    float cbg_ret = cbg_self_->GetLineGap();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Font_GetEmSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    float cbg_ret = cbg_self_->GetEmSize();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Font_GetIsStaticFont(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsStaticFont();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Font_GetPath(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetPath();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Font_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Font_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Font*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_ImageFont_GetGlyph(void* cbg_self, int32_t character) {
    auto cbg_self_ = (Altseed2::ImageFont*)(cbg_self);

    int32_t cbg_arg0 = character;
    std::shared_ptr<Altseed2::Glyph> cbg_ret = cbg_self_->GetGlyph(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Glyph>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_ImageFont_GetFontTexture(void* cbg_self, int32_t index) {
    auto cbg_self_ = (Altseed2::ImageFont*)(cbg_self);

    int32_t cbg_arg0 = index;
    std::shared_ptr<Altseed2::Texture2D> cbg_ret = cbg_self_->GetFontTexture(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Texture2D>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_ImageFont_GetKerning(void* cbg_self, int32_t c1, int32_t c2) {
    auto cbg_self_ = (Altseed2::ImageFont*)(cbg_self);

    int32_t cbg_arg0 = c1;
    int32_t cbg_arg1 = c2;
    int32_t cbg_ret = cbg_self_->GetKerning(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_ImageFont_AddImageGlyph(void* cbg_self, int32_t character, void* texture) {
    auto cbg_self_ = (Altseed2::ImageFont*)(cbg_self);

    int32_t cbg_arg0 = character;
    std::shared_ptr<Altseed2::TextureBase> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::TextureBase>((Altseed2::TextureBase*)texture);
    cbg_self_->AddImageGlyph(cbg_arg0, cbg_arg1);
}

CBGEXPORT void* CBGSTDCALL cbg_ImageFont_GetImageGlyph(void* cbg_self, int32_t character) {
    auto cbg_self_ = (Altseed2::ImageFont*)(cbg_self);

    int32_t cbg_arg0 = character;
    std::shared_ptr<Altseed2::TextureBase> cbg_ret = cbg_self_->GetImageGlyph(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::TextureBase>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_ImageFont_GetSamplingSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ImageFont*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetSamplingSize();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_ImageFont_GetAscent(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ImageFont*)(cbg_self);

    float cbg_ret = cbg_self_->GetAscent();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_ImageFont_GetDescent(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ImageFont*)(cbg_self);

    float cbg_ret = cbg_self_->GetDescent();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_ImageFont_GetLineGap(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ImageFont*)(cbg_self);

    float cbg_ret = cbg_self_->GetLineGap();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_ImageFont_GetEmSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ImageFont*)(cbg_self);

    float cbg_ret = cbg_self_->GetEmSize();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_ImageFont_GetIsStaticFont(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ImageFont*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsStaticFont();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_ImageFont_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ImageFont*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_ImageFont_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ImageFont*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_CullingSystem_GetInstance() {
    std::shared_ptr<Altseed2::CullingSystem> cbg_ret = Altseed2::CullingSystem::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::CullingSystem>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_CullingSystem_Initialize() {
    bool cbg_ret = Altseed2::CullingSystem::Initialize();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_CullingSystem_Terminate() {
    Altseed2::CullingSystem::Terminate();
}

CBGEXPORT void CBGSTDCALL cbg_CullingSystem_Register(void* cbg_self, void* rendered) {
    auto cbg_self_ = (Altseed2::CullingSystem*)(cbg_self);

    std::shared_ptr<Altseed2::Rendered> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Rendered>((Altseed2::Rendered*)rendered);
    cbg_self_->Register(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_CullingSystem_UpdateAABB(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CullingSystem*)(cbg_self);

    cbg_self_->UpdateAABB();
}

CBGEXPORT void CBGSTDCALL cbg_CullingSystem_Cull(void* cbg_self, Altseed2::RectF_C rect) {
    auto cbg_self_ = (Altseed2::CullingSystem*)(cbg_self);

    Altseed2::RectF_C cbg_arg0 = rect;
    cbg_self_->Cull(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_CullingSystem_Unregister(void* cbg_self, void* rendered) {
    auto cbg_self_ = (Altseed2::CullingSystem*)(cbg_self);

    std::shared_ptr<Altseed2::Rendered> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Rendered>((Altseed2::Rendered*)rendered);
    cbg_self_->Unregister(cbg_arg0);
}

CBGEXPORT int32_t CBGSTDCALL cbg_CullingSystem_GetDrawingRenderedCount(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CullingSystem*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetDrawingRenderedCount();
    return cbg_ret;
}

CBGEXPORT void* CBGSTDCALL cbg_CullingSystem_GetDrawingRenderedIds(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CullingSystem*)(cbg_self);

    std::shared_ptr<Altseed2::Int32Array> cbg_ret = cbg_self_->GetDrawingRenderedIds();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Int32Array>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_CullingSystem_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CullingSystem*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_CullingSystem_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CullingSystem*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT Altseed2::Matrix44F_C CBGSTDCALL cbg_Rendered_GetTransform(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Rendered*)(cbg_self);

    Altseed2::Matrix44F_C cbg_ret = cbg_self_->GetTransform();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Rendered_SetTransform(void* cbg_self, Altseed2::Matrix44F_C value) {
    auto cbg_self_ = (Altseed2::Rendered*)(cbg_self);

    Altseed2::Matrix44F_C cbg_arg0 = value;
    cbg_self_->SetTransform(cbg_arg0);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Rendered_GetId(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Rendered*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetId();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Rendered_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Rendered*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Rendered_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Rendered*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedCamera_Create() {
    std::shared_ptr<Altseed2::RenderedCamera> cbg_ret = Altseed2::RenderedCamera::Create();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::RenderedCamera>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedCamera_GetTargetTexture(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedCamera*)(cbg_self);

    std::shared_ptr<Altseed2::RenderTexture> cbg_ret = cbg_self_->GetTargetTexture();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::RenderTexture>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedCamera_SetTargetTexture(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::RenderedCamera*)(cbg_self);

    std::shared_ptr<Altseed2::RenderTexture> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::RenderTexture>((Altseed2::RenderTexture*)value);
    cbg_self_->SetTargetTexture(cbg_arg0);
}

CBGEXPORT Altseed2::RenderPassParameter_C CBGSTDCALL cbg_RenderedCamera_GetRenderPassParameter(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedCamera*)(cbg_self);

    Altseed2::RenderPassParameter_C cbg_ret = cbg_self_->GetRenderPassParameter();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedCamera_SetRenderPassParameter(void* cbg_self, Altseed2::RenderPassParameter_C value) {
    auto cbg_self_ = (Altseed2::RenderedCamera*)(cbg_self);

    Altseed2::RenderPassParameter_C cbg_arg0 = value;
    cbg_self_->SetRenderPassParameter(cbg_arg0);
}

CBGEXPORT Altseed2::Matrix44F_C CBGSTDCALL cbg_RenderedCamera_GetProjectionMatrix(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedCamera*)(cbg_self);

    Altseed2::Matrix44F_C cbg_ret = cbg_self_->GetProjectionMatrix();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Matrix44F_C CBGSTDCALL cbg_RenderedCamera_GetViewMatrix(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedCamera*)(cbg_self);

    Altseed2::Matrix44F_C cbg_ret = cbg_self_->GetViewMatrix();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedCamera_SetViewMatrix(void* cbg_self, Altseed2::Matrix44F_C value) {
    auto cbg_self_ = (Altseed2::RenderedCamera*)(cbg_self);

    Altseed2::Matrix44F_C cbg_arg0 = value;
    cbg_self_->SetViewMatrix(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedCamera_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedCamera*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_RenderedCamera_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedCamera*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedSprite_Create() {
    std::shared_ptr<Altseed2::RenderedSprite> cbg_ret = Altseed2::RenderedSprite::Create();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::RenderedSprite>(cbg_ret);
}

CBGEXPORT Altseed2::AlphaBlend_C CBGSTDCALL cbg_RenderedSprite_GetAlphaBlend(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedSprite*)(cbg_self);

    Altseed2::AlphaBlend_C cbg_ret = cbg_self_->GetAlphaBlend();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_SetAlphaBlend(void* cbg_self, Altseed2::AlphaBlend_C value) {
    auto cbg_self_ = (Altseed2::RenderedSprite*)(cbg_self);

    Altseed2::AlphaBlend_C cbg_arg0 = value;
    cbg_self_->SetAlphaBlend(cbg_arg0);
}

CBGEXPORT Altseed2::RectF_C CBGSTDCALL cbg_RenderedSprite_GetSrc(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedSprite*)(cbg_self);

    Altseed2::RectF_C cbg_ret = cbg_self_->GetSrc();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_SetSrc(void* cbg_self, Altseed2::RectF_C value) {
    auto cbg_self_ = (Altseed2::RenderedSprite*)(cbg_self);

    Altseed2::RectF_C cbg_arg0 = value;
    cbg_self_->SetSrc(cbg_arg0);
}

CBGEXPORT Altseed2::Color_C CBGSTDCALL cbg_RenderedSprite_GetColor(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedSprite*)(cbg_self);

    Altseed2::Color_C cbg_ret = cbg_self_->GetColor();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_SetColor(void* cbg_self, Altseed2::Color_C value) {
    auto cbg_self_ = (Altseed2::RenderedSprite*)(cbg_self);

    Altseed2::Color_C cbg_arg0 = value;
    cbg_self_->SetColor(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedSprite_GetTexture(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedSprite*)(cbg_self);

    std::shared_ptr<Altseed2::TextureBase> cbg_ret = cbg_self_->GetTexture();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::TextureBase>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_SetTexture(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::RenderedSprite*)(cbg_self);

    std::shared_ptr<Altseed2::TextureBase> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::TextureBase>((Altseed2::TextureBase*)value);
    cbg_self_->SetTexture(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedSprite_GetMaterial(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedSprite*)(cbg_self);

    std::shared_ptr<Altseed2::Material> cbg_ret = cbg_self_->GetMaterial();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Material>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_SetMaterial(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::RenderedSprite*)(cbg_self);

    std::shared_ptr<Altseed2::Material> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Material>((Altseed2::Material*)value);
    cbg_self_->SetMaterial(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedSprite*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_RenderedSprite_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedSprite*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedText_Create() {
    std::shared_ptr<Altseed2::RenderedText> cbg_ret = Altseed2::RenderedText::Create();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::RenderedText>(cbg_ret);
}

CBGEXPORT Altseed2::AlphaBlend_C CBGSTDCALL cbg_RenderedText_GetAlphaBlend(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    Altseed2::AlphaBlend_C cbg_ret = cbg_self_->GetAlphaBlend();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetAlphaBlend(void* cbg_self, Altseed2::AlphaBlend_C value) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    Altseed2::AlphaBlend_C cbg_arg0 = value;
    cbg_self_->SetAlphaBlend(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedText_GetMaterialGlyph(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    std::shared_ptr<Altseed2::Material> cbg_ret = cbg_self_->GetMaterialGlyph();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Material>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetMaterialGlyph(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    std::shared_ptr<Altseed2::Material> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Material>((Altseed2::Material*)value);
    cbg_self_->SetMaterialGlyph(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedText_GetMaterialImage(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    std::shared_ptr<Altseed2::Material> cbg_ret = cbg_self_->GetMaterialImage();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Material>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetMaterialImage(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    std::shared_ptr<Altseed2::Material> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Material>((Altseed2::Material*)value);
    cbg_self_->SetMaterialImage(cbg_arg0);
}

CBGEXPORT Altseed2::Color_C CBGSTDCALL cbg_RenderedText_GetColor(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    Altseed2::Color_C cbg_ret = cbg_self_->GetColor();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetColor(void* cbg_self, Altseed2::Color_C value) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    Altseed2::Color_C cbg_arg0 = value;
    cbg_self_->SetColor(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedText_GetFont(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    std::shared_ptr<Altseed2::Font> cbg_ret = cbg_self_->GetFont();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Font>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetFont(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    std::shared_ptr<Altseed2::Font> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Font>((Altseed2::Font*)value);
    cbg_self_->SetFont(cbg_arg0);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_RenderedText_GetText(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetText();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetText(void* cbg_self, const char16_t* value) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    const char16_t* cbg_arg0 = value;
    cbg_self_->SetText(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_RenderedText_GetIsEnableKerning(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsEnableKerning();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetIsEnableKerning(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetIsEnableKerning(cbg_arg0);
}

CBGEXPORT int32_t CBGSTDCALL cbg_RenderedText_GetWritingDirection(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    Altseed2::WritingDirection cbg_ret = cbg_self_->GetWritingDirection();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetWritingDirection(void* cbg_self, int32_t value) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    Altseed2::WritingDirection cbg_arg0 = (Altseed2::WritingDirection)value;
    cbg_self_->SetWritingDirection(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_RenderedText_GetCharacterSpace(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    float cbg_ret = cbg_self_->GetCharacterSpace();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetCharacterSpace(void* cbg_self, float value) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    float cbg_arg0 = value;
    cbg_self_->SetCharacterSpace(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_RenderedText_GetLineGap(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    float cbg_ret = cbg_self_->GetLineGap();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetLineGap(void* cbg_self, float value) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    float cbg_arg0 = value;
    cbg_self_->SetLineGap(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_RenderedText_GetFontSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    float cbg_ret = cbg_self_->GetFontSize();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_SetFontSize(void* cbg_self, float value) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    float cbg_arg0 = value;
    cbg_self_->SetFontSize(cbg_arg0);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_RenderedText_GetRenderingSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetRenderingSize();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_RenderedText_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedText*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedPolygon_Create() {
    std::shared_ptr<Altseed2::RenderedPolygon> cbg_ret = Altseed2::RenderedPolygon::Create();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::RenderedPolygon>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_CreateVertexesByVector2F(void* cbg_self, void* vectors) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed2::Vector2FArray> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Vector2FArray>((Altseed2::Vector2FArray*)vectors);
    cbg_self_->CreateVertexesByVector2F(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_OverwriteVertexesColor(void* cbg_self, Altseed2::Color_C color) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    Altseed2::Color_C cbg_arg0 = color;
    cbg_self_->OverwriteVertexesColor(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_SetDefaultIndexBuffer(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    cbg_self_->SetDefaultIndexBuffer();
}

CBGEXPORT Altseed2::AlphaBlend_C CBGSTDCALL cbg_RenderedPolygon_GetAlphaBlend(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    Altseed2::AlphaBlend_C cbg_ret = cbg_self_->GetAlphaBlend();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_SetAlphaBlend(void* cbg_self, Altseed2::AlphaBlend_C value) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    Altseed2::AlphaBlend_C cbg_arg0 = value;
    cbg_self_->SetAlphaBlend(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedPolygon_GetBuffers(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed2::Int32Array> cbg_ret = cbg_self_->GetBuffers();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Int32Array>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_SetBuffers(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed2::Int32Array> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Int32Array>((Altseed2::Int32Array*)value);
    cbg_self_->SetBuffers(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedPolygon_GetVertexes(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed2::VertexArray> cbg_ret = cbg_self_->GetVertexes();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::VertexArray>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_SetVertexes(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed2::VertexArray> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::VertexArray>((Altseed2::VertexArray*)value);
    cbg_self_->SetVertexes(cbg_arg0);
}

CBGEXPORT Altseed2::RectF_C CBGSTDCALL cbg_RenderedPolygon_GetSrc(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    Altseed2::RectF_C cbg_ret = cbg_self_->GetSrc();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_SetSrc(void* cbg_self, Altseed2::RectF_C value) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    Altseed2::RectF_C cbg_arg0 = value;
    cbg_self_->SetSrc(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedPolygon_GetTexture(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed2::TextureBase> cbg_ret = cbg_self_->GetTexture();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::TextureBase>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_SetTexture(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed2::TextureBase> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::TextureBase>((Altseed2::TextureBase*)value);
    cbg_self_->SetTexture(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_RenderedPolygon_GetMaterial(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed2::Material> cbg_ret = cbg_self_->GetMaterial();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Material>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_SetMaterial(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    std::shared_ptr<Altseed2::Material> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Material>((Altseed2::Material*)value);
    cbg_self_->SetMaterial(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_RenderedPolygon_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::RenderedPolygon*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Renderer_GetInstance() {
    std::shared_ptr<Altseed2::Renderer> cbg_ret = Altseed2::Renderer::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Renderer>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Renderer_Initialize(void* window, void* graphics, void* cullingSystem) {
    std::shared_ptr<Altseed2::Window> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Window>((Altseed2::Window*)window);
    std::shared_ptr<Altseed2::Graphics> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::Graphics>((Altseed2::Graphics*)graphics);
    std::shared_ptr<Altseed2::CullingSystem> cbg_arg2 = Altseed2::CreateAndAddSharedPtr<Altseed2::CullingSystem>((Altseed2::CullingSystem*)cullingSystem);
    bool cbg_ret = Altseed2::Renderer::Initialize(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_Terminate() {
    Altseed2::Renderer::Terminate();
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_DrawPolygon(void* cbg_self, void* polygon) {
    auto cbg_self_ = (Altseed2::Renderer*)(cbg_self);

    std::shared_ptr<Altseed2::RenderedPolygon> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::RenderedPolygon>((Altseed2::RenderedPolygon*)polygon);
    cbg_self_->DrawPolygon(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_DrawSprite(void* cbg_self, void* sprite) {
    auto cbg_self_ = (Altseed2::Renderer*)(cbg_self);

    std::shared_ptr<Altseed2::RenderedSprite> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::RenderedSprite>((Altseed2::RenderedSprite*)sprite);
    cbg_self_->DrawSprite(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_DrawText(void* cbg_self, void* text) {
    auto cbg_self_ = (Altseed2::Renderer*)(cbg_self);

    std::shared_ptr<Altseed2::RenderedText> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::RenderedText>((Altseed2::RenderedText*)text);
    cbg_self_->DrawText(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_Render(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Renderer*)(cbg_self);

    cbg_self_->Render();
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_ResetCamera(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Renderer*)(cbg_self);

    cbg_self_->ResetCamera();
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_SetCamera(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::Renderer*)(cbg_self);

    std::shared_ptr<Altseed2::RenderedCamera> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::RenderedCamera>((Altseed2::RenderedCamera*)value);
    cbg_self_->SetCamera(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Renderer*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Renderer_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Renderer*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_ShaderCompiler_GetInstance() {
    std::shared_ptr<Altseed2::ShaderCompiler> cbg_ret = Altseed2::ShaderCompiler::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::ShaderCompiler>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_ShaderCompiler_Initialize(void* graphics, void* file) {
    std::shared_ptr<Altseed2::Graphics> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Graphics>((Altseed2::Graphics*)graphics);
    std::shared_ptr<Altseed2::File> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::File>((Altseed2::File*)file);
    bool cbg_ret = Altseed2::ShaderCompiler::Initialize(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_ShaderCompiler_Terminate() {
    Altseed2::ShaderCompiler::Terminate();
}

CBGEXPORT void CBGSTDCALL cbg_ShaderCompiler_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ShaderCompiler*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_ShaderCompiler_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ShaderCompiler*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_StreamFile_Create(const char16_t* path) {
    const char16_t* cbg_arg0 = path;
    std::shared_ptr<Altseed2::StreamFile> cbg_ret = Altseed2::StreamFile::Create(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::StreamFile>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_StreamFile_Read(void* cbg_self, int32_t size) {
    auto cbg_self_ = (Altseed2::StreamFile*)(cbg_self);

    int32_t cbg_arg0 = size;
    int32_t cbg_ret = cbg_self_->Read(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_StreamFile_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StreamFile*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_StreamFile_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StreamFile*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetSize();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_StreamFile_GetCurrentPosition(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StreamFile*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCurrentPosition();
    return cbg_ret;
}

CBGEXPORT void* CBGSTDCALL cbg_StreamFile_GetInt8ArrayTempBuffer(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StreamFile*)(cbg_self);

    std::shared_ptr<Altseed2::Int8Array> cbg_ret = cbg_self_->GetInt8ArrayTempBuffer();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Int8Array>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_StreamFile_GetTempBufferSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StreamFile*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetTempBufferSize();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_StreamFile_GetIsInPackage(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StreamFile*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsInPackage();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_StreamFile_GetPath(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StreamFile*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetPath();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_StreamFile_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StreamFile*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_StreamFile_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::StreamFile*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Cursor_Create(const char16_t* path, Altseed2::Vector2I_C hot) {
    const char16_t* cbg_arg0 = path;
    Altseed2::Vector2I_C cbg_arg1 = hot;
    std::shared_ptr<Altseed2::Cursor> cbg_ret = Altseed2::Cursor::Create(cbg_arg0, cbg_arg1);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Cursor>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Cursor_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Cursor*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Cursor_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Cursor*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT bool CBGSTDCALL cbg_JoystickInfo_IsJoystickType(void* cbg_self, int32_t type) {
    auto cbg_self_ = (Altseed2::JoystickInfo*)(cbg_self);

    Altseed2::JoystickType cbg_arg0 = (Altseed2::JoystickType)type;
    bool cbg_ret = cbg_self_->IsJoystickType(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_JoystickInfo_GetName(void* cbg_self) {
    auto cbg_self_ = (Altseed2::JoystickInfo*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetName();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_JoystickInfo_GetButtonCount(void* cbg_self) {
    auto cbg_self_ = (Altseed2::JoystickInfo*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetButtonCount();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_JoystickInfo_GetAxisCount(void* cbg_self) {
    auto cbg_self_ = (Altseed2::JoystickInfo*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetAxisCount();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_JoystickInfo_GetIsGamepad(void* cbg_self) {
    auto cbg_self_ = (Altseed2::JoystickInfo*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsGamepad();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_JoystickInfo_GetGamepadName(void* cbg_self) {
    auto cbg_self_ = (Altseed2::JoystickInfo*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetGamepadName();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_JoystickInfo_GetGUID(void* cbg_self) {
    auto cbg_self_ = (Altseed2::JoystickInfo*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetGUID();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_JoystickInfo_GetBustype(void* cbg_self) {
    auto cbg_self_ = (Altseed2::JoystickInfo*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetBustype();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_JoystickInfo_GetVendor(void* cbg_self) {
    auto cbg_self_ = (Altseed2::JoystickInfo*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetVendor();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_JoystickInfo_GetProduct(void* cbg_self) {
    auto cbg_self_ = (Altseed2::JoystickInfo*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetProduct();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_JoystickInfo_GetVersion(void* cbg_self) {
    auto cbg_self_ = (Altseed2::JoystickInfo*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetVersion();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_JoystickInfo_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::JoystickInfo*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_JoystickInfo_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::JoystickInfo*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Joystick_GetInstance() {
    std::shared_ptr<Altseed2::Joystick> cbg_ret = Altseed2::Joystick::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Joystick>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Joystick_RefreshInputState(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Joystick*)(cbg_self);

    cbg_self_->RefreshInputState();
}

CBGEXPORT bool CBGSTDCALL cbg_Joystick_IsPresent(void* cbg_self, int32_t joystickIndex) {
    auto cbg_self_ = (Altseed2::Joystick*)(cbg_self);

    int32_t cbg_arg0 = joystickIndex;
    bool cbg_ret = cbg_self_->IsPresent(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void* CBGSTDCALL cbg_Joystick_GetJoystickInfo(void* cbg_self, int32_t joystickIndex) {
    auto cbg_self_ = (Altseed2::Joystick*)(cbg_self);

    int32_t cbg_arg0 = joystickIndex;
    std::shared_ptr<Altseed2::JoystickInfo> cbg_ret = cbg_self_->GetJoystickInfo(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::JoystickInfo>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Joystick_GetButtonStateByIndex(void* cbg_self, int32_t joystickIndex, int32_t buttonIndex) {
    auto cbg_self_ = (Altseed2::Joystick*)(cbg_self);

    int32_t cbg_arg0 = joystickIndex;
    int32_t cbg_arg1 = buttonIndex;
    Altseed2::ButtonState cbg_ret = cbg_self_->GetButtonStateByIndex(cbg_arg0, cbg_arg1);
    return (int32_t)cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Joystick_GetButtonStateByType(void* cbg_self, int32_t joystickIndex, int32_t type) {
    auto cbg_self_ = (Altseed2::Joystick*)(cbg_self);

    int32_t cbg_arg0 = joystickIndex;
    Altseed2::JoystickButton cbg_arg1 = (Altseed2::JoystickButton)type;
    Altseed2::ButtonState cbg_ret = cbg_self_->GetButtonStateByType(cbg_arg0, cbg_arg1);
    return (int32_t)cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Joystick_GetAxisStateByIndex(void* cbg_self, int32_t joystickIndex, int32_t axisIndex) {
    auto cbg_self_ = (Altseed2::Joystick*)(cbg_self);

    int32_t cbg_arg0 = joystickIndex;
    int32_t cbg_arg1 = axisIndex;
    float cbg_ret = cbg_self_->GetAxisStateByIndex(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Joystick_GetAxisStateByType(void* cbg_self, int32_t joystickIndex, int32_t type) {
    auto cbg_self_ = (Altseed2::Joystick*)(cbg_self);

    int32_t cbg_arg0 = joystickIndex;
    Altseed2::JoystickAxis cbg_arg1 = (Altseed2::JoystickAxis)type;
    float cbg_ret = cbg_self_->GetAxisStateByType(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Joystick_GetConnectedJoystickCount(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Joystick*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetConnectedJoystickCount();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Joystick_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Joystick*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Joystick_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Joystick*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Keyboard_GetInstance() {
    std::shared_ptr<Altseed2::Keyboard> cbg_ret = Altseed2::Keyboard::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Keyboard>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Keyboard_RefleshKeyStates(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Keyboard*)(cbg_self);

    cbg_self_->RefleshKeyStates();
}

CBGEXPORT int32_t CBGSTDCALL cbg_Keyboard_GetKeyState(void* cbg_self, int32_t key) {
    auto cbg_self_ = (Altseed2::Keyboard*)(cbg_self);

    Altseed2::Key cbg_arg0 = (Altseed2::Key)key;
    Altseed2::ButtonState cbg_ret = cbg_self_->GetKeyState(cbg_arg0);
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Keyboard_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Keyboard*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Keyboard_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Keyboard*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Mouse_GetInstance() {
    std::shared_ptr<Altseed2::Mouse> cbg_ret = Altseed2::Mouse::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Mouse>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_RefreshInputState(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Mouse*)(cbg_self);

    cbg_self_->RefreshInputState();
}

CBGEXPORT int32_t CBGSTDCALL cbg_Mouse_GetMouseButtonState(void* cbg_self, int32_t button) {
    auto cbg_self_ = (Altseed2::Mouse*)(cbg_self);

    Altseed2::MouseButton cbg_arg0 = (Altseed2::MouseButton)button;
    Altseed2::ButtonState cbg_ret = cbg_self_->GetMouseButtonState(cbg_arg0);
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_SetMouseButtonState(void* cbg_self, int32_t button, int32_t state) {
    auto cbg_self_ = (Altseed2::Mouse*)(cbg_self);

    Altseed2::MouseButton cbg_arg0 = (Altseed2::MouseButton)button;
    Altseed2::ButtonState cbg_arg1 = (Altseed2::ButtonState)state;
    cbg_self_->SetMouseButtonState(cbg_arg0, cbg_arg1);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Mouse_GetPosition(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Mouse*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetPosition();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_SetPosition(void* cbg_self, Altseed2::Vector2F_C value) {
    auto cbg_self_ = (Altseed2::Mouse*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = value;
    cbg_self_->SetPosition(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_Mouse_GetWheel(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Mouse*)(cbg_self);

    float cbg_ret = cbg_self_->GetWheel();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Mouse_GetCursorMode(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Mouse*)(cbg_self);

    Altseed2::CursorMode cbg_ret = cbg_self_->GetCursorMode();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_SetCursorMode(void* cbg_self, int32_t value) {
    auto cbg_self_ = (Altseed2::Mouse*)(cbg_self);

    Altseed2::CursorMode cbg_arg0 = (Altseed2::CursorMode)value;
    cbg_self_->SetCursorMode(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_SetCursorImage(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::Mouse*)(cbg_self);

    std::shared_ptr<Altseed2::Cursor> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Cursor>((Altseed2::Cursor*)value);
    cbg_self_->SetCursorImage(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Mouse*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Mouse_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Mouse*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT bool CBGSTDCALL cbg_MediaPlayer_Play(void* cbg_self, bool isLoopingMode) {
    auto cbg_self_ = (Altseed2::MediaPlayer*)(cbg_self);

    bool cbg_arg0 = isLoopingMode;
    bool cbg_ret = cbg_self_->Play(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_MediaPlayer_WriteToRenderTexture(void* cbg_self, void* target) {
    auto cbg_self_ = (Altseed2::MediaPlayer*)(cbg_self);

    std::shared_ptr<Altseed2::RenderTexture> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::RenderTexture>((Altseed2::RenderTexture*)target);
    bool cbg_ret = cbg_self_->WriteToRenderTexture(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void* CBGSTDCALL cbg_MediaPlayer_Load(const char16_t* path) {
    const char16_t* cbg_arg0 = path;
    std::shared_ptr<Altseed2::MediaPlayer> cbg_ret = Altseed2::MediaPlayer::Load(cbg_arg0);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::MediaPlayer>(cbg_ret);
}

CBGEXPORT Altseed2::Vector2I_C CBGSTDCALL cbg_MediaPlayer_GetSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::MediaPlayer*)(cbg_self);

    Altseed2::Vector2I_C cbg_ret = cbg_self_->GetSize();
    return (cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_MediaPlayer_GetCurrentFrame(void* cbg_self) {
    auto cbg_self_ = (Altseed2::MediaPlayer*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetCurrentFrame();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_MediaPlayer_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::MediaPlayer*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_MediaPlayer_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::MediaPlayer*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT bool CBGSTDCALL cbg_Collider_GetIsCollidedWith(void* cbg_self, void* collider) {
    auto cbg_self_ = (Altseed2::Collider*)(cbg_self);

    std::shared_ptr<Altseed2::Collider> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Collider>((Altseed2::Collider*)collider);
    bool cbg_ret = cbg_self_->GetIsCollidedWith(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Collider_GetPosition(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Collider*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetPosition();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Collider_SetPosition(void* cbg_self, Altseed2::Vector2F_C value) {
    auto cbg_self_ = (Altseed2::Collider*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = value;
    cbg_self_->SetPosition(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_Collider_GetRotation(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Collider*)(cbg_self);

    float cbg_ret = cbg_self_->GetRotation();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Collider_SetRotation(void* cbg_self, float value) {
    auto cbg_self_ = (Altseed2::Collider*)(cbg_self);

    float cbg_arg0 = value;
    cbg_self_->SetRotation(cbg_arg0);
}

CBGEXPORT Altseed2::Matrix44F_C CBGSTDCALL cbg_Collider_GetTransform(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Collider*)(cbg_self);

    Altseed2::Matrix44F_C cbg_ret = cbg_self_->GetTransform();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Collider_SetTransform(void* cbg_self, Altseed2::Matrix44F_C value) {
    auto cbg_self_ = (Altseed2::Collider*)(cbg_self);

    Altseed2::Matrix44F_C cbg_arg0 = value;
    cbg_self_->SetTransform(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Collider_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Collider*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Collider_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Collider*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_ShapeCollider_Create() {
    std::shared_ptr<Altseed2::ShapeCollider> cbg_ret = Altseed2::ShapeCollider::Create();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::ShapeCollider>(cbg_ret);
}

CBGEXPORT void* CBGSTDCALL cbg_ShapeCollider_GetVertexes(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ShapeCollider*)(cbg_self);

    std::shared_ptr<Altseed2::Vector2FArray> cbg_ret = cbg_self_->GetVertexes();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Vector2FArray>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_ShapeCollider_SetVertexes(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::ShapeCollider*)(cbg_self);

    std::shared_ptr<Altseed2::Vector2FArray> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Vector2FArray>((Altseed2::Vector2FArray*)value);
    cbg_self_->SetVertexes(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_ShapeCollider_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ShapeCollider*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_ShapeCollider_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::ShapeCollider*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_PolygonCollider_Create() {
    std::shared_ptr<Altseed2::PolygonCollider> cbg_ret = Altseed2::PolygonCollider::Create();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::PolygonCollider>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_PolygonCollider_SetDefaultIndexBuffer(void* cbg_self) {
    auto cbg_self_ = (Altseed2::PolygonCollider*)(cbg_self);

    cbg_self_->SetDefaultIndexBuffer();
}

CBGEXPORT void* CBGSTDCALL cbg_PolygonCollider_GetBuffers(void* cbg_self) {
    auto cbg_self_ = (Altseed2::PolygonCollider*)(cbg_self);

    std::shared_ptr<Altseed2::Int32Array> cbg_ret = cbg_self_->GetBuffers();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Int32Array>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_PolygonCollider_SetBuffers(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::PolygonCollider*)(cbg_self);

    std::shared_ptr<Altseed2::Int32Array> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Int32Array>((Altseed2::Int32Array*)value);
    cbg_self_->SetBuffers(cbg_arg0);
}

CBGEXPORT void* CBGSTDCALL cbg_PolygonCollider_GetVertexes(void* cbg_self) {
    auto cbg_self_ = (Altseed2::PolygonCollider*)(cbg_self);

    std::shared_ptr<Altseed2::Vector2FArray> cbg_ret = cbg_self_->GetVertexes();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Vector2FArray>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_PolygonCollider_SetVertexes(void* cbg_self, void* value) {
    auto cbg_self_ = (Altseed2::PolygonCollider*)(cbg_self);

    std::shared_ptr<Altseed2::Vector2FArray> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Vector2FArray>((Altseed2::Vector2FArray*)value);
    cbg_self_->SetVertexes(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_PolygonCollider_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::PolygonCollider*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_PolygonCollider_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::PolygonCollider*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_EdgeCollider_Create() {
    std::shared_ptr<Altseed2::EdgeCollider> cbg_ret = Altseed2::EdgeCollider::Create();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::EdgeCollider>(cbg_ret);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_EdgeCollider_GetPoint1(void* cbg_self) {
    auto cbg_self_ = (Altseed2::EdgeCollider*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetPoint1();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_EdgeCollider_SetPoint1(void* cbg_self, Altseed2::Vector2F_C value) {
    auto cbg_self_ = (Altseed2::EdgeCollider*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = value;
    cbg_self_->SetPoint1(cbg_arg0);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_EdgeCollider_GetPoint2(void* cbg_self) {
    auto cbg_self_ = (Altseed2::EdgeCollider*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetPoint2();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_EdgeCollider_SetPoint2(void* cbg_self, Altseed2::Vector2F_C value) {
    auto cbg_self_ = (Altseed2::EdgeCollider*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = value;
    cbg_self_->SetPoint2(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_EdgeCollider_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::EdgeCollider*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_EdgeCollider_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::EdgeCollider*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_CircleCollider_Create() {
    std::shared_ptr<Altseed2::CircleCollider> cbg_ret = Altseed2::CircleCollider::Create();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::CircleCollider>(cbg_ret);
}

CBGEXPORT float CBGSTDCALL cbg_CircleCollider_GetRadius(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CircleCollider*)(cbg_self);

    float cbg_ret = cbg_self_->GetRadius();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_CircleCollider_SetRadius(void* cbg_self, float value) {
    auto cbg_self_ = (Altseed2::CircleCollider*)(cbg_self);

    float cbg_arg0 = value;
    cbg_self_->SetRadius(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_CircleCollider_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CircleCollider*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_CircleCollider_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::CircleCollider*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Sound_Load(const char16_t* path, bool isDecompressed) {
    const char16_t* cbg_arg0 = path;
    bool cbg_arg1 = isDecompressed;
    std::shared_ptr<Altseed2::Sound> cbg_ret = Altseed2::Sound::Load(cbg_arg0, cbg_arg1);
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Sound>(cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Sound_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Sound*)(cbg_self);

    bool cbg_ret = cbg_self_->Reload();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Sound_GetLoopStartingPoint(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Sound*)(cbg_self);

    float cbg_ret = cbg_self_->GetLoopStartingPoint();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Sound_SetLoopStartingPoint(void* cbg_self, float value) {
    auto cbg_self_ = (Altseed2::Sound*)(cbg_self);

    float cbg_arg0 = value;
    cbg_self_->SetLoopStartingPoint(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_Sound_GetLoopEndPoint(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Sound*)(cbg_self);

    float cbg_ret = cbg_self_->GetLoopEndPoint();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Sound_SetLoopEndPoint(void* cbg_self, float value) {
    auto cbg_self_ = (Altseed2::Sound*)(cbg_self);

    float cbg_arg0 = value;
    cbg_self_->SetLoopEndPoint(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Sound_GetIsLoopingMode(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Sound*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsLoopingMode();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Sound_SetIsLoopingMode(void* cbg_self, bool value) {
    auto cbg_self_ = (Altseed2::Sound*)(cbg_self);

    bool cbg_arg0 = value;
    cbg_self_->SetIsLoopingMode(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_Sound_GetLength(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Sound*)(cbg_self);

    float cbg_ret = cbg_self_->GetLength();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Sound_GetPath(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Sound*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetPath();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Sound_GetIsDecompressed(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Sound*)(cbg_self);

    bool cbg_ret = cbg_self_->GetIsDecompressed();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Sound_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Sound*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Sound_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Sound*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_SoundMixer_GetInstance() {
    std::shared_ptr<Altseed2::SoundMixer> cbg_ret = Altseed2::SoundMixer::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::SoundMixer>(cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_SoundMixer_Play(void* cbg_self, void* sound) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    std::shared_ptr<Altseed2::Sound> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::Sound>((Altseed2::Sound*)sound);
    int32_t cbg_ret = cbg_self_->Play(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_SoundMixer_GetIsPlaying(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    bool cbg_ret = cbg_self_->GetIsPlaying(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_StopAll(void* cbg_self) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    cbg_self_->StopAll();
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_Stop(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    cbg_self_->Stop(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_Pause(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    cbg_self_->Pause(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_Resume(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    cbg_self_->Resume(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_SetVolume(void* cbg_self, int32_t id, float volume) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = volume;
    cbg_self_->SetVolume(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_FadeIn(void* cbg_self, int32_t id, float second) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = second;
    cbg_self_->FadeIn(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_FadeOut(void* cbg_self, int32_t id, float second) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = second;
    cbg_self_->FadeOut(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_Fade(void* cbg_self, int32_t id, float second, float targetedVolume) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = second;
    float cbg_arg2 = targetedVolume;
    cbg_self_->Fade(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT bool CBGSTDCALL cbg_SoundMixer_GetIsPlaybackSpeedEnabled(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    bool cbg_ret = cbg_self_->GetIsPlaybackSpeedEnabled(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_SetIsPlaybackSpeedEnabled(void* cbg_self, int32_t id, bool isPlaybackSpeedEnabled) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    bool cbg_arg1 = isPlaybackSpeedEnabled;
    cbg_self_->SetIsPlaybackSpeedEnabled(cbg_arg0, cbg_arg1);
}

CBGEXPORT float CBGSTDCALL cbg_SoundMixer_GetPlaybackSpeed(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_ret = cbg_self_->GetPlaybackSpeed(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_SetPlaybackSpeed(void* cbg_self, int32_t id, float playbackSpeed) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = playbackSpeed;
    cbg_self_->SetPlaybackSpeed(cbg_arg0, cbg_arg1);
}

CBGEXPORT float CBGSTDCALL cbg_SoundMixer_GetPanningPosition(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_ret = cbg_self_->GetPanningPosition(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_SetPanningPosition(void* cbg_self, int32_t id, float panningPosition) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = panningPosition;
    cbg_self_->SetPanningPosition(cbg_arg0, cbg_arg1);
}

CBGEXPORT float CBGSTDCALL cbg_SoundMixer_GetPlaybackPosition(void* cbg_self, int32_t id) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_ret = cbg_self_->GetPlaybackPosition(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_SetPlaybackPosition(void* cbg_self, int32_t id, float position) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    float cbg_arg1 = position;
    cbg_self_->SetPlaybackPosition(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_GetSpectrum(void* cbg_self, int32_t id, void* spectrums, int32_t window) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    int32_t cbg_arg0 = id;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)spectrums);
    Altseed2::FFTWindow cbg_arg2 = (Altseed2::FFTWindow)window;
    cbg_self_->GetSpectrum(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_Reload(void* cbg_self) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    cbg_self_->Reload();
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_SoundMixer_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::SoundMixer*)(cbg_self);

    cbg_self_->Release();
}

CBGEXPORT void* CBGSTDCALL cbg_Tool_GetInstance() {
    std::shared_ptr<Altseed2::Tool> cbg_ret = Altseed2::Tool::GetInstance();
    return (void*)Altseed2::AddAndGetSharedPtr<Altseed2::Tool>(cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_NewFrame(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->NewFrame();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Render(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->Render();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_AddFontFromFileTTF(void* cbg_self, const char16_t* path, float sizePixels, int32_t ranges) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = path;
    float cbg_arg1 = sizePixels;
    Altseed2::ToolGlyphRange cbg_arg2 = (Altseed2::ToolGlyphRange)ranges;
    bool cbg_ret = cbg_self_->AddFontFromFileTTF(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_ListBox(void* cbg_self, const char16_t* label, int32_t * current, const char16_t* items_separated_by_tabs, int32_t popup_max_height_in_items) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    int32_t* cbg_arg1 = current;
    const char16_t* cbg_arg2 = items_separated_by_tabs;
    int32_t cbg_arg3 = popup_max_height_in_items;
    bool cbg_ret = cbg_self_->ListBox(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Tool_InputText(void* cbg_self, const char16_t* label, const char16_t* input, int32_t max_length, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    const char16_t* cbg_arg1 = input;
    int32_t cbg_arg2 = max_length;
    Altseed2::ToolInputTextFlags cbg_arg3 = (Altseed2::ToolInputTextFlags)flags;
    const char16_t* cbg_ret = cbg_self_->InputText(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Tool_InputTextWithHint(void* cbg_self, const char16_t* label, const char16_t* hint, const char16_t* input, int32_t max_length, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    const char16_t* cbg_arg1 = hint;
    const char16_t* cbg_arg2 = input;
    int32_t cbg_arg3 = max_length;
    Altseed2::ToolInputTextFlags cbg_arg4 = (Altseed2::ToolInputTextFlags)flags;
    const char16_t* cbg_ret = cbg_self_->InputTextWithHint(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4);
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Tool_InputTextMultiline(void* cbg_self, const char16_t* label, const char16_t* input, int32_t max_length, Altseed2::Vector2F_C size, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    const char16_t* cbg_arg1 = input;
    int32_t cbg_arg2 = max_length;
    Altseed2::Vector2F_C cbg_arg3 = size;
    Altseed2::ToolInputTextFlags cbg_arg4 = (Altseed2::ToolInputTextFlags)flags;
    const char16_t* cbg_ret = cbg_self_->InputTextMultiline(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_ColorEdit3_char16p_FloatArray_ToolColorEditFlags(void* cbg_self, const char16_t* label, void* col, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)col);
    Altseed2::ToolColorEditFlags cbg_arg2 = (Altseed2::ToolColorEditFlags)flags;
    bool cbg_ret = cbg_self_->ColorEdit3(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_ColorEdit4_char16p_FloatArray_ToolColorEditFlags(void* cbg_self, const char16_t* label, void* col, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)col);
    Altseed2::ToolColorEditFlags cbg_arg2 = (Altseed2::ToolColorEditFlags)flags;
    bool cbg_ret = cbg_self_->ColorEdit4(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Image(void* cbg_self, void* texture, Altseed2::Vector2F_C size, Altseed2::Vector2F_C uv0, Altseed2::Vector2F_C uv1, Altseed2::Color_C tint_col, Altseed2::Color_C border_col) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    std::shared_ptr<Altseed2::TextureBase> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::TextureBase>((Altseed2::TextureBase*)texture);
    Altseed2::Vector2F_C cbg_arg1 = size;
    Altseed2::Vector2F_C cbg_arg2 = uv0;
    Altseed2::Vector2F_C cbg_arg3 = uv1;
    Altseed2::Color_C cbg_arg4 = tint_col;
    Altseed2::Color_C cbg_arg5 = border_col;
    cbg_self_->Image(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_ImageButton(void* cbg_self, void* texture, Altseed2::Vector2F_C size, Altseed2::Vector2F_C uv0, Altseed2::Vector2F_C uv1, int32_t frame_padding, Altseed2::Color_C bg_col, Altseed2::Color_C tint_col) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    std::shared_ptr<Altseed2::TextureBase> cbg_arg0 = Altseed2::CreateAndAddSharedPtr<Altseed2::TextureBase>((Altseed2::TextureBase*)texture);
    Altseed2::Vector2F_C cbg_arg1 = size;
    Altseed2::Vector2F_C cbg_arg2 = uv0;
    Altseed2::Vector2F_C cbg_arg3 = uv1;
    int32_t cbg_arg4 = frame_padding;
    Altseed2::Color_C cbg_arg5 = bg_col;
    Altseed2::Color_C cbg_arg6 = tint_col;
    bool cbg_ret = cbg_self_->ImageButton(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_Combo(void* cbg_self, const char16_t* label, int32_t * current_item, const char16_t* items_separated_by_tabs, int32_t popup_max_height_in_items) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    int32_t* cbg_arg1 = current_item;
    const char16_t* cbg_arg2 = items_separated_by_tabs;
    int32_t cbg_arg3 = popup_max_height_in_items;
    bool cbg_ret = cbg_self_->Combo(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PlotLines(void* cbg_self, const char16_t* label, void* values, int32_t values_count, int32_t values_offset, const char16_t* overlay_text, float scale_min, float scale_max, Altseed2::Vector2F_C graph_size, int32_t stride) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)values);
    int32_t cbg_arg2 = values_count;
    int32_t cbg_arg3 = values_offset;
    const char16_t* cbg_arg4 = overlay_text;
    float cbg_arg5 = scale_min;
    float cbg_arg6 = scale_max;
    Altseed2::Vector2F_C cbg_arg7 = graph_size;
    int32_t cbg_arg8 = stride;
    cbg_self_->PlotLines(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6, cbg_arg7, cbg_arg8);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PlotHistogram(void* cbg_self, const char16_t* label, void* values, int32_t values_count, int32_t values_offset, const char16_t* overlay_text, float scale_min, float scale_max, Altseed2::Vector2F_C graph_size, int32_t stride) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)values);
    int32_t cbg_arg2 = values_count;
    int32_t cbg_arg3 = values_offset;
    const char16_t* cbg_arg4 = overlay_text;
    float cbg_arg5 = scale_min;
    float cbg_arg6 = scale_max;
    Altseed2::Vector2F_C cbg_arg7 = graph_size;
    int32_t cbg_arg8 = stride;
    cbg_self_->PlotHistogram(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6, cbg_arg7, cbg_arg8);
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetTime(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetTime();
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_GetMainViewportID(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetMainViewportID();
    return cbg_ret;
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetMainViewportPos(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetMainViewportPos();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetMainViewportSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetMainViewportSize();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetMainViewportWorkPos(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetMainViewportWorkPos();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetMainViewportWorkSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetMainViewportWorkSize();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_DockSpace(void* cbg_self, int32_t id, Altseed2::Vector2F_C size, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = id;
    Altseed2::Vector2F_C cbg_arg1 = size;
    Altseed2::ToolDockNodeFlags cbg_arg2 = (Altseed2::ToolDockNodeFlags)flags;
    cbg_self_->DockSpace(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginDockHost(void* cbg_self, const char16_t* label, Altseed2::Vector2F_C offset) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed2::Vector2F_C cbg_arg1 = offset;
    bool cbg_ret = cbg_self_->BeginDockHost(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_ShowDemoWindowNoCloseButton(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->ShowDemoWindowNoCloseButton();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_ShowAboutWindowNoCloseButton(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->ShowAboutWindowNoCloseButton();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_ShowMetricsWindowNoCloseButton(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->ShowMetricsWindowNoCloseButton();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_Begin_char16p_ToolWindowFlags(void* cbg_self, const char16_t* name, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = name;
    Altseed2::ToolWindowFlags cbg_arg1 = (Altseed2::ToolWindowFlags)flags;
    bool cbg_ret = cbg_self_->Begin(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_Begin_char16p_boolp_ToolWindowFlags(void* cbg_self, const char16_t* name, bool * p_open, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = name;
    bool* cbg_arg1 = p_open;
    Altseed2::ToolWindowFlags cbg_arg2 = (Altseed2::ToolWindowFlags)flags;
    bool cbg_ret = cbg_self_->Begin(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginPopupModal_char16p_ToolWindowFlags(void* cbg_self, const char16_t* name, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = name;
    Altseed2::ToolWindowFlags cbg_arg1 = (Altseed2::ToolWindowFlags)flags;
    bool cbg_ret = cbg_self_->BeginPopupModal(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginPopupModal_char16p_boolp_ToolWindowFlags(void* cbg_self, const char16_t* name, bool * p_open, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = name;
    bool* cbg_arg1 = p_open;
    Altseed2::ToolWindowFlags cbg_arg2 = (Altseed2::ToolWindowFlags)flags;
    bool cbg_ret = cbg_self_->BeginPopupModal(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginTabItem_char16p_ToolTabItemFlags(void* cbg_self, const char16_t* label, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed2::ToolTabItemFlags cbg_arg1 = (Altseed2::ToolTabItemFlags)flags;
    bool cbg_ret = cbg_self_->BeginTabItem(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginTabItem_char16p_boolp_ToolTabItemFlags(void* cbg_self, const char16_t* label, bool * p_open, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool* cbg_arg1 = p_open;
    Altseed2::ToolTabItemFlags cbg_arg2 = (Altseed2::ToolTabItemFlags)flags;
    bool cbg_ret = cbg_self_->BeginTabItem(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Tool_OpenDialog(void* cbg_self, const char16_t* filter, const char16_t* defaultPath) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = filter;
    const char16_t* cbg_arg1 = defaultPath;
    const char16_t* cbg_ret = cbg_self_->OpenDialog(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Tool_OpenDialogMultiple(void* cbg_self, const char16_t* filter, const char16_t* defaultPath) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = filter;
    const char16_t* cbg_arg1 = defaultPath;
    const char16_t* cbg_ret = cbg_self_->OpenDialogMultiple(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Tool_SaveDialog(void* cbg_self, const char16_t* filter, const char16_t* defaultPath) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = filter;
    const char16_t* cbg_arg1 = defaultPath;
    const char16_t* cbg_ret = cbg_self_->SaveDialog(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Tool_PickFolder(void* cbg_self, const char16_t* defaultPath) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = defaultPath;
    const char16_t* cbg_ret = cbg_self_->PickFolder(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SetDragDropPayload(void* cbg_self, const char16_t* type, void* data, int32_t cond) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = type;
    std::shared_ptr<Altseed2::Int8Array> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::Int8Array>((Altseed2::Int8Array*)data);
    Altseed2::ToolCond cbg_arg2 = (Altseed2::ToolCond)cond;
    bool cbg_ret = cbg_self_->SetDragDropPayload(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_AcceptDragDropPayload(void* cbg_self, const char16_t* type, int32_t dragDropFlags, void* result) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = type;
    Altseed2::ToolDragDropFlags cbg_arg1 = (Altseed2::ToolDragDropFlags)dragDropFlags;
    std::shared_ptr<Altseed2::Int8Array> cbg_arg2 = Altseed2::CreateAndAddSharedPtr<Altseed2::Int8Array>((Altseed2::Int8Array*)result);
    bool cbg_ret = cbg_self_->AcceptDragDropPayload(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_ShowDemoWindow(void* cbg_self, bool * p_open) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool* cbg_arg0 = p_open;
    cbg_self_->ShowDemoWindow(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_ShowAboutWindow(void* cbg_self, bool * p_open) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool* cbg_arg0 = p_open;
    cbg_self_->ShowAboutWindow(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_ShowMetricsWindow(void* cbg_self, bool * p_open) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool* cbg_arg0 = p_open;
    cbg_self_->ShowMetricsWindow(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_ShowStyleSelector(void* cbg_self, const char16_t* label) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool cbg_ret = cbg_self_->ShowStyleSelector(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_ShowFontSelector(void* cbg_self, const char16_t* label) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    cbg_self_->ShowFontSelector(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_ShowUserGuide(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->ShowUserGuide();
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Tool_GetVersion(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetVersion();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_End(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->End();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginChild_char16p_Vector2F_C_bool_ToolWindowFlags(void* cbg_self, const char16_t* str_id, Altseed2::Vector2F_C size, bool border, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    Altseed2::Vector2F_C cbg_arg1 = size;
    bool cbg_arg2 = border;
    Altseed2::ToolWindowFlags cbg_arg3 = (Altseed2::ToolWindowFlags)flags;
    bool cbg_ret = cbg_self_->BeginChild(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginChild_int_Vector2F_C_bool_ToolWindowFlags(void* cbg_self, int32_t id, Altseed2::Vector2F_C size, bool border, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = id;
    Altseed2::Vector2F_C cbg_arg1 = size;
    bool cbg_arg2 = border;
    Altseed2::ToolWindowFlags cbg_arg3 = (Altseed2::ToolWindowFlags)flags;
    bool cbg_ret = cbg_self_->BeginChild(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndChild(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->EndChild();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsWindowAppearing(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsWindowAppearing();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsWindowCollapsed(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsWindowCollapsed();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsWindowFocused(void* cbg_self, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolFocusedFlags cbg_arg0 = (Altseed2::ToolFocusedFlags)flags;
    bool cbg_ret = cbg_self_->IsWindowFocused(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsWindowHovered(void* cbg_self, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolHoveredFlags cbg_arg0 = (Altseed2::ToolHoveredFlags)flags;
    bool cbg_ret = cbg_self_->IsWindowHovered(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetWindowDpiScale(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetWindowDpiScale();
    return cbg_ret;
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetWindowPos(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetWindowPos();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetWindowSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetWindowSize();
    return (cbg_ret);
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetWindowWidth(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetWindowWidth();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetWindowHeight(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetWindowHeight();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextWindowPos(void* cbg_self, Altseed2::Vector2F_C pos, int32_t cond, Altseed2::Vector2F_C pivot) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = pos;
    Altseed2::ToolCond cbg_arg1 = (Altseed2::ToolCond)cond;
    Altseed2::Vector2F_C cbg_arg2 = pivot;
    cbg_self_->SetNextWindowPos(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextWindowSize(void* cbg_self, Altseed2::Vector2F_C size, int32_t cond) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = size;
    Altseed2::ToolCond cbg_arg1 = (Altseed2::ToolCond)cond;
    cbg_self_->SetNextWindowSize(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextWindowContentSize(void* cbg_self, Altseed2::Vector2F_C size) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = size;
    cbg_self_->SetNextWindowContentSize(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextWindowCollapsed(void* cbg_self, bool collapsed, int32_t cond) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_arg0 = collapsed;
    Altseed2::ToolCond cbg_arg1 = (Altseed2::ToolCond)cond;
    cbg_self_->SetNextWindowCollapsed(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextWindowFocus(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->SetNextWindowFocus();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextWindowBgAlpha(void* cbg_self, float alpha) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = alpha;
    cbg_self_->SetNextWindowBgAlpha(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextWindowViewport(void* cbg_self, int32_t viewport_id) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = viewport_id;
    cbg_self_->SetNextWindowViewport(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetWindowPos_Vector2F_C_ToolCond(void* cbg_self, Altseed2::Vector2F_C pos, int32_t cond) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = pos;
    Altseed2::ToolCond cbg_arg1 = (Altseed2::ToolCond)cond;
    cbg_self_->SetWindowPos(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetWindowPos_char16p_Vector2F_C_ToolCond(void* cbg_self, const char16_t* name, Altseed2::Vector2F_C pos, int32_t cond) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = name;
    Altseed2::Vector2F_C cbg_arg1 = pos;
    Altseed2::ToolCond cbg_arg2 = (Altseed2::ToolCond)cond;
    cbg_self_->SetWindowPos(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetWindowSize_Vector2F_C_ToolCond(void* cbg_self, Altseed2::Vector2F_C size, int32_t cond) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = size;
    Altseed2::ToolCond cbg_arg1 = (Altseed2::ToolCond)cond;
    cbg_self_->SetWindowSize(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetWindowSize_char16p_Vector2F_C_ToolCond(void* cbg_self, const char16_t* name, Altseed2::Vector2F_C size, int32_t cond) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = name;
    Altseed2::Vector2F_C cbg_arg1 = size;
    Altseed2::ToolCond cbg_arg2 = (Altseed2::ToolCond)cond;
    cbg_self_->SetWindowSize(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetWindowCollapsed_bool_ToolCond(void* cbg_self, bool collapsed, int32_t cond) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_arg0 = collapsed;
    Altseed2::ToolCond cbg_arg1 = (Altseed2::ToolCond)cond;
    cbg_self_->SetWindowCollapsed(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetWindowCollapsed_char16p_bool_ToolCond(void* cbg_self, const char16_t* name, bool collapsed, int32_t cond) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = name;
    bool cbg_arg1 = collapsed;
    Altseed2::ToolCond cbg_arg2 = (Altseed2::ToolCond)cond;
    cbg_self_->SetWindowCollapsed(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetWindowFocus_(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->SetWindowFocus();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetWindowFocus_char16p(void* cbg_self, const char16_t* name) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = name;
    cbg_self_->SetWindowFocus(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetWindowFontScale(void* cbg_self, float scale) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = scale;
    cbg_self_->SetWindowFontScale(cbg_arg0);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetContentRegionMax(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetContentRegionMax();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetContentRegionAvail(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetContentRegionAvail();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetWindowContentRegionMin(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetWindowContentRegionMin();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetWindowContentRegionMax(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetWindowContentRegionMax();
    return (cbg_ret);
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetWindowContentRegionWidth(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetWindowContentRegionWidth();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetScrollX(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetScrollX();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetScrollY(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetScrollY();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetScrollMaxX(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetScrollMaxX();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetScrollMaxY(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetScrollMaxY();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetScrollX(void* cbg_self, float scroll_x) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = scroll_x;
    cbg_self_->SetScrollX(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetScrollY(void* cbg_self, float scroll_y) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = scroll_y;
    cbg_self_->SetScrollY(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetScrollHereX(void* cbg_self, float center_x_ratio) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = center_x_ratio;
    cbg_self_->SetScrollHereX(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetScrollHereY(void* cbg_self, float center_y_ratio) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = center_y_ratio;
    cbg_self_->SetScrollHereY(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetScrollFromPosX(void* cbg_self, float local_x, float center_x_ratio) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = local_x;
    float cbg_arg1 = center_x_ratio;
    cbg_self_->SetScrollFromPosX(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetScrollFromPosY(void* cbg_self, float local_y, float center_y_ratio) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = local_y;
    float cbg_arg1 = center_y_ratio;
    cbg_self_->SetScrollFromPosY(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PopFont(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->PopFont();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushStyleColor_ToolCol_int(void* cbg_self, int32_t idx, int32_t col) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolCol cbg_arg0 = (Altseed2::ToolCol)idx;
    int32_t cbg_arg1 = col;
    cbg_self_->PushStyleColor(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushStyleColor_ToolCol_Vector4F_C(void* cbg_self, int32_t idx, Altseed2::Vector4F_C col) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolCol cbg_arg0 = (Altseed2::ToolCol)idx;
    Altseed2::Vector4F_C cbg_arg1 = col;
    cbg_self_->PushStyleColor(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PopStyleColor(void* cbg_self, int32_t count) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = count;
    cbg_self_->PopStyleColor(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushStyleVar_ToolStyleVar_float(void* cbg_self, int32_t idx, float val) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolStyleVar cbg_arg0 = (Altseed2::ToolStyleVar)idx;
    float cbg_arg1 = val;
    cbg_self_->PushStyleVar(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushStyleVar_ToolStyleVar_Vector2F_C(void* cbg_self, int32_t idx, Altseed2::Vector2F_C val) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolStyleVar cbg_arg0 = (Altseed2::ToolStyleVar)idx;
    Altseed2::Vector2F_C cbg_arg1 = val;
    cbg_self_->PushStyleVar(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PopStyleVar(void* cbg_self, int32_t count) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = count;
    cbg_self_->PopStyleVar(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetFontSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetFontSize();
    return cbg_ret;
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetFontTexUvWhitePixel(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetFontTexUvWhitePixel();
    return (cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_GetColorU32_ToolCol_float(void* cbg_self, int32_t idx, float alpha_mul) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolCol cbg_arg0 = (Altseed2::ToolCol)idx;
    float cbg_arg1 = alpha_mul;
    int32_t cbg_ret = cbg_self_->GetColorU32(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_GetColorU32_Vector4F_C(void* cbg_self, Altseed2::Vector4F_C col) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector4F_C cbg_arg0 = col;
    int32_t cbg_ret = cbg_self_->GetColorU32(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_GetColorU32_int(void* cbg_self, int32_t col) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = col;
    int32_t cbg_ret = cbg_self_->GetColorU32(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushItemWidth(void* cbg_self, float item_width) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = item_width;
    cbg_self_->PushItemWidth(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PopItemWidth(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->PopItemWidth();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextItemWidth(void* cbg_self, float item_width) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = item_width;
    cbg_self_->SetNextItemWidth(cbg_arg0);
}

CBGEXPORT float CBGSTDCALL cbg_Tool_CalcItemWidth(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->CalcItemWidth();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushTextWrapPos(void* cbg_self, float wrap_local_pos_x) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = wrap_local_pos_x;
    cbg_self_->PushTextWrapPos(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PopTextWrapPos(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->PopTextWrapPos();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushAllowKeyboardFocus(void* cbg_self, bool allow_keyboard_focus) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_arg0 = allow_keyboard_focus;
    cbg_self_->PushAllowKeyboardFocus(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PopAllowKeyboardFocus(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->PopAllowKeyboardFocus();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushButtonRepeat(void* cbg_self, bool repeat) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_arg0 = repeat;
    cbg_self_->PushButtonRepeat(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PopButtonRepeat(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->PopButtonRepeat();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Separator(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->Separator();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SameLine(void* cbg_self, float offset_from_start_x, float spacing) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = offset_from_start_x;
    float cbg_arg1 = spacing;
    cbg_self_->SameLine(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_NewLine(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->NewLine();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Spacing(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->Spacing();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Dummy(void* cbg_self, Altseed2::Vector2F_C size) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = size;
    cbg_self_->Dummy(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Indent(void* cbg_self, float indent_w) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = indent_w;
    cbg_self_->Indent(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Unindent(void* cbg_self, float indent_w) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = indent_w;
    cbg_self_->Unindent(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_BeginGroup(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->BeginGroup();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndGroup(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->EndGroup();
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetCursorPos(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetCursorPos();
    return (cbg_ret);
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetCursorPosX(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetCursorPosX();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetCursorPosY(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetCursorPosY();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetCursorPos(void* cbg_self, Altseed2::Vector2F_C local_pos) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = local_pos;
    cbg_self_->SetCursorPos(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetCursorPosX(void* cbg_self, float local_x) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = local_x;
    cbg_self_->SetCursorPosX(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetCursorPosY(void* cbg_self, float local_y) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = local_y;
    cbg_self_->SetCursorPosY(cbg_arg0);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetCursorStartPos(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetCursorStartPos();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetCursorScreenPos(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetCursorScreenPos();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetCursorScreenPos(void* cbg_self, Altseed2::Vector2F_C pos) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = pos;
    cbg_self_->SetCursorScreenPos(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_AlignTextToFramePadding(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->AlignTextToFramePadding();
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetTextLineHeight(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetTextLineHeight();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetTextLineHeightWithSpacing(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetTextLineHeightWithSpacing();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetFrameHeight(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetFrameHeight();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetFrameHeightWithSpacing(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetFrameHeightWithSpacing();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushID_char16p(void* cbg_self, const char16_t* str_id) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    cbg_self_->PushID(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushID_char16p_char16p(void* cbg_self, const char16_t* str_id_begin, const char16_t* str_id_end) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id_begin;
    const char16_t* cbg_arg1 = str_id_end;
    cbg_self_->PushID(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushID_int(void* cbg_self, int32_t int_id) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = int_id;
    cbg_self_->PushID(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PopID(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->PopID();
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_GetID_char16p(void* cbg_self, const char16_t* str_id) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    int32_t cbg_ret = cbg_self_->GetID(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_GetID_char16p_char16p(void* cbg_self, const char16_t* str_id_begin, const char16_t* str_id_end) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id_begin;
    const char16_t* cbg_arg1 = str_id_end;
    int32_t cbg_ret = cbg_self_->GetID(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_TextUnformatted(void* cbg_self, const char16_t* text, const char16_t* text_end) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = text;
    const char16_t* cbg_arg1 = text_end;
    cbg_self_->TextUnformatted(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Text(void* cbg_self, const char16_t* fmt) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = fmt;
    cbg_self_->Text(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_TextColored(void* cbg_self, Altseed2::Vector4F_C col, const char16_t* fmt) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector4F_C cbg_arg0 = col;
    const char16_t* cbg_arg1 = fmt;
    cbg_self_->TextColored(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_TextDisabled(void* cbg_self, const char16_t* fmt) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = fmt;
    cbg_self_->TextDisabled(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_TextWrapped(void* cbg_self, const char16_t* fmt) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = fmt;
    cbg_self_->TextWrapped(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_LabelText(void* cbg_self, const char16_t* label, const char16_t* fmt) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    const char16_t* cbg_arg1 = fmt;
    cbg_self_->LabelText(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_BulletText(void* cbg_self, const char16_t* fmt) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = fmt;
    cbg_self_->BulletText(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_Button(void* cbg_self, const char16_t* label, Altseed2::Vector2F_C size) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed2::Vector2F_C cbg_arg1 = size;
    bool cbg_ret = cbg_self_->Button(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SmallButton(void* cbg_self, const char16_t* label) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool cbg_ret = cbg_self_->SmallButton(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_InvisibleButton(void* cbg_self, const char16_t* str_id, Altseed2::Vector2F_C size, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    Altseed2::Vector2F_C cbg_arg1 = size;
    Altseed2::ToolButtonFlags cbg_arg2 = (Altseed2::ToolButtonFlags)flags;
    bool cbg_ret = cbg_self_->InvisibleButton(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_ArrowButton(void* cbg_self, const char16_t* str_id, int32_t dir) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    Altseed2::ToolDir cbg_arg1 = (Altseed2::ToolDir)dir;
    bool cbg_ret = cbg_self_->ArrowButton(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_Checkbox(void* cbg_self, const char16_t* label, bool * v) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool* cbg_arg1 = v;
    bool cbg_ret = cbg_self_->Checkbox(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_RadioButton_char16p_bool(void* cbg_self, const char16_t* label, bool active) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool cbg_arg1 = active;
    bool cbg_ret = cbg_self_->RadioButton(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_RadioButton_char16p_intp_int(void* cbg_self, const char16_t* label, int32_t * v, int32_t v_button) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    int32_t* cbg_arg1 = v;
    int32_t cbg_arg2 = v_button;
    bool cbg_ret = cbg_self_->RadioButton(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_ProgressBar(void* cbg_self, float fraction, Altseed2::Vector2F_C size_arg, const char16_t* overlay) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_arg0 = fraction;
    Altseed2::Vector2F_C cbg_arg1 = size_arg;
    const char16_t* cbg_arg2 = overlay;
    cbg_self_->ProgressBar(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Bullet(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->Bullet();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginCombo(void* cbg_self, const char16_t* label, const char16_t* preview_value, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    const char16_t* cbg_arg1 = preview_value;
    Altseed2::ToolComboFlags cbg_arg2 = (Altseed2::ToolComboFlags)flags;
    bool cbg_ret = cbg_self_->BeginCombo(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndCombo(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->EndCombo();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_DragFloat(void* cbg_self, const char16_t* label, float * v, float v_speed, float v_min, float v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    float* cbg_arg1 = v;
    float cbg_arg2 = v_speed;
    float cbg_arg3 = v_min;
    float cbg_arg4 = v_max;
    const char16_t* cbg_arg5 = format;
    Altseed2::ToolSliderFlags cbg_arg6 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->DragFloat(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_DragFloat2(void* cbg_self, const char16_t* label, void* v, float v_speed, float v_min, float v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)v);
    float cbg_arg2 = v_speed;
    float cbg_arg3 = v_min;
    float cbg_arg4 = v_max;
    const char16_t* cbg_arg5 = format;
    Altseed2::ToolSliderFlags cbg_arg6 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->DragFloat2(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_DragFloat3(void* cbg_self, const char16_t* label, void* v, float v_speed, float v_min, float v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)v);
    float cbg_arg2 = v_speed;
    float cbg_arg3 = v_min;
    float cbg_arg4 = v_max;
    const char16_t* cbg_arg5 = format;
    Altseed2::ToolSliderFlags cbg_arg6 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->DragFloat3(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_DragFloat4(void* cbg_self, const char16_t* label, void* v, float v_speed, float v_min, float v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)v);
    float cbg_arg2 = v_speed;
    float cbg_arg3 = v_min;
    float cbg_arg4 = v_max;
    const char16_t* cbg_arg5 = format;
    Altseed2::ToolSliderFlags cbg_arg6 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->DragFloat4(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_DragFloatRange2(void* cbg_self, const char16_t* label, float * v_current_min, float * v_current_max, float v_speed, float v_min, float v_max, const char16_t* format, const char16_t* format_max, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    float* cbg_arg1 = v_current_min;
    float* cbg_arg2 = v_current_max;
    float cbg_arg3 = v_speed;
    float cbg_arg4 = v_min;
    float cbg_arg5 = v_max;
    const char16_t* cbg_arg6 = format;
    const char16_t* cbg_arg7 = format_max;
    Altseed2::ToolSliderFlags cbg_arg8 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->DragFloatRange2(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6, cbg_arg7, cbg_arg8);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_DragInt(void* cbg_self, const char16_t* label, int32_t * v, float v_speed, int32_t v_min, int32_t v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    int32_t* cbg_arg1 = v;
    float cbg_arg2 = v_speed;
    int32_t cbg_arg3 = v_min;
    int32_t cbg_arg4 = v_max;
    const char16_t* cbg_arg5 = format;
    Altseed2::ToolSliderFlags cbg_arg6 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->DragInt(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_DragInt2(void* cbg_self, const char16_t* label, void* v, float v_speed, int32_t v_min, int32_t v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::Int32Array> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::Int32Array>((Altseed2::Int32Array*)v);
    float cbg_arg2 = v_speed;
    int32_t cbg_arg3 = v_min;
    int32_t cbg_arg4 = v_max;
    const char16_t* cbg_arg5 = format;
    Altseed2::ToolSliderFlags cbg_arg6 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->DragInt2(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_DragInt3(void* cbg_self, const char16_t* label, void* v, float v_speed, int32_t v_min, int32_t v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::Int32Array> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::Int32Array>((Altseed2::Int32Array*)v);
    float cbg_arg2 = v_speed;
    int32_t cbg_arg3 = v_min;
    int32_t cbg_arg4 = v_max;
    const char16_t* cbg_arg5 = format;
    Altseed2::ToolSliderFlags cbg_arg6 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->DragInt3(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_DragInt4(void* cbg_self, const char16_t* label, void* v, float v_speed, int32_t v_min, int32_t v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::Int32Array> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::Int32Array>((Altseed2::Int32Array*)v);
    float cbg_arg2 = v_speed;
    int32_t cbg_arg3 = v_min;
    int32_t cbg_arg4 = v_max;
    const char16_t* cbg_arg5 = format;
    Altseed2::ToolSliderFlags cbg_arg6 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->DragInt4(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_DragIntRange2(void* cbg_self, const char16_t* label, int32_t * v_current_min, int32_t * v_current_max, float v_speed, int32_t v_min, int32_t v_max, const char16_t* format, const char16_t* format_max, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    int32_t* cbg_arg1 = v_current_min;
    int32_t* cbg_arg2 = v_current_max;
    float cbg_arg3 = v_speed;
    int32_t cbg_arg4 = v_min;
    int32_t cbg_arg5 = v_max;
    const char16_t* cbg_arg6 = format;
    const char16_t* cbg_arg7 = format_max;
    Altseed2::ToolSliderFlags cbg_arg8 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->DragIntRange2(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6, cbg_arg7, cbg_arg8);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SliderFloat(void* cbg_self, const char16_t* label, float * v, float v_min, float v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    float* cbg_arg1 = v;
    float cbg_arg2 = v_min;
    float cbg_arg3 = v_max;
    const char16_t* cbg_arg4 = format;
    Altseed2::ToolSliderFlags cbg_arg5 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->SliderFloat(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SliderFloat2(void* cbg_self, const char16_t* label, void* v, float v_min, float v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)v);
    float cbg_arg2 = v_min;
    float cbg_arg3 = v_max;
    const char16_t* cbg_arg4 = format;
    Altseed2::ToolSliderFlags cbg_arg5 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->SliderFloat2(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SliderFloat3(void* cbg_self, const char16_t* label, void* v, float v_min, float v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)v);
    float cbg_arg2 = v_min;
    float cbg_arg3 = v_max;
    const char16_t* cbg_arg4 = format;
    Altseed2::ToolSliderFlags cbg_arg5 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->SliderFloat3(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SliderFloat4(void* cbg_self, const char16_t* label, void* v, float v_min, float v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)v);
    float cbg_arg2 = v_min;
    float cbg_arg3 = v_max;
    const char16_t* cbg_arg4 = format;
    Altseed2::ToolSliderFlags cbg_arg5 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->SliderFloat4(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SliderAngle(void* cbg_self, const char16_t* label, float * v_rad, float v_degrees_min, float v_degrees_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    float* cbg_arg1 = v_rad;
    float cbg_arg2 = v_degrees_min;
    float cbg_arg3 = v_degrees_max;
    const char16_t* cbg_arg4 = format;
    Altseed2::ToolSliderFlags cbg_arg5 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->SliderAngle(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SliderInt(void* cbg_self, const char16_t* label, int32_t * v, int32_t v_min, int32_t v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    int32_t* cbg_arg1 = v;
    int32_t cbg_arg2 = v_min;
    int32_t cbg_arg3 = v_max;
    const char16_t* cbg_arg4 = format;
    Altseed2::ToolSliderFlags cbg_arg5 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->SliderInt(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SliderInt2(void* cbg_self, const char16_t* label, void* v, int32_t v_min, int32_t v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::Int32Array> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::Int32Array>((Altseed2::Int32Array*)v);
    int32_t cbg_arg2 = v_min;
    int32_t cbg_arg3 = v_max;
    const char16_t* cbg_arg4 = format;
    Altseed2::ToolSliderFlags cbg_arg5 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->SliderInt2(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SliderInt3(void* cbg_self, const char16_t* label, void* v, int32_t v_min, int32_t v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::Int32Array> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::Int32Array>((Altseed2::Int32Array*)v);
    int32_t cbg_arg2 = v_min;
    int32_t cbg_arg3 = v_max;
    const char16_t* cbg_arg4 = format;
    Altseed2::ToolSliderFlags cbg_arg5 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->SliderInt3(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_SliderInt4(void* cbg_self, const char16_t* label, void* v, int32_t v_min, int32_t v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::Int32Array> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::Int32Array>((Altseed2::Int32Array*)v);
    int32_t cbg_arg2 = v_min;
    int32_t cbg_arg3 = v_max;
    const char16_t* cbg_arg4 = format;
    Altseed2::ToolSliderFlags cbg_arg5 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->SliderInt4(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_VSliderFloat(void* cbg_self, const char16_t* label, Altseed2::Vector2F_C size, float * v, float v_min, float v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed2::Vector2F_C cbg_arg1 = size;
    float* cbg_arg2 = v;
    float cbg_arg3 = v_min;
    float cbg_arg4 = v_max;
    const char16_t* cbg_arg5 = format;
    Altseed2::ToolSliderFlags cbg_arg6 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->VSliderFloat(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_VSliderInt(void* cbg_self, const char16_t* label, Altseed2::Vector2F_C size, int32_t * v, int32_t v_min, int32_t v_max, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed2::Vector2F_C cbg_arg1 = size;
    int32_t* cbg_arg2 = v;
    int32_t cbg_arg3 = v_min;
    int32_t cbg_arg4 = v_max;
    const char16_t* cbg_arg5 = format;
    Altseed2::ToolSliderFlags cbg_arg6 = (Altseed2::ToolSliderFlags)flags;
    bool cbg_ret = cbg_self_->VSliderInt(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5, cbg_arg6);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_InputFloat(void* cbg_self, const char16_t* label, float * v, float step, float step_fast, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    float* cbg_arg1 = v;
    float cbg_arg2 = step;
    float cbg_arg3 = step_fast;
    const char16_t* cbg_arg4 = format;
    Altseed2::ToolInputTextFlags cbg_arg5 = (Altseed2::ToolInputTextFlags)flags;
    bool cbg_ret = cbg_self_->InputFloat(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4, cbg_arg5);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_InputFloat2(void* cbg_self, const char16_t* label, void* v, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)v);
    const char16_t* cbg_arg2 = format;
    Altseed2::ToolInputTextFlags cbg_arg3 = (Altseed2::ToolInputTextFlags)flags;
    bool cbg_ret = cbg_self_->InputFloat2(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_InputFloat3(void* cbg_self, const char16_t* label, void* v, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)v);
    const char16_t* cbg_arg2 = format;
    Altseed2::ToolInputTextFlags cbg_arg3 = (Altseed2::ToolInputTextFlags)flags;
    bool cbg_ret = cbg_self_->InputFloat3(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_InputFloat4(void* cbg_self, const char16_t* label, void* v, const char16_t* format, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)v);
    const char16_t* cbg_arg2 = format;
    Altseed2::ToolInputTextFlags cbg_arg3 = (Altseed2::ToolInputTextFlags)flags;
    bool cbg_ret = cbg_self_->InputFloat4(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_InputInt(void* cbg_self, const char16_t* label, int32_t * v, int32_t step, int32_t step_fast, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    int32_t* cbg_arg1 = v;
    int32_t cbg_arg2 = step;
    int32_t cbg_arg3 = step_fast;
    Altseed2::ToolInputTextFlags cbg_arg4 = (Altseed2::ToolInputTextFlags)flags;
    bool cbg_ret = cbg_self_->InputInt(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3, cbg_arg4);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_InputInt2(void* cbg_self, const char16_t* label, void* v, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::Int32Array> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::Int32Array>((Altseed2::Int32Array*)v);
    Altseed2::ToolInputTextFlags cbg_arg2 = (Altseed2::ToolInputTextFlags)flags;
    bool cbg_ret = cbg_self_->InputInt2(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_InputInt3(void* cbg_self, const char16_t* label, void* v, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::Int32Array> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::Int32Array>((Altseed2::Int32Array*)v);
    Altseed2::ToolInputTextFlags cbg_arg2 = (Altseed2::ToolInputTextFlags)flags;
    bool cbg_ret = cbg_self_->InputInt3(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_InputInt4(void* cbg_self, const char16_t* label, void* v, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::Int32Array> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::Int32Array>((Altseed2::Int32Array*)v);
    Altseed2::ToolInputTextFlags cbg_arg2 = (Altseed2::ToolInputTextFlags)flags;
    bool cbg_ret = cbg_self_->InputInt4(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_ColorPicker3(void* cbg_self, const char16_t* label, void* col, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)col);
    Altseed2::ToolColorEditFlags cbg_arg2 = (Altseed2::ToolColorEditFlags)flags;
    bool cbg_ret = cbg_self_->ColorPicker3(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_ColorPicker4(void* cbg_self, const char16_t* label, void* col, int32_t flags, float * ref_col) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    std::shared_ptr<Altseed2::FloatArray> cbg_arg1 = Altseed2::CreateAndAddSharedPtr<Altseed2::FloatArray>((Altseed2::FloatArray*)col);
    Altseed2::ToolColorEditFlags cbg_arg2 = (Altseed2::ToolColorEditFlags)flags;
    float* cbg_arg3 = ref_col;
    bool cbg_ret = cbg_self_->ColorPicker4(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetColorEditOptions(void* cbg_self, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolColorEditFlags cbg_arg0 = (Altseed2::ToolColorEditFlags)flags;
    cbg_self_->SetColorEditOptions(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_TreeNode_char16p(void* cbg_self, const char16_t* label) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool cbg_ret = cbg_self_->TreeNode(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_TreeNode_char16p_char16p(void* cbg_self, const char16_t* str_id, const char16_t* fmt) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    const char16_t* cbg_arg1 = fmt;
    bool cbg_ret = cbg_self_->TreeNode(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_TreeNodeEx_char16p_ToolTreeNodeFlags(void* cbg_self, const char16_t* label, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed2::ToolTreeNodeFlags cbg_arg1 = (Altseed2::ToolTreeNodeFlags)flags;
    bool cbg_ret = cbg_self_->TreeNodeEx(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_TreeNodeEx_char16p_ToolTreeNodeFlags_char16p(void* cbg_self, const char16_t* str_id, int32_t flags, const char16_t* fmt) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    Altseed2::ToolTreeNodeFlags cbg_arg1 = (Altseed2::ToolTreeNodeFlags)flags;
    const char16_t* cbg_arg2 = fmt;
    bool cbg_ret = cbg_self_->TreeNodeEx(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_TreePush(void* cbg_self, const char16_t* str_id) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    cbg_self_->TreePush(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_TreePop(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->TreePop();
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetTreeNodeToLabelSpacing(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    float cbg_ret = cbg_self_->GetTreeNodeToLabelSpacing();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_CollapsingHeader_char16p_ToolTreeNodeFlags(void* cbg_self, const char16_t* label, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed2::ToolTreeNodeFlags cbg_arg1 = (Altseed2::ToolTreeNodeFlags)flags;
    bool cbg_ret = cbg_self_->CollapsingHeader(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_CollapsingHeader_char16p_boolp_ToolTreeNodeFlags(void* cbg_self, const char16_t* label, bool * p_open, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool* cbg_arg1 = p_open;
    Altseed2::ToolTreeNodeFlags cbg_arg2 = (Altseed2::ToolTreeNodeFlags)flags;
    bool cbg_ret = cbg_self_->CollapsingHeader(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextItemOpen(void* cbg_self, bool is_open, int32_t cond) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_arg0 = is_open;
    Altseed2::ToolCond cbg_arg1 = (Altseed2::ToolCond)cond;
    cbg_self_->SetNextItemOpen(cbg_arg0, cbg_arg1);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_Selectable_char16p_bool_ToolSelectableFlags_Vector2F_C(void* cbg_self, const char16_t* label, bool selected, int32_t flags, Altseed2::Vector2F_C size) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool cbg_arg1 = selected;
    Altseed2::ToolSelectableFlags cbg_arg2 = (Altseed2::ToolSelectableFlags)flags;
    Altseed2::Vector2F_C cbg_arg3 = size;
    bool cbg_ret = cbg_self_->Selectable(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_Selectable_char16p_boolp_ToolSelectableFlags_Vector2F_C(void* cbg_self, const char16_t* label, bool * p_selected, int32_t flags, Altseed2::Vector2F_C size) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool* cbg_arg1 = p_selected;
    Altseed2::ToolSelectableFlags cbg_arg2 = (Altseed2::ToolSelectableFlags)flags;
    Altseed2::Vector2F_C cbg_arg3 = size;
    bool cbg_ret = cbg_self_->Selectable(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_ListBoxHeader_char16p_Vector2F_C(void* cbg_self, const char16_t* label, Altseed2::Vector2F_C size) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed2::Vector2F_C cbg_arg1 = size;
    bool cbg_ret = cbg_self_->ListBoxHeader(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_ListBoxHeader_char16p_int_int(void* cbg_self, const char16_t* label, int32_t items_count, int32_t height_in_items) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    int32_t cbg_arg1 = items_count;
    int32_t cbg_arg2 = height_in_items;
    bool cbg_ret = cbg_self_->ListBoxHeader(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_ListBoxFooter(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->ListBoxFooter();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Value_char16p_bool(void* cbg_self, const char16_t* prefix, bool b) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = prefix;
    bool cbg_arg1 = b;
    cbg_self_->Value(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Value_char16p_int(void* cbg_self, const char16_t* prefix, int32_t v) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = prefix;
    int32_t cbg_arg1 = v;
    cbg_self_->Value(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Value_char16p_float_char16p(void* cbg_self, const char16_t* prefix, float v, const char16_t* float_format) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = prefix;
    float cbg_arg1 = v;
    const char16_t* cbg_arg2 = float_format;
    cbg_self_->Value(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginMenuBar(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->BeginMenuBar();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndMenuBar(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->EndMenuBar();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginMainMenuBar(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->BeginMainMenuBar();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndMainMenuBar(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->EndMainMenuBar();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginMenu(void* cbg_self, const char16_t* label, bool enabled) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    bool cbg_arg1 = enabled;
    bool cbg_ret = cbg_self_->BeginMenu(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndMenu(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->EndMenu();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_MenuItem_char16p_char16p_bool_bool(void* cbg_self, const char16_t* label, const char16_t* shortcut, bool selected, bool enabled) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    const char16_t* cbg_arg1 = shortcut;
    bool cbg_arg2 = selected;
    bool cbg_arg3 = enabled;
    bool cbg_ret = cbg_self_->MenuItem(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_MenuItem_char16p_char16p_boolp_bool(void* cbg_self, const char16_t* label, const char16_t* shortcut, bool * p_selected, bool enabled) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    const char16_t* cbg_arg1 = shortcut;
    bool* cbg_arg2 = p_selected;
    bool cbg_arg3 = enabled;
    bool cbg_ret = cbg_self_->MenuItem(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_BeginTooltip(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->BeginTooltip();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndTooltip(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->EndTooltip();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetTooltip(void* cbg_self, const char16_t* fmt) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = fmt;
    cbg_self_->SetTooltip(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginPopup(void* cbg_self, const char16_t* str_id, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    Altseed2::ToolWindowFlags cbg_arg1 = (Altseed2::ToolWindowFlags)flags;
    bool cbg_ret = cbg_self_->BeginPopup(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndPopup(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->EndPopup();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_OpenPopup(void* cbg_self, const char16_t* str_id, int32_t popup_flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    Altseed2::ToolPopupFlags cbg_arg1 = (Altseed2::ToolPopupFlags)popup_flags;
    cbg_self_->OpenPopup(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_OpenPopupOnItemClick(void* cbg_self, const char16_t* str_id, int32_t popup_flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    Altseed2::ToolPopupFlags cbg_arg1 = (Altseed2::ToolPopupFlags)popup_flags;
    cbg_self_->OpenPopupOnItemClick(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_CloseCurrentPopup(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->CloseCurrentPopup();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginPopupContextItem(void* cbg_self, const char16_t* str_id, int32_t popup_flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    Altseed2::ToolPopupFlags cbg_arg1 = (Altseed2::ToolPopupFlags)popup_flags;
    bool cbg_ret = cbg_self_->BeginPopupContextItem(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginPopupContextWindow(void* cbg_self, const char16_t* str_id, int32_t popup_flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    Altseed2::ToolPopupFlags cbg_arg1 = (Altseed2::ToolPopupFlags)popup_flags;
    bool cbg_ret = cbg_self_->BeginPopupContextWindow(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginPopupContextVoid(void* cbg_self, const char16_t* str_id, int32_t popup_flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    Altseed2::ToolPopupFlags cbg_arg1 = (Altseed2::ToolPopupFlags)popup_flags;
    bool cbg_ret = cbg_self_->BeginPopupContextVoid(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsPopupOpen(void* cbg_self, const char16_t* str_id, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    Altseed2::ToolPopupFlags cbg_arg1 = (Altseed2::ToolPopupFlags)flags;
    bool cbg_ret = cbg_self_->IsPopupOpen(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Columns(void* cbg_self, int32_t count, const char16_t* id, bool border) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = count;
    const char16_t* cbg_arg1 = id;
    bool cbg_arg2 = border;
    cbg_self_->Columns(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_NextColumn(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->NextColumn();
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_GetColumnIndex(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetColumnIndex();
    return cbg_ret;
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetColumnWidth(void* cbg_self, int32_t column_index) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = column_index;
    float cbg_ret = cbg_self_->GetColumnWidth(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetColumnWidth(void* cbg_self, int32_t column_index, float width) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = column_index;
    float cbg_arg1 = width;
    cbg_self_->SetColumnWidth(cbg_arg0, cbg_arg1);
}

CBGEXPORT float CBGSTDCALL cbg_Tool_GetColumnOffset(void* cbg_self, int32_t column_index) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = column_index;
    float cbg_ret = cbg_self_->GetColumnOffset(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetColumnOffset(void* cbg_self, int32_t column_index, float offset_x) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = column_index;
    float cbg_arg1 = offset_x;
    cbg_self_->SetColumnOffset(cbg_arg0, cbg_arg1);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_GetColumnsCount(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetColumnsCount();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginTabBar(void* cbg_self, const char16_t* str_id, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = str_id;
    Altseed2::ToolTabBarFlags cbg_arg1 = (Altseed2::ToolTabBarFlags)flags;
    bool cbg_ret = cbg_self_->BeginTabBar(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndTabBar(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->EndTabBar();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndTabItem(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->EndTabItem();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_TabItemButton(void* cbg_self, const char16_t* label, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = label;
    Altseed2::ToolTabItemFlags cbg_arg1 = (Altseed2::ToolTabItemFlags)flags;
    bool cbg_ret = cbg_self_->TabItemButton(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetTabItemClosed(void* cbg_self, const char16_t* tab_or_docked_window_label) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = tab_or_docked_window_label;
    cbg_self_->SetTabItemClosed(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetNextWindowDockID(void* cbg_self, int32_t dock_id, int32_t cond) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = dock_id;
    Altseed2::ToolCond cbg_arg1 = (Altseed2::ToolCond)cond;
    cbg_self_->SetNextWindowDockID(cbg_arg0, cbg_arg1);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_GetWindowDockID(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetWindowDockID();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsWindowDocked(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsWindowDocked();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_LogToTTY(void* cbg_self, int32_t auto_open_depth) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = auto_open_depth;
    cbg_self_->LogToTTY(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_LogToFile(void* cbg_self, int32_t auto_open_depth, const char16_t* filename) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = auto_open_depth;
    const char16_t* cbg_arg1 = filename;
    cbg_self_->LogToFile(cbg_arg0, cbg_arg1);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_LogToClipboard(void* cbg_self, int32_t auto_open_depth) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = auto_open_depth;
    cbg_self_->LogToClipboard(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_LogFinish(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->LogFinish();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_LogButtons(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->LogButtons();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_LogText(void* cbg_self, const char16_t* fmt) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = fmt;
    cbg_self_->LogText(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginDragDropSource(void* cbg_self, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolDragDropFlags cbg_arg0 = (Altseed2::ToolDragDropFlags)flags;
    bool cbg_ret = cbg_self_->BeginDragDropSource(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndDragDropSource(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->EndDragDropSource();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginDragDropTarget(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->BeginDragDropTarget();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndDragDropTarget(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->EndDragDropTarget();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PushClipRect(void* cbg_self, Altseed2::Vector2F_C clip_rect_min, Altseed2::Vector2F_C clip_rect_max, bool intersect_with_current_clip_rect) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = clip_rect_min;
    Altseed2::Vector2F_C cbg_arg1 = clip_rect_max;
    bool cbg_arg2 = intersect_with_current_clip_rect;
    cbg_self_->PushClipRect(cbg_arg0, cbg_arg1, cbg_arg2);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_PopClipRect(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->PopClipRect();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetItemDefaultFocus(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->SetItemDefaultFocus();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetKeyboardFocusHere(void* cbg_self, int32_t offset) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = offset;
    cbg_self_->SetKeyboardFocusHere(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsItemHovered(void* cbg_self, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolHoveredFlags cbg_arg0 = (Altseed2::ToolHoveredFlags)flags;
    bool cbg_ret = cbg_self_->IsItemHovered(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsItemActive(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsItemActive();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsItemFocused(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsItemFocused();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsItemClicked(void* cbg_self, int32_t mouse_button) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolMouseButton cbg_arg0 = (Altseed2::ToolMouseButton)mouse_button;
    bool cbg_ret = cbg_self_->IsItemClicked(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsItemVisible(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsItemVisible();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsItemEdited(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsItemEdited();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsItemActivated(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsItemActivated();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsItemDeactivated(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsItemDeactivated();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsItemDeactivatedAfterEdit(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsItemDeactivatedAfterEdit();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsItemToggledOpen(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsItemToggledOpen();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsAnyItemHovered(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsAnyItemHovered();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsAnyItemActive(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsAnyItemActive();
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsAnyItemFocused(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsAnyItemFocused();
    return cbg_ret;
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetItemRectMin(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetItemRectMin();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetItemRectMax(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetItemRectMax();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetItemRectSize(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetItemRectSize();
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetItemAllowOverlap(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->SetItemAllowOverlap();
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsRectVisible_Vector2F_C(void* cbg_self, Altseed2::Vector2F_C size) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = size;
    bool cbg_ret = cbg_self_->IsRectVisible(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsRectVisible_Vector2F_C_Vector2F_C(void* cbg_self, Altseed2::Vector2F_C rect_min, Altseed2::Vector2F_C rect_max) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = rect_min;
    Altseed2::Vector2F_C cbg_arg1 = rect_max;
    bool cbg_ret = cbg_self_->IsRectVisible(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_GetFrameCount(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_ret = cbg_self_->GetFrameCount();
    return cbg_ret;
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Tool_GetStyleColorName(void* cbg_self, int32_t idx) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolCol cbg_arg0 = (Altseed2::ToolCol)idx;
    const char16_t* cbg_ret = cbg_self_->GetStyleColorName(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_CalcListClipping(void* cbg_self, int32_t items_count, float items_height, int32_t * out_items_display_start, int32_t * out_items_display_end) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = items_count;
    float cbg_arg1 = items_height;
    int32_t* cbg_arg2 = out_items_display_start;
    int32_t* cbg_arg3 = out_items_display_end;
    cbg_self_->CalcListClipping(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_BeginChildFrame(void* cbg_self, int32_t id, Altseed2::Vector2F_C size, int32_t flags) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = id;
    Altseed2::Vector2F_C cbg_arg1 = size;
    Altseed2::ToolWindowFlags cbg_arg2 = (Altseed2::ToolWindowFlags)flags;
    bool cbg_ret = cbg_self_->BeginChildFrame(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_EndChildFrame(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->EndChildFrame();
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_CalcTextSize(void* cbg_self, const char16_t* text, const char16_t* text_end, bool hide_text_after_double_hash, float wrap_width) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = text;
    const char16_t* cbg_arg1 = text_end;
    bool cbg_arg2 = hide_text_after_double_hash;
    float cbg_arg3 = wrap_width;
    Altseed2::Vector2F_C cbg_ret = cbg_self_->CalcTextSize(cbg_arg0, cbg_arg1, cbg_arg2, cbg_arg3);
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector4F_C CBGSTDCALL cbg_Tool_ColorConvertU32ToFloat4(void* cbg_self, int32_t in_) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = in_;
    Altseed2::Vector4F_C cbg_ret = cbg_self_->ColorConvertU32ToFloat4(cbg_arg0);
    return (cbg_ret);
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_ColorConvertFloat4ToU32(void* cbg_self, Altseed2::Vector4F_C in_) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector4F_C cbg_arg0 = in_;
    int32_t cbg_ret = cbg_self_->ColorConvertFloat4ToU32(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_GetKeyIndex(void* cbg_self, int32_t imgui_key) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolKey cbg_arg0 = (Altseed2::ToolKey)imgui_key;
    int32_t cbg_ret = cbg_self_->GetKeyIndex(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsKeyDown(void* cbg_self, int32_t user_key_index) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = user_key_index;
    bool cbg_ret = cbg_self_->IsKeyDown(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsKeyPressed(void* cbg_self, int32_t user_key_index, bool repeat) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = user_key_index;
    bool cbg_arg1 = repeat;
    bool cbg_ret = cbg_self_->IsKeyPressed(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsKeyReleased(void* cbg_self, int32_t user_key_index) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = user_key_index;
    bool cbg_ret = cbg_self_->IsKeyReleased(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_GetKeyPressedAmount(void* cbg_self, int32_t key_index, float repeat_delay, float rate) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    int32_t cbg_arg0 = key_index;
    float cbg_arg1 = repeat_delay;
    float cbg_arg2 = rate;
    int32_t cbg_ret = cbg_self_->GetKeyPressedAmount(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_CaptureKeyboardFromApp(void* cbg_self, bool want_capture_keyboard_value) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_arg0 = want_capture_keyboard_value;
    cbg_self_->CaptureKeyboardFromApp(cbg_arg0);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsMouseDown(void* cbg_self, int32_t button) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolMouseButton cbg_arg0 = (Altseed2::ToolMouseButton)button;
    bool cbg_ret = cbg_self_->IsMouseDown(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsMouseClicked(void* cbg_self, int32_t button, bool repeat) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolMouseButton cbg_arg0 = (Altseed2::ToolMouseButton)button;
    bool cbg_arg1 = repeat;
    bool cbg_ret = cbg_self_->IsMouseClicked(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsMouseReleased(void* cbg_self, int32_t button) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolMouseButton cbg_arg0 = (Altseed2::ToolMouseButton)button;
    bool cbg_ret = cbg_self_->IsMouseReleased(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsMouseDoubleClicked(void* cbg_self, int32_t button) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolMouseButton cbg_arg0 = (Altseed2::ToolMouseButton)button;
    bool cbg_ret = cbg_self_->IsMouseDoubleClicked(cbg_arg0);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsMouseHoveringRect(void* cbg_self, Altseed2::Vector2F_C r_min, Altseed2::Vector2F_C r_max, bool clip) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_arg0 = r_min;
    Altseed2::Vector2F_C cbg_arg1 = r_max;
    bool cbg_arg2 = clip;
    bool cbg_ret = cbg_self_->IsMouseHoveringRect(cbg_arg0, cbg_arg1, cbg_arg2);
    return cbg_ret;
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsAnyMouseDown(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_ret = cbg_self_->IsAnyMouseDown();
    return cbg_ret;
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetMousePos(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetMousePos();
    return (cbg_ret);
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetMousePosOnOpeningCurrentPopup(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetMousePosOnOpeningCurrentPopup();
    return (cbg_ret);
}

CBGEXPORT bool CBGSTDCALL cbg_Tool_IsMouseDragging(void* cbg_self, int32_t button, float lock_threshold) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolMouseButton cbg_arg0 = (Altseed2::ToolMouseButton)button;
    float cbg_arg1 = lock_threshold;
    bool cbg_ret = cbg_self_->IsMouseDragging(cbg_arg0, cbg_arg1);
    return cbg_ret;
}

CBGEXPORT Altseed2::Vector2F_C CBGSTDCALL cbg_Tool_GetMouseDragDelta(void* cbg_self, int32_t button, float lock_threshold) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolMouseButton cbg_arg0 = (Altseed2::ToolMouseButton)button;
    float cbg_arg1 = lock_threshold;
    Altseed2::Vector2F_C cbg_ret = cbg_self_->GetMouseDragDelta(cbg_arg0, cbg_arg1);
    return (cbg_ret);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_ResetMouseDragDelta(void* cbg_self, int32_t button) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolMouseButton cbg_arg0 = (Altseed2::ToolMouseButton)button;
    cbg_self_->ResetMouseDragDelta(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetMouseCursor(void* cbg_self, int32_t cursor_type) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolMouseCursor cbg_arg0 = (Altseed2::ToolMouseCursor)cursor_type;
    cbg_self_->SetMouseCursor(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_CaptureMouseFromApp(void* cbg_self, bool want_capture_mouse_value) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    bool cbg_arg0 = want_capture_mouse_value;
    cbg_self_->CaptureMouseFromApp(cbg_arg0);
}

CBGEXPORT const char16_t* CBGSTDCALL cbg_Tool_GetClipboardText(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_ret = cbg_self_->GetClipboardText();
    return cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetClipboardText(void* cbg_self, const char16_t* text) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = text;
    cbg_self_->SetClipboardText(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_LoadIniSettingsFromDisk(void* cbg_self, const char16_t* ini_filename) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = ini_filename;
    cbg_self_->LoadIniSettingsFromDisk(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SaveIniSettingsToDisk(void* cbg_self, const char16_t* ini_filename) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    const char16_t* cbg_arg0 = ini_filename;
    cbg_self_->SaveIniSettingsToDisk(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_UpdatePlatformWindows(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->UpdatePlatformWindows();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_DestroyPlatformWindows(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->DestroyPlatformWindows();
}

CBGEXPORT int32_t CBGSTDCALL cbg_Tool_GetToolUsage(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolUsage cbg_ret = cbg_self_->GetToolUsage();
    return (int32_t)cbg_ret;
}

CBGEXPORT void CBGSTDCALL cbg_Tool_SetToolUsage(void* cbg_self, int32_t value) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    Altseed2::ToolUsage cbg_arg0 = (Altseed2::ToolUsage)value;
    cbg_self_->SetToolUsage(cbg_arg0);
}

CBGEXPORT void CBGSTDCALL cbg_Tool_AddRef(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->AddRef();
}

CBGEXPORT void CBGSTDCALL cbg_Tool_Release(void* cbg_self) {
    auto cbg_self_ = (Altseed2::Tool*)(cbg_self);

    cbg_self_->Release();
}


}

