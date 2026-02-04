#pragma once
/* 
    Class for Snake 
    Create Snake
    Update Snake?
    Remove Snake?
*/

class Snake{
    private:
    const int m_SpawningRow = 0;
    const int m_SpawningCol = 0;

    private:
    int m_SnakeHeadRowPos;
    int m_SnakeHeadColPos;
    int m_SnakeHeadPrevRowPos;
    int m_SnakeHeadPrevColPos;

    private:
    int m_PrevRowPos;
    int m_PrevColPos;

    private:
    bool IsSnakeDead;

    private:
    static const int m_MAX_SNAKE_SIZE = 100;
    static const int m_Attributes = 3;

    private:
    int m_Snake[m_MAX_SNAKE_SIZE][m_Attributes];

    public:
    Snake() : m_Snake{'<', m_SpawningRow, m_SpawningCol} 
    {
        for(int i = 1; i < m_MAX_SNAKE_SIZE; i++){
            m_Snake[i][0] = ' ';
        }
    }

    public:
    void MoveSnake(const int move);
    bool CheckCollsion();
    void AddBody(const int index);
    int NextPos(int NewPos);
    bool ValidMove(int Row, int Col) const;
    bool CheckPosition(int* Row, int* Col);

    public:
    //Getter
    char GetSnake() const;
    int GetSnakeHeadRowPos() const;
    int GetSnakeHeadColPos() const;
    int GetPrevRowPos() const;
    int GetPrevColPos() const;
    int GetSize() const;
    int CurrSize() const;
    int GetSpecificRowPos(int index) const;
    int GetSpecificColPos(int index) const;
    bool GetSnakeDead() const;

    public:
    //Setter
    void SetSnakeHeadRowPos(int Row);
    void SetSnakeHeadColPos(int Col);
    void SetSnakeHeadCharacter(char head);
};