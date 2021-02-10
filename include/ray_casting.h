#ifndef _RAY_CASTING_H
#define _RAY_CASTING_H

#include "surface.h"
#include "map.h"

void RayCasting(Surface* pSurface, Map* pMap, int nPlayerX, int nPlayerY,
  float fPlayerAngle);

#endif
