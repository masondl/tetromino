#ifndef _TETROMINO_UI_H
#define _TETROMINO_UI_H

#include <SFML/Graphics.hpp>

#include "TetrominoModel.hpp"

class TetrominoUI
{
    private:
    TetrominoModel& model;
    sf::Color getColorByType(TetrominoType_e type);
    
    public:
    TetrominoUI(TetrominoModel& newModel);
    void run();
};

#endif
