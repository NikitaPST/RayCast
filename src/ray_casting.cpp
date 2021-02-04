#include "ray_casting.h"
#include "settings.h"
#include "draw.h"

#include <cmath>
#include <tuple>

const float DIST = NUM_RAYS / (2 * std::tan(FOV / 2.0));
const float PROJ_COEFF = 3 * DIST * TILE_SIZE;
const int SCALE = (int)(SCREEN_WIDTH / NUM_RAYS);

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
      //DrawLine(pSurface, nPlayerX, nPlayerY, (int)fX, (int)fY, 0xFF282828);
      TILE tile = std::make_tuple(
        (int)(fX / TILE_SIZE) * TILE_SIZE, (int)(fY / TILE_SIZE) * TILE_SIZE);
      if (pMap->count(tile))
      {
          float fDepth = nDepth * std::cos(fPlayerAngle - fCurAngle);
          float fProjHeight = PROJ_COEFF / fDepth;
          Uint8 nColor = (Uint8)(255 / (1 + fDepth * fDepth * 0.00002));
          DrawFillRect(pSurface, nRay*SCALE,
            SCREEN_HEIGHT / 2 - (int)(fProjHeight / 2),
            nRay*SCALE + SCALE,
            SCREEN_HEIGHT / 2 - (int)(fProjHeight / 2) + (int)fProjHeight,
            FromRGB(pSurface, nColor, nColor / 2, nColor / 3)
          );
          break;
      }
    }
    fCurAngle += DELTA_ANGLE;
  }
}
