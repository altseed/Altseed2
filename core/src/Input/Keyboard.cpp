#include "Keyboard.h"

namespace altseed {

Keyboard::Keyboard() {}

Keyboard::~Keyboard() {}

bool Keyboard::Intialize(Window* window) { return false; }

void Keyboard::RefleshKeyStates() {}

ButtonState Keyboard::GetKeyState(Keys key) const { return ButtonState::Free; }

};  // namespace altseed