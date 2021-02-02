#ifndef _MAP_H
#define _MAP_H

#include <string>
#include <tuple>
#include <set>

#define TILE_SIZE 100
#define TILE std::tuple<int, int>

class Map
{
public:
  Map(std::string strFileName);
  ~Map();

  std::set<TILE>::iterator begin();
  std::set<TILE>::iterator end();
  size_t count(TILE val);
private:
  int m_nWidth;
  int m_nHeight;
  std::set<TILE> m_MapSet;
};

#endif
