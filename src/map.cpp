#include "map.h"

#include <fstream>
#include <algorithm>
#include <stdio.h>

Map::Map(std::string strFileName)
{
  printf("Reading map from: %s\n", strFileName.c_str());
  std::ifstream infile(strFileName);

  std::string strLine;
  while (std::getline(infile, strLine))
  {
    for (int i=0; i<strLine.size(); i++)
    {
      if (strLine[i] == 'W')
      {
          m_MapSet.insert(std::make_tuple(i * TILE_SIZE,
            m_nHeight * TILE_SIZE));
      }
    }
    m_nWidth = std::max((int)strLine.length(), m_nWidth);
    m_nHeight++;
  }

  printf("Map size: (%d, %d)\n", m_nWidth, m_nHeight);
}

Map::~Map()
{
}

std::set<TILE>::iterator Map::begin()
{
  return m_MapSet.begin();
}

std::set<TILE>::iterator Map::end()
{
  return m_MapSet.end();
}

size_t Map::count(TILE val)
{
  return m_MapSet.count(val);
}
