#pragma once

#include <LLGI.Base.h>
#include <stdint.h>
#include <memory>
#include "../Graphics/Color.h"
#include "../Math/Matrix44F.h"
#include "../Math/Vector2F.h"
#include "../Math/Vector3F.h"

namespace Altseed {

class Graphics;
class CommandList;
class Material;
class Texture2D;
class MaterialPropertyBlock;
class MaterialPropertyBlockCollection;
class Shader;

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
        std::shared_ptr<Texture2D> texture;
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
    std::shared_ptr<LLGI::VertexBuffer> vertexBuffer_;
    std::shared_ptr<LLGI::IndexBuffer> indexBuffer_;
    int32_t vbOffset_ = 0;
    int32_t ibOffset_ = 0;

    std::shared_ptr<Material> matDefaultSprite_;
    std::shared_ptr<Material> matDefaultText_;

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
            const std::shared_ptr<Texture2D>& texture,
            const std::shared_ptr<Material>& material,
            const std::shared_ptr<MaterialPropertyBlock>& propBlock);

    void Render(CommandList* commandList);
    void ResetCache();

    void SetViewProjectionWithWindowsSize(const Vector2I& windowSize);

    void SetViewProjection(const Matrix44F& matView, const Matrix44F& matProjection);

    std::shared_ptr<Material> GetMaterialDefaultSprite() const { return matDefaultSprite_; }
    std::shared_ptr<Material> GetMaterialDefaultText() const { return matDefaultText_; }
};

}  // namespace Altseed