#include "CommandList.h"
#include "../Graphics/Graphics.h"
#include "RenderTexture.h"

namespace Altseed {

std::shared_ptr<CommandList> CommandList::Create() {
    auto g = Graphics::GetInstance()->GetGraphicsLLGI();
    auto memoryPool = LLGI::CreateSharedPtr(g->CreateSingleFrameMemoryPool(1024 * 1024 * 16, 128));  // TODO : fix DX12 bug
    auto commandListPool = std::make_shared<LLGI::CommandListPool>(g, memoryPool.get(), 3);
    auto ret = CreateSharedPtr(new CommandList());

    ret->memoryPool_ = memoryPool;
    ret->commandListPool_ = commandListPool;
    ret->batchRenderer_ = std::make_shared<BatchRenderer>(Graphics::GetInstance());

    return ret;
}

void CommandList::StartFrame() {
    memoryPool_->NewFrame();
    currentCommandList_ = commandListPool_->Get();
    currentCommandList_->Begin();

    for (auto& c : renderPassCaches_) {
        c.second.Life--;
    }

    for (auto it = renderPassCaches_.begin(); it != renderPassCaches_.end();) {
        if (it->second.Life == 0) {
            it = renderPassCaches_.erase(it);
        } else {
            it++;
        }
    }
}

void CommandList::EndFrame() {
    if (isInRenderPass_) {
        Flush();
        currentCommandList_->EndRenderPass();
        isInRenderPass_ = false;
        currentRenderPass_ = nullptr;
    }
    currentCommandList_->End();
}

void CommandList::SetScissor(const RectI& scissor) { currentCommandList_->SetScissor(scissor.X, scissor.Y, scissor.Width, scissor.Height); }

void CommandList::SetDefaultRenderTarget() {
    auto g = Graphics::GetInstance()->GetGraphicsLLGI();

    if (isInRenderPass_) {
        Flush();
        currentCommandList_->EndRenderPass();
    }

    auto r = LLGI::CreateSharedPtr(Graphics::GetInstance()->GetCurrentScreen(LLGI::Color8(255, 0, 0, 255), true, true));
    r->AddRef();

    currentCommandList_->BeginRenderPass(r.get());
    currentRenderPass_ = r;
    isInRenderPass_ = true;
}

void CommandList::SetRenderTarget(std::shared_ptr<RenderTexture> target, const RectI& viewport) {
    auto it = renderPassCaches_.find(target);

    if (it == renderPassCaches_.end()) {
        auto g = Graphics::GetInstance()->GetGraphicsLLGI();

        LLGI::Texture* texture = target->GetNativeTexture().get();
        auto renderPass = LLGI::CreateSharedPtr(g->CreateRenderPass((const LLGI::Texture**)&texture, 1, nullptr));
        RenderPassCache cache;
        cache.Life = 5;
        cache.Stored = renderPass;
        renderPassCaches_[target] = cache;
    } else {
        // extend life to avoid to remove
        it->second.Life = 5;
    }

    if (isInRenderPass_) {
        Flush();
        currentCommandList_->EndRenderPass();
    }

    currentCommandList_->BeginRenderPass(renderPassCaches_[target].Stored.get());
    currentRenderPass_ = renderPassCaches_[target].Stored;
    isInRenderPass_ = true;
}

void CommandList::Draw(
        const BatchVertex* vb, const int32_t* ib, int32_t vbCount, int32_t ibCount, const std::shared_ptr<Texture2D>& texture) {
    isBatchRenderDirtied_ = true;
    batchRenderer_->Draw(vb, ib, vbCount, ibCount, texture);
}

void CommandList::Flush() {
    if (isBatchRenderDirtied_) {
        batchRenderer_->Render(this);
        batchRenderer_->ResetCache();
    }
}

void CommandList::SetViewProjectionWithWindowsSize(const Vector2DI& windowSize) {
    batchRenderer_->SetViewProjectionWithWindowsSize(windowSize);
}

LLGI::SingleFrameMemoryPool* CommandList::GetMemoryPool() const { return memoryPool_.get(); }

LLGI::RenderPass* CommandList::GetCurrentRenderPass() const { return currentRenderPass_.get(); }

LLGI::CommandList* CommandList::GetLL() const { return currentCommandList_; }

}  // namespace Altseed