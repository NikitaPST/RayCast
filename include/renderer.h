#ifndef _RENDERER_H
#define _RENDERER_H

#include <SDL2/SDL.h>

#include "surface.h"

class Renderer
{
public:
  Renderer();
  ~Renderer();

  bool Init();
  bool CreateWindow(const int nWidth, const int nHeight);
  bool Run();
  void Render();
  void Shutdown();

  Surface* GetScreenSurface();
private:
  bool m_bDisposed;

  SDL_Window* m_pWindow;
  Surface* m_pScreenSurface;
};

#endif
