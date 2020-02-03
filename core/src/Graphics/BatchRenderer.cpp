#include "BatchRenderer.h"
#include "../Graphics/Graphics.h"
#include "BuildinShader.h"
#include "CommandList.h"
#include "Material.h"

namespace Altseed {

BatchRenderer::BatchRenderer(std::shared_ptr<Graphics> graphics) {
    auto gLL = graphics->GetGraphicsLLGI();
    rawVertexBuffer_.reserve(VertexBufferMax);
    vertexBuffer_ = LLGI::CreateSharedPtr(gLL->CreateVertexBuffer(sizeof(BatchVertex) * VertexBufferMax));
    indexBuffer_ = LLGI::CreateSharedPtr(gLL->CreateIndexBuffer(4, IndexBufferMax));
    matPropBlockCollection_ = MakeAsdShared<MaterialPropertyBlockCollection>();

    matDefaultSprite_ = MakeAsdShared<Material>();
    auto vs = graphics->GetBuildinShader()->Create(BuildinShaderType::SpriteUnlitVS);
    auto ps = graphics->GetBuildinShader()->Create(BuildinShaderType::SpriteUnlitPS);
    matDefaultSprite_->SetShader(ps);

    {
        LLGI::TextureInitializationParameter texParam;
        texParam.Size = LLGI::Vec2I(16, 16);

        std::shared_ptr<LLGI::Texture> texture = LLGI::CreateSharedPtr(gLL->CreateTexture(texParam));
        auto texture_buf = (LLGI::Color8*)texture->Lock();
        for (int y = 0; y < 16; y++) {
            for (int x = 0; x < 16; x++) {
                texture_buf[x + y * 16].R = 255;
                texture_buf[x + y * 16].G = 255;
                texture_buf[x + y * 16].B = 255;
                texture_buf[x + y * 16].A = 255;
            }
        }
        texture->Unlock();
    }
}

void BatchRenderer::StoreTextures(CommandList* commandList, std::shared_ptr<Shader> shader, LLGI::ShaderStageType shaderStage) {
    for (const auto& info : shader->GetReflectionTextures()) {
        auto v = matPropBlockCollection_->GetTexture(info.Name.c_str());

        if (v.get() == nullptr) {
            commandList->GetLL()->SetTexture(
                    dammy.get(), LLGI::TextureWrapMode::Repeat, LLGI::TextureMinMagFilter::Linear, info.Offset, shaderStage);

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

void BatchRenderer::StoreUniforms(CommandList* commandList, std::shared_ptr<Shader> shader, LLGI::ShaderStageType shaderStage) {
    if (shader->GetUniformSize() == 0) {
        return;
    }

    LLGI::ConstantBuffer* cb = nullptr;
    cb = commandList->GetMemoryPool()->CreateConstantBuffer(shader->GetUniformSize());

    auto bufv = static_cast<uint8_t*>(cb->Lock());
    for (const auto& info : shader->GetReflectionUniforms()) {
        if (info.Size == sizeof(float) * 4) {
            auto v = matPropBlockCollection_->GetVector4F(info.Name.c_str());
            memcpy(bufv + info.Offset, &v, info.Size);
        }

        if (info.Size == sizeof(float) * 16) {
            auto v = matPropBlockCollection_->GetMatrix44F(info.Name.c_str());
            memcpy(bufv + info.Offset, &v, info.Size);
        }
    }

    cb->Unlock();

    commandList->GetLL()->SetConstantBuffer(cb, shaderStage);

    LLGI::SafeRelease(cb);
}

void BatchRenderer::Draw(
        const BatchVertex* vb,
        const int32_t* ib,
        int32_t vbCount,
        int32_t ibCount,
        const std::shared_ptr<Texture2D>& texture,
        const std::shared_ptr<Material>& material,
        const std::shared_ptr<MaterialPropertyBlock>& propBlock) {
    if (batches_.size() == 0 || batches_.back().texture != texture || batches_.back().material != material ||
        batches_.back().propBlock != propBlock) {
        Batch batch;
        batch.texture = texture;
        batch.material = material;
        batch.propBlock = propBlock;
        batch.VertexCount = 0;
        batch.IndexCount = 0;
        batch.VertexOffset = rawVertexBuffer_.size();
        batch.IndexOffset = rawIndexBuffer_.size();
        batches_.emplace_back(batch);
    }

    auto& b = batches_.back();

    auto current = rawVertexBuffer_.size();

    for (int32_t i = 0; i < vbCount; i++) {
        rawVertexBuffer_.emplace_back(vb[i]);
    }

    for (int32_t i = 0; i < ibCount; i++) {
        rawIndexBuffer_.emplace_back(ib[i]);
    }

    b.VertexCount += vbCount;
    b.IndexCount += ibCount;
}

void BatchRenderer::Render(CommandList* commandList) {
    if (batches_.size() == 0) return;

    if (VertexBufferMax < vbOffset_ + rawVertexBuffer_.size()) {
        vbOffset_ = 0;
    }

    if (IndexBufferMax < ibOffset_ + rawIndexBuffer_.size()) {
        ibOffset_ = 0;
    }

    // TODO need to cause warning
    if (VertexBufferMax < rawVertexBuffer_.size()) return;

    // TODO need to cause warning
    if (IndexBufferMax < rawIndexBuffer_.size()) return;

    auto pvb = static_cast<BatchVertex*>(vertexBuffer_->Lock()) + vbOffset_;
    auto pib = static_cast<int32_t*>(indexBuffer_->Lock()) + ibOffset_;

    memcpy(pvb, rawVertexBuffer_.data(), sizeof(BatchVertex) * rawVertexBuffer_.size());
    memcpy(pib, rawIndexBuffer_.data(), sizeof(int32_t) * rawIndexBuffer_.size());

    vertexBuffer_->Unlock();
    indexBuffer_->Unlock();

    for (const auto& batch : batches_) {
        std::shared_ptr<Material> material;
        if (batch.material == nullptr) {
            material = matDefaultSprite_;
            material->SetTexture(u"txt", batch.texture);
        }

        if (batch.texture != nullptr) {
            material->SetTexture(u"mainTex", batch.texture);
        }

        material->SetMatrix44F(u"matView", this->matView_);
        material->SetMatrix44F(u"matProjection", this->matProjection_);

        // TODO default value block
        matPropBlockCollection_->Clear();
        matPropBlockCollection_->Add(material->GetPropertyBlock());

        if (batch.propBlock != nullptr) {
            matPropBlockCollection_->Add(batch.propBlock);
        }

        // VB, IB
        commandList->GetLL()->SetVertexBuffer(
                vertexBuffer_.get(), sizeof(BatchVertex), (vbOffset_ + batch.VertexOffset) * sizeof(BatchVertex));
        commandList->GetLL()->SetIndexBuffer(indexBuffer_.get(), (ibOffset_ + batch.IndexOffset) * sizeof(int32_t));

        // pipeline state
        commandList->GetLL()->SetPipelineState(material->GetPipelineState(commandList->GetCurrentRenderPass()).get());

        // constant buffer
        StoreUniforms(commandList, material->GetVertexShader(), LLGI::ShaderStageType::Vertex);
        StoreUniforms(commandList, material->GetShader(), LLGI::ShaderStageType::Pixel);

        // texture
        StoreTextures(commandList, material->GetVertexShader(), LLGI::ShaderStageType::Vertex);
        StoreTextures(commandList, material->GetShader(), LLGI::ShaderStageType::Pixel);

        // draw
        commandList->GetLL()->Draw(batch.IndexCount / 3);
    }
}

void BatchRenderer::ResetCache() {
    batches_.resize(0);
    rawVertexBuffer_.resize(0);
    rawIndexBuffer_.resize(0);
}

void BatchRenderer::SetViewProjectionWithWindowsSize(const Vector2DI& windowSize) {
    matView_.SetIdentity();
    matProjection_.SetIdentity();
    matProjection_.Values[0][0] = 2.0f / windowSize.X;
    matProjection_.Values[1][1] = -2.0f / windowSize.Y;
    matProjection_.Values[0][3] = -1.0f;
    matProjection_.Values[1][3] = 1.0f;
}

}  // namespace Altseed