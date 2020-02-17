#pragma once

#include <stdint.h>
#include <memory>

#include "../BatchRenderer.h"
#include "Rendered.h"

namespace Altseed {

class Texture2D;
class RenderedSprite;
class RenderedCamera;
class CommandList;
class RenderedSprite;
class RenderedCamera;
class Window;

class Renderer : public BaseObject {
private:
    static std::shared_ptr<Renderer> instance_;
    std::shared_ptr<Window> window_;
    std::shared_ptr<Graphics> graphics_;
    std::shared_ptr<BatchRenderer> renderedBatchRenderer_;
    std::shared_ptr<BatchRenderer> batchRenderer_;
    std::vector<std::shared_ptr<RenderedCamera>> cameras_;

public:
    Renderer(std::shared_ptr<Window> window, std::shared_ptr<Graphics> graphics);
    virtual ~Renderer();

    static std::shared_ptr<Renderer>& GetInstance();

    static bool Initialize(std::shared_ptr<Window> window, std::shared_ptr<Graphics> graphics);

    static void Terminate();

    void DrawPolygon(const BatchVertex* vb, const int32_t* ib, int32_t vbCount, int32_t ibCount, const std::shared_ptr<Texture2D>& texture);

    void DrawPolygon(const BatchVertex* vb, const int32_t* ib, int32_t vbCount, int32_t ibCount, const std::shared_ptr<Material>& material);

    void DrawSprite(std::shared_ptr<RenderedSprite> sprite);

    void Render(std::shared_ptr<CommandList> commandList);
    
	std::shared_ptr<RenderedCamera> CreateCamera();
};

}  // namespace Altseed