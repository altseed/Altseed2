#pragma once
#include <GLFW/glfw3.h>
#include <libpng16/png.h>
#include <stb_image.h>

#include <array>
#include <functional>

#include "../IO/StaticFile.h"
#include "../Math/Vector2I.h"
#include "../Window/Window.h"
#include "ButtonState.h"

namespace Altseed2 {
class Cursor : public BaseObject {
private:
    //    std::shared_ptr<GLFWcursor>
    GLFWcursor* native_;

    static bool LoadPNGImage(
            void* data,
            int32_t size,
            bool rev,
            int32_t& imagewidth,
            int32_t& imageheight,
            ::std::vector<uint8_t>& imagedst,
            const char16_t* path);

public:
    Cursor(GLFWcursor* cursor);

    ~Cursor();

    GLFWcursor* GetNative() const { return native_; };

    static std::shared_ptr<Cursor> Create(const char16_t* path, Vector2I hot);
};

}  // namespace Altseed2
