#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "TetrominoModel.hpp"

void TetrominoModel::moveToBottom(Tetromino& tetromino)
{
    while (!isAtBottom(tetromino))
    {
        tetromino.moveDown();
    }
}

void TetrominoModel::moveToPlaced(const Tetromino& tetromino)
{
    TetrominoType_e type = tetromino.getType();
    placed[tetromino.getRow(0)][tetromino.getCol(0)] = type;
    placed[tetromino.getRow(1)][tetromino.getCol(1)] = type;
    placed[tetromino.getRow(2)][tetromino.getCol(2)] = type;
    placed[tetromino.getRow(3)][tetromino.getCol(3)] = type;
}

bool TetrominoModel::isAtBottom(const Tetromino& tetromino)
{
    // At bottom if we are literally at bottom of grid...
    // or if we have hit another placed piece
    return ((tetromino.getFurthestDown() == GRID_HEIGHT-1) ||
           (placed[tetromino.getRow(0)+1][tetromino.getCol(0)] != TETROMINO_TYPE_EMPTY) ||
           (placed[tetromino.getRow(1)+1][tetromino.getCol(1)] != TETROMINO_TYPE_EMPTY) ||
           (placed[tetromino.getRow(2)+1][tetromino.getCol(2)] != TETROMINO_TYPE_EMPTY) ||
           (placed[tetromino.getRow(3)+1][tetromino.getCol(3)] != TETROMINO_TYPE_EMPTY));
}

void TetrominoModel::clearFullLines()
{
    int combo = 0;
    for (int row = GRID_HEIGHT-1; row >= 0; --row)
    {
        if (isRowFull(placed[row]))
        {
            shiftDown(row);
            ++row; // We need to check the same row again in the loop
            ++clearedLines;
            ++ combo;
            if (clearedLines <= 100 && 
                (clearedLines % 10 == 0))
            {
                ++level;
            }
        }
    }
    
    while (combo > 0)
    {
        score += (combo * 100);
        --combo;
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

int TetrominoModel::getHighestOccupiedRow()
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

void TetrominoModel::moveInBounds(Tetromino& tetromino)
{
    while (tetromino.getFurthestLeft() < 0)
    {
        tetromino.moveRight();
    }
    
    while (tetromino.getFurthestRight() >= GRID_WIDTH)
    {
        tetromino.moveLeft();
    }
    
    while (tetromino.getFurthestDown() >= GRID_HEIGHT)
    {
        tetromino.moveUp();
    }
}

bool TetrominoModel::isValid(Tetromino& tetromino)
{
    return (placed[tetromino.getRow(0)][tetromino.getCol(0)] == TETROMINO_TYPE_EMPTY) &&
           (placed[tetromino.getRow(1)][tetromino.getCol(1)] == TETROMINO_TYPE_EMPTY) &&
           (placed[tetromino.getRow(2)][tetromino.getCol(2)] == TETROMINO_TYPE_EMPTY) &&
           (placed[tetromino.getRow(3)][tetromino.getCol(3)] == TETROMINO_TYPE_EMPTY);
}

TetrominoModel::TetrominoModel() 
    : active(TETROMINO_TYPE_EMPTY),
      next(TETROMINO_TYPE_EMPTY),
      hold(TETROMINO_TYPE_EMPTY),
      activeDropped(TETROMINO_TYPE_EMPTY)
{
    clearedLines = 0;
    score = 0;
    level = 0;
    hasActive = false;
    isRunning  = false;
    hasHeld = false;
    
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

const Tetromino& TetrominoModel::getNext() const
{
    return next;
}

const Grid_t& TetrominoModel::getPlaced() const
{
    return placed;
}

const Tetromino& TetrominoModel::getActiveDropped() const
{
    return activeDropped;
}

const Tetromino& TetrominoModel::getHold() const
{
    return hold;
}

const int TetrominoModel::getClearedLines() const
{
    return clearedLines;
}

const long TetrominoModel::getScore() const
{
    return score;
}

const bool TetrominoModel::getIsRunning() const
{
    return isRunning;
}

const int TetrominoModel::getLevel() const
{
    return level;
}

void TetrominoModel::start()
{
    clock.restart();
    srand( time(NULL) );
    
    int index = rand() % TETROMINO_TYPES_SIZE;
    next = Tetromino(TETROMINO_TYPES[index]);
    hold = Tetromino(TETROMINO_TYPE_EMPTY);
    
    for (int row = 0; row < GRID_HEIGHT; ++row)
    {
        for (int col = 0; col < GRID_WIDTH; ++col)
        {
            placed[row][col] = TETROMINO_TYPE_EMPTY;
        }
    }
    
    clearedLines = 0;
    score = 0;
    level = 1;
    isRunning = true;
    hasHeld = false;
}

void TetrominoModel::checkGameOver()
{
    if (isRowOccupied(placed[3]))
    {
        isRunning = false;
        hasActive = false;
        next = Tetromino(TETROMINO_TYPE_EMPTY);
        hold = Tetromino(TETROMINO_TYPE_EMPTY);
    }
}

void TetrominoModel::update()
{
    checkGameOver();
    sf::Time elapsed = clock.getElapsedTime();
    // Advance game every 1 second.
    // TODO: drop this time interval as game level increases
    if (isRunning)
    {
        if (!hasActive)
        {
            // If there is no active tetromino, start dropping a new one.
            // Select a random type
            int index = rand() % TETROMINO_TYPES_SIZE;
            active = next; 
            next = Tetromino(TETROMINO_TYPES[index]);
            hasActive = true;
            hasHeld = false;
        }
        else if (isAtBottom(active))
        {
            moveToPlaced(active);
            hasActive = false;
            clearFullLines();
        }
        else if (elapsed.asMilliseconds() > SPEEDS[level-1])
        {
            active.moveDown();
            
            clock.restart();
        }
        
        activeDropped = active;
        moveToBottom(activeDropped); 
    }
    else if (isRunning && hasActive)
    {
        activeDropped = active;
        moveToBottom(activeDropped);   
    }
}

void TetrominoModel::moveActive(TetrominoMove_e move)
{
    if (hasActive)
    {
        Tetromino moved = active;
        switch (move)
        {
            case TETROMINO_MOVE_LEFT:
                if (moved.getFurthestLeft() > 0)
                {
                    moved.moveLeft();
                }
                break;
                
            case TETROMINO_MOVE_RIGHT:
                if (moved.getFurthestRight() < GRID_WIDTH-1)
                {
                    moved.moveRight();
                }
                break;
                
            case TETROMINO_MOVE_DOWN:
                if (!isAtBottom(moved))
                {
                    moved.moveDown();
                    score += 1;
                }
                break;
            
            case TETROMINO_MOVE_ROTATE:
                moved.rotate();
                // Make sure the rotation hasn't moved it out of bounds
                moveInBounds(moved);
                break;
                
            case TETROMINO_MOVE_DROP:
                score += (GRID_HEIGHT - moved.getFurthestDown());
                moveToBottom(moved);
                break;
                
            case TETROMINO_MOVE_HOLD:
                if (!hasHeld)
                {
                    if (hold.getType() == TETROMINO_TYPE_EMPTY)
                    {
                        hold = Tetromino(moved.getType());
                        hasActive = false;
                    }
                    else
                    {
                        TetrominoType_e holdType = hold.getType();
                        hold   = Tetromino(moved.getType());
                        moved  = Tetromino(holdType);
                    }
                    hasHeld = true;
                }
                break;
                
            default:
                printf("Unkown move! %d\n", 
                       static_cast<int>(move));
        }
        
        if (isValid(moved))
        {
            active = moved;
        }
    }
}
