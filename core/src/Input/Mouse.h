#pragma once
#include <GLFW/glfw3.h>

#include <array>
#include <functional>

#include "../IO/StaticFile.h"
#include "../Math/Vector2F.h"
#include "../Window/Window.h"
#include "ButtonState.h"
#include "Cursor.h"

namespace Altseed2 {
enum class MouseButton : int32_t {
    /**
     @brief 左ボタン
     */
    ButtonLeft = 0,

    /**
     @brief 右ボタン
     */
    ButtonRight = 1,

    /**
     @brief 中央ボタン
     */
    ButtonMiddle = 2,

    /**
     @brief サブボタン1
     */
    SubButton1 = 3,

    /**
     @brief サブボタン2
     */
    SubButton2 = 4,

    /**
     @brief サブボタン3
     */
    SubButton3 = 5,

    /**
     @brief サブボタン4
     */
    SubButton4 = 6,

    /**
     @brief サブボタン5
     */
    SubButton5 = 7,
};

enum class CursorMode : int32_t {
    //カーソルを常に表示。
    Normal = 0x00034001,
    //ウィンドウ上のカーソルを非表示。
    Hidden = 0x00034002,
    //カーソルを常に非表示
    Disable = 0x00034003,
};

class Mouse : public BaseObject {
private:
    static std::shared_ptr<Mouse> instance_;
    std::shared_ptr<Window> window_;

    static const int KEY_NUM = 8;
    static const int ModeCodes[3];

    std::array<bool, KEY_NUM> currentState_;
    std::array<bool, KEY_NUM> oldState_;

    float wheel_ = 0;

public:
#if !USE_CBG
    static bool Initialize(std::shared_ptr<Window>& window);

    static void Terminate() { instance_ = nullptr; }
#endif

    static std::shared_ptr<Mouse>& GetInstance();

    void RefreshInputState();

    void SetPosition(Vector2F vec);

    Vector2F GetPosition();

#if !USE_CBG

    void SetWheelCallback(std::function<void(double x, double y)> func);

#endif

    float GetWheel() const;

    ButtonState GetMouseButtonState(MouseButton button) const;

    void SetCursorMode(CursorMode mode);

    void SetCursorImage(std::shared_ptr<Cursor> cursor);

    CursorMode GetCursorMode() const;
};

}  // namespace Altseed2
