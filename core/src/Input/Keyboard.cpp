#include "Keyboard.h"

namespace altseed {

std::shared_ptr<Keyboard> Keyboard::instance = nullptr;

bool Keyboard::Intialize(Window* window) { return false; }

void Keyboard::Terminate() {}

std::shared_ptr<Keyboard>& Keyboard::GetInstance() { return instance; }

void Keyboard::RefleshKeyStates() {}

ButtonState Keyboard::GetKeyState(Keys key) const { return ButtonState::Free; }

};  // namespace altseed