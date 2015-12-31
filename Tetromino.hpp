#ifndef _Tetromino_H
#define _Tetromino_H

// The different types of Tetrominos - 
// note: must also be added to next array to appear in game!
enum TetrominoType_e
{
    Tetromino_TYPE_EMPTY,
    
    /* 
     * XX
     * XX
     */ 
    Tetromino_TYPE_O,
    
    /* 
     * X
     * XX
     * X
     */ 
    Tetromino_TYPE_T
};



class Tetromino
{
    private:
    TetrominoType_e type;
    // Coordinates of each block
    int rows[4];
    int cols[4];
    
    public:
    Tetromino(TetrominoType_e newType);
    void moveDown();
    void moveRight();
    void moveLeft();
    
    int getFurthestRight() const;
    int getFurthestLeft() const;
    int getFurthestDown() const;
    
    // Getters
    TetrominoType_e getType() const;
    int getRow(int n) const;
    int getCol(int n) const;
};

#endif
