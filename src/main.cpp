#include <SDL2/SDL.h>
#include <stdio.h>
#include <array>
#include <cmath>
#include <tuple>

#include "settings.h"
#include "renderer.h"
#include "clock.h"
#include "draw.h"
#include "player.h"
#include "map.h"
#include "visualizer.h"

int main(int argc, char* args[])
{
  Renderer* pRenderer = new Renderer();
  Clock* pClock = new Clock();
  Player* pPlayer = new Player(PLAYER_POS_X, PLAYER_POS_Y, 0.0f, PLAYER_SPEED);
  Map* pMap = new Map("resources/test.map");

  if (pRenderer->Init())
  {
    printf("Initialization - Success\n");

    if (pRenderer->CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT))
    {
      printf("Window Creation - Success\n");

      Surface* pScreenSurface = pRenderer->GetScreenSurface();
      Surface* pMapSurface = new Surface(SCREEN_WIDTH / MAP_SCALE,
        SCREEN_HEIGHT / MAP_SCALE);
      Visualizer* pVisualizer = new Visualizer(pScreenSurface, pMapSurface);
      while (pRenderer->Run())
      {
        pScreenSurface->Fill(0x00, 0x00, 0x00);

        std::array<bool, 512> aKeysPressed =
          pRenderer->GetInput()->GetKeysPressed();

        pPlayer->Move(aKeysPressed);

        pVisualizer->RenderBackground();
        pVisualizer->RenderWorld(pMap, pPlayer->GetX(), pPlayer->GetY(),
          pPlayer->GetAngle());
        pVisualizer->RenderMiniMap(pPlayer, pMap);
        pVisualizer->RenderFps(pClock);

        pRenderer->Render();
        pClock->Tick(FPS);
      }

      delete pVisualizer; pVisualizer = NULL;
      delete pMapSurface; pMapSurface = NULL;
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

  delete pMap; pMap = NULL;
  delete pPlayer; pPlayer = NULL;
  delete pClock; pClock = NULL;
  delete pRenderer; pRenderer = NULL;

  return 0;
}
