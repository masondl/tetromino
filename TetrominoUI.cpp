#include "TetrominoUI.hpp"

const int SQUARE_SIZE = 30;
const int GRID_OFFSET = 20;

// COLORS
const sf::Color BACKGROUND_COLOR = sf::Color(191, 212, 219);
const sf::Color GRID_COLOR       = sf::Color::Black; 
const sf::Color O_COLOR          = sf::Color::Yellow;
const sf::Color T_COLOR          = sf::Color::Magenta; 
const sf::Color I_COLOR          = sf::Color(48, 150, 145);
const sf::Color S_COLOR          = sf::Color::Red; 
const sf::Color Z_COLOR          = sf::Color::Blue;
const sf::Color L_COLOR          = sf::Color::Green; 
const sf::Color J_COLOR          = sf::Color(255, 132, 0);

TetrominoUI::TetrominoUI(TetrominoModel& newModel)
    : model(newModel)
{
}

sf::Color TetrominoUI::getColorByType(TetrominoType_e type)
{
    switch (type)
    {
        case TETROMINO_TYPE_O:
            return O_COLOR;
            
        case TETROMINO_TYPE_T:
            return T_COLOR;
        
        case TETROMINO_TYPE_I:
            return I_COLOR;
            
        case TETROMINO_TYPE_S:
            return S_COLOR;
        
        case TETROMINO_TYPE_Z:
            return Z_COLOR;
            
        case TETROMINO_TYPE_L:
            return L_COLOR;
        
        case TETROMINO_TYPE_J:
            return J_COLOR;
            
        case TETROMINO_TYPE_EMPTY:
        default:
            return BACKGROUND_COLOR;
    }
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
                    model.moveActive(TETROMINO_MOVE_RIGHT);
                }
                
                if (event.key.code == sf::Keyboard::Left)
                {
                    model.moveActive(TETROMINO_MOVE_LEFT);
                }
                
                if (event.key.code == sf::Keyboard::Down)
                {
                    model.moveActive(TETROMINO_MOVE_DOWN);
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
                rect.setFillColor(getColorByType(placed[row][col]));
                rect.setOutlineThickness(1);
                rect.setOutlineColor(GRID_COLOR);
                rect.setPosition(GRID_OFFSET + (col * SQUARE_SIZE), 
                                 GRID_OFFSET + (row * SQUARE_SIZE));
                window.draw(rect);
            }
        }
        
        if (model.getHasActive())
        {
            // Draw dropped active block
            Tetromino activeDropped = model.getActiveDropped();
            for (int block = 0; block <= 3; ++block)
            {
                sf::RectangleShape rect(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
                rect.setFillColor(GRID_COLOR);
                rect.setPosition(GRID_OFFSET + (activeDropped.getCol(block) * SQUARE_SIZE), 
                                 GRID_OFFSET + (activeDropped.getRow(block) * SQUARE_SIZE));
                window.draw(rect);
            }
            
            // Draw active block
            Tetromino active = model.getActive();
            for (int block = 0; block <= 3; ++block)
            {
                sf::RectangleShape rect(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
                rect.setFillColor(getColorByType(active.getType()));
                rect.setOutlineThickness(1);
                rect.setOutlineColor(GRID_COLOR);
                rect.setPosition(GRID_OFFSET + (active.getCol(block) * SQUARE_SIZE), 
                                 GRID_OFFSET + (active.getRow(block) * SQUARE_SIZE));
                window.draw(rect);
            }
        }
        
        window.display();
    }
}
