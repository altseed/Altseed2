#include "CommandList.h"

#ifdef _WIN32
#define STBI_WINDOWS_UTF8
#endif

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "../Graphics/Graphics.h"
#include "../Logger/Log.h"
#include "../System/SynchronizationContext.h"
#include "BuiltinShader.h"
#include "FrameDebugger.h"
#include "RenderTexture.h"

namespace Altseed {

RenderPassParameter::operator RenderPassParameter_C() const {
    auto m = RenderPassParameter();
    m.ClearColor = ClearColor;
    m.ColorCare = ColorCare;
    m.DepthCare = DepthCare;
    return m;
}

RenderPassParameter_C::operator RenderPassParameter() const {
    auto m = RenderPassParameter_C();
    m.ClearColor = ClearColor;
    m.ColorCare = ColorCare;
    m.DepthCare = DepthCare;
    return m;
}

std::shared_ptr<CommandList> CommandList::Create() {
    auto g = Graphics::GetInstance()->GetGraphicsLLGI();
    auto memoryPool = LLGI::CreateSharedPtr(g->CreateSingleFrameMemoryPool(1024 * 1024 * 16, 128));
    auto commandListPool = std::make_shared<LLGI::CommandListPool>(g, memoryPool.get(), 3);
    auto ret = CreateSharedPtr(new CommandList());

    ret->memoryPool_ = memoryPool;
    ret->commandListPool_ = commandListPool;

    {
        LLGI::TextureInitializationParameter texParam;
        texParam.Size = LLGI::Vec2I(TextureMinimumSize, TextureMinimumSize);

        std::shared_ptr<LLGI::Texture> texture = LLGI::CreateSharedPtr(g->CreateTexture(texParam));
        auto texture_buf = (LLGI::Color8*)texture->Lock();
        for (int y = 0; y < TextureMinimumSize; y++) {
            for (int x = 0; x < TextureMinimumSize; x++) {
                texture_buf[x + y * TextureMinimumSize].R = TextureDefaultColor;
                texture_buf[x + y * TextureMinimumSize].G = TextureDefaultColor;
                texture_buf[x + y * TextureMinimumSize].B = TextureDefaultColor;
                texture_buf[x + y * TextureMinimumSize].A = TextureDefaultColor;
            }
        }
        texture->Unlock();
        ret->proxyTexture_ = texture;
    }

    ret->matPropBlockCollection_ = MakeAsdShared<MaterialPropertyBlockCollection>();

    {
        ret->blitVB_ = LLGI::CreateSharedPtr(g->CreateVertexBuffer(sizeof(BatchVertex) * 4));
        ret->blitIB_ = LLGI::CreateSharedPtr(g->CreateIndexBuffer(4, 6));

        {
            auto vb = static_cast<BatchVertex*>(ret->blitVB_->Lock());

            vb[0].Pos.X = -1.0f;
            vb[0].Pos.Y = 1.0f;
            vb[0].Pos.Z = 0.5f;
            vb[0].UV1.X = 0.0f;
            vb[0].UV1.Y = 0.0f;

            vb[1].Pos.X = 1.0f;
            vb[1].Pos.Y = 1.0f;
            vb[1].Pos.Z = 0.5f;
            vb[1].UV1.X = 1.0f;
            vb[1].UV1.Y = 0.0f;

            vb[2].Pos.X = 1.0f;
            vb[2].Pos.Y = -1.0f;
            vb[2].Pos.Z = 0.5f;
            vb[2].UV1.X = 1.0f;
            vb[2].UV1.Y = 1.0f;

            vb[3].Pos.X = -1.0f;
            vb[3].Pos.Y = -1.0f;
            vb[3].Pos.Z = 0.5f;
            vb[3].UV1.X = 0.0f;
            vb[3].UV1.Y = 1.0f;

            for (size_t i = 0; i < 4; i++) {
                vb[i].UV2 = vb[i].UV1;
                vb[i].Col.R = TextureDefaultColor;
                vb[i].Col.G = TextureDefaultColor;
                vb[i].Col.B = TextureDefaultColor;
                vb[i].Col.A = TextureDefaultColor;
            }

            ret->blitVB_->Unlock();
        }

        {
            auto ib = static_cast<int32_t*>(ret->blitIB_->Lock());

            ib[0] = 0;
            ib[1] = 1;
            ib[2] = 2;
            ib[3] = 2;
            ib[4] = 3;
            ib[5] = 0;

            ret->blitIB_->Unlock();
        }
    }

    return ret;
}

std::shared_ptr<RenderTexture> CommandList::GetScreenTexture() const { return internalScreen_; }

void CommandList::StartFrame() {
    if (copyMaterial_ == nullptr) {
        copyMaterial_ = MakeAsdShared<Material>();
        auto vs = Graphics::GetInstance()->GetBuiltinShader()->Create(BuiltinShaderType::SpriteUnlitVS);
        auto ps = Graphics::GetInstance()->GetBuiltinShader()->Create(BuiltinShaderType::SpriteUnlitPS);
        copyMaterial_->SetShader(ps);
    }

    // Generate internal screen
    {
        auto cc = Graphics::GetInstance()->GetClearColor().ToLL();
        auto r = Graphics::GetInstance()->GetCurrentScreen(cc, true, true);

        auto g = Graphics::GetInstance()->GetGraphicsLLGI();
        if (internalScreen_ == nullptr || internalScreen_->GetSize().X != r->GetRenderTexture(0)->GetSizeAs2D().X ||
            internalScreen_->GetSize().Y != r->GetRenderTexture(0)->GetSizeAs2D().Y) {
            auto size = r->GetRenderTexture(0)->GetSizeAs2D();
            internalScreen_ = RenderTexture::Create(Vector2I(size.X, size.Y));
            internalScreen_->SetInstanceName(u"InternalScreen");
        }
    }

    memoryPool_->NewFrame();
    currentCommandList_ = commandListPool_->Get();
    currentCommandList_->Begin();

    for (auto& c : renderPassCaches_) {
        c.second.Life--;
    }

    for (auto it = renderPassCaches_.begin(); it != renderPassCaches_.end();) {
        if (it->second.Life == 0) {
            it = renderPassCaches_.erase(it);
        } else {
            it++;
        }
    }

    // Reset
    isRequiredNotToPresent_ = false;
}

void CommandList::EndFrame() {
    if (isInRenderPass_) {
        EndRenderPass();
    }
    currentCommandList_->End();

    FrameDebugger::GetInstance()->EndFrame();
}

void CommandList::SetScissor(const RectI& scissor) { currentCommandList_->SetScissor(scissor.X, scissor.Y, scissor.Width, scissor.Height); }

void CommandList::BeginRenderPass(std::shared_ptr<RenderTexture> target, std::shared_ptr<LLGI::RenderPass> renderPass) {
    if (isInRenderPass_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::BeginRenderPass: invalid CommandList state");
        return;
    }

    currentCommandList_->BeginRenderPass(renderPass.get());
    currentRenderPass_ = renderPass;
    currentRenderTarget_ = target;
    isInRenderPass_ = true;

    FrameDebugger::GetInstance()->SetRenderTarget(target);
    FrameDebugger::GetInstance()->BeginRenderPass();
}

void CommandList::EndRenderPass() {
    if (!isInRenderPass_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::EndRenderPass: invalid CommandList state");
        return;
    }

    currentCommandList_->EndRenderPass();
    FrameDebugger::GetInstance()->EndRenderPass();
    isInRenderPass_ = false;
    currentRenderPass_ = nullptr;
    currentRenderTarget_ = nullptr;
}

void CommandList::PauseRenderPass() {
    if (!isInRenderPass_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::EndRenderPass: invalid CommandList state");
        return;
    }

    currentCommandList_->EndRenderPass();
    FrameDebugger::GetInstance()->EndRenderPass();
    isInRenderPass_ = false;
}

void CommandList::ResumeRenderPass() {
    if (isInRenderPass_ || currentRenderPass_ == nullptr) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::ResumeRenderPass: invalid CommandList state");
        return;
    }

