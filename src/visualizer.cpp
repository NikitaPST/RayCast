#include "visualizer.h"
#include "settings.h"
#include "draw.h"
#include "ray_casting.h"
#include "color.h"

Visualizer::Visualizer(Surface* pSurface, Surface* pMapSurface)
{
  m_pSurface = pSurface;
  m_pMapSurface = pMapSurface;
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

void Visualizer::RenderMiniMap(Player* pPlayer, Map* pMap)
{
  int nMapX = pPlayer->GetX() / MAP_SCALE;
  int nMapY = pPlayer->GetY() / MAP_SCALE;

  m_pMapSurface->Fill(0x00, 0x00, 0x00);

  DrawLine(m_pMapSurface, nMapX, nMapY,
    (nMapX + 12 * cos(pPlayer->GetAngle())),
    (nMapY + 12 * sin(pPlayer->GetAngle())),
    0xFFDCDC00);
  DrawFillCircle(m_pMapSurface, nMapX, nMapY, 5, 0xFFDC0000);

  for (auto it = pMap->begin_minimap(),
    end = pMap->end_minimap(); it != end; it++)
  {
    std::tuple<int, int> coord = *it;
    int x = std::get<0>(coord);
    int y = std::get<1>(coord);

    DrawRect(m_pMapSurface, x, y, x + MAP_TILE_SIZE, y + MAP_TILE_SIZE,
      0xFF005000);
  }

  m_pSurface->Blit(m_pMapSurface, MAP_POS_X, MAP_POS_Y);
}
