#include <sstream>

#include "TetrominoUI.hpp"

TetrominoUI::TetrominoUI(TetrominoModel& newModel)
    : model(newModel)
{
}

sf::Color TetrominoUI::getColorByGrid(Grid_t placed, int row, int col)
{
    if (!model.getIsRunning() || row < 4)
        return DEAD_ZONE_COLOR;
    else
        return getColorByType(placed[row][col]);
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
    sf::Font font;
    font.loadFromFile(FONT_PATH);
    
    while (window.isOpen())
    {
        if (model.getIsRunning())
            model.update();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (!model.getIsRunning())
                {
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        model.start();
                    }
                }
                else
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
                    
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        model.moveActive(TETROMINO_MOVE_DROP);
                    }
                    
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        model.moveActive(TETROMINO_MOVE_ROTATE);
                    }
                    
                    if (event.key.code == sf::Keyboard::LAlt)
                    {
                        model.moveActive(TETROMINO_MOVE_HOLD);
                    }
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
                rect.setFillColor(getColorByGrid(placed, row, col));
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
                rect.setOutlineThickness(1);
                rect.setOutlineColor(getColorByType(activeDropped.getType()));
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
        
        // Draw next
        Tetromino next = model.getNext();
        if (next.getType() != TETROMINO_TYPE_EMPTY)
        {
            for (int block = 0; block <= 3; ++block)
            {
                sf::RectangleShape rect(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
                rect.setFillColor(getColorByType(next.getType()));
                rect.setOutlineThickness(1);
                rect.setOutlineColor(GRID_COLOR);
                rect.setPosition(300 + (next.getCol(block) * SQUARE_SIZE), 
                                 100 + (next.getRow(block) * SQUARE_SIZE));
                window.draw(rect);
            }
        }
        
        // Draw hold
        Tetromino hold = model.getHold();
        if (hold.getType() != TETROMINO_TYPE_EMPTY)
        {
            for (int block = 0; block <= 3; ++block)
            {
                sf::RectangleShape rect(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
                rect.setFillColor(getColorByType(hold.getType()));
                rect.setOutlineThickness(1);
                rect.setOutlineColor(GRID_COLOR);
                rect.setPosition(300 + (hold.getCol(block) * SQUARE_SIZE), 
                                 300 + (hold.getRow(block) * SQUARE_SIZE));
                window.draw(rect);
            }
        }
        
        // Draw text
        sf::Text lines;
        lines.setFont(font);
        lines.setColor(GRID_COLOR);

        lines.setString("Next:");
        lines.setPosition(340, 40);
        window.draw(lines);

        lines.setString("Hold:");
        lines.setPosition(340, 240);
        window.draw(lines);
        
        lines.setString("Level:");
        lines.setPosition(340, 530);
        window.draw(lines);
        
        std::stringstream ss;
        ss << model.getLevel();
        lines.setString(ss.str());
        lines.setPosition(340, 560);
        window.draw(lines);

        lines.setString("Lines Cleared:");
        lines.setPosition(340, 600);
        window.draw(lines);
        
        std::stringstream ss2;
        ss2 << model.getClearedLines();
        lines.setString(ss2.str());
        lines.setPosition(340, 630);
        window.draw(lines);
        
        lines.setString("Score:");
        lines.setPosition(340, 670);
        window.draw(lines);
        
        std::stringstream ss3;
        ss3 << model.getScore();
        lines.setString(ss3.str());
        lines.setPosition(340, 700);
        window.draw(lines);
        
        // Display press space to start
        if (!model.getIsRunning())
        {
            lines.setString("Press space to start");
            lines.setPosition(150, 750);
            window.draw(lines);
        }
        
        window.display();
    }
}
