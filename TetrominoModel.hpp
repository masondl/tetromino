#ifndef _TETROMINO_MODEL_H
#define _TETROMINO_MODEL_H

#include <array>
#include <SFML/System.hpp>
#include "Tetromino.hpp"

enum TetrominoMove_e
{
    TETROMINO_MOVE_LEFT,
    TETROMINO_MOVE_RIGHT,
    TETROMINO_MOVE_DOWN
//    TETROMINO_MOVE_DROP
};

const int GRID_WIDTH  = 10;
const int GRID_HEIGHT = 20;

typedef std::array<TetrominoType_e, GRID_WIDTH>  GridRow_t;
typedef std::array<GridRow_t,       GRID_HEIGHT> Grid_t;

class TetrominoModel
{
    private:
    bool isRuning;
    bool hasActive;
    Tetromino active;
    Tetromino activeDropped;
    Grid_t placed;
    sf::Clock clock;

    // Moves a Tetromino to the bottom
    void moveToBottom(Tetromino& Tetromino);
    // Moves a Tetromino to the placed grid - it is no longer active after this.
    void moveToPlaced(const Tetromino& Tetromino);
    // Checks if a Tetromio is at the bottom
    bool isAtBottom(const Tetromino& Tetromino);
    // Clears any full lines from the grid
    void clearFullLines();
    // Checks if a row is full
    bool isRowFull(const GridRow_t& row);
    void shiftDown(const int baseIndex);
    // Returns the highest row which is occupied by any placed piece. Undefined if none are occupied.
    int  getHighestOccupiedRow();
    bool isRowOccupied(const GridRow_t& row);

    public:
    TetrominoModel();
    
    // Getters
    const bool getHasActive() const;
    const Tetromino& getActive() const;
    const Grid_t& getPlaced() const;
    // Get a Tetromino representing where the active brick would be if dropped
    const Tetromino& getActiveDropped() const;
    
    // start must be called once to start the game.
    void start();
    // update should be called before each frame is rendered to update the model.
    void update();
    // Move the active piece
    void moveActive(TetrominoMove_e move);
};

#endif
