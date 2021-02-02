#include "ray_casting.h"
#include "settings.h"
#include "draw.h"

#include <cmath>
#include <tuple>

void RayCasting(Surface* pSurface, Map* pMap, int nPlayerX, int nPlayerY,
  float fPlayerAngle)
{
  float fCurAngle = fPlayerAngle - (FOV / 2.0);
  int nXo = nPlayerX;
  int nYo = nPlayerY;

  for (int nRay=0; nRay < NUM_RAYS; nRay++)
  {
    float fSinA = std::sin(fCurAngle);
    float fCosA = std::cos(fCurAngle);
    for (int nDepth=0; nDepth < MAX_DEPTH; nDepth++)
    {
      float fX = nXo + nDepth * fCosA;
      float fY = nYo + nDepth * fSinA;
      DrawLine(pSurface, nPlayerX, nPlayerY, (int)fX, (int)fY, 0xFF282828);
      TILE tile = std::make_tuple(
        (int)(fX / TILE_SIZE) * TILE_SIZE, (int)(fY / TILE_SIZE) * TILE_SIZE);
      if (pMap->count(tile))
        break;
    }
    fCurAngle += DELTA_ANGLE;
  }
}
