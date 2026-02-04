#include "Food.h"
#include <iostream>

int Food::GetFoodRowPos() const
{
    return m_FoodPosRow;
}

int Food::GetFoodColPos() const
{
    return m_FoodPosCol;
}

char Food::GetFood() const
{
    return m_Food;
}

void Food::SetFoodRowPos(int Row)
{
    m_FoodPosRow = Row;
}

void Food::SetFoodColPos(int Col)
{
    m_FoodPosCol = Col;
}

void Food::DisplayFood()
{
    std::cout << m_Food << std::endl;
}
