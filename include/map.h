#ifndef _MAP_H
#define _MAP_H

#include <string>
#include <tuple>
#include <set>

#include "settings.h"

#define TILE_SIZE 100
#define MAP_TILE_SIZE (TILE_SIZE / MAP_SCALE)
#define TILE std::tuple<int, int>

class Map
{
public:
  Map(std::string strFileName);
  ~Map();

  std::set<TILE>::iterator begin();
  std::set<TILE>::iterator end();
  std::set<TILE>::iterator begin_minimap();
  std::set<TILE>::iterator end_minimap();
  size_t count(TILE val);
private:
  int m_nWidth;
  int m_nHeight;
  std::set<TILE> m_MapSet;
  std::set<TILE> m_MiniMapSet;
};

#endif
