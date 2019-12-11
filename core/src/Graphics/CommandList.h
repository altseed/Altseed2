
#pragma once

#include <LLGI.Graphics.h>
#include <Utils/LLGI.CommandListPool.h>
#include <map>
#include "../BaseObject.h"
#include "../Graphics/BatchRenderer.h"
#include "../Graphics/Color.h"
#include "../Math/RectI.h"
#include "../Math/Vector2DF.h"
#include "../Math/Vector3DF.h"

namespace altseed {

class Graphics;
class RenderTexture;

class CommandList : public BaseObject {
private:
    struct RenderPassCache {
        int32_t Life;
        std::shared_ptr<LLGI::RenderPass> Stored;
    };

    std::map<std::shared_ptr<RenderTexture>, RenderPassCache> renderPassCaches_;

    LLGI::CommandList* currentCommandList_ = nullptr;
    std::shared_ptr<LLGI::SingleFrameMemoryPool> memoryPool_;
    std::shared_ptr<LLGI::CommandListPool> commandListPool_;
    std::shared_ptr<BatchRenderer> batchRenderer_;
    std::shared_ptr<LLGI::RenderPass> currentRenderPass_;
    bool isBatchRenderDirtied_ = false;
    bool isInRenderPass_ = false;

public:
    static std::shared_ptr<CommandList> Create();

    void StartFrame();

	void EndFrame();

    void SetScissor(const RectI& scissor);

    void SetRenderTarget(std::shared_ptr<RenderTexture> target, const RectI& viewport);

    void Draw(const BatchVertex* vb, const int32_t* ib, int32_t vbCount, int32_t ibCount, const std::shared_ptr<Texture2D>& texture);

    void Flush();

	LLGI::SingleFrameMemoryPool* GetMemoryPool() const;
	LLGI::RenderPass* GetCurrentRenderPass() const;
    LLGI::CommandList* GetLL() const;
};

}  // namespace altseed