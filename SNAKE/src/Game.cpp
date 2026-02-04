#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>

void Game::CreateFood()
{
    /* 
        Add so the food can not spawn inside the snake
    */

    int count = 0;
    this->m_Food = new Food();
    int Row = this->m_Food->GetFoodRowPos();
    int Col = this->m_Food->GetFoodColPos();
    if(!m_Snake.CheckPosition(&Row, &Col))
    {   
        char Food = this->m_Food->GetFood();
        m_Map.SetMapPos(Row, Col, Food);
        std::cout << "Food Spawned\n";
    }
    else
    {   //Belive this is bugged!
        while (m_Snake.CheckPosition(&Row, &Col) && count < 5)
        {
            DeleteFood();
            this->m_Food = new Food();
            int Row = this->m_Food->GetFoodRowPos();
            int Col = this->m_Food->GetFoodColPos();
            count++;
        }
        char Food = this->m_Food->GetFood();
        m_Map.SetMapPos(Row, Col, Food);
        std::cout << "Food Spawned\n";
    }
    
}

void Game::DeleteFood()
{
    delete m_Food;
    m_Food = nullptr;
    std::cout << "Food Deleted\n";
}

void Game::RespawnFood()
{
    DeleteFood();
    CreateFood();
}

void Game::SpawnSnake()
{
    int Row = m_Snake.GetSnakeHeadRowPos();
    int Col = m_Snake.GetSnakeHeadColPos();
    char Head = m_Snake.GetSnake();
    m_Map.SetMapPos(Row, Col, Head);
}

void Game::RemoveOldSnake()
{
    if(m_Snake.CurrSize() == 1)
    {
        m_Map.SetMapPos(m_Snake.GetSnakeHeadRowPos(), m_Snake.GetSnakeHeadColPos(), '.');
    }
    else if(m_Snake.CurrSize() > 1)
    {
        //Remove the previous position from the last position of the snake
        m_Map.SetMapPos(m_Snake.GetSpecificRowPos(m_Snake.CurrSize() - 1), m_Snake.GetSpecificColPos(m_Snake.CurrSize() - 1), '.');
    }
}    

//Handle so how the snake moves
int Game::CalcNextMove()
{
    /* 
        1 is forward
        2 is backward
        3 is downward
        4 is upward
    */

    //Move forward columwise
    if(m_Snake.ValidMove(m_Snake.GetSnakeHeadRowPos(), m_Snake.NextPos(1)) && m_Snake.GetSnakeHeadColPos() < m_Food->GetFoodColPos() && PrevMove != 2)
    {
        PrevMove = 1;
        std::cout << "Move forward!\n";
        m_Snake.SetSnakeHeadCharacter('<');
        return 1; //Forwards
    } 
    else if(m_Snake.ValidMove(m_Snake.GetSnakeHeadRowPos(), m_Snake.NextPos(2)) && m_Snake.GetSnakeHeadColPos() > m_Food->GetFoodColPos() && PrevMove != 1)
    {
        PrevMove = 2;
        std::cout << "Move backward!\n";
        m_Snake.SetSnakeHeadCharacter('>');
        return 2; //Backwards
    }
    else if(m_Snake.ValidMove(m_Snake.NextPos(3), m_Snake.GetSnakeHeadColPos()) && m_Snake.GetSnakeHeadRowPos() < m_Food->GetFoodRowPos())
    {
        PrevMove = 3;
        std::cout << "Move downward!\n";
        m_Snake.SetSnakeHeadCharacter('^');
        return 3; //Downwards

    } 
    else if(m_Snake.ValidMove(m_Snake.NextPos(4), m_Snake.GetSnakeHeadColPos()) && m_Snake.GetSnakeHeadRowPos() > m_Food->GetFoodRowPos())
    {
        std::cout << "Move uppward!\n";
        m_Snake.SetSnakeHeadCharacter('v');
        PrevMove = 4;
        return 4;
    }
    else if(m_Snake.ValidMove(m_Snake.GetSnakeHeadRowPos(), m_Snake.NextPos(1)))
    {
        PrevMove = 1;
        std::cout << "Move forward!\n";
        m_Snake.SetSnakeHeadCharacter('<');
        return 1; //Forwards
    }
    else
    {
        std::cout << "Failed move for all positions: " << m_Snake.GetSnakeHeadRowPos() << " " << m_Snake.NextPos(1) << "\n"
                                                       << m_Snake.GetSnakeHeadRowPos() << " " << m_Snake.NextPos(2) << "\n"
                                                       << m_Snake.NextPos(3) << " " << m_Snake.GetSnakeHeadColPos() << "\n"
                                                       << m_Snake.NextPos(4) << " " << m_Snake.GetSnakeHeadColPos() << "\n";
        return 0;
    }
    return 0;
}

