#pragma once
#include <cstdlib>
/* 
    Class for a food object
    Create food
    Remove food
*/

class Food{
    private:
    const char m_Food;
    int m_FoodPosRow;
    int m_FoodPosCol;
    
    public:
    //Constructor for food
    //Not Random right now need to fix
    Food() : m_Food('*'), m_FoodPosRow(rand() % 10), m_FoodPosCol(rand() % 20) {}

    public:
    int GetFoodRowPos() const;
    int GetFoodColPos() const;
    char GetFood() const;

    public:
    void SetFoodRowPos(int Row);
    void SetFoodColPos(int Col); 
    

    public:
    //Debugging purpose
    void DisplayFood();
};