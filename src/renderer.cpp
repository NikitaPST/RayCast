#include "renderer.h"

Renderer::Renderer()
{
  m_bDisposed = false;

  m_pWindow = NULL;
  m_pScreenSurface = NULL;
}

Renderer::~Renderer()
{
  if (!m_bDisposed)
  {
    Shutdown();
  }

  if (m_pScreenSurface)
    delete m_pScreenSurface; m_pScreenSurface = NULL;
}

bool Renderer::Init()
{
  return (SDL_Init(SDL_INIT_VIDEO) == 0);
}

bool Renderer::CreateWindow(const int nWidth, const int nHeight)
{
  m_pWindow = SDL_CreateWindow("RayCast", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, nWidth, nHeight, SDL_WINDOW_SHOWN);
  if (m_pWindow)
  {
    m_pScreenSurface = new Surface(SDL_GetWindowSurface(m_pWindow), true);
    return true;
  }
  return false;
}

void Renderer::Shutdown()
{
  if (m_bDisposed)
    return;

  if (m_pWindow)
  {
    SDL_DestroyWindow(m_pWindow);
    m_pWindow = NULL;
  }

  SDL_Quit();

  m_bDisposed = true;
}

bool Renderer::Run()
{
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0)
  {
    if (e.type == SDL_QUIT)
    {
      return false;
    }
  }
  return true;
}

void Renderer::Render()
{
  SDL_UpdateWindowSurface(m_pWindow);
}

Surface* Renderer::GetScreenSurface()
{
  return m_pScreenSurface;
}
