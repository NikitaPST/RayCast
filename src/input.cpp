#include "input.h"

#include <algorithm>

Input::Input()
{
}

Input::~Input()
{
}

void Input::Reset()
{
  m_aKeysDown.fill(false);
}

void Input::KeyDown(SDL_Keysym key)
{
  m_aKeysDown[key.scancode] = true;
  m_aKeysPressed[key.scancode] = true;
}

void Input::KeyUp(SDL_Keysym key)
{
  m_aKeysPressed[key.scancode] = false;
}

std::array<bool, 512> Input::GetKeysPressed()
{
  return m_aKeysPressed;
}
