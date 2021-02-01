#ifndef _MAP_H
#define _MAP_H

#include <string>
#include <tuple>
#include <set>

#define TILE_SIZE 100

class Map
{
public:
  Map(std::string strFileName);
  ~Map();

  std::set<std::tuple<int, int>>::iterator begin();
  std::set<std::tuple<int, int>>::iterator end();
private:
  int m_nWidth;
  int m_nHeight;
  std::set<std::tuple<int, int>> m_MapSet;
};

#endif
