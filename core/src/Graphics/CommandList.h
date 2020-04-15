
#pragma once

#include <LLGI.Graphics.h>
#include <Utils/LLGI.CommandListPool.h>

#include <map>

#include "../BaseObject.h"
#include "../Graphics/BatchRenderer.h"
#include "../Graphics/Color.h"
#include "../Math/RectI.h"
#include "../Math/Vector2F.h"
#include "../Math/Vector3F.h"

namespace Altseed {

class Graphics;
class RenderTexture;

enum class RenderTargetCareType : int32_t {
    DontCare,
    Clear,
};

struct RenderPassParameter_C;

struct RenderPassParameter {
    Color ClearColor = Color(0, 0, 0, 0);
    RenderTargetCareType ColorCare = RenderTargetCareType::Clear;
    RenderTargetCareType DepthCare = RenderTargetCareType::Clear;

    operator RenderPassParameter_C() const;
};

struct RenderPassParameter_C {
    Color_C ClearColor;
    RenderTargetCareType ColorCare;
    RenderTargetCareType DepthCare;

    operator RenderPassParameter() const;
};

class CommandList : public BaseObject {
private:
    struct RenderPassCache {
        int32_t Life = 0;
        std::shared_ptr<LLGI::RenderPass> Stored;
    };

    std::map<std::shared_ptr<RenderTexture>, RenderPassCache> renderPassCaches_;

    LLGI::CommandList* currentCommandList_ = nullptr;
    std::shared_ptr<LLGI::SingleFrameMemoryPool> memoryPool_;
    std::shared_ptr<LLGI::CommandListPool> commandListPool_;
    std::shared_ptr<RenderTexture> currentRenderTarget_;
    std::shared_ptr<LLGI::RenderPass> currentRenderPass_;
    bool isInRenderPass_ = false;

    std::shared_ptr<RenderTexture> internalScreen_;

    std::shared_ptr<LLGI::VertexBuffer> blitVB_;
    std::shared_ptr<LLGI::IndexBuffer> blitIB_;
    std::shared_ptr<Material> copyMaterial_;

    std::shared_ptr<LLGI::Texture> proxyTexture_;
    std::shared_ptr<MaterialPropertyBlockCollection> matPropBlockCollection_;

    bool isRequiredNotToPresent_ = false;

public:
    static std::shared_ptr<CommandList> Create();

    std::shared_ptr<RenderTexture> GetScreenTexture() const;

    void StartFrame();

    void EndFrame();

    void SetScissor(const RectI& scissor);

    void BeginRenderPass(std::shared_ptr<RenderTexture> target, std::shared_ptr<LLGI::RenderPass> renderPass);

    void EndRenderPass();

    void PauseRenderPass();

    void ResumeRenderPass();

    void SetRenderTarget(std::shared_ptr<RenderTexture> target, const RenderPassParameter& renderPassParameter);

    /**
        @brief	apply material and render to target texture.
        @note
        src is stored as mainTex
    */
    void RenderToRenderTarget(std::shared_ptr<Material> material);

    /**
      @brief  (internal function) Set render target with a real screen
  */
    void SetRenderTargetWithScreen();

    /**
        @brief  (internal function) Present a screen texture into a screen
    */
    void PresentInternal();

    /**
        @brief  (internal function) required not to present in this frame
    */
    void RequireNotToPresent();

    void StoreUniforms(
            CommandList* commandList,
            std::shared_ptr<Shader> shader,
            LLGI::ShaderStageType shaderStage,
            std::shared_ptr<MaterialPropertyBlockCollection> matPropBlockCollection);
    void StoreTextures(
            CommandList* commandList,
            std::shared_ptr<Shader> shader,
            LLGI::ShaderStageType shaderStage,
            std::shared_ptr<MaterialPropertyBlockCollection> matPropBlockCollection);

    /**
        @brief Call CopyTexture outside of RenderPass
    */
    void CopyTexture(std::shared_ptr<RenderTexture> src, std::shared_ptr<RenderTexture> dst);

    std::shared_ptr<RenderTexture> GetCurrentRenderTarget() const;

    LLGI::SingleFrameMemoryPool* GetMemoryPool() const;
    LLGI::RenderPass* GetCurrentRenderPass() const;
    LLGI::CommandList* GetLL() const;
};

}  // namespace Altseed