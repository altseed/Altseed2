#pragma once

#include <stdint.h>
#include <memory>

#include "../../Common/Array.h"
#include "../BatchRenderer.h"
#include "Rendered.h"
#include "../RenderTexture.h"

namespace Altseed {

class Texture2D;
class RenderedSprite;
class RenderedText;
class RenderedPolygon;
class RenderedCamera;
class CommandList;
class Window;

class Renderer : public BaseObject {
private:
    struct RenderTextureCacheKey {
        private:
            Vector2I value_;
        public:
            RenderTextureCacheKey(Vector2I value) { value_ = value; }
            bool operator<(const RenderTextureCacheKey& other) const { return value_.X < other.value_.X && value_.Y < other.value_.Y; }
    };

    struct RenderTextureCache {
        int32_t Life = 0;
        std::shared_ptr<RenderTexture> Stored;
    };

    static std::shared_ptr<Renderer> instance_;
    std::shared_ptr<Window> window_;
    std::shared_ptr<Graphics> graphics_;
    std::shared_ptr<BatchRenderer> batchRenderer_;
    std::shared_ptr<CullingSystem> cullingSystem_;
    std::vector<std::shared_ptr<RenderedCamera>> cameras_;

    std::map<RenderTextureCacheKey, RenderTextureCache> renderTextureCaches_;

public:
    Renderer(std::shared_ptr<Window> window, std::shared_ptr<Graphics> graphics, std::shared_ptr<CullingSystem> cullingSystem);
    virtual ~Renderer();

    static std::shared_ptr<Renderer>& GetInstance();

    static bool Initialize(
            std::shared_ptr<Window> window, std::shared_ptr<Graphics> graphics, std::shared_ptr<CullingSystem> cullingSystem);

    static void Terminate();

    void DoEvent();

    void DrawPolygon(const BatchVertex* vb, const int32_t* ib, int32_t vbCount, int32_t ibCount, const std::shared_ptr<Texture2D>& texture);

    void DrawPolygon(const BatchVertex* vb, const int32_t* ib, int32_t vbCount, int32_t ibCount, const std::shared_ptr<Material>& material);

    void DrawPolygon(
            std::shared_ptr<VertexArray> vb,
            std::shared_ptr<Int32Array> ib,
            const std::shared_ptr<Texture2D>& texture = nullptr,
            const std::shared_ptr<Material>& material = nullptr);

    void DrawPolygon(std::shared_ptr<RenderedPolygon> text);

    void DrawSprite(std::shared_ptr<RenderedSprite> sprite);

#ifdef _WIN32
#undef DrawText
#endif
    void DrawText(std::shared_ptr<RenderedText> text);

    void RenderPostEffect(std::shared_ptr<Material> material);

    void Render();

    void SetCamera(std::shared_ptr<RenderedCamera> camera);

    void ResetCamera();
};

}  // namespace Altseed