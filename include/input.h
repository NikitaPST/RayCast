#ifndef _INPUT_H
#define _INPUT_H

#include <SDL2/SDL.h>
#include <array>

class Input
{
public:
  Input();
  ~Input();

  void Reset();
  void KeyDown(SDL_Keysym key);
  void KeyUp(SDL_Keysym key);

  std::array<bool, 512> GetKeysPressed();
private:
  std::array<bool, 512> m_aKeysDown;
  std::array<bool, 512> m_aKeysPressed;
};

#endif
