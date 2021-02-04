#include "visualizer.h"
#include "settings.h"
#include "draw.h"
#include "ray_casting.h"
#include "color.h"

Visualizer::Visualizer(Surface* pSurface)
{
  m_pSurface = pSurface;
  m_pFont =
    new Font("/usr/share/fonts/liberation-sans/LiberationSans-Bold.ttf",
    36, Color::ColorFromRGB(255, 0, 0));
}

Visualizer::~Visualizer()
{
  delete m_pFont; m_pFont = NULL;
}

void Visualizer::RenderBackground()
{
  DrawFillRect(m_pSurface, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2,
    0xFF00BBFF);
  DrawFillRect(m_pSurface, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH,
    SCREEN_HEIGHT, 0xFF282828);
}

void Visualizer::RenderWorld(Map* pMap, int nPlayerX, int nPlayerY,
  float fPlayerAngle)
{
  RayCasting(m_pSurface, pMap, nPlayerX, nPlayerY, fPlayerAngle);
}

void Visualizer::RenderFps(Clock* pClock)
{
  char sFps[10];
  snprintf(sFps, 10, "%d", (int)pClock->GetFps());
  Surface* pFpsSurf = m_pFont->Render(sFps);
  m_pSurface->Blit(pFpsSurf, SCREEN_WIDTH - 65, 5);
  pFpsSurf->Shutdown();
  delete pFpsSurf; pFpsSurf = NULL;
}
