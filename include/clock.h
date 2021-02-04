#ifndef _CLOCK_H
#define _CLOCK_H

class Clock
{
public:
  Clock();
  ~Clock();

  int Tick(float fFramerate = 0.0f);
  float GetFps();
private:
  int m_nLastTick;
  int m_nFpsCount;
  int m_nFpsTick;
  float m_fFps;
  int m_nTimepassed;
  int m_nRawpassed;

  int TickBase(bool bUseAccurateDelay, float fFramerate = 0.0f);
  int CalcAccurateDelay(int nTicks);
};

#endif
