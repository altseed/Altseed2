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

namespace Altseed2 {

RenderPassParameter::operator RenderPassParameter_C() const {
    auto m = RenderPassParameter_C();
    m.ClearColor = ClearColor;
    m.IsColorCleared = IsColorCleared;
    m.IsDepthCleared = IsDepthCleared;
    return m;
}

RenderPassParameter_C::operator RenderPassParameter() const {
    auto m = RenderPassParameter();
    m.ClearColor = ClearColor;
    m.IsColorCleared = IsColorCleared;
    m.IsDepthCleared = IsDepthCleared;
    return m;
}

std::shared_ptr<CommandList::RenderPass> CommandList::CreateRenderPass(std::shared_ptr<RenderTexture> target) {
    auto it = renderPassCaches_.find(target);

    if (it == renderPassCaches_.end()) {
        auto g = Graphics::GetInstance()->GetGraphicsLLGI();

        LLGI::Texture* texture = target->GetNativeTexture().get();
        auto renderPass = LLGI::CreateSharedPtr(g->CreateRenderPass((LLGI::Texture**)&texture, 1, nullptr));

        auto rp = std::make_shared<RenderPass>();
        rp->Stored = renderPass;
        rp->RenderTarget = target;
        RenderPassCache cache;
        cache.Life = 5;
        cache.Stored = rp;
        renderPassCaches_[target] = cache;

        return rp;
    } else {
        // extend life to avoid to remove
        it->second.Life = 5;
        return it->second.Stored;
    }
}

std::shared_ptr<CommandList> CommandList::Create() {
    auto g = Graphics::GetInstance()->GetGraphicsLLGI();
    auto memoryPool = LLGI::CreateSharedPtr(g->CreateSingleFrameMemoryPool(1024 * 1024 * 16, 128));
    auto commandListPool = std::make_shared<LLGI::CommandListPool>(g, memoryPool.get(), 3);
    auto ret = CreateSharedPtr(new CommandList());

    ret->screenTextureFormat_ = TextureFormatType::R8G8B8A8_UNORM;

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
        ret->blitVB_ = LLGI::CreateSharedPtr(g->CreateBuffer(LLGI::BufferUsageType::Vertex, sizeof(BatchVertex) * 4));
        ret->blitIB_ = LLGI::CreateSharedPtr(g->CreateBuffer(LLGI::BufferUsageType::Index, 4 * 6));

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

void CommandList::Begin() {
    if (isInFrame_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::Begin: This function must be paired with EndFrame.");
        return;
    }

    isInFrame_ = true;

    memoryPool_->NewFrame();
    currentCommandList_ = commandListPool_->Get();
    currentCommandList_->Begin();
}

void CommandList::End() {
    if (!isInFrame_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::End: This function must be paired with StartFrame.");
        return;
    }

    currentCommandList_->End();

    isInFrame_ = false;
}

void CommandList::StartFrame(const RenderPassParameter& renderPassParameter) {
    if (isInFrame_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::StartFrame: This function must be paired with EndFrame.");
        return;
    }

    isInFrame_ = true;

    if (copyMaterial_ == nullptr) {
        copyMaterial_ = MakeAsdShared<Material>();
        auto vs = Graphics::GetInstance()->GetBuiltinShader()->Create(BuiltinShaderType::SpriteUnlitVS);
        auto ps = Graphics::GetInstance()->GetBuiltinShader()->Create(BuiltinShaderType::SpriteUnlitPS);
        copyMaterial_->SetShader(ps);
    }

    // Generate internal screen
    {
        auto r = Graphics::GetInstance()->GetCurrentScreen(
                renderPassParameter.ClearColor.ToLL(), renderPassParameter.IsColorCleared, renderPassParameter.IsDepthCleared);

        auto g = Graphics::GetInstance()->GetGraphicsLLGI();
        if (internalScreen_ == nullptr ||
            internalScreen_->GetFormat() != screenTextureFormat_ ||
            internalScreen_->GetSize().X != r->GetRenderTexture(0)->GetSizeAs2D().X ||
            internalScreen_->GetSize().Y != r->GetRenderTexture(0)->GetSizeAs2D().Y) {
            auto size = r->GetRenderTexture(0)->GetSizeAs2D();
            internalScreen_ = RenderTexture::Create(Vector2I(size.X, size.Y), screenTextureFormat_);
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

    currentCommandList_->UploadBuffer(blitIB_.get());
    currentCommandList_->UploadBuffer(blitVB_.get());
}

void CommandList::EndFrame() {
    if (!isInFrame_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::EndFrame: This function must be paired with StartFrame.");
        return;
    }

    if (isInRenderPass_) {
        EndRenderPass();
    }
    currentCommandList_->End();

    FrameDebugger::GetInstance()->EndFrame();

    isInFrame_ = false;
}

void CommandList::SetScissor(const RectI& scissor) { currentCommandList_->SetScissor(scissor.X, scissor.Y, scissor.Width, scissor.Height); }

void CommandList::BeginRenderPass(std::shared_ptr<RenderPass> renderPass) {
    if (!isInFrame_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::BeginRenderPass: This function must be called in Frame.");
        return;
    }

    if (isInRenderPass_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::BeginRenderPass: invalid CommandList state");
        return;
    }

    currentCommandList_->BeginRenderPass(renderPass->Stored.get());
    currentRenderPass_ = renderPass;
    isInRenderPass_ = true;

    FrameDebugger::GetInstance()->SetRenderTarget(renderPass->RenderTarget);
    FrameDebugger::GetInstance()->BeginRenderPass();
}

void CommandList::EndRenderPass() {
    if (!isInFrame_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::EndRenderPass: This function must be called in Frame.");
        return;
    }

    if (!isInRenderPass_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::EndRenderPass: invalid CommandList state");
        return;
    }

    currentCommandList_->EndRenderPass();
    FrameDebugger::GetInstance()->EndRenderPass();
    isInRenderPass_ = false;
    currentRenderPass_ = nullptr;
    currentRenderPassLL_ = nullptr;
}

void CommandList::PauseRenderPass() {
    if (!isInFrame_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::PauseRenderPass: This function must be called in Frame.");
        return;
    }

    if (!isInRenderPass_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::EndRenderPass: invalid CommandList state");
        return;
    }

    currentCommandList_->EndRenderPass();
    FrameDebugger::GetInstance()->EndRenderPass();
    isInRenderPass_ = false;
}

void CommandList::ResumeRenderPass() {
    if (!isInFrame_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::ResumeRenderPass: This function must be called in Frame.");
        return;
    }

    if (isInRenderPass_ || (currentRenderPass_ == nullptr && currentRenderPassLL_ == nullptr)) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::ResumeRenderPass: invalid CommandList state");
        return;
    }

    if (currentRenderPass_ != nullptr) {
        currentRenderPass_->Stored->SetIsColorCleared(false);
        currentRenderPass_->Stored->SetIsDepthCleared(false);

        currentCommandList_->BeginRenderPass(currentRenderPass_->Stored.get());
    } else {
        currentCommandList_->BeginRenderPass(currentRenderPassLL_);
    }

    isInRenderPass_ = true;

    FrameDebugger::GetInstance()->BeginRenderPass();
}

void CommandList::UploadBuffer(std::shared_ptr<Buffer> buffer) {
    currentCommandList_->UploadBuffer(buffer->GetLL().get());
}

void CommandList::ReadbackBuffer(std::shared_ptr<Buffer> buffer) {
    currentCommandList_->ReadBackBuffer(buffer->GetLL().get());
}

void CommandList::CopyBuffer(std::shared_ptr<Buffer> src, std::shared_ptr<Buffer> dst) {
    currentCommandList_->CopyBuffer(src->GetLL().get(), dst->GetLL().get());
}

void CommandList::SetRenderTarget(std::shared_ptr<RenderTexture> target, const RenderPassParameter& renderPassParameter) {
    if (!isInFrame_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::SetRenderTarget: This function must be called in Frame.");
        return;
    }

    auto stored = CreateRenderPass(target);

    stored->Stored->SetClearColor(renderPassParameter.ClearColor.ToLL());
    stored->Stored->SetIsColorCleared(renderPassParameter.IsColorCleared);
    stored->Stored->SetIsDepthCleared(renderPassParameter.IsDepthCleared);

    if (isInRenderPass_) {
        EndRenderPass();
    }

    BeginRenderPass(renderPassCaches_[target].Stored);
}

void CommandList::RenderToRenderTexture(
        std::shared_ptr<Material> material, std::shared_ptr<RenderTexture> target, const RenderPassParameter& renderPassParameter) {
    if (!isInFrame_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::RenderToRenderTexture: This function must be called in Frame.");
        return;
    }

    std::shared_ptr<Altseed2::RenderTexture> currentTarget;

    if (currentRenderPass_ != nullptr) {
        currentTarget = currentRenderPass_->RenderTarget;
    }

    SetRenderTarget(target, renderPassParameter);
    RenderToRenderTarget(material);

    if (currentTarget != nullptr) {
        auto param = renderPassParameter;
        param.IsColorCleared = false;
        param.IsDepthCleared = false;
        SetRenderTarget(currentTarget, param);
    }
}

void CommandList::RenderToRenderTarget(std::shared_ptr<Material> material) {
    if (!isInFrame_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::RenderToRenderTarget: This function must be called in Frame.");
        return;
    }

    // default paramter
    Matrix44F matE;
    matE.SetIdentity();
    material->SetMatrix44F(u"matView", matE);
    material->SetMatrix44F(u"matProjection", matE);
    matPropBlockCollection_->Clear();
    matPropBlockCollection_->Add(material->GetPropertyBlock());

    // VB, IB
    currentCommandList_->SetVertexBuffer(blitVB_.get(), sizeof(BatchVertex), 0);
    currentCommandList_->SetIndexBuffer(blitIB_.get(), 4, 0);

    // pipeline state
    auto renderPass = GetCurrentRenderPass();
    ASD_ASSERT(renderPass != nullptr, "RenderPass is null.");

    currentCommandList_->SetPipelineState(material->GetPipelineState(renderPass).get());

    // constant buffer
    StoreUniforms(this, material->GetShader(ShaderStageType::Vertex), LLGI::ShaderStageType::Vertex, matPropBlockCollection_);
    StoreUniforms(this, material->GetShader(ShaderStageType::Pixel), LLGI::ShaderStageType::Pixel, matPropBlockCollection_);

    // texture
    currentCommandList_->ResetTextures();
    StoreTextures(this, material->GetShader(ShaderStageType::Vertex), LLGI::ShaderStageType::Vertex, matPropBlockCollection_);
    StoreTextures(this, material->GetShader(ShaderStageType::Pixel), LLGI::ShaderStageType::Pixel, matPropBlockCollection_);

    Draw(2);
}

void CommandList::SetRenderTargetWithScreen(const RenderPassParameter& renderPassParameter) {
    if (!isInFrame_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::SetRenderTargetWithScreen: This function must be called in Frame.");
        return;
    }

    auto g = Graphics::GetInstance()->GetGraphicsLLGI();

    if (isInRenderPass_) {
        EndRenderPass();
    }

    auto r = Graphics::GetInstance()->GetCurrentScreen(
            renderPassParameter.ClearColor.ToLL(), renderPassParameter.IsColorCleared, renderPassParameter.IsDepthCleared);

    currentCommandList_->BeginRenderPass(r);
    currentRenderPassLL_ = r;
    isInRenderPass_ = true;
}

void CommandList::PresentInternal() {
    if (!isPresentScreenBufferDirectly_) return;

    if (isInRenderPass_) {
        EndRenderPass();
    }

    RenderPassParameter param;
    param.IsColorCleared = true;
    param.IsDepthCleared = false;
    param.ClearColor = Color(0, 0, 0, 0);
    SetRenderTargetWithScreen(param);

    copyMaterial_->SetTexture(u"mainTex", internalScreen_);
    RenderToRenderTarget(copyMaterial_);

    EndRenderPass();
}

bool CommandList::GetIsPresentScreenBufferDirectly() const { return isPresentScreenBufferDirectly_; }

void CommandList::SetIsPresentScreenBufferDirectly(bool value) { isPresentScreenBufferDirectly_ = value; }

void CommandList::StoreTextures(
        CommandList* commandList,
        std::shared_ptr<Shader> shader,
        LLGI::ShaderStageType shaderStage,
        std::shared_ptr<MaterialPropertyBlockCollection> matPropBlockCollection) {
    for (const auto& info : shader->GetReflectionTextures()) {
        auto v = matPropBlockCollection->GetTexture(info.Name.c_str());

        if (v.get() == nullptr) {
            commandList->GetLL()->SetTexture(
                    proxyTexture_.get(),
                    static_cast<LLGI::TextureWrapMode>(TextureWrapMode::Clamp),
                    static_cast<LLGI::TextureMinMagFilter>(TextureFilterType::Linear),
                    info.Offset,
                    shaderStage);
            FrameDebugger::GetInstance()->Texture(shader->GetStageType(), u"proxyTexture_");

        } else {
            commandList->GetLL()->SetTexture(
                    v->GetNativeTexture().get(),
                    static_cast<LLGI::TextureWrapMode>(v->GetWrapMode()),
                    static_cast<LLGI::TextureMinMagFilter>(v->GetFilterType()),
                    info.Offset,
                    shaderStage);
            FrameDebugger::GetInstance()->Texture(shader->GetStageType(), v->GetInstanceName());
        }
    }
}

void CommandList::SetVertexBuffer(LLGI::Buffer* vb, int32_t stride, int32_t offset) {
    GetLL()->SetVertexBuffer(vb, stride, offset);
    FrameDebugger::GetInstance()->SetVertexBuffer(stride, offset);
}

void CommandList::SetIndexBuffer(LLGI::Buffer* ib, int32_t stride, int32_t offset) {
    GetLL()->SetIndexBuffer(ib, stride, offset);
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

    LLGI::Buffer* cb = nullptr;
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

    bool isPauseRenderPass = isInRenderPass_;

    commandList->GetLL()->SetConstantBuffer(cb, shaderStage);
    if (isPauseRenderPass)
        PauseRenderPass();
    commandList->GetLL()->UploadBuffer(cb);
    if (isPauseRenderPass)
        ResumeRenderPass();

    LLGI::SafeRelease(cb);
}

void CommandList::Draw(int32_t instanceCount) {
    GetLL()->Draw(instanceCount);

    if (FrameDebugger::GetInstance()->GetIsEnabled() && currentRenderPass_ != nullptr) {
        LLGI::Texture* texture = currentRenderPass_->Stored->GetRenderTexture(0);
        if (texture->GetType() == LLGI::TextureType::Screen) {
            return;
        }

        auto path = FrameDebugger::GetInstance()->GetDebuggingRenderTargetFileNameAndMoveNext();
        FrameDebugger::GetInstance()->Render(instanceCount, path);

        auto target = RenderTexture::Create(Vector2I(texture->GetSizeAs2D().X, texture->GetSizeAs2D().Y), TextureFormatType::R8G8B8A8_UNORM);

        currentCommandList_->EndRenderPass();
        isInRenderPass_ = false;
        auto renderPass = currentRenderPass_;

        CopyTexture(renderPass->RenderTarget, target);

        renderPass->Stored->SetIsColorCleared(false);
        renderPass->Stored->SetIsDepthCleared(false);
        currentCommandList_->BeginRenderPass(renderPass->Stored.get());
        isInRenderPass_ = true;

        SaveRenderTexture(path.c_str(), target);
    }
}

void CommandList::SetVertexBuffer(std::shared_ptr<Buffer> vb, int32_t stride, int32_t offset) {
    SetVertexBuffer(vb->GetLL().get(), stride, offset);
}

void CommandList::SetIndexBuffer(std::shared_ptr<Buffer> ib, int32_t stride, int32_t offset) {
    SetIndexBuffer(ib->GetLL().get(), stride, offset);
}

void CommandList::SetMaterial(std::shared_ptr<Material> material) {
    if (!isInRenderPass_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::SetMaterial: This function must be called in Frame.");
        return;
    }

    for (int i = 0; i < 2; i++) {
        auto shaderStage = static_cast<ShaderStageType>(i);

        auto shader = material->GetShader(shaderStage);
        if (shader == nullptr || shader->GetUniformSize() == 0) {
            continue;
        }

        LLGI::Buffer* cb = nullptr;
        cb = GetMemoryPool()->CreateConstantBuffer(shader->GetUniformSize());

        auto bufv = static_cast<uint8_t*>(cb->Lock());
        for (const auto& info : shader->GetReflectionUniforms()) {
            if (info.Size == sizeof(float) * 4) {
                auto v = material->GetPropertyBlock()->GetVector4F(info.Name.c_str());
                memcpy(bufv + info.Offset, &v, info.Size);
                FrameDebugger::GetInstance()->Uniform(shader->GetStageType(), info.Name, v);
            }

            if (info.Size == sizeof(float) * 16) {
                auto v = material->GetPropertyBlock()->GetMatrix44F(info.Name.c_str());
                v.SetTransposed();
                memcpy(bufv + info.Offset, &v, info.Size);
                FrameDebugger::GetInstance()->Uniform(shader->GetStageType(), info.Name, v);
            }
        }

        cb->Unlock();

        bool isPauseRenderPass = isInRenderPass_;

        GetLL()->SetConstantBuffer(cb, (LLGI::ShaderStageType)shaderStage);
        if (isPauseRenderPass)
            PauseRenderPass();
        GetLL()->UploadBuffer(cb);
        if (isPauseRenderPass)
            ResumeRenderPass();

        LLGI::SafeRelease(cb);

        for (const auto& info : shader->GetReflectionTextures()) {
            auto v = material->GetPropertyBlock()->GetTexture(info.Name.c_str());

            if (v.get() == nullptr) {
                GetLL()->SetTexture(
                        proxyTexture_.get(),
                        static_cast<LLGI::TextureWrapMode>(TextureWrapMode::Clamp),
                        static_cast<LLGI::TextureMinMagFilter>(TextureFilterType::Linear),
                        info.Offset,
                        (LLGI::ShaderStageType)shaderStage);
                FrameDebugger::GetInstance()->Texture(shader->GetStageType(), u"proxyTexture_");

            } else {
                GetLL()->SetTexture(
                        v->GetNativeTexture().get(),
                        static_cast<LLGI::TextureWrapMode>(v->GetWrapMode()),
                        static_cast<LLGI::TextureMinMagFilter>(v->GetFilterType()),
                        info.Offset,
                        (LLGI::ShaderStageType)shaderStage);
                FrameDebugger::GetInstance()->Texture(shader->GetStageType(), v->GetInstanceName());
            }
        }
    }

    // pipeline state
    GetLL()->SetPipelineState(material->GetPipelineState(GetCurrentRenderPass()).get());
}

void CommandList::BeginComputePass() {
    GetLL()->BeginComputePass();
}

void CommandList::EndComputePass() {
    GetLL()->EndComputePass();
}

void CommandList::SetComputeBuffer(std::shared_ptr<Buffer> buffer, int32_t stride, int32_t unit) {
    GetLL()->SetComputeBuffer(buffer->GetLL().get(), stride, unit);
}

void CommandList::SetComputePipelineState(std::shared_ptr<ComputePipelineState> computePipelineState) {
    auto shader = computePipelineState->GetShader();

    if (shader != nullptr && shader->GetUniformSize() != 0) {
        LLGI::Buffer* cb = nullptr;
        cb = GetMemoryPool()->CreateConstantBuffer(shader->GetUniformSize());

        auto bufv = static_cast<uint8_t*>(cb->Lock());
        for (const auto& info : shader->GetReflectionUniforms()) {
            if (info.Size == sizeof(float) * 4) {
                auto v = computePipelineState->GetPropertyBlock()->GetVector4F(info.Name.c_str());
                memcpy(bufv + info.Offset, &v, info.Size);
                FrameDebugger::GetInstance()->Uniform(shader->GetStageType(), info.Name, v);
            }

            if (info.Size == sizeof(float) * 16) {
                auto v = computePipelineState->GetPropertyBlock()->GetMatrix44F(info.Name.c_str());
                v.SetTransposed();
                memcpy(bufv + info.Offset, &v, info.Size);
                FrameDebugger::GetInstance()->Uniform(shader->GetStageType(), info.Name, v);
            }
        }

        EndComputePass();
        cb->Unlock();
        BeginComputePass();

        GetLL()->SetConstantBuffer(cb, LLGI::ShaderStageType::Compute);
        GetLL()->UploadBuffer(cb);

        LLGI::SafeRelease(cb);
    }

    // pipeline state
    GetLL()->SetPipelineState(computePipelineState->GetPipelineState().get());
}

void CommandList::Dispatch(int32_t x, int32_t y, int32_t z) {
    GetLL()->Dispatch(x, y, z);
}

void CommandList::CopyTexture(std::shared_ptr<RenderTexture> src, std::shared_ptr<RenderTexture> dst) {
    if (!isInFrame_) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::CopyTexture: This function must be called in Frame.");
        return;
    }

    if (src->GetFormat() != dst->GetFormat() || src->GetSize() != dst->GetSize()) {
        copyMaterial_->SetTexture(u"mainTex", src);
        RenderToRenderTexture(copyMaterial_, dst, RenderPassParameter());
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

void CommandList::ResetTextures() {
    currentCommandList_->ResetTextures();
}

void CommandList::ResetComputeBuffers() {
    currentCommandList_->ResetComputeBuffer();
}

LLGI::SingleFrameMemoryPool* CommandList::GetMemoryPool() const { return memoryPool_.get(); }

LLGI::RenderPass* CommandList::GetCurrentRenderPass() const {
    if (currentRenderPassLL_ != nullptr) return currentRenderPassLL_;
    if (currentRenderPass_ == nullptr) return nullptr;
    return currentRenderPass_->Stored.get();
}

LLGI::RenderPass* CommandList::GetScreenRenderPass() {
    auto renderPass = CreateRenderPass(GetScreenTexture());
    return renderPass->Stored.get();
}

LLGI::RenderPass* CommandList::GetActualScreenRenderPass() const {
    return Graphics::GetInstance()->GetCurrentScreen(Color().ToLL(), false, false);
}

LLGI::CommandList* CommandList::GetLL() const { return currentCommandList_; }

void CommandList::SaveRenderTexture(const char16_t* path, std::shared_ptr<RenderTexture> texture) {
    if (currentCommandList_ == nullptr) return;

    RETURN_IF_NULL(path, );

    if (texture->GetFormat() != TextureFormatType::R8G8B8A8_UNORM) {
        Log::GetInstance()->Error(LogCategory::Core, u"CommandList::SaveRenderTexture: TextureFormatType is unsupported");
        return;
    }

    currentCommandList_->AddRef();
    auto commandList = LLGI::CreateSharedPtr(currentCommandList_);
    std::u16string filepath(path);

    auto screen = texture;

    auto f = [commandList, filepath, screen]() -> void {
        commandList->WaitUntilCompleted();
        auto data = Graphics::GetInstance()->GetGraphicsLLGI()->CaptureRenderTarget(screen->GetNativeTexture().get());

        if (data.size() == 0) {
            Log::GetInstance()->Error(LogCategory::Core, u"A format of saveed textures cannot saved because it is unsupported format.");
            return;
        }

        auto path8 = utf16_to_utf8(filepath.c_str());

        stbi_write_png(path8.c_str(), screen->GetSize().X, screen->GetSize().Y, 4, data.data(), screen->GetSize().X * 4);
    };

    SynchronizationContext::GetInstance()->AddEvent(f);
}

}  // namespace Altseed2