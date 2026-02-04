#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>

void Game::CreateFood()
{
    /* 
        Add so the food can not spawn inside the snake

        Solution
        Check if the row and col pos of the food is not the same as any
        pos in the snake body and head.
        If it is generate a new food piece
        Otherwise spawn the food in a valid position.
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
    //Need to set the last previous pos to '.'
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
        
        Problem right now, in iteration 157 it has to valid moves
        but returns 0 for some reason which means it think it has no
        valid moves to do.

        The problem is that the snake gets stuck because it cant move forward
        because the col pos is > then the col pos of the snake. Makes it not valid
        And to move downward the row pos has to be < smaller then the food. Which is false to.

        Solution, maybe make a spefific case for this problem. Like if it cant move anywhere just move the snake
        to a valid position until it use the row/col pos can work
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
    //Valid move here returns false which is wrong because it is a valid move?? 
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

//Check over this
void Game::MoveSnake()
{
    /* 
        This get called after the removal of snake
        Needs to work for 1, 2, 3 and 4
    */
    m_Snake.MoveSnake(CalcNextMove()); //Get the next move and update the whole snake

    int Row = m_Snake.GetSnakeHeadRowPos();
    int Col = m_Snake.GetSnakeHeadColPos();
    char Head = m_Snake.GetSnake();

    //Needs to be checked
    if(Row >= m_Map.GetRows())
    {
        {
            //std::cout << "No higher row to move to: Set Row to 0!\n";
            m_Snake.SetSnakeHeadRowPos(0);
            //std::cout << "Set Snake head position at: " << m_Snake.GetSnakeHeadRowPos() << std::endl;
            m_Map.SetMapPos(m_Snake.GetSnakeHeadRowPos(), Col, Head);
        }
        if(m_Snake.CurrSize() > 1)
        {
            for(int i = 1; i < m_Snake.CurrSize(); i++)
            {
                int RowBody = m_Snake.GetSpecificRowPos(i);
                int ColBody = m_Snake.GetSpecificColPos(i);
                //std::cout << "Set the snake body: " << RowBody << " " << ColBody << std::endl;
                m_Map.SetMapPos(RowBody, ColBody, 'o');
            }
        }
    }
    else if(Row < 0)
    {
        //std::cout << "No lower rows to move to: Set Row to Max Row Size: " << m_Map.GetRows() << std::endl;
        {
            m_Snake.SetSnakeHeadRowPos(m_Map.GetRows() - 1);
            //std::cout << "Set Snake head position at: " << m_Snake.GetSnakeHeadRowPos() << " " << Col << std::endl;
            m_Map.SetMapPos(m_Snake.GetSnakeHeadRowPos(), Col, Head); //Set head correctly
        }
        if(m_Snake.CurrSize() > 1)
        {
            for(int i = 1; i < m_Snake.CurrSize(); i++)
            {
                int RowBody = m_Snake.GetSpecificRowPos(i);
                int ColBody = m_Snake.GetSpecificColPos(i);
                //std::cout << "Set the snake body: " << RowBody << " " << ColBody << std::endl;
                m_Map.SetMapPos(RowBody, ColBody, 'o');
            }
        }
    }
    else if(Col < 0)
    {
        //std::cout << "No lower colums to move to: Set Colum to Max Colum Size: " << m_Map.GetCols() << std::endl;
        {
            m_Snake.SetSnakeHeadColPos(m_Map.GetCols() - 1);
            //std::cout << "Set Snake head position at: " << m_Snake.GetSnakeHeadRowPos() << " " << Col << std::endl;
            m_Map.SetMapPos(m_Snake.GetSnakeHeadRowPos(), Col, Head); //Set head correctly
        }
        //Set body
        if(m_Snake.CurrSize() > 1)
        {
            for(int i = 1; i < m_Snake.CurrSize(); i++)
            {
                int RowBody = m_Snake.GetSpecificRowPos(i);
                int ColBody = m_Snake.GetSpecificColPos(i);
                //std::cout << "Set the snake body: " << RowBody << " " << ColBody << std::endl;
                m_Map.SetMapPos(RowBody, ColBody, 'o');
            }
        }

    }
    else if(Col >= m_Map.GetCols())
    {
        //std::cout << "No higher colums to move to: Set Colum to 0: " << std::endl;
        {
            m_Snake.SetSnakeHeadColPos(0);
            //std::cout << "Set Snake head position at: " << m_Snake.GetSnakeHeadColPos() << " " << Col << std::endl;
            m_Map.SetMapPos(Row, m_Snake.GetSnakeHeadColPos(), Head); //Set head correctly
        }
        //Set body
        if(m_Snake.CurrSize() > 1)
        {
            for(int i = 1; i < m_Snake.CurrSize(); i++)
            {
                int RowBody = m_Snake.GetSpecificRowPos(i);
                int ColBody = m_Snake.GetSpecificColPos(i);
                //std::cout << "Set the snake body: " << RowBody << " " << ColBody << std::endl;
                m_Map.SetMapPos(RowBody, ColBody, 'o');
            }
        }
        
    }
    else
    {
        m_Map.SetMapPos(Row, Col, Head); //Set head on map //Correct
        //std::cout << "Set Snake head position at: " << Row << " " << Col << std::endl;

        if(m_Snake.CurrSize() > 1)
        {
            //std::cout << "Current size: " << m_Snake.CurrSize() << "\n"; // 2
            for(int i = 1; i < m_Snake.CurrSize(); i++)
            {
                //All current pos
                int RowBody = m_Snake.GetSpecificRowPos(i);
                int ColBody = m_Snake.GetSpecificColPos(i);
                //std::cout << "Set snake body: " << RowBody << " " << ColBody << std::endl;
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
    int count = 0;
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