#include "color.h"

Color::Color()
{
}

Color::Color(Uint8 r, Uint8 g, Uint8 b)
{
  m_color.r = r;
  m_color.g = g;
  m_color.b = b;
}

Color::~Color()
{
}

SDL_Color Color::GetColor()
{
  return m_color;
}

Color Color::ColorFromRGB(Uint8 r, Uint8 g, Uint8 b)
{
  return Color(r, g, b);
}
