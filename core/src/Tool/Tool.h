#pragma once

#include "../Graphics/Graphics.h"

class ImguiPlatform;

namespace Altseed {

class Graphics;

class Tool : public BaseObject {
private:
    static std::shared_ptr<Tool> instance_;
    std::shared_ptr<ImguiPlatform> platform_;

public:
    static std::shared_ptr<Tool>& GetInstance();

    static bool Initialize(std::shared_ptr<Graphics> graphics);

    static void Terminate();

    Tool(std::shared_ptr<Graphics> graphics);

    virtual ~Tool();

    void NewFrame();

    void Render();

    bool Begin(const char16_t* name);

    void Text(const char16_t* text);

    void End();
};

}  // namespace Altseed