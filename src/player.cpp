#include "player.h"

#include <SDL2/SDL.h>

#include <stdio.h>

#define ANGLE_INC 0.02f

Player::Player(int nX, int nY, float fAngle, int nSpeed)
{
  m_nX = nX;
  m_nY = nY;
  m_fAngle = fAngle;
  m_nSpeed = nSpeed;
}

Player::~Player()
{
}

void Player::Move(std::array<bool, 512> aKeysPressed)
{
  if (aKeysPressed[SDL_SCANCODE_W])
  {
    m_nY -= m_nSpeed;
  }
  if (aKeysPressed[SDL_SCANCODE_S])
  {
    m_nY += m_nSpeed;
  }
  if (aKeysPressed[SDL_SCANCODE_A])
  {
    m_nX -= m_nSpeed;
  }
  if (aKeysPressed[SDL_SCANCODE_D])
  {
    m_nX += m_nSpeed;
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
  return m_nX;
}

int Player::GetY()
{
  return m_nY;
}

float Player::GetAngle()
{
  return m_fAngle;
}
