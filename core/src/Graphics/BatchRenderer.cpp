#include "BatchRenderer.h"
#include "../Graphics/Graphics.h"
#include "CommandList.h"
#include "Material.h"

namespace altseed {

BatchRenderer::BatchRenderer(std::shared_ptr<Graphics> graphics) {
    auto graphicsLLGI = graphics->GetGraphicsLLGI();
    rawVertexBuffer_.reserve(VertexBufferMax);
    vertexBuffer_ = LLGI::CreateSharedPtr(graphicsLLGI->CreateVertexBuffer(sizeof(BatchVertex) * VertexBufferMax));
    indexBuffer_ = LLGI::CreateSharedPtr(graphicsLLGI->CreateIndexBuffer(4, IndexBufferMax));
    matPropBlockCollection_ = MakeAsdShared<MaterialPropertyBlockCollection>();

    matDefaultSprite_ = MakeAsdShared<Material>();
}

void BatchRenderer::Draw(
        const BatchVertex* vb, const int32_t* ib, int32_t vbCount, int32_t ibCount, const std::shared_ptr<Texture2D>& texture) {
    if (batches_.size() == 0 || batches_.back().texture != texture) {
        Batch batch;
        batch.texture = texture;
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
        rawIndexBuffer_.emplace_back(ib[i] + current);
    }

    b.VertexCount += vbCount;
    b.IndexCount += ibCount;
}

void BatchRenderer::Draw(
        const BatchVertex* vb, const int32_t* ib, int32_t vbCount, int32_t ibCount, const std::shared_ptr<Material>& material) {
    if (batches_.size() == 0 || batches_.back().material != material) {
        Batch batch;
        batch.material = material;
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
        rawIndexBuffer_.emplace_back(ib[i] + current);
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

    memcpy(pvb, rawVertexBuffer_.data(), sizeof(BatchVertex) * rawIndexBuffer_.size());
    memcpy(pib, rawIndexBuffer_.data(), sizeof(int32_t) * rawIndexBuffer_.size());

    vertexBuffer_->Unlock();
    indexBuffer_->Unlock();

    for (const auto& batch : batches_) {
        std::shared_ptr<Material> material;
        if (batch.material == nullptr) {
            material = matDefaultSprite_;
        }

		// TODO default value block
		matPropBlockCollection_->Clear();
        matPropBlockCollection_->Add(material->GetPropertyBlock());

        // VB, IB
        commandList->GetLL()->SetVertexBuffer(
                vertexBuffer_.get(), sizeof(BatchVertex), (vbOffset_ + batch.VertexOffset) * sizeof(BatchVertex));
        commandList->GetLL()->SetIndexBuffer(indexBuffer_.get(), (ibOffset_ + batch.IndexOffset) * sizeof(int32_t));

        // pipeline state
        commandList->GetLL()->SetPipelineState(material->GetPipelineState(commandList->GetCurrentRenderPass()).get());

        // constant buffer
        LLGI::ConstantBuffer* cbVS = nullptr;
        LLGI::ConstantBuffer* cbPS = nullptr;

        if (material->GetVertexShader()->GetUniformSize() > 0) {
            cbVS = commandList->GetMemoryPool()->CreateConstantBuffer(material->GetVertexShader()->GetUniformSize());
        }

        if (material->GetShader()->GetUniformSize() > 0) {
            cbPS = commandList->GetMemoryPool()->CreateConstantBuffer(material->GetShader()->GetUniformSize());
        }

        // TODO nullcheck
        auto bufv = static_cast<uint8_t*>(cbVS->Lock());
        for (const auto& info : material->GetVertexShader()->GetReflectionUniforms()) {
            if (info.Size == sizeof(float) * 4) {
                auto v = matPropBlockCollection_->GetVector4F(info.Name.c_str());
                memcpy(bufv + info.Offset, &v, info.Size);
            }

            if (info.Size == sizeof(float) * 16) {
                auto v = matPropBlockCollection_->GetMatrix44F(info.Name.c_str());
                memcpy(bufv + info.Offset, &v, info.Size);
            }
        }
        cbVS->Unlock();

        // TODO nullcheck
        auto bufp = static_cast<uint8_t*>(cbPS->Lock());
        for (const auto& info : material->GetShader()->GetReflectionUniforms()) {
            if (info.Size == sizeof(float) * 4) {
                auto v = matPropBlockCollection_->GetVector4F(info.Name.c_str());
                memcpy(bufp + info.Offset, &v, info.Size);
            }

            if (info.Size == sizeof(float) * 16) {
                auto v = matPropBlockCollection_->GetMatrix44F(info.Name.c_str());
                memcpy(bufp + info.Offset, &v, info.Size);
            }
        }
        cbPS->Unlock();

        commandList->GetLL()->SetConstantBuffer(cbVS, LLGI::ShaderStageType::Vertex);
        commandList->GetLL()->SetConstantBuffer(cbPS, LLGI::ShaderStageType::Pixel);

        LLGI::SafeRelease(cbVS);
        LLGI::SafeRelease(cbPS);

        // texture

		// TODO dammy
        for (const auto& info : material->GetVertexShader()->GetReflectionTextures()) {
            auto v = matPropBlockCollection_->GetTexture(info.Name.c_str());
            commandList->GetLL()->SetTexture(
                    v->GetNativeTexture().get(),
                    LLGI::TextureWrapMode::Repeat,
                    LLGI::TextureMinMagFilter::Linear,
                    info.Offset,
                    LLGI::ShaderStageType::Vertex);
        }

        for (const auto& info : material->GetShader()->GetReflectionTextures()) {
            auto v = matPropBlockCollection_->GetTexture(info.Name.c_str());
            commandList->GetLL()->SetTexture(
                    v->GetNativeTexture().get(),
                    LLGI::TextureWrapMode::Repeat,
                    LLGI::TextureMinMagFilter::Linear,
                    info.Offset,
                    LLGI::ShaderStageType::Pixel);
        }

        // draw
        commandList->GetLL()->Draw(batch.IndexCount / 3);
    }
}

void BatchRenderer::ResetCache() {
    batches_.resize(0);
    rawVertexBuffer_.resize(0);
    rawIndexBuffer_.resize(0);
}

}  // namespace altseed