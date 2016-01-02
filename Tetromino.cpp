#include <cstdio>

#include "Tetromino.hpp"

Tetromino::Tetromino(TetrominoType_e newType)
{
    type = newType;
    rotation = ROTATION_UP;
    switch (type)
    {
        case TETROMINO_TYPE_O:
            rows[0] = 0; cols[0] = 4;
            rows[1] = 0; cols[1] = 5;
            rows[2] = 1; cols[2] = 4;
            rows[3] = 1; cols[3] = 5;
            break;
            
        case TETROMINO_TYPE_T:
            rows[0] = 0; cols[0] = 4;
            rows[1] = 1; cols[1] = 4;
            rows[2] = 2; cols[2] = 4;
            rows[3] = 1; cols[3] = 5;
            break;
            
        case TETROMINO_TYPE_I:
            rows[0] = 0; cols[0] = 4;
            rows[1] = 1; cols[1] = 4;
            rows[2] = 2; cols[2] = 4;
            rows[3] = 3; cols[3] = 4;
            break;
            
        case TETROMINO_TYPE_S:
            rows[0] = 0; cols[0] = 4;
            rows[1] = 1; cols[1] = 4;
            rows[2] = 1; cols[2] = 5;
            rows[3] = 2; cols[3] = 5;
            break;
            
        case TETROMINO_TYPE_Z:
            rows[0] = 0; cols[0] = 5;
            rows[1] = 1; cols[1] = 4;
            rows[2] = 1; cols[2] = 5;
            rows[3] = 2; cols[3] = 4;
            break;
            
        case TETROMINO_TYPE_L:
            rows[0] = 0; cols[0] = 4;
            rows[1] = 1; cols[1] = 4;
            rows[2] = 2; cols[2] = 4;
            rows[3] = 2; cols[3] = 5;
            break;
            
        case TETROMINO_TYPE_J:
            rows[0] = 0; cols[0] = 5;
            rows[1] = 1; cols[1] = 5;
            rows[2] = 2; cols[2] = 5;
            rows[3] = 2; cols[3] = 4;
            break;
        
        case TETROMINO_TYPE_EMPTY:
            break;
            
        default:
            printf("Unkown type! %d\n", 
                   static_cast<int>(newType));
    }
}

void Tetromino::rotateT()
{
    /* 
     * 0            3      3
     * 13   013    01     012
     * 2     2      2
     */ 
    switch (rotation)
    {
        case ROTATION_UP:
            rows[0] = rows[0]+1; cols[0] = cols[0]-1;
            rotation = ROTATION_RIGHT;
            break;
            
        case ROTATION_RIGHT:
            rows[3] = rows[3]-1; cols[3] = cols[3]-1;
            rotation = ROTATION_DOWN;
            break;
        
        case ROTATION_DOWN:
            rows[2] = rows[2]-1; cols[2] = cols[2]+1;
            rotation = ROTATION_LEFT;
            break;
            
        case ROTATION_LEFT:
            rows[0] = rows[0]-1; cols[0] = cols[0]+1;
            rows[2] = rows[2]+1; cols[2] = cols[2]-1;
            rows[3] = rows[3]+1; cols[3] = cols[3]+1;
            rotation = ROTATION_UP;
            break;
            
        default:
            break;
    }
}

void Tetromino::rotateI()
{
    switch (rotation)
    {
        case ROTATION_UP:
            rows[0] = rows[0]+1; cols[0] = cols[0]+1;
            rows[2] = rows[2]-1; cols[2] = cols[2]+2;
            rows[3] = rows[3]-2; cols[3] = cols[3]+3;
            rotation = ROTATION_RIGHT;
            break;
            
        case ROTATION_RIGHT:
            rows[0] = rows[0]-1; cols[0] = cols[0]-1;
            rows[2] = rows[2]+1; cols[2] = cols[2]-2;
            rows[3] = rows[3]+2; cols[3] = cols[3]-3;
            rotation = ROTATION_UP;
            break;
            
        default:
            break;
    }
}

void Tetromino::rotateS()
{
    /* 
     * 0            
     * 12    12
     *  3   03
     */ 
    switch (rotation)
    {
        case ROTATION_UP:
            rows[0] = rows[0]+2; cols[0] = cols[0]-1;
            cols[3] = cols[3]-1;
            rotation = ROTATION_RIGHT;
            break;
            
        case ROTATION_RIGHT:
            rows[0] = rows[0]-2; cols[0] = cols[0]+1;
            cols[3] = cols[3]+1;
            rotation = ROTATION_UP;
            break;
            
        default:
            break;
    }
}

void Tetromino::rotateZ()
{
    /* 
     *  0            
     * 12  12
     * 3    03
     */ 
    switch (rotation)
    {
        case ROTATION_UP:
            rows[0] = rows[0]+2;
            cols[3] = cols[3]+2;
            rotation = ROTATION_RIGHT;
            break;
            
        case ROTATION_RIGHT:
            rows[0] = rows[0]-2;
            cols[3] = cols[3]-2;
            rotation = ROTATION_UP;
            break;
            
        default:
            break;
    }
}

void Tetromino::rotateL()
{
    /* 
     * 0                    0
     * 1    103    01     123
     * 23   2       2
     *              3
     */ 
    switch (rotation)
    {
        case ROTATION_UP:
            rows[0] = rows[0]+1; cols[0] = cols[0]+1;
            rows[3] = rows[3]-1; cols[3] = cols[3]+1;
            rotation = ROTATION_RIGHT;
            break;
            
        case ROTATION_RIGHT:
            cols[0] = cols[0]-2;
            rows[3] = rows[3]+2; cols[3] = cols[3]-2;
            rotation = ROTATION_DOWN;
            break;
        
        case ROTATION_DOWN:
            rows[0] = rows[0]-1; cols[0] = cols[0]+3;
            rows[2] = rows[2]-1; cols[2] = cols[2]+1;
            rows[3] = rows[3]-2; cols[3] = cols[3]+2;
            rotation = ROTATION_LEFT;
            break;
            
        case ROTATION_LEFT:
            cols[0] = cols[0]-2;
            rows[2] = rows[2]+1; cols[2] = cols[2]-1;
            rows[3] = rows[3]+1; cols[3] = cols[3]-1;
            rotation = ROTATION_UP;
            break;
            
        default:
            break;
    }
}

void Tetromino::rotateJ()
{
    /* 
     *  0   3               
     *  1   210    10     102
     * 32          2        3
     *             3
     */ 
    switch (rotation)
    {
        case ROTATION_UP:
            rows[0] = rows[0]+1; cols[0] = cols[0]+1;
            rows[2] = rows[2]-1; cols[2] = cols[2]-1;
            rows[3] = rows[3]-2;
            rotation = ROTATION_RIGHT;
            break;
            
        case ROTATION_RIGHT:
            rows[2] = rows[2]+1; cols[2] = cols[2]+1;
            rows[3] = rows[3]+3; cols[3] = cols[3]+1;
            rotation = ROTATION_DOWN;
            break;
        
        case ROTATION_DOWN:
            rows[2] = rows[2]-1; cols[2] = cols[2]+2;
            rows[3] = rows[3]-1; cols[3] = cols[3]+2;
            rotation = ROTATION_LEFT;
            break;
            
        case ROTATION_LEFT:
            rows[0] = rows[0]-1; cols[0] = cols[0]-1;
            rows[2] = rows[2]+1; cols[2] = cols[2]-2;
            cols[3] = cols[3]-3;
            rotation = ROTATION_UP;
            break;
            
        default:
            break;
    }
}

void Tetromino::moveDown()
{
    rows[0]++;
    rows[1]++;
    rows[2]++;
    rows[3]++; 
}

void Tetromino::moveUp()
{
    rows[0]--;
    rows[1]--;
    rows[2]--;
    rows[3]--; 
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

void Tetromino::rotate()
{
    switch (type)
    {
        case TETROMINO_TYPE_O:
            break;
            
        case TETROMINO_TYPE_T:
            rotateT();
            break;
            
        case TETROMINO_TYPE_I:
            rotateI();
            break;
            
        case TETROMINO_TYPE_S:
            rotateS();
            break;
            
        case TETROMINO_TYPE_Z:
            rotateZ();
            break;
            
        case TETROMINO_TYPE_L:
            rotateL();
            break;
            
        case TETROMINO_TYPE_J:
            rotateJ();
            break;
        
        case TETROMINO_TYPE_EMPTY:
            break;
            
        default:
            printf("Unkown type! %d\n", 
                   static_cast<int>(type));
    }
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
