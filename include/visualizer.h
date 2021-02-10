#ifndef _VISUALIZER_H
#define _VISUALIZER_H

#include "surface.h"
#include "map.h"
#include "clock.h"
#include "font.h"
#include "player.h"

class Visualizer
{
public:
  Visualizer(Surface* pSurface, Surface* pMapSurface);
  ~Visualizer();

  void RenderBackground();
  void RenderWorld(Map* pMap, int nPlayerX, int nPlayerY, float fPlayerAngle);
  void RenderFps(Clock* pClock);
  void RenderMiniMap(Player* pPlayer, Map* pMap);
private:
  Surface* m_pSurface;
  Surface* m_pMapSurface;
  Font* m_pFont;
};

#endif
