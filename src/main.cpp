#include <SDL2/SDL.h>
#include <stdio.h>
#include <array>
#include <cmath>

#include "settings.h"
#include "renderer.h"
#include "clock.h"
#include "draw.h"
#include "player.h"

int main(int argc, char* args[])
{
  Renderer* pRenderer = new Renderer();
  Clock* pClock = new Clock();
  Player* pPlayer = new Player(PLAYER_POS_X, PLAYER_POS_Y, 0.0f, PLAYER_SPEED);

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

        std::array<bool, 512> aKeysPressed =
          pRenderer->GetInput()->GetKeysPressed();

        pPlayer->Move(aKeysPressed);

        DrawFillCircle(pScreenSurface, pPlayer->GetX(), pPlayer->GetY(), 12,
          0xFF00FF00);
        DrawLine(pScreenSurface, pPlayer->GetX(), pPlayer->GetY(),
          (pPlayer->GetX() + SCREEN_WIDTH * cos(pPlayer->GetAngle())),
          (pPlayer->GetY() + SCREEN_WIDTH * sin(pPlayer->GetAngle())),
          0xFF00FF00);

        pRenderer->Render();
        pClock->Tick(FPS);
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

  delete pPlayer; pPlayer = NULL;
  delete pClock; pClock = NULL;
  delete pRenderer; pRenderer = NULL;

  return 0;
}
