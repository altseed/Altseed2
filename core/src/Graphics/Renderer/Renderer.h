#pragma once

#include <stdint.h>

#include <memory>

#include "../../Common/Array.h"
#include "../BatchRenderer.h"
#include "Rendered.h"

#ifdef _WIN32
#undef DrawText
#endif

namespace Altseed2 {

class Texture2D;
class RenderedSprite;
class RenderedText;
class RenderedPolygon;
class RenderedCamera;
class CommandList;
class Window;

class Renderer : public BaseObject {
private:
    static std::shared_ptr<Renderer> instance_;
    std::shared_ptr<Window> window_;
    std::shared_ptr<Graphics> graphics_;
    std::shared_ptr<BatchRenderer> batchRenderer_;
    std::shared_ptr<CullingSystem> cullingSystem_;
    std::vector<std::shared_ptr<RenderedCamera>> cameras_;
    std::shared_ptr<RenderedCamera> currentCamera_;

public:
    Renderer(std::shared_ptr<Window> window, std::shared_ptr<Graphics> graphics, std::shared_ptr<CullingSystem> cullingSystem);
    virtual ~Renderer();

    static std::shared_ptr<Renderer>& GetInstance();

    static bool Initialize(
            std::shared_ptr<Window> window, std::shared_ptr<Graphics> graphics, std::shared_ptr<CullingSystem> cullingSystem);
    static void Terminate();

    void DrawPolygon(std::shared_ptr<RenderedPolygon> text);
    void DrawSprite(std::shared_ptr<RenderedSprite> sprite);
    void DrawText(std::shared_ptr<RenderedText> text);

    void Render();

    void SetCamera(std::shared_ptr<RenderedCamera> camera);
    void ResetCamera();

    void OnTerminating() override;
};

}  // namespace Altseed2