#include "BatchRenderer.h"

#include "../Graphics/Graphics.h"
#include "../Logger/Log.h"
#include "BuiltinShader.h"
#include "CommandList.h"
#include "Material.h"

namespace Altseed2 {

BatchRenderer::BatchRenderer(std::shared_ptr<Graphics> graphics) {
    auto gLL = graphics->GetGraphicsLLGI();
    rawVertexBuffer_.reserve(VertexBufferMax);
    vertexBuffer_ = LLGI::CreateSharedPtr(gLL->CreateBuffer(LLGI::BufferUsageType::Vertex, sizeof(BatchVertex) * VertexBufferMax));
    indexBuffer_ = LLGI::CreateSharedPtr(gLL->CreateBuffer(LLGI::BufferUsageType::Index, 4 * IndexBufferMax));
    matPropBlockCollection_ = MakeAsdShared<MaterialPropertyBlockCollection>();
}

void BatchRenderer::Draw(
        const BatchVertex* vb,
        const int32_t* ib,
        int32_t vbCount,
        int32_t ibCount,
        const std::shared_ptr<TextureBase>& texture,
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

void BatchRenderer::UploadBuffer() {
    if (batches_.size() == 0) return;

    auto commandList = Graphics::GetInstance()->GetCommandList();

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

    auto lockedVB = static_cast<BatchVertex*>(vertexBuffer_->Lock());
    auto lockedIB = static_cast<int32_t*>(indexBuffer_->Lock());

    if (lockedVB == nullptr || lockedIB == nullptr) {
        LOG_CRITICAL(u"BatchRenderer : Failed to lock.");
    }

    auto pvb = lockedVB + vbOffset_;
    auto pib = lockedIB + ibOffset_;

    memcpy(pvb, rawVertexBuffer_.data(), sizeof(BatchVertex) * rawVertexBuffer_.size());
    memcpy(pib, rawIndexBuffer_.data(), sizeof(int32_t) * rawIndexBuffer_.size());

    vertexBuffer_->Unlock();
    indexBuffer_->Unlock();

    commandList->GetLL()->UploadBuffer(indexBuffer_.get());
    commandList->GetLL()->UploadBuffer(vertexBuffer_.get());
}

void BatchRenderer::Render() {
    if (batches_.size() == 0) return;

    // TODO need to cause warning
    if (VertexBufferMax < rawVertexBuffer_.size()) return;

    // TODO need to cause warning
    if (IndexBufferMax < rawIndexBuffer_.size()) return;

    auto commandList = Graphics::GetInstance()->GetCommandList();

    for (const auto& batch : batches_) {
        if (batch.material == nullptr) {
            LOG_CRITICAL(u"BatchRenderer : Material not set.");
        }
        auto material = batch.material;

        material->SetTexture(u"mainTex", batch.texture);

        material->SetMatrix44F(u"matView", this->matView_);
        material->SetMatrix44F(u"matProjection", this->matProjection_);

        // TODO default value block
        matPropBlockCollection_->Clear();
        matPropBlockCollection_->Add(material->GetPropertyBlock());

        if (batch.propBlock != nullptr) {
            matPropBlockCollection_->Add(batch.propBlock);
        }

        // VB, IB
        commandList->SetVertexBuffer(vertexBuffer_.get(), sizeof(BatchVertex), (vbOffset_ + batch.VertexOffset) * sizeof(BatchVertex));
        commandList->SetIndexBuffer(indexBuffer_.get(), 4, (ibOffset_ + batch.IndexOffset) * sizeof(int32_t));

        // pipeline state
        commandList->GetLL()->SetPipelineState(material->GetPipelineState(commandList->GetCurrentRenderPass()).get());

        // constant buffer
        commandList->StoreUniforms(
                commandList.get(), material->GetShader(ShaderStageType::Vertex), LLGI::ShaderStageType::Vertex, matPropBlockCollection_);
        commandList->StoreUniforms(
                commandList.get(), material->GetShader(ShaderStageType::Pixel), LLGI::ShaderStageType::Pixel, matPropBlockCollection_);

        // texture
        commandList->GetLL()->ResetTextures();
        commandList->StoreTextures(
                commandList.get(), material->GetShader(ShaderStageType::Vertex), LLGI::ShaderStageType::Vertex, matPropBlockCollection_);
        commandList->StoreTextures(
                commandList.get(), material->GetShader(ShaderStageType::Pixel), LLGI::ShaderStageType::Pixel, matPropBlockCollection_);

        // draw
        commandList->Draw(batch.IndexCount / 3);
    }

    vbOffset_ += static_cast<int32_t>(rawVertexBuffer_.size());
    ibOffset_ += static_cast<int32_t>(rawIndexBuffer_.size());
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

void BatchRenderer::SetViewProjection(const Matrix44F& matView, const Matrix44F& matProjection) {
    matView_ = matView;
    matProjection_ = matProjection;
}

std::shared_ptr<Material> BatchRenderer::GetMaterialDefaultSprite(const AlphaBlend blend) {
    auto mat = matDefaultSprite_[blend];

    if (mat != nullptr) return mat;

    auto vs = Graphics::GetInstance()->GetBuiltinShader()->Create(BuiltinShaderType::SpriteUnlitVS);
    auto ps = Graphics::GetInstance()->GetBuiltinShader()->Create(BuiltinShaderType::SpriteUnlitPS);

    mat = MakeAsdShared<Material>();
    mat->SetShader(vs);
    mat->SetShader(ps);
    mat->SetAlphaBlend(blend);
    matDefaultSprite_[blend] = mat;

    return mat;
}

std::shared_ptr<Material> BatchRenderer::GetMaterialDefaultText(const AlphaBlend blend) {
    auto mat = matDefaultText_[blend];

    if (mat != nullptr) return mat;

    auto vs = Graphics::GetInstance()->GetBuiltinShader()->Create(BuiltinShaderType::SpriteUnlitVS);
    auto ps = Graphics::GetInstance()->GetBuiltinShader()->Create(BuiltinShaderType::FontUnlitPS);

    mat = MakeAsdShared<Material>();
    mat->SetShader(vs);
    mat->SetShader(ps);
    mat->SetAlphaBlend(blend);
    matDefaultText_[blend] = mat;

    return mat;
}

}  // namespace Altseed2