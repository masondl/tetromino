#include <cstdio>
#include <cstdlib>
#include <ctime>

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
           (placed[Tetromino.getRow(0)+1][Tetromino.getCol(0)] != TETROMINO_TYPE_EMPTY) ||
           (placed[Tetromino.getRow(1)+1][Tetromino.getCol(1)] != TETROMINO_TYPE_EMPTY) ||
           (placed[Tetromino.getRow(2)+1][Tetromino.getCol(2)] != TETROMINO_TYPE_EMPTY) ||
           (placed[Tetromino.getRow(3)+1][Tetromino.getCol(3)] != TETROMINO_TYPE_EMPTY));
}

void TetrominoModel::clearFullLines()
{
    for (int row = GRID_HEIGHT-1; row >= 0; --row)
    {
        if (isRowFull(placed[row]))
        {
            shiftDown(row);
        }
    }
}

bool TetrominoModel::isRowFull(const GridRow_t& row)
{
    for (int rowIndex = 0; rowIndex < GRID_WIDTH; ++rowIndex)
    {
        if (row[rowIndex] == TETROMINO_TYPE_EMPTY)
        {
            return false;
        }
    }
    
    return true;
}

bool TetrominoModel::isRowOccupied(const GridRow_t& row)
{
    for (int rowIndex = 0; rowIndex < GRID_WIDTH; ++rowIndex)
    {
        if (row[rowIndex] != TETROMINO_TYPE_EMPTY)
        {
            return true;
        }
    }
    
    return false;
}

void TetrominoModel::shiftDown(const int baseIndex)
{
    int topIndex = getHighestOccupiedRow();
    for (int row = baseIndex; row >= topIndex; --row)
    {
        placed[row] = placed[row-1];
    }
}

int  TetrominoModel::getHighestOccupiedRow()
{
    for (int row = 0; row < GRID_HEIGHT; ++row)
    {
        if (isRowOccupied(placed[row]))
        {
            return row;
        }
    }
    
    return -1;
}

TetrominoModel::TetrominoModel() 
    : active(TETROMINO_TYPE_EMPTY),
      activeDropped(TETROMINO_TYPE_EMPTY)
{
    hasActive = false;
    isRuning  = false;
    
    for (int row = 0; row < GRID_HEIGHT; ++row)
    {
        for (int col = 0; col < GRID_WIDTH; ++col)
        {
            placed[row][col] = TETROMINO_TYPE_EMPTY;
        }
    }
}

const bool TetrominoModel::getHasActive() const
{
    return hasActive;
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
    srand( time(NULL) );
}

void TetrominoModel::update()
{
    sf::Time elapsed = clock.getElapsedTime();
    // Advance game every 1 second.
    // TODO: drop this time interval as game level increases
    if (isRuning && (elapsed.asMilliseconds() > 1000))
    {
        if (!hasActive)
        {
            // If there is no active tetromino, start dropping a new one.
            // Select a random type
            int index = rand() % TETROMINO_TYPES_SIZE;
            active = Tetromino(TETROMINO_TYPES[index]);
            hasActive = true;
        }
        else
        {
            if (isAtBottom(active))
            {
                moveToPlaced(active);
                hasActive = false;
                clearFullLines();
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
    if (hasActive)
    {
        switch (move)
        {
            case TETROMINO_MOVE_LEFT:
                if (active.getFurthestLeft() > 0)
                {
                    active.moveLeft();
                }
                break;
                
            case TETROMINO_MOVE_RIGHT:
                if (active.getFurthestRight() < GRID_WIDTH-1)
                {
                    active.moveRight();
                }
                break;
                
            case TETROMINO_MOVE_DOWN:
                if (!isAtBottom(active))
                {
                    active.moveDown();
                }
                break;
                
            default:
                printf("Unkown move! %d\n", 
                       static_cast<int>(move));
        }
    }
}