    currentRenderPass_->SetIsColorCleared(false);
    currentRenderPass_->SetIsDepthCleared(false);

    currentCommandList_->BeginRenderPass(currentRenderPass_.get());
    isInRenderPass_ = true;

    FrameDebugger::GetInstance()->BeginRenderPass();
}

void CommandList::SetRenderTarget(std::shared_ptr<RenderTexture> target, const RenderPassParameter& renderPassParameter) {
    auto it = renderPassCaches_.find(target);

    if (it == renderPassCaches_.end()) {
        auto g = Graphics::GetInstance()->GetGraphicsLLGI();

        LLGI::Texture* texture = target->GetNativeTexture().get();
        auto renderPass = LLGI::CreateSharedPtr(g->CreateRenderPass((const LLGI::Texture**)&texture, 1, nullptr));

        RenderPassCache cache;
        cache.Life = 5;
        cache.Stored = renderPass;
        renderPassCaches_[target] = cache;
    } else {
        // extend life to avoid to remove
        it->second.Life = 5;
    }

    renderPassCaches_[target].Stored->SetIsColorCleared(renderPassParameter.ColorCare == RenderTargetCareType::Clear);
    renderPassCaches_[target].Stored->SetIsDepthCleared(renderPassParameter.ColorCare == RenderTargetCareType::Clear);
    renderPassCaches_[target].Stored->SetClearColor(renderPassParameter.ClearColor.ToLL());

    if (isInRenderPass_) {
        EndRenderPass();
    }

    BeginRenderPass(target, renderPassCaches_[target].Stored);
}

