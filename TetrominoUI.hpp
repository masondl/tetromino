#ifndef _Tetromino_UI_H
#define _Tetromino_UI_H

#include "TetrominoModel.hpp"

class TetrominoUI
{
    private:
    TetrominoModel& model;
    
    public:
    TetrominoUI(TetrominoModel& newModel);
    void run();
};

#endif
