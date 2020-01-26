#pragma once

#include <GLFW/glfw3.h>

#include <array>

#include "../Window/Window.h"
#include "ButtonState.h"

namespace Altseed {

enum class Keys : int32_t {
    Unknown,
    Space,  ///< Space
    Apostrophe,  ///< : (` in US )
    Comma,  ///< ,
    Minus,  ///< -
    Period,  ///< .
    Slash,  ///< /
    Num0,  ///< 0
    Num1,  ///< 1
    Num2,  ///< 2
    Num3,  ///< 3
    Num4,  ///< 4
    Num5,  ///< 5
    Num6,  ///< 6
    Num7,  ///< 7
    Num8,  ///< 8
    Num9,  ///< 9
    Semicolon,  ///< ;
    Equal,  ///< ^ (= in US )
    A,  ///< A
    B,  ///< B
    C,  ///< C
    D,  ///< D
    E,  ///< E
    F,  ///< F
    G,  ///< G
    H,  ///< H
    I,  ///< I
    J,  ///< J
    K,  ///< K
    L,  ///< L
    M,  ///< M
    N,  ///< N
    O,  ///< O
    P,  ///< P
    Q,  ///< Q
    R,  ///< R
    S,  ///< S
    T,  ///< T
    U,  ///< U
    V,  ///< V
    W,  ///< W
    X,  ///< X
    Y,  ///< Y
    Z,  ///< Z
    LeftBracket,  ///< @ ([ in US )
    Backslash,  ///< ] (\ in US )
    RightBracket,  ///< [ (] in US )
    GraveAccent,  ///< Hankaku/Zenkaku
    World1,
    World2,
    Escape,  ///< Esc
    Enter,  ///< Enter
    Tab,  ///< Tab
    Backspace,  ///< BackSpace
    Insert,  ///< Insert
    Delete,  ///< Delete
    Right,  ///< →
    Left,  ///< ←
    Down,  ///< ↓
    Up,  ///< ↑
    PageUp,  ///< PageUp
    PageDown,  ///< PageDown
    Home,  ///< Home
    End,  ///< End
    CapsLock,  ///< CapsLock
    ScrollLock,  ///< ScrollLock
    NumLock,  ///< NumLock
    PrintScreen,  ///< PrintScreen
    Pause,  ///< Pause
    F1,  ///< F1
    F2,  ///< F2
    F3,  ///< F3
    F4,  ///< F4
    F5,  ///< F5
    F6,  ///< F6
    F7,  ///< F7
    F8,  ///< F8
    F9,  ///< F9
    F10,  ///< F10
    F11,  ///< F11
    F12,  ///< F12
    F13,  ///< F13
    F14,  ///< F14
    F15,  ///< F15
    F16,  ///< F16
    F17,  ///< F17
    F18,  ///< F18
    F19,  ///< F19
    F20,  ///< F20
    F21,  ///< F21
    F22,  ///< F22
    F23,  ///< F23
    F24,  ///< F24
    F25,  ///< F25
    Keypad0,  ///< Numpad0
    Keypad1,  ///< Numpad1
    Keypad2,  ///< Numpad2
    Keypad3,  ///< Numpad3
    Keypad4,  ///< Numpad4
    Keypad5,  ///< Numpad5
    Keypad6,  ///< Numpad6
    Keypad7,  ///< Numpad7
    Keypad8,  ///< Numpad8
    Keypad9,  ///< Numpad9
    KeypadDecimal,  ///< Numpad.
    KeypadDivide,  ///< Numpad/
    KeypadMultiply,  ///< Numpad*
    KeypadSubstract,  ///< Numpad-
    KeypadAdd,  ///< Numpad+
    KeypadEnter,  ///< NumpadEnter
    KeypadEqual,  ///< Numpad=
    LeftShift,  ///< Left-Shift
    LeftControl,  ///< Left-Ctrl
    LeftAlt,  ///< Left-Alt
    LeftWin,  ///< Left-Win
    RightShift,  ///< Right-Shift
    RightControl,  ///< Right-Ctrl
    RightAlt,  ///< Right-Alt
    RightWin,  ///< Right-Win
    Menu,  ///< Menu
    Last,
    MAX
};

class Keyboard : public BaseObject {
private:
    static std::shared_ptr<Keyboard> instance;
    std::shared_ptr<Window> window;

    //! because of msvc bug, it cannot use Keys::MAX
    static const int keyCodes[122];

    std::array<bool, static_cast<int>(Keys::MAX)> currentState;
    std::array<bool, static_cast<int>(Keys::MAX)> oldState;

public:
    static bool Initialize(std::shared_ptr<Window>& window);

    static void Terminate() {}

    static std::shared_ptr<Keyboard>& GetInstance();

    void RefleshKeyStates();

    ButtonState GetKeyState(Keys key) const;

    // Add Callback Registerer/Unregisterer?
};

}  // namespace Altseed
