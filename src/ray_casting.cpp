#include "ray_casting.h"
#include "settings.h"
#include "draw.h"

#include <cmath>
#include <tuple>

const float DIST = NUM_RAYS / (2 * std::tan(FOV / 2.0));
const float PROJ_COEFF = 3 * DIST * TILE_SIZE;
const int SCALE = (int)(SCREEN_WIDTH / NUM_RAYS);

int Mapping(int nValue)
{
  return (int)(nValue / TILE_SIZE) * TILE_SIZE;
}

void RayCasting(Surface* pSurface, Map* pMap, int nPlayerX, int nPlayerY,
  float fPlayerAngle)
{
  int nY, nX;
  int ndY, ndX;
  float fDepthV, fDepthH;

  int nXo = nPlayerX;
  int nYo = nPlayerY;
  int nXm = Mapping(nXo);
  int nYm = Mapping(nYo);
  float fCurAngle = fPlayerAngle - (FOV / 2.0);

  for (int nRay=0; nRay < NUM_RAYS; nRay++)
  {
    float fSinA = std::sin(fCurAngle);
    float fCosA = std::cos(fCurAngle);

    nX = (fCosA >= 0.0f) ? nXm + TILE_SIZE : nXm;
    ndX = (fCosA >= 0.0f) ? 1 : -1;

    for (int i=0; i < SCREEN_WIDTH; i+= TILE_SIZE)
    {
      fDepthV = (nX - nXo) / fCosA;
      nY = (int)(nYo + fDepthV * fSinA);
      TILE tile = std::make_tuple(Mapping(nX + ndX), Mapping(nY));
      if (pMap->count(tile))
        break;
      nX += ndX * TILE_SIZE;
    }

    nY = (fSinA >= 0.0f) ? nYm + TILE_SIZE : nYm;
    ndY = (fSinA >= 0.0f) ? 1 : -1;
    for (int i=0; i < SCREEN_HEIGHT; i+= TILE_SIZE)
    {
      fDepthH = (nY - nYo) / fSinA;
      nX = (int)(nXo + fDepthH * fCosA);
      TILE tile = std::make_tuple(Mapping(nX), Mapping(nY + ndY));
      if (pMap->count(tile))
        break;
      nY += ndY * TILE_SIZE;
    }

    float fDepth = (fDepthV < fDepthH) ? fDepthV : fDepthH;
    fDepth = fDepth * std::cos(fPlayerAngle - fCurAngle);
    float fProjHeight = PROJ_COEFF / fDepth;
    Uint8 nColor = (Uint8)(255 / (1 + fDepth * fDepth * 0.00002));
    DrawFillRect(pSurface, nRay*SCALE,
      SCREEN_HEIGHT / 2 - (int)(fProjHeight / 2),
      nRay*SCALE + SCALE,
      SCREEN_HEIGHT / 2 - (int)(fProjHeight / 2) + (int)fProjHeight,
      FromRGB(pSurface, nColor, nColor / 2, nColor / 3)
    );
    fCurAngle += DELTA_ANGLE;
  }
}

void RayCastingNaive(Surface* pSurface, Map* pMap, int nPlayerX, int nPlayerY,
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
