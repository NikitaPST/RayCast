#include "player.h"

#include <SDL2/SDL.h>

#include <cmath>

#define ANGLE_INC 0.02f

Player::Player(int nX, int nY, float fAngle, int nSpeed)
{
  m_fX = nX;
  m_fY = nY;
  m_fAngle = fAngle;
  m_nSpeed = nSpeed;
}

Player::~Player()
{
}

void Player::Move(std::array<bool, 512> aKeysPressed)
{
  float fSinA = std::sin(m_fAngle);
  float fCosA = std::cos(m_fAngle);
  if (aKeysPressed[SDL_SCANCODE_W])
  {
    m_fX += m_nSpeed * fCosA;
    m_fY += m_nSpeed * fSinA;
  }
  if (aKeysPressed[SDL_SCANCODE_S])
  {
    m_fX -= m_nSpeed * fCosA;
    m_fY -= m_nSpeed * fSinA;
  }
  if (aKeysPressed[SDL_SCANCODE_A])
  {
    m_fX += m_nSpeed * fSinA;
    m_fY -= m_nSpeed * fCosA;
  }
  if (aKeysPressed[SDL_SCANCODE_D])
  {
    m_fX -= m_nSpeed * fSinA;
    m_fY += m_nSpeed * fCosA;
  }
  if (aKeysPressed[SDL_SCANCODE_LEFT])
  {
    m_fAngle -= ANGLE_INC;
  }
  if (aKeysPressed[SDL_SCANCODE_RIGHT])
  {
    m_fAngle += ANGLE_INC;
  }
}

int Player::GetX()
{
  return (int)std::round(m_fX);
}

int Player::GetY()
{
  return (int)std::round(m_fY);
}

float Player::GetAngle()
{
  return m_fAngle;
}
