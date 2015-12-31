#include <cstdio>

#include "Tetromino.hpp"

Tetromino::Tetromino(TetrominoType_e newType)
{
    type = newType;
    switch (type)
    {
        case TETROMINO_TYPE_O:
            rows[0] = 0; cols[0] = 0;
            rows[1] = 0; cols[1] = 1;
            rows[2] = 1; cols[2] = 0;
            rows[3] = 1; cols[3] = 1;
            break;
            
        case TETROMINO_TYPE_T:
            rows[0] = 0; cols[0] = 0;
            rows[1] = 1; cols[1] = 0;
            rows[2] = 2; cols[2] = 0;
            rows[3] = 1; cols[3] = 1;
            break;
            
        case TETROMINO_TYPE_I:
            rows[0] = 0; cols[0] = 0;
            rows[1] = 1; cols[1] = 0;
            rows[2] = 2; cols[2] = 0;
            rows[3] = 3; cols[3] = 0;
            break;
            
        case TETROMINO_TYPE_S:
            rows[0] = 0; cols[0] = 0;
            rows[1] = 1; cols[1] = 0;
            rows[2] = 1; cols[2] = 1;
            rows[3] = 2; cols[3] = 1;
            break;
            
        case TETROMINO_TYPE_Z:
            rows[0] = 0; cols[0] = 1;
            rows[1] = 1; cols[1] = 0;
            rows[2] = 1; cols[2] = 1;
            rows[3] = 2; cols[3] = 0;
            break;
            
        case TETROMINO_TYPE_L:
            rows[0] = 0; cols[0] = 0;
            rows[1] = 1; cols[1] = 0;
            rows[2] = 2; cols[2] = 0;
            rows[3] = 2; cols[3] = 1;
            break;
            
        case TETROMINO_TYPE_J:
            rows[0] = 0; cols[0] = 1;
            rows[1] = 1; cols[1] = 1;
            rows[2] = 2; cols[2] = 1;
            rows[3] = 2; cols[3] = 0;
            break;
        
        default:
            printf("Unkown type! %d\n", 
                   static_cast<int>(newType));
    }
}

void Tetromino::moveDown()
{
    rows[0]++;
    rows[1]++;
    rows[2]++;
    rows[3]++; 
}

void Tetromino::moveRight()
{
    cols[0]++;
    cols[1]++;
    cols[2]++;
    cols[3]++;
}

void Tetromino::moveLeft()
{
    cols[0]--;
    cols[1]--;
    cols[2]--;
    cols[3]--;
}
    
int Tetromino::getFurthestRight() const
{
    int furthest = cols[0];
    if (cols[1] > furthest) furthest = cols[1];
    if (cols[2] > furthest) furthest = cols[2];
    if (cols[3] > furthest) furthest = cols[3];
    return furthest;
}

int Tetromino::getFurthestLeft() const
{
    int furthest = cols[0];
    if (cols[1] < furthest) furthest = cols[1];
    if (cols[2] < furthest) furthest = cols[2];
    if (cols[3] < furthest) furthest = cols[3];    
    return furthest;
}

int Tetromino::getFurthestDown() const
{
    int furthest = rows[0];
    if (rows[1] > furthest) furthest = rows[1];
    if (rows[2] > furthest) furthest = rows[2];
    if (rows[3] > furthest) furthest = rows[3];     
    return furthest;
}
    
// Getters
TetrominoType_e Tetromino::getType() const
{
    return type;
}

int Tetromino::getRow(int n) const
{
    return rows[n];
}

int Tetromino::getCol(int n) const
{
    return cols[n];
}
