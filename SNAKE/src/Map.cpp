#include "Map.h"
#include <iostream>

Map::Map()
{
    InitMap();
}

void Map::InitMap()
{
    for(int i = 0; i < m_RowSize; i++){
        for(int j = 0; j < m_ColSize; j++){
            m_Map[i][j] = '.';
        }
    }
}

void Map::DisplayMap()
{
    for(int i = 0; i < m_RowSize; i++){
        std::cout << "\n";
        for(int j = 0; j < m_ColSize; j++){
            std::cout << m_Map[i][j];
        }
    }
    std::cout << "\n";
}

int Map::GetRows() const
{
    return m_RowSize;
}

int Map::GetCols() const
{
    return m_ColSize;
}

void Map::SetMapPos(int Row, int Col, char obj)
{
    m_Map[Row][Col] = obj;
}
