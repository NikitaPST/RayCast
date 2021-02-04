#ifndef _VISUALIZER_H
#define _VISUALIZER_H

#include "surface.h"
#include "map.h"
#include "clock.h"
#include "font.h"

class Visualizer
{
public:
  Visualizer(Surface* pSurface);
  ~Visualizer();

  void RenderBackground();
  void RenderWorld(Map* pMap, int nPlayerX, int nPlayerY, float fPlayerAngle);
  void RenderFps(Clock* pClock);
private:
  Surface* m_pSurface;
  Font* m_pFont;
};

#endif
