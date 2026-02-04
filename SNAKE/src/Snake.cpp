#include "Snake.h"
#include <string>
#include <iostream>

/* 
    Move Snake should update each pos in the snake array
    if there is only the head in the snake it should only update the head

    if there is a body each pos in the body should get the previous pos of the 
    body piece before it.
*/

void Snake::MoveSnake(const int move)
{
    /* 
        Last known pos in the snake array becomes the previous pos after the snake has moved
    */

    {
        //This keeps track of the last pos which becomes the previous after the snake has moved
        //Used for adding body to the back and also deleting a piece of the snake when it has moved.
        m_PrevRowPos = m_Snake[CurrSize() - 1][1];
        m_PrevColPos = m_Snake[CurrSize() - 1][2];
        std::cout << "The Previous Position is: " << m_PrevRowPos << " " << m_PrevColPos << std::endl;
    }

    {
        //This gives the previous head position so i can use that
        //as a starting point when I update the body
        m_SnakeHeadPrevRowPos = m_Snake[0][1];
        m_SnakeHeadPrevColPos = m_Snake[0][2];
    }
    
    switch(move)
    {
        case 0:
            std::cout << "Calc Move function is bugged or no valid moves so snake is dead\n";
            IsSnakeDead = true;
            break;
        case 1:
            if(CurrSize() == 1)
            {
                m_Snake[0][2]++; //Only move head forward if head is the only body of the snake
            }
            else if(CurrSize() > 1)
            {   
                m_Snake[0][2]++; //First move head
                //Move body
                for(int i = 1; i < CurrSize(); i++)
                {
                    int PrevRow = m_Snake[i][1];
                    int PrevCol = m_Snake[i][2];
                    //This is wrong right now
                    m_Snake[i][1] = m_SnakeHeadPrevRowPos;
                    m_Snake[i][2] = m_SnakeHeadPrevColPos;

                    m_SnakeHeadPrevRowPos = PrevRow;
                    m_SnakeHeadPrevColPos = PrevCol;
                    
                    std::cout << "Update the snake body: " << m_Snake[i][1] << " " << m_Snake[i][2] << std::endl;
                }
            }
            break;
        case 2:
            if(CurrSize() == 1)
            {
                m_Snake[0][2]--; //Only move head forward if head is the only body of the snake
            }
            else if(CurrSize() > 1)
            {   
                m_Snake[0][2]--; //First move head
                //Move body
                for(int i = 1; i < CurrSize(); i++)
                {
                    int PrevRow = m_Snake[i][1];
                    int PrevCol = m_Snake[i][2];
                    m_Snake[i][1] = m_SnakeHeadPrevRowPos;
                    m_Snake[i][2] = m_SnakeHeadPrevColPos;

                    m_SnakeHeadPrevRowPos = PrevRow;
                    m_SnakeHeadPrevColPos = PrevCol;
                    
                    std::cout << "Update the snake body: " << m_Snake[i][1] << " " << m_Snake[i][2] << std::endl;
                }
            }
            break;
        case 3:
            if(CurrSize() == 1)
            {
                m_Snake[0][1]++; //Only move head forward if head is the only body of the snake
            }
            else if(CurrSize() > 1)
            {   
                m_Snake[0][1]++; //First move head
                //Move body
                for(int i = 1; i < CurrSize(); i++)
                {
                    int PrevRow = m_Snake[i][1];
                    int PrevCol = m_Snake[i][2];
                    m_Snake[i][1] = m_SnakeHeadPrevRowPos;
                    m_Snake[i][2] = m_SnakeHeadPrevColPos;

                    m_SnakeHeadPrevRowPos = PrevRow;
                    m_SnakeHeadPrevColPos = PrevCol;
                    
                    std::cout << "Update the snake body: " << m_Snake[i][1] << " " << m_Snake[i][2] << std::endl;
                }
            }
            break;
        case 4:
            //BELIVE THIS IS WORKING!!
            if(CurrSize() == 1)
            {
                m_Snake[0][1]--; //Only update head if head is the only body of the snake
                std::cout << "Update snake head position upwards: " << m_Snake[0][1] << std::endl;
            }
            else if(CurrSize() > 1)
            {
                m_Snake[0][1]--; //Only update head if head is the only body of the snake
                std::cout << "Update snake head position upwards: " << m_Snake[0][1] << std::endl;

                //Move body
                for(int i = 1; i < CurrSize(); i++)
                {
                    int PrevRow = m_Snake[i][1];
                    int PrevCol = m_Snake[i][2];
                    
                    m_Snake[i][1] = m_SnakeHeadPrevRowPos;
                    m_Snake[i][2] = m_SnakeHeadPrevColPos;

                    m_SnakeHeadPrevRowPos = PrevRow;
                    m_SnakeHeadPrevColPos = PrevCol;
                    
                    std::cout << "Update the snake body: " << m_Snake[i][1] << " " << m_Snake[i][2] << std::endl;
                }
            }
            break;
    }

}

