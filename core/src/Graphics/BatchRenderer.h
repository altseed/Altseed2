#pragma once

#include <LLGI.Base.h>
#include <stdint.h>

#include <memory>

#include "../Graphics/Color.h"
#include "../Math/Matrix44F.h"
#include "../Math/Vector2F.h"
#include "../Math/Vector3F.h"
#include "Material.h"

#if !USE_CBG

namespace Altseed2 {

class Graphics;
class CommandList;
class TextureBase;

struct BatchVertex {
    Vector3F Pos;
    Color Col;
    Vector2F UV1;
    Vector2F UV2;
};

class BatchRenderer {
private:
    static const int32_t VertexBufferMax = 1024 * 200;
    static const int32_t IndexBufferMax = 1024 * 200 * 4;

    struct Batch {
        std::shared_ptr<TextureBase> texture;
        std::shared_ptr<Material> material;
        std::shared_ptr<MaterialPropertyBlock> propBlock;

        int32_t VertexOffset = 0;
        int32_t IndexOffset = 0;
        int32_t VertexCount = 0;
        int32_t IndexCount = 0;
    };

    std::vector<Batch> batches_;
    std::vector<BatchVertex> rawVertexBuffer_;
    std::vector<int32_t> rawIndexBuffer_;
    std::shared_ptr<LLGI::Buffer> vertexBuffer_;
    std::shared_ptr<LLGI::Buffer> indexBuffer_;
    int32_t vbOffset_ = 0;
    int32_t ibOffset_ = 0;

    std::unordered_map<AlphaBlend, std::shared_ptr<Material>, AlphaBlend::Hash> matDefaultSprite_;
    std::unordered_map<AlphaBlend, std::shared_ptr<Material>, AlphaBlend::Hash> matDefaultText_;

    std::shared_ptr<MaterialPropertyBlockCollection> matPropBlockCollection_;
    Matrix44F matView_;
    Matrix44F matProjection_;

public:
    BatchRenderer(std::shared_ptr<Graphics> graphics);
    void Draw(
            const BatchVertex* vb,
            const int32_t* ib,
            int32_t vbCount,
            int32_t ibCount,
            const std::shared_ptr<TextureBase>& texture,
            const std::shared_ptr<Material>& material,
            const std::shared_ptr<MaterialPropertyBlock>& propBlock);

    void UploadBuffer();
    void Render();
    void ResetCache();

    void SetViewProjectionWithWindowsSize(const Vector2I& windowSize);

    void SetViewProjection(const Matrix44F& matView, const Matrix44F& matProjection);

    std::shared_ptr<Material> GetMaterialDefaultSprite(const AlphaBlend blend);
    std::shared_ptr<Material> GetMaterialDefaultText(const AlphaBlend blend);
};

}  // namespace Altseed2

#endif