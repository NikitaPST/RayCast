#include <SDL2/SDL.h>
#include <stdio.h>

#include "settings.h"
#include "renderer.h"
#include "clock.h"
#include "draw.h"

int main(int argc, char* args[])
{
  Renderer* pRenderer = new Renderer();
  Clock* pClock = new Clock();

  if (pRenderer->Init())
  {
    printf("Initialization - Success\n");

    if (pRenderer->CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT))
    {
      printf("Window Creation - Success\n");

      Surface* pScreenSurface = pRenderer->GetScreenSurface();
      while (pRenderer->Run())
      {
        pScreenSurface->Fill(0x00, 0x00, 0x00);

        DrawPixel(pScreenSurface, PLAYER_POS_X, PLAYER_POS_Y, 0xFF00FF00);
        DrawFillRect(pScreenSurface, 100, 100, 300, 300, 0xFFFF0000);
        DrawLine(pScreenSurface, 100, 100, 300, 300, 0xFF00FF00);
        DrawFillCircle(pScreenSurface, 200, 200, 15, 0xFF0000FF);

        pRenderer->Render();
        pClock->Tick();
      }
    }
    else
    {
      printf("Window Creation - Failure");
    }

    pRenderer->Shutdown();
  }
  else
  {
    printf("Initialization - Failure!\n");
  }

  delete pClock; pClock = NULL;
  delete pRenderer; pRenderer = NULL;

  return 0;
}
