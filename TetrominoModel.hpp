#ifndef _Tetromino_MODEL_H
#define _Tetromino_MODEL_H

#include <array>
#include <SFML/System.hpp>
#include "Tetromino.hpp"

enum TetrominoMove_e
{
    Tetromino_MOVE_LEFT,
    Tetromino_MOVE_RIGHT,
    Tetromino_MOVE_DOWN
//    Tetromino_MOVE_DROP
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
    void moveToPlaced(const Tetromino& Tetromino);
    bool isAtBottom(const Tetromino& Tetromino);

    public:
    TetrominoModel();
    
    // Methods for getting the game state
    const Tetromino& getActive() const;
    const Grid_t& getPlaced() const;
    // Get a Tetromino representing where the active brick would be if dropped
    const Tetromino& getActiveDropped() const;
    
    // Modifying game state
    void start();
    void update();
    void moveActive(TetrominoMove_e move);
};

#endif
