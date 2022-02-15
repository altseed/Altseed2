
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
#include "ComputePipelineState.h"

namespace Altseed2 {

class Graphics;
class RenderTexture;

enum class RenderTargetCareType : int32_t {
    DontCare,
    Clear,
};

struct RenderPassParameter_C;

struct RenderPassParameter {
    Color ClearColor = Color(0, 0, 0, 0);
    bool IsColorCleared = true;
    bool IsDepthCleared = true;

    operator RenderPassParameter_C() const;
};

struct RenderPassParameter_C {
    Color_C ClearColor;
    bool IsColorCleared;
    bool IsDepthCleared;

    operator RenderPassParameter() const;
};

class CommandList : public BaseObject {
private:
    struct RenderPass {
        std::shared_ptr<RenderTexture> RenderTarget;
        std::shared_ptr<LLGI::RenderPass> Stored;
    };

    struct RenderPassCache {
        int32_t Life = 0;
        std::shared_ptr<RenderPass> Stored;
    };

    std::map<std::shared_ptr<RenderTexture>, RenderPassCache> renderPassCaches_;

    LLGI::CommandList* currentCommandList_ = nullptr;
    std::shared_ptr<LLGI::SingleFrameMemoryPool> memoryPool_;
    std::shared_ptr<LLGI::CommandListPool> commandListPool_;
    std::shared_ptr<RenderPass> currentRenderPass_;
    LLGI::RenderPass* currentRenderPassLL_ = nullptr;

    bool isInRenderPass_ = false;
    bool isInFrame_ = false;

    std::shared_ptr<RenderTexture> internalScreen_;
    TextureFormatType screenTextureFormat_;

    std::shared_ptr<LLGI::Buffer> blitVB_;
    std::shared_ptr<LLGI::Buffer> blitIB_;
    std::shared_ptr<Material> copyMaterial_;

    std::shared_ptr<LLGI::Texture> proxyTexture_;
    std::shared_ptr<MaterialPropertyBlockCollection> matPropBlockCollection_;

    Vector3I numThreads_;

    bool isPresentScreenBufferDirectly_ = true;

    std::shared_ptr<RenderPass> CreateRenderPass(std::shared_ptr<RenderTexture> target);

public:
    static std::shared_ptr<CommandList> Create();

    std::shared_ptr<RenderTexture> GetScreenTexture() const;

    void Begin();

    void End();

#if !USE_CBG
    void StartFrame(const RenderPassParameter& renderPassParameter);

    void EndFrame();
#endif

    void SetScissor(const RectI& scissor);

#if !USE_CBG
    void BeginRenderPass(std::shared_ptr<RenderPass> renderPass);
#endif

    void EndRenderPass();

    void PauseRenderPass();

    void ResumeRenderPass();

    void UploadBuffer(std::shared_ptr<Buffer> buffer);

    void ReadbackBuffer(std::shared_ptr<Buffer> buffer);

    void CopyBuffer(std::shared_ptr<Buffer> src, std::shared_ptr<Buffer> dst);

    void SetRenderTarget(std::shared_ptr<RenderTexture> target, const RenderPassParameter& renderPassParameter);

    void RenderToRenderTexture(
            std::shared_ptr<Material> material, std::shared_ptr<RenderTexture> target, const RenderPassParameter& renderPassParameter);

    TextureFormatType GetScreenTextureFormat() const { return screenTextureFormat_; }
    void SetScreenTextureFormat(const TextureFormatType format) { screenTextureFormat_ = format; }

    /**
        @brief	apply material and render to target texture.
        @note
        src is stored as mainTex
    */
    void RenderToRenderTarget(std::shared_ptr<Material> material);

#if !USE_CBG

    /**
      @brief  (internal function) Set render target with a real screen
  */
    void SetRenderTargetWithScreen(const RenderPassParameter& renderPassParameter);

    /**
        @brief  (internal function) Present a screen texture into a screen
    */
    void PresentInternal();

    /**
        @brief  (internal function)
    */
    bool GetIsPresentScreenBufferDirectly() const;

    /**
        @brief  (internal function)
    */
    void SetIsPresentScreenBufferDirectly(bool value);

    void SetVertexBuffer(LLGI::Buffer* vb, int32_t stride, int32_t offset);

    void SetIndexBuffer(LLGI::Buffer* ib, int32_t stride, int32_t offset);

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
#endif

    void Draw(int32_t instanceCount);

    void SetVertexBuffer(std::shared_ptr<Buffer> vb, int32_t stride, int32_t offset);
    void SetIndexBuffer(std::shared_ptr<Buffer> ib, int32_t stride, int32_t offset);
    void SetMaterial(std::shared_ptr<Material> material);

    void BeginComputePass();
    void EndComputePass();

    void SetComputeBuffer(std::shared_ptr<Buffer> buffer, int32_t stride, int32_t unit, ShaderStageType shaderStage = ShaderStageType::Compute);
    void SetComputePipelineState(std::shared_ptr<ComputePipelineState> computePipelineState);
    void Dispatch(int32_t x, int32_t y, int32_t z);

    void CopyTexture(std::shared_ptr<RenderTexture> src, std::shared_ptr<RenderTexture> dst);

    void ResetTextures();
    void ResetComputeBuffers();

#if !USE_CBG

    LLGI::SingleFrameMemoryPool* GetMemoryPool() const;
    LLGI::RenderPass* GetCurrentRenderPass() const;

    LLGI::RenderPass* GetScreenRenderPass();

    LLGI::RenderPass* GetActualScreenRenderPass() const;

    LLGI::CommandList* GetLL() const;
#endif

    void SaveRenderTexture(const char16_t* path, std::shared_ptr<RenderTexture> texture);
};

}  // namespace Altseed2