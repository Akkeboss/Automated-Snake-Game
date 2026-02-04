#pragma once
#include "Food.h"
#include "Snake.h"

/* 
    Class for creating and handling the snake game map
*/

class Map{
    private:
    static const int m_RowSize = 10;
    static const int m_ColSize = 20;
    char m_Map[m_RowSize][m_ColSize];

    public:
    //Constructor
    Map();

    public:
    //Functions
    void InitMap();
    void DisplayMap();

    public:
    //Getter
    int GetRows() const;
    int GetCols() const; 

    public:
    //Setter
    void SetMapPos(int Row, int Col, char obj);
};