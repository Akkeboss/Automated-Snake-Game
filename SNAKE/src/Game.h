#pragma once
#include "Snake.h"
#include "Map.h"

/* 
    Class for Game
    Logic handling
    Check States
    Update States
    Display Game
    Display Results
*/
class Game{    
    private:
    int StepsTaken = 0;
    int Score = 0;
    int PrevMove = 0;

    private:
    bool IsSnakeDead;
    
    private:
    Snake m_Snake;
    Map m_Map;
    Food* m_Food = nullptr;

    private:
    void CreateFood();
    void DeleteFood();
    void RespawnFood();

    private:
    void SpawnSnake();
    void RemoveOldSnake();
    int CalcNextMove();
    void MoveSnake();
    bool IsEaten();
    void AddBody();

    private:
    bool SnakeDead();
    void UpdateSnake();
    void RenderMap();
    void DisplayResult() const;

    public:

    void run();
};