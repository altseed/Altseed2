#include "CommandList.h"

#include "../Graphics/Graphics.h"
#include "BuiltinShader.h"
#include "RenderTexture.h"

namespace Altseed {

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
        auto r = Graphics::GetInstance()->GetCurrentScreen(LLGI::Color8(50, 50, 50, 255), true, true);
        auto g = Graphics::GetInstance()->GetGraphicsLLGI();
        if (internalScreen_ == nullptr || internalScreen_->GetSize().X != r->GetRenderTexture(0)->GetSizeAs2D().X ||
            internalScreen_->GetSize().Y != r->GetRenderTexture(0)->GetSizeAs2D().Y) {
            auto size = r->GetRenderTexture(0)->GetSizeAs2D();
            internalScreen_ = RenderTexture::Create(Vector2I(size.X, size.Y));
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
        currentCommandList_->EndRenderPass();
        isInRenderPass_ = false;
        currentRenderPass_ = nullptr;
    }
    currentCommandList_->End();
}

void CommandList::SetScissor(const RectI& scissor) { currentCommandList_->SetScissor(scissor.X, scissor.Y, scissor.Width, scissor.Height); }

void CommandList::SetRenderTarget(std::shared_ptr<RenderTexture> target, const RectI& viewport) {
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

    if (isInRenderPass_) {
        currentCommandList_->EndRenderPass();
    }

    currentCommandList_->BeginRenderPass(renderPassCaches_[target].Stored.get());
    currentRenderPass_ = renderPassCaches_[target].Stored;
    isInRenderPass_ = true;
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
    StoreUniforms(this, material->GetVertexShader(), LLGI::ShaderStageType::Vertex, matPropBlockCollection_);
    StoreUniforms(this, material->GetShader(), LLGI::ShaderStageType::Pixel, matPropBlockCollection_);

    // texture
    StoreTextures(this, material->GetVertexShader(), LLGI::ShaderStageType::Vertex, matPropBlockCollection_);
    StoreTextures(this, material->GetShader(), LLGI::ShaderStageType::Pixel, matPropBlockCollection_);

    // draw
    currentCommandList_->Draw(2);
}

void CommandList::SetRenderTargetWithScreen() {
    auto g = Graphics::GetInstance()->GetGraphicsLLGI();

    auto r = LLGI::CreateSharedPtr(Graphics::GetInstance()->GetCurrentScreen(LLGI::Color8(50, 50, 50, 255), true, true));
    r->AddRef();

    if (r == currentRenderPass_) {
        return;
    }

    if (isInRenderPass_) {
        currentCommandList_->EndRenderPass();
    }

    currentCommandList_->BeginRenderPass(r.get());
    currentRenderPass_ = r;
    isInRenderPass_ = true;
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

        } else {
            commandList->GetLL()->SetTexture(
                    v->GetNativeTexture().get(),
                    LLGI::TextureWrapMode::Repeat,
                    LLGI::TextureMinMagFilter::Linear,
                    info.Offset,
                    shaderStage);
        }
    }
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
        }

        if (info.Size == sizeof(float) * 16) {
            auto v = matPropBlockCollection->GetMatrix44F(info.Name.c_str());
            v.SetTransposed();
            memcpy(bufv + info.Offset, &v, info.Size);
        }
    }

    cb->Unlock();

    commandList->GetLL()->SetConstantBuffer(cb, shaderStage);

    LLGI::SafeRelease(cb);
}

LLGI::SingleFrameMemoryPool* CommandList::GetMemoryPool() const { return memoryPool_.get(); }

LLGI::RenderPass* CommandList::GetCurrentRenderPass() const { return currentRenderPass_.get(); }

LLGI::CommandList* CommandList::GetLL() const { return currentCommandList_; }

}  // namespace Altseed