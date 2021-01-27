#ifndef _SURFACE_H
#define _SURFACE_H

#include <SDL2/SDL.h>

class Surface
{
public:
  Surface(SDL_Surface* pSurface, bool bNonDisposable = false);
  ~Surface();

  void Shutdown();
  void Fill(Uint8 r, Uint8 g, Uint8 b);

  SDL_Surface* GetInnerSurface();
  Uint8 GetBytesPerPixel();
private:
  bool m_bDisposed;
  bool m_bNonDisposable;
  SDL_Surface* m_pSurface;
};

#endif
