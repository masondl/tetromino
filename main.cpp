#include <cstdlib>

#include "TetrominoModel.hpp"
#include "TetrominoUI.hpp"

int main(int argc, char* argv[])
{
    TetrominoModel model;
    TetrominoUI    ui(model);
    
    ui.run();
    return EXIT_SUCCESS;
}