//Bugged
bool Snake::CheckCollsion()
{
    /* 
        Check if the posistion of the snake head is inside the arry
        Meaning:
        If the row and col pos of snake head == ANY row and col pos in the body
    */
    int CurrHeadRow = GetSnakeHeadRowPos();
    int CurrHeadCol = GetSnakeHeadColPos();
    for(int i = 1; i < CurrSize(); i++){
        if(CurrHeadRow == m_Snake[i][1] && CurrHeadCol == m_Snake[i][2])
        {
            std::cout << "Snake has died!\n";
            return true;
        } 
    }
    return false;
}

void Snake::AddBody(const int index)
{
    /* 
        Always set the PrevPos depending on the last pos of the snake array
    */
    
    std::cout << "The prev from AddBody is: " << m_PrevRowPos << " " << m_PrevColPos << std::endl;
    m_Snake[index][0] = 'o';
    m_Snake[index][1] = m_PrevRowPos;
    m_Snake[index][2] = m_PrevColPos;
}

int Snake::NextPos(int NewPos)
{
    /* 
        Need a copy of snake because this is just to check
        which move is available
        if i change the real snake here we get some problems
    */

    int SnakeCopyRow = m_Snake[0][1];
    int SnakeCopyCol = m_Snake[0][2];

    switch (NewPos)
    {
    case 1:
        //Move snake forward
        SnakeCopyCol++;
        return SnakeCopyCol;
        break;
    case 2:
        //Move snake backward
        SnakeCopyCol--;
        return SnakeCopyCol;
        break;
    case 3:
        //Move snake downwards
        SnakeCopyRow++;
        return SnakeCopyRow;
        break;
    case 4:
        //Move snake upwards
        SnakeCopyRow--;
        return SnakeCopyRow;
        break;
    default:
        break;
    }
    return 0;
}

bool Snake::ValidMove(int Row, int Col) const
{
    for(int i = 0; i < CurrSize(); i++){
        if(Row == m_Snake[i][1] && Col == m_Snake[i][2]){
            return false;
        }
    }
    return true;
}

bool Snake::CheckPosition(int *Row, int *Col)
{
    for(int i = 0; i < CurrSize(); i++){
        if(*Row == m_Snake[i][1] && *Col == m_Snake[i][2])
        {
            return true;
        }
    }
    return false;
}

char Snake::GetSnake() const
{
    return m_Snake[0][0];
}

int Snake::GetSnakeHeadColPos() const
{
    return m_Snake[0][2];
}

int Snake::GetPrevRowPos() const
{
    return m_Snake[m_PrevRowPos][1];
}

int Snake::GetPrevColPos() const
{
    return m_Snake[m_PrevColPos][2];
}

int Snake::GetSize() const
{
    return m_MAX_SNAKE_SIZE;
}

int Snake::CurrSize() const
{
    int count = 0;
    while(m_Snake[count][0] != ' ')
    {
        count++;
    }
    return count;
}

int Snake::GetSpecificRowPos(int index) const
{
    return m_Snake[index][1];
}

int Snake::GetSpecificColPos(int index) const
{
    return m_Snake[index][2];
}

bool Snake::GetSnakeDead() const
{
    return IsSnakeDead;
}

void Snake::SetSnakeHeadRowPos(int Row)
{
    m_Snake[0][1] = Row;
}

void Snake::SetSnakeHeadColPos(int Col)
{
    m_Snake[0][2] = Col;
}

void Snake::SetSnakeHeadCharacter(char head)
{
    m_Snake[0][0] = head;
}

int Snake::GetSnakeHeadRowPos() const
{
    return m_Snake[0][1];
}


