#ifndef _TETROMINO_H
#define _TETROMINO_H

// The different types of Tetrominos - 
// note: must also be added to next array to appear in game!
enum TetrominoType_e
{
    TETROMINO_TYPE_EMPTY,
    
    /* 
     * XX
     * XX
     */ 
    TETROMINO_TYPE_O,
    
    /* 
     * X
     * XX
     * X
     */ 
    TETROMINO_TYPE_T,
    
    /* 
     * X
     * X
     * X
     * X
     */ 
    TETROMINO_TYPE_I,
    
    /* 
     * X   X
     * XX XX
     *  X X
     */ 
    TETROMINO_TYPE_S,
    TETROMINO_TYPE_Z,
    
    /* 
     * X   X
     * X   X
     * XX XX
     */ 
    TETROMINO_TYPE_L,
    TETROMINO_TYPE_J
};

const TetrominoType_e TETROMINO_TYPES[] = { TETROMINO_TYPE_O,
                                            TETROMINO_TYPE_T,
                                            TETROMINO_TYPE_I,
                                            TETROMINO_TYPE_S,
                                            TETROMINO_TYPE_Z,
                                            TETROMINO_TYPE_L,
                                            TETROMINO_TYPE_J };
const size_t TETROMINO_TYPES_SIZE = 
    (sizeof(TETROMINO_TYPES) / sizeof(TetrominoType_e));

class Tetromino
{
    private:
    TetrominoType_e type;
    // Coordinates of each block
    int rows[4];
    int cols[4];
    
    public:
    Tetromino(TetrominoType_e newType);
    
    // Move the Tetromino in the specified direction.
    // It is the callers responsibility to make sure the move is valid.
    void moveDown();
    void moveRight();
    void moveLeft();
    
    // Get the furthest occupied row/col in a particular direction.
    int getFurthestRight() const;
    int getFurthestLeft() const;
    int getFurthestDown() const;
    
    // Getters.
    // n is block number, 0 - 3. 
    // Calling with an int other than 0 thru 3 is undefined.
    TetrominoType_e getType() const;
    int getRow(int n) const;
    int getCol(int n) const;
};

#endif
