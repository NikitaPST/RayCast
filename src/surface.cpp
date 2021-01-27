#include "surface.h"

Surface::Surface(SDL_Surface* pSurface, bool bNonDisposable)
{
  m_pSurface = pSurface;
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

Uint8 Surface::GetBytesPerPixel()
{
  return m_pSurface->format->BytesPerPixel;
}

SDL_Surface* Surface::GetInnerSurface()
{
  return m_pSurface;
}
