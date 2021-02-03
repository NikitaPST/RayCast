#ifndef _DRAW_H
#define _DRAW_H

#include "surface.h"

void DrawPixel(Surface* pSurface, Sint16 x, Sint16 y, Uint32 nColor);

void DrawLine(Surface* pSurface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2,
  Uint32 nColor);

void DrawRect(Surface* pSurface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2,
  Uint32 nColor);

void DrawFillRect(Surface* pSurface, Sint16 x1, Sint16 y1, Sint16 x2,
  Sint16 y2, Uint32 nColor);

void DrawCircle(Surface* pSurface, Sint16 x0, Sint16 y0, Uint16 r,
  Uint32 nColor);

void DrawFillCircle(Surface* pSurface, Sint16 x0, Sint16 y0, Uint16 r,
  Uint32 nColor);

Uint32 FromRGB(Surface* pSurface, Uint8 r, Uint8 g, Uint8 b);

#endif
