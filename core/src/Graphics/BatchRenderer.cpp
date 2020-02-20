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
        rawIndexBuffer_.emplace_back(ib[i] + b.VertexCount);
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
            material->SetTexture(u"mainTex", batch.texture);
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
        commandList->StoreUniforms(commandList, material->GetVertexShader(), LLGI::ShaderStageType::Vertex, matPropBlockCollection_);
        commandList->StoreUniforms(commandList, material->GetShader(), LLGI::ShaderStageType::Pixel, matPropBlockCollection_);

        // texture
        commandList->StoreTextures(commandList, material->GetVertexShader(), LLGI::ShaderStageType::Vertex, matPropBlockCollection_);
        commandList->StoreTextures(commandList, material->GetShader(), LLGI::ShaderStageType::Pixel, matPropBlockCollection_);

        // draw
        commandList->GetLL()->Draw(batch.IndexCount / 3);
    }
}

void BatchRenderer::ResetCache() {
    batches_.resize(0);
    rawVertexBuffer_.resize(0);
    rawIndexBuffer_.resize(0);
}

void BatchRenderer::SetViewProjectionWithWindowsSize(const Vector2I& windowSize) {
    matView_.SetIdentity();
    matProjection_.SetIdentity();
    matProjection_.Values[0][0] = 2.0f / windowSize.X;
    matProjection_.Values[1][1] = -2.0f / windowSize.Y;
    matProjection_.Values[0][3] = -1.0f;
    matProjection_.Values[1][3] = 1.0f;
}

}  // namespace Altseed