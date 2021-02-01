#ifndef _PLAYER_H
#define _PLAYER_H

#include <array>

class Player
{
public:
  Player(int nX, int nY, float fAngle, int nSpeed);
  ~Player();

  void Move(std::array<bool, 512> aKeysPressed);

  int GetX();
  int GetY();
  float GetAngle();
private:
  float m_fX;
  float m_fY;
  float m_fAngle;
  int m_nSpeed;
};

#endif
