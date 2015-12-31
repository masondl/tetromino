#include <SFML/Graphics.hpp>

#include "TetrominoUI.hpp"

const int SQUARE_SIZE = 30;
const int GRID_OFFSET = 20;

// COLORS
const sf::Color BACKGROUND_COLOR = sf::Color(191, 212, 219);

TetrominoUI::TetrominoUI(TetrominoModel& newModel)
    : model(newModel)
{
}

void TetrominoUI::run()
{
    sf::RenderWindow window(sf::VideoMode(600, 800), "Tetromino");
    
    model.start();
    while (window.isOpen())
    {
        model.update();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Right)
                {
                    model.moveActive(Tetromino_MOVE_RIGHT);
                }
                
                if (event.key.code == sf::Keyboard::Left)
                {
                    model.moveActive(Tetromino_MOVE_LEFT);
                }
                
                if (event.key.code == sf::Keyboard::Down)
                {
                    model.moveActive(Tetromino_MOVE_DOWN);
                }
            }
            
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        window.clear(BACKGROUND_COLOR);
        
        // Draw grid
        Grid_t placed = model.getPlaced();
        for (int row = 0; row < GRID_HEIGHT; ++row)
        {
            for (int col = 0; col < GRID_WIDTH; ++col)
            {
                sf::RectangleShape rect(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
                
                switch (placed[row][col])
                {
                    case Tetromino_TYPE_O:
                        rect.setFillColor(sf::Color::Yellow);
                        break;
                        
                    case Tetromino_TYPE_EMPTY:
                    default:
                        rect.setFillColor(BACKGROUND_COLOR);
                        break;
                }
                
                rect.setOutlineThickness(1);
                rect.setOutlineColor(sf::Color::Black);
                rect.setPosition(GRID_OFFSET + (col * SQUARE_SIZE), 
                                 GRID_OFFSET + (row * SQUARE_SIZE));
                window.draw(rect);
            }
        }
        
        // Draw dropped active block
        Tetromino activeDropped = model.getActiveDropped();
        for (int block = 0; block <= 3; ++block)
        {
            sf::RectangleShape rect(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            rect.setFillColor(sf::Color::Black);
            rect.setPosition(GRID_OFFSET + (activeDropped.getCol(block) * SQUARE_SIZE), 
                             GRID_OFFSET + (activeDropped.getRow(block) * SQUARE_SIZE));
            window.draw(rect);
        }
        
        // Draw active block
        Tetromino active = model.getActive();
        for (int block = 0; block <= 3; ++block)
        {
            sf::RectangleShape rect(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            rect.setFillColor(sf::Color::Yellow);
            rect.setOutlineThickness(1);
            rect.setOutlineColor(sf::Color::Black);
            rect.setPosition(GRID_OFFSET + (active.getCol(block) * SQUARE_SIZE), 
                             GRID_OFFSET + (active.getRow(block) * SQUARE_SIZE));
            window.draw(rect);
        }
        
        window.display();
    }
}
