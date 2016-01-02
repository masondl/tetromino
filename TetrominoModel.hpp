#ifndef _TETROMINO_MODEL_H
#define _TETROMINO_MODEL_H

#include <array>
#include <SFML/System.hpp>
#include "Tetromino.hpp"

enum TetrominoMove_e
{
    TETROMINO_MOVE_LEFT,
    TETROMINO_MOVE_RIGHT,
    TETROMINO_MOVE_DOWN,
    TETROMINO_MOVE_ROTATE,
    TETROMINO_MOVE_DROP,
    TETROMINO_MOVE_HOLD
};

const int GRID_WIDTH  = 10;
const int GRID_HEIGHT = 24;
const int SPEEDS[] = {800, 700, 600, 500, 400, 300, 200, 100, 50, 30};

typedef std::array<TetrominoType_e, GRID_WIDTH>  GridRow_t;
typedef std::array<GridRow_t,       GRID_HEIGHT> Grid_t;

class TetrominoModel
{
    private:
    bool isRunning;
    bool hasActive;
    Tetromino next;
    Tetromino active;
    Tetromino activeDropped;
    Tetromino hold;
    bool hasHeld;
    Grid_t placed;
    sf::Clock clock;
    int clearedLines;
    int level;
    long score;

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
    void checkGameOver();

    void moveInBounds(Tetromino& tetromino);
    bool isValid(Tetromino& tetromino);

    public:
    TetrominoModel();
    
    // Getters
    const bool getHasActive() const;
    const Tetromino& getActive() const;
    const Tetromino& getNext() const;
    const Tetromino& getHold() const;
    const Grid_t& getPlaced() const;
    // Get a Tetromino representing where the active brick would be if dropped
    const Tetromino& getActiveDropped() const;
    const int getClearedLines() const;
    const long getScore() const;
    const bool getIsRunning() const;
    const int getLevel() const;
    
    // start must be called once to start the game.
    void start();
    // update should be called before each frame is rendered to update the model.
    void update();
    // Move the active piece
    void moveActive(TetrominoMove_e move);
};

#endif
