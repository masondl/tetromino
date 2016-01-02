#ifndef _TETROMINO_UI_H
#define _TETROMINO_UI_H

#include <SFML/Graphics.hpp>

#include "TetrominoModel.hpp"

const char* const FONT_PATH = "/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-B.ttf";

const int SQUARE_SIZE = 30;
const int GRID_OFFSET = 20;

// COLORS
const sf::Color BACKGROUND_COLOR = sf::Color(191, 212, 219);
const sf::Color DEAD_ZONE_COLOR = sf::Color(255, 187, 173);
const sf::Color GRID_COLOR       = sf::Color::Black; 
const sf::Color O_COLOR          = sf::Color::Yellow;
const sf::Color T_COLOR          = sf::Color::Magenta; 
const sf::Color I_COLOR          = sf::Color(48, 150, 145);
const sf::Color S_COLOR          = sf::Color::Red; 
const sf::Color Z_COLOR          = sf::Color::Blue;
const sf::Color L_COLOR          = sf::Color::Green; 
const sf::Color J_COLOR          = sf::Color(255, 132, 0);

class TetrominoUI
{
    private:
    TetrominoModel& model;
    sf::Color getColorByType(TetrominoType_e type);
    sf::Color getColorByGrid(Grid_t placed, int row, int col);
    
    public:
    TetrominoUI(TetrominoModel& newModel);
    void run();
};

#endif
