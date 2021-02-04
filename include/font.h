#ifndef _FONT_H
#define _FONT_H

#include "surface.h"
#include "color.h"

#include <SDL2/SDL_ttf.h>

class Font
{
public:
  Font(const char* sFontName, int nSize, Color color);
  ~Font();

  Surface* Render(const char* sText);
private:
  TTF_Font* m_pFont;
  Color m_color;
};

#endif