void CommandList::RenderToRenderTexture(std::shared_ptr<Material> material, std::shared_ptr<RenderTexture> target) {
    auto currentTarget = currentRenderTarget_;

    RenderPassParameter param;
    param.ClearColor = Graphics::GetInstance()->GetClearColor();
    param.ColorCare = RenderTargetCareType::Clear;
    param.DepthCare = RenderTargetCareType::Clear;

    SetRenderTarget(target, param);
    RenderToRenderTarget(material);

    if (currentTarget != nullptr) {
        param.ColorCare = RenderTargetCareType::DontCare;
        param.DepthCare = RenderTargetCareType::DontCare;
        SetRenderTarget(currentTarget, param);
    }
}

void CommandList::RenderToRenderTarget(std::shared_ptr<Material> material) {
    // default paramter
    Matrix44F matE;
    matE.SetIdentity();
    material->SetMatrix44F(u"matView", matE);
    material->SetMatrix44F(u"matProjection", matE);
    matPropBlockCollection_->Clear();
    matPropBlockCollection_->Add(material->GetPropertyBlock());

    // VB, IB
    currentCommandList_->SetVertexBuffer(blitVB_.get(), sizeof(BatchVertex), 0);
    currentCommandList_->SetIndexBuffer(blitIB_.get(), 0);

    // pipeline state
    currentCommandList_->SetPipelineState(material->GetPipelineState(GetCurrentRenderPass()).get());

    // constant buffer
    StoreUniforms(this, material->GetShader(ShaderStageType::Vertex), LLGI::ShaderStageType::Vertex, matPropBlockCollection_);
    StoreUniforms(this, material->GetShader(ShaderStageType::Pixel), LLGI::ShaderStageType::Pixel, matPropBlockCollection_);

    // texture
    StoreTextures(this, material->GetShader(ShaderStageType::Vertex), LLGI::ShaderStageType::Vertex, matPropBlockCollection_);
    StoreTextures(this, material->GetShader(ShaderStageType::Pixel), LLGI::ShaderStageType::Pixel, matPropBlockCollection_);

    Draw(2);
}

void CommandList::SetRenderTargetWithScreen() {
    auto g = Graphics::GetInstance()->GetGraphicsLLGI();

    auto r = LLGI::CreateSharedPtr(Graphics::GetInstance()->GetCurrentScreen(LLGI::Color8(50, 50, 50, 255), true, true));
    r->AddRef();

    if (r == currentRenderPass_) {
        return;
    }

    if (isInRenderPass_) {
        EndRenderPass();
    }

    BeginRenderPass(internalScreen_, r);
}

void CommandList::PresentInternal() {
    if (isRequiredNotToPresent_) return;

    SetRenderTargetWithScreen();

    copyMaterial_->SetTexture(u"mainTex", internalScreen_);
    RenderToRenderTarget(copyMaterial_);
}

void CommandList::RequireNotToPresent() { isRequiredNotToPresent_ = true; }

void CommandList::StoreTextures(
        CommandList* commandList,
        std::shared_ptr<Shader> shader,
        LLGI::ShaderStageType shaderStage,
        std::shared_ptr<MaterialPropertyBlockCollection> matPropBlockCollection) {
    for (const auto& info : shader->GetReflectionTextures()) {
        auto v = matPropBlockCollection->GetTexture(info.Name.c_str());

        if (v.get() == nullptr) {
            commandList->GetLL()->SetTexture(
                    proxyTexture_.get(), LLGI::TextureWrapMode::Repeat, LLGI::TextureMinMagFilter::Linear, info.Offset, shaderStage);
            FrameDebugger::GetInstance()->Texture(shader->GetStageType(), u"proxyTexture_");

        } else {
            commandList->GetLL()->SetTexture(
                    v->GetNativeTexture().get(),
                    LLGI::TextureWrapMode::Repeat,
                    LLGI::TextureMinMagFilter::Linear,
                    info.Offset,
                    shaderStage);
            FrameDebugger::GetInstance()->Texture(shader->GetStageType(), v->GetInstanceName());
        }
    }
}

void CommandList::SetVertexBuffer(LLGI::VertexBuffer* vb, int32_t stride, int32_t offset) {
    GetLL()->SetVertexBuffer(vb, stride, offset);
    FrameDebugger::GetInstance()->SetVertexBuffer(stride, offset);
}

