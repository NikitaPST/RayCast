#ifndef _RENDERER_H
#define _RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "surface.h"
#include "input.h"

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
  Input* GetInput();
private:
  bool m_bDisposed;

  Input* m_pInput;

  SDL_Window* m_pWindow;
  Surface* m_pScreenSurface;
};

#endif
