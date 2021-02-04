#include "font.h"

Font::Font(const char* sFontName, int nSize, Color color)
{
  m_pFont = TTF_OpenFont(sFontName, nSize);
  m_color = color;
}

Font::~Font()
{
  TTF_CloseFont(m_pFont); m_pFont = NULL;
}

Surface* Font::Render(const char* sText)
{
  return new Surface(TTF_RenderText_Solid(m_pFont, sText, m_color.GetColor()));
}