//Move the snake to next position
void Game::MoveSnake()
{
    m_Snake.MoveSnake(CalcNextMove()); //Get the next move and update the whole snake

    int Row = m_Snake.GetSnakeHeadRowPos();
    int Col = m_Snake.GetSnakeHeadColPos();
    char Head = m_Snake.GetSnake();

    //Needs to be checked
    if(Row >= m_Map.GetRows())
    {
        {
            m_Snake.SetSnakeHeadRowPos(0);
            m_Map.SetMapPos(m_Snake.GetSnakeHeadRowPos(), Col, Head);
        }
        if(m_Snake.CurrSize() > 1)
        {
            for(int i = 1; i < m_Snake.CurrSize(); i++)
            {
                int RowBody = m_Snake.GetSpecificRowPos(i);
                int ColBody = m_Snake.GetSpecificColPos(i);
                m_Map.SetMapPos(RowBody, ColBody, 'o');
            }
        }
    }
    else if(Row < 0)
    {
        {
            m_Snake.SetSnakeHeadRowPos(m_Map.GetRows() - 1);
            m_Map.SetMapPos(m_Snake.GetSnakeHeadRowPos(), Col, Head); //Set head correctly
        }
        if(m_Snake.CurrSize() > 1)
        {
            for(int i = 1; i < m_Snake.CurrSize(); i++)
            {
                int RowBody = m_Snake.GetSpecificRowPos(i);
                int ColBody = m_Snake.GetSpecificColPos(i);
                m_Map.SetMapPos(RowBody, ColBody, 'o');
            }
        }
    }
    else if(Col < 0)
    {
        {
            m_Snake.SetSnakeHeadColPos(m_Map.GetCols() - 1);
            m_Map.SetMapPos(m_Snake.GetSnakeHeadRowPos(), Col, Head); //Set head correctly
        }
        //Set body
        if(m_Snake.CurrSize() > 1)
        {
            for(int i = 1; i < m_Snake.CurrSize(); i++)
            {
                int RowBody = m_Snake.GetSpecificRowPos(i);
                int ColBody = m_Snake.GetSpecificColPos(i);
                m_Map.SetMapPos(RowBody, ColBody, 'o');
            }
        }

    }
    else if(Col >= m_Map.GetCols())
    {
        {
            m_Snake.SetSnakeHeadColPos(0);
            m_Map.SetMapPos(Row, m_Snake.GetSnakeHeadColPos(), Head); //Set head correctly
        }
        //Set body
        if(m_Snake.CurrSize() > 1)
        {
            for(int i = 1; i < m_Snake.CurrSize(); i++)
            {
                int RowBody = m_Snake.GetSpecificRowPos(i);
                int ColBody = m_Snake.GetSpecificColPos(i);
                m_Map.SetMapPos(RowBody, ColBody, 'o');
            }
        }
        
    }
    else
    {
        m_Map.SetMapPos(Row, Col, Head); //Set head on map //Correct
        if(m_Snake.CurrSize() > 1)
        {
            for(int i = 1; i < m_Snake.CurrSize(); i++)
            {
                //All current pos
                int RowBody = m_Snake.GetSpecificRowPos(i);
                int ColBody = m_Snake.GetSpecificColPos(i);
                m_Map.SetMapPos(RowBody, ColBody, 'o');
            }
        }    
    }
        
}

bool Game::IsEaten()
{
    //Check if the new pos of the snake is the same pos of the food
    int SnakeRow = m_Snake.GetSnakeHeadRowPos();
    int SnakeCol = m_Snake.GetSnakeHeadColPos();
    int FoodRow = this->m_Food->GetFoodRowPos();
    int FoodCol = this->m_Food->GetFoodColPos();
    if(SnakeRow == FoodRow && SnakeCol == FoodCol){
        RespawnFood();
        return true;
    }
    return false;
}

void Game::AddBody()
{
    std::cout << "The score is: " << Score << std::endl;
    m_Snake.AddBody(Score);
    int Row = m_Snake.GetSpecificRowPos(Score);
    int Col = m_Snake.GetSpecificColPos(Score);
    m_Map.SetMapPos(Row, Col, 'o');
}

bool Game::SnakeDead()
{
    if(m_Snake.CheckCollsion())
        return true;
    else
        return m_Snake.GetSnakeDead();
    
    return false;
}

void Game::UpdateSnake()
{
    RemoveOldSnake(); //First
    MoveSnake(); //Second 
    StepsTaken++;
    if(IsEaten())
    {
        Score++;
        AddBody();
    }

    
}

void Game::RenderMap()
{
    m_Map.DisplayMap();
}

void Game::DisplayResult() const
{
    std::cout << "The score is " << Score << std::endl;
    std::cout << "Steps taken by the snake is: " << StepsTaken << std::endl;
}

//Main Game Loop
void Game::run()
{
    /* 
        If snake is dead then exit loop and quit game
        If not then move the snake one step
            Check if there is a food piece in that position
                If it is then eat it
                Add a body piece

    */
    IsSnakeDead = false;
    int count = 0; //Debugging purpose
    CreateFood();
    SpawnSnake();
    RenderMap();
    while(!IsSnakeDead)
    {
        UpdateSnake();
        RenderMap();
        count++;
        IsSnakeDead = SnakeDead();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    DisplayResult();
    
}