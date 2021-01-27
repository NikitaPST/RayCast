#include "draw.h"

#include <stdio.h>

void PutPixel(SDL_Surface* pSurface, Sint16 x, Sint16 y, Uint32 nColor)
{
  int bpp = pSurface->format->BytesPerPixel;
  Uint8 *p = (Uint8*)pSurface->pixels + y*pSurface->pitch + x * bpp;
  *(Uint32*)p = nColor;
}

void DrawPixel(Surface* pSurface, Sint16 x, Sint16 y, Uint32 nColor)
{
  SDL_Surface* pInnerSurface = pSurface->GetInnerSurface();

  if (SDL_MUSTLOCK(pInnerSurface))
  {
    if (SDL_LockSurface(pInnerSurface) < 0)
      return;
  }

  PutPixel(pInnerSurface, x, y, nColor);

  if (SDL_MUSTLOCK(pInnerSurface))
  {
    SDL_UnlockSurface(pInnerSurface);
  }
}

void PutLine(SDL_Surface* pSurface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2,
  Uint32 nColor)
{
  double x = x2 - x1;
  double y = y2 - y1;
  double length = sqrt(x*x + y*y);
  double addx = x / length;
  double addy = y / length;
  x = x1;
  y = y1;

  for (int i=0; i<length; i++)
  {
    PutPixel(pSurface, x, y, nColor);
    x += addx;
    y += addy;
  }
}

void DrawLine(Surface* pSurface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2,
  Uint32 nColor)
{
  SDL_Surface* pInnerSurface = pSurface->GetInnerSurface();

  if (SDL_MUSTLOCK(pInnerSurface))
  {
    if (SDL_LockSurface(pInnerSurface) < 0)
      return;
  }

  PutLine(pInnerSurface, x1, y1, x2, y2, nColor);

  if (SDL_MUSTLOCK(pInnerSurface))
  {
    SDL_UnlockSurface(pInnerSurface);
  }
}

void DrawRect(Surface* pSurface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2,
  Uint32 nColor)
{
  SDL_Surface* pInnerSurface = pSurface->GetInnerSurface();

  if (SDL_MUSTLOCK(pInnerSurface))
  {
    if (SDL_LockSurface(pInnerSurface) < 0)
      return;
  }

  PutLine(pInnerSurface, x1, y1, x2, y1, nColor);
  PutLine(pInnerSurface, x2, y1, x2, y2, nColor);
  PutLine(pInnerSurface, x1, y1, x1, y2, nColor);
  PutLine(pInnerSurface, x1, y2, x2, y2, nColor);

  if (SDL_MUSTLOCK(pInnerSurface))
  {
    SDL_UnlockSurface(pInnerSurface);
  }
}

void DrawFillRect(Surface* pSurface, Sint16 x1, Sint16 y1, Sint16 x2,
  Sint16 y2, Uint32 nColor)
{
  SDL_Surface* pInnerSurface = pSurface->GetInnerSurface();

  if (SDL_MUSTLOCK(pInnerSurface))
  {
    if (SDL_LockSurface(pInnerSurface) < 0)
      return;
  }

  for (Sint16 y=y1; y<=y2; y++)
  {
    PutLine(pInnerSurface, x1, y, x2, y, nColor);
  }

  if (SDL_MUSTLOCK(pInnerSurface))
  {
    SDL_UnlockSurface(pInnerSurface);
  }
}

void DrawCircle(Surface* pSurface, Sint16 x0, Sint16 y0, Uint16 r,
  Uint32 nColor)
{
  Sint16 x = 0;
  Sint16 y = r - 1;
  Sint16 d = 3 - 2*r;
  Sint16 nDiagonalInc = 10 - 4*r;
  Sint16 nRightInc = 6;

  SDL_Surface* pInnerSurface = pSurface->GetInnerSurface();

  if (SDL_MUSTLOCK(pInnerSurface))
  {
    if (SDL_LockSurface(pInnerSurface) < 0)
      return;
  }

  while (x <= y)
  {
    PutPixel(pInnerSurface, x0+x, y0+y, nColor);  // 1
    PutPixel(pInnerSurface, x0+x, y0-y, nColor);  // 2
    PutPixel(pInnerSurface, x0-x, y0+y, nColor);  // 1
    PutPixel(pInnerSurface, x0-x, y0-y, nColor);  // 2
    PutPixel(pInnerSurface, x0+y, y0+x, nColor);    // 3
    PutPixel(pInnerSurface, x0+y, y0-x, nColor);  // 4
    PutPixel(pInnerSurface, x0-y, y0+x, nColor);    // 3
    PutPixel(pInnerSurface, x0-y, y0-x, nColor);  // 4

    if (d >= 0)
    {
      d += nDiagonalInc;
      nDiagonalInc += 8;
      y -= 1;
    } else {
      d += nRightInc;
      nDiagonalInc += 4;
    }
    nRightInc += 4;
    x += 1;
  }

  if (SDL_MUSTLOCK(pInnerSurface))
  {
    SDL_UnlockSurface(pInnerSurface);
  }
}

void DrawFillCircle(Surface* pSurface, Sint16 x0, Sint16 y0, Uint16 r,
  Uint32 nColor)
{
  Sint16 x = 0;
  Sint16 y = r - 1;
  Sint16 d = 3 - 2*r;
  Sint16 nDiagonalInc = 10 - 4*r;
  Sint16 nRightInc = 6;

  SDL_Surface* pInnerSurface = pSurface->GetInnerSurface();

  if (SDL_MUSTLOCK(pInnerSurface))
  {
    if (SDL_LockSurface(pInnerSurface) < 0)
      return;
  }

  while (x <= y)
  {
    PutLine(pInnerSurface, x0+x, y0+y, x0-x, y0+y, nColor);
    PutLine(pInnerSurface, x0+x, y0-y, x0-x, y0-y, nColor);
    PutLine(pInnerSurface, x0+y, y0+x, x0-y, y0+x, nColor);
    PutLine(pInnerSurface, x0+y, y0-x, x0-y, y0-x, nColor);

    if (d >= 0)
    {
      d += nDiagonalInc;
      nDiagonalInc += 8;
      y -= 1;
    } else {
      d += nRightInc;
      nDiagonalInc += 4;
    }
    nRightInc += 4;
    x += 1;
  }

  if (SDL_MUSTLOCK(pInnerSurface))
  {
    SDL_UnlockSurface(pInnerSurface);
  }
}
