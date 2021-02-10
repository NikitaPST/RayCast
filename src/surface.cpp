#include "surface.h"

Surface::Surface(SDL_Surface* pSurface, bool bNonDisposable)
{
  m_pSurface = pSurface;
  m_bNonDisposable = bNonDisposable;

  m_bDisposed = false;
}

Surface::Surface(int nWidth, int nHeight, bool bNonDisposable)
{
  Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  m_pSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, nWidth, nHeight, 32, rmask,
    gmask, bmask, amask);
  m_bNonDisposable = bNonDisposable;
  m_bDisposed = false;
}

Surface::~Surface()
{
  if (!m_bDisposed)
  {
    Shutdown();
  }
}

void Surface::Shutdown()
{
  if (m_bDisposed)
    return;

  if (!m_bNonDisposable)
  {
    SDL_FreeSurface(m_pSurface);
    m_pSurface = NULL;
  }

  m_bDisposed = true;
}

void Surface::Fill(Uint8 r, Uint8 g, Uint8 b)
{
  SDL_FillRect(m_pSurface, NULL, SDL_MapRGB(m_pSurface->format, r, g, b));
}

void Surface::Blit(Surface* pSrc, int x, int y)
{
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = pSrc->GetWidth();
  rect.h = pSrc->GetHeight();

  SDL_BlitSurface(pSrc->GetInnerSurface(), NULL, m_pSurface, &rect);
}

Uint8 Surface::GetBytesPerPixel()
{
  return m_pSurface->format->BytesPerPixel;
}

SDL_Surface* Surface::GetInnerSurface()
{
  return m_pSurface;
}

int Surface::GetWidth()
{
  return m_pSurface->w;
}

int Surface::GetHeight()
{
  return m_pSurface->h;
}
