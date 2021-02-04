#include "clock.h"

#include <SDL2/SDL.h>

#define WORST_CLOCK_ACCURACY 12

Clock::Clock()
{
  if (!SDL_WasInit(SDL_INIT_TIMER))
  {
    SDL_InitSubSystem(SDL_INIT_TIMER);
  }

  m_nFpsTick = 0;
  m_nTimepassed = 0;
  m_nRawpassed = 0;
  m_nLastTick = SDL_GetTicks();
  m_fFps = 0.0f;
  m_nFpsCount = 0;
}

Clock::~Clock()
{
}

int Clock::TickBase(bool bUseAccurateDelay, float fFramerate)
{
  int nNowTime = 0;

  if (fFramerate > 0.0f)
  {
    int nDelay, nEndTime = (int)((1.0f / fFramerate) * 1000.0f);
    m_nRawpassed = SDL_GetTicks() - m_nLastTick;
    nDelay = nEndTime - m_nRawpassed;

    if (bUseAccurateDelay)
    {
      nDelay = CalcAccurateDelay(nDelay);
    }
    else
    {
      if (nDelay < 0)
      {
        nDelay = 0;
      }
      SDL_Delay((Uint32)nDelay);
    }

    if (nDelay == -1)
    {
      return -1;
    }
  }

  nNowTime = SDL_GetTicks();
  m_nTimepassed = nNowTime - m_nLastTick;
  m_nFpsCount += 1;
  m_nLastTick = nNowTime;
  if (fFramerate == 0.0f)
  {
    m_nRawpassed = m_nTimepassed;
  }

  if (m_nFpsTick == 0)
  {
    m_nFpsCount = 0;
    m_nFpsTick = nNowTime;
  }
  else if (m_nFpsCount >= 10)
  {
    m_fFps = m_nFpsCount / ((nNowTime - m_nFpsTick) / 1000.0f);
    m_nFpsCount = 0;
    m_nFpsTick = nNowTime;
  }

  return m_nTimepassed;
}

int Clock::CalcAccurateDelay(int nTicks)
{
  if (nTicks <= 0)
    return 0;

  int nDelay;
  int nFuncStart = SDL_GetTicks();
  if (nTicks >= WORST_CLOCK_ACCURACY)
  {
    nDelay = (nTicks - 2) - (nTicks % WORST_CLOCK_ACCURACY);
    if (nDelay >= WORST_CLOCK_ACCURACY)
    {
      SDL_Delay(nDelay);
    }
  }
  do
  {
    nDelay = nTicks - (SDL_GetTicks() - nFuncStart);
  } while (nDelay > 0);

  return (SDL_GetTicks() - nFuncStart);
}

int Clock::Tick(float fFramerate)
{
  return TickBase(false, fFramerate);
}

float Clock::GetFps()
{
  return m_fFps;
}
