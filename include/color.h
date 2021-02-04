#ifndef _COLOR_H
#define _COLOR_H

#include <SDL2/SDL.h>

class Color
{
public:
  Color();
  Color(Uint8 r, Uint8 g, Uint8 b);
  ~Color();

  SDL_Color GetColor();

  static Color ColorFromRGB(Uint8 r, Uint8 g, Uint8 b);
private:
  SDL_Color m_color;
};

#endif