void CommandList::SetIndexBuffer(LLGI::IndexBuffer* ib, int32_t offset) {
    GetLL()->SetIndexBuffer(ib, offset);
    FrameDebugger::GetInstance()->SetIndexBuffer(offset);
}

void CommandList::StoreUniforms(
        CommandList* commandList,
        std::shared_ptr<Shader> shader,
        LLGI::ShaderStageType shaderStage,
        std::shared_ptr<MaterialPropertyBlockCollection> matPropBlockCollection) {
    if (shader->GetUniformSize() == 0) {
        return;
    }

    LLGI::ConstantBuffer* cb = nullptr;
    cb = commandList->GetMemoryPool()->CreateConstantBuffer(shader->GetUniformSize());

    auto bufv = static_cast<uint8_t*>(cb->Lock());
    for (const auto& info : shader->GetReflectionUniforms()) {
        if (info.Size == sizeof(float) * 4) {
            auto v = matPropBlockCollection->GetVector4F(info.Name.c_str());
            memcpy(bufv + info.Offset, &v, info.Size);
            FrameDebugger::GetInstance()->Uniform(shader->GetStageType(), info.Name, v);
        }

        if (info.Size == sizeof(float) * 16) {
            auto v = matPropBlockCollection->GetMatrix44F(info.Name.c_str());
            v.SetTransposed();
            memcpy(bufv + info.Offset, &v, info.Size);
            FrameDebugger::GetInstance()->Uniform(shader->GetStageType(), info.Name, v);
        }
    }

    cb->Unlock();

    commandList->GetLL()->SetConstantBuffer(cb, shaderStage);

    LLGI::SafeRelease(cb);
}

void CommandList::Draw(int32_t instanceCount) {
    GetLL()->Draw(instanceCount);

    if (FrameDebugger::GetInstance()->GetIsEnabled()) {
        auto texture = currentRenderPass_->GetRenderTexture(0);
        if (texture->GetType() == LLGI::TextureType::Screen) {
            return;
        }

        auto path = FrameDebugger::GetInstance()->GetDebuggingRenderTargetFileNameAndMoveNext();
        FrameDebugger::GetInstance()->Render(instanceCount, path);

        auto target = RenderTexture::Create(Vector2I(texture->GetSizeAs2D().X, texture->GetSizeAs2D().Y));

        currentCommandList_->EndRenderPass();
        currentCommandList_->CopyTexture(texture, target->GetNativeTexture().get());

        currentRenderPass_->SetIsColorCleared(false);
        currentRenderPass_->SetIsDepthCleared(false);

        currentCommandList_->BeginRenderPass(currentRenderPass_.get());

        SaveRenderTexture(path.c_str(), target);
    }
}

void CommandList::CopyTexture(std::shared_ptr<RenderTexture> src, std::shared_ptr<RenderTexture> dst) {
    auto srcSize = src->GetSize();
    auto dstSize = dst->GetSize();

    if (srcSize != dstSize) {
        Log::GetInstance()->Error(
                LogCategory::Core,
                u"CommandList::CopyTexture failed, src's size ({}, {}) is not equal to dst's size ({}, {})",
                srcSize.X,
                srcSize.Y,
                dstSize.X,
                dstSize.Y);
        return;
    }

    if (isInRenderPass_) {
        PauseRenderPass();
        currentCommandList_->CopyTexture(src->GetNativeTexture().get(), dst->GetNativeTexture().get());
        ResumeRenderPass();
    } else {
        currentCommandList_->CopyTexture(src->GetNativeTexture().get(), dst->GetNativeTexture().get());
    }
}

LLGI::SingleFrameMemoryPool* CommandList::GetMemoryPool() const { return memoryPool_.get(); }

LLGI::RenderPass* CommandList::GetCurrentRenderPass() const { return currentRenderPass_.get(); }

LLGI::CommandList* CommandList::GetLL() const { return currentCommandList_; }

void CommandList::SaveRenderTexture(const char16_t* path, std::shared_ptr<RenderTexture> texture) {
    if (currentCommandList_ == nullptr) return;

    currentCommandList_->AddRef();
    auto commandList = LLGI::CreateSharedPtr(currentCommandList_);
    std::u16string filepath(path);

    auto screen = texture;

    auto f = [commandList, filepath, screen]() -> void {
        commandList->WaitUntilCompleted();
        auto data = Graphics::GetInstance()->GetGraphicsLLGI()->CaptureRenderTarget(screen->GetNativeTexture().get());

        auto path8 = utf16_to_utf8(filepath.c_str());

        stbi_write_png(path8.c_str(), screen->GetSize().X, screen->GetSize().Y, 4, data.data(), screen->GetSize().X * 4);
    };

    SynchronizationContext::GetInstance()->AddEvent(f);
}

}  // namespace Altseed