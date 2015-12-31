#include <cstdio>

#include "TetrominoModel.hpp"

void TetrominoModel::moveToBottom(Tetromino& Tetromino)
{
    while (!isAtBottom(Tetromino))
    {
        Tetromino.moveDown();
    }
}

void TetrominoModel::moveToPlaced(const Tetromino& Tetromino)
{
    TetrominoType_e type = Tetromino.getType();
    placed[Tetromino.getRow(0)][Tetromino.getCol(0)] = type;
    placed[Tetromino.getRow(1)][Tetromino.getCol(1)] = type;
    placed[Tetromino.getRow(2)][Tetromino.getCol(2)] = type;
    placed[Tetromino.getRow(3)][Tetromino.getCol(3)] = type;
}

bool TetrominoModel::isAtBottom(const Tetromino& Tetromino)
{
    // At bottom if we are literally at bottom of grid...
    // or if we have hit another placed piece
    return ((Tetromino.getFurthestDown() == GRID_HEIGHT-1) ||
           (placed[Tetromino.getRow(0)+1][Tetromino.getCol(0)] != Tetromino_TYPE_EMPTY) ||
           (placed[Tetromino.getRow(1)+1][Tetromino.getCol(1)] != Tetromino_TYPE_EMPTY) ||
           (placed[Tetromino.getRow(2)+1][Tetromino.getCol(2)] != Tetromino_TYPE_EMPTY) ||
           (placed[Tetromino.getRow(3)+1][Tetromino.getCol(3)] != Tetromino_TYPE_EMPTY));
}

TetrominoModel::TetrominoModel() 
    : active(Tetromino_TYPE_EMPTY),
      activeDropped(Tetromino_TYPE_EMPTY)
{
    hasActive = false;
    isRuning  = false;
    
    for (int row = 0; row < GRID_HEIGHT; ++row)
    {
        for (int col = 0; col < GRID_WIDTH; ++col)
        {
            placed[row][col] = Tetromino_TYPE_EMPTY;
        }
    }
}

const Tetromino& TetrominoModel::getActive() const
{
    return active;
}

const Grid_t& TetrominoModel::getPlaced() const
{
    return placed;
}

const Tetromino& TetrominoModel::getActiveDropped() const
{
    return activeDropped;
}

void TetrominoModel::start()
{
    clock.restart();
    isRuning = true;
}

void TetrominoModel::update()
{
    sf::Time elapsed = clock.getElapsedTime();
    if (isRuning && (elapsed.asMilliseconds() > 1000))
    {
        if (!hasActive)
        {
            active = Tetromino(Tetromino_TYPE_O);
            hasActive = true;
        }
        else
        {
            if (isAtBottom(active))
            {
                moveToPlaced(active);
                hasActive = false;
            }
            else
            {
                active.moveDown();
            }
        }
        
        activeDropped = active;
        moveToBottom(activeDropped); 
        
        clock.restart();
    }
    else if (isRuning && hasActive)
    {
        activeDropped = active;
        moveToBottom(activeDropped);   
    }
}

void TetrominoModel::moveActive(TetrominoMove_e move)
{
    switch (move)
    {
        case Tetromino_MOVE_LEFT:
            if (active.getFurthestLeft() > 0)
            {
                active.moveLeft();
            }
            break;
            
        case Tetromino_MOVE_RIGHT:
            if (active.getFurthestRight() < GRID_WIDTH-1)
            {
                active.moveRight();
            }
            break;
            
        case Tetromino_MOVE_DOWN:
            if (active.getFurthestDown() < GRID_HEIGHT-1)
            {
                active.moveDown();
            }
            break;
            
        default:
            printf("Unkown move! %d\n", 
                   static_cast<int>(move));
    }
}
