all: Main
	
Tetromino.o: Tetromino.cpp Tetromino.hpp
	g++ -c -std=c++11 Tetromino.cpp -o Tetromino.o

TetrominoModel.o: TetrominoModel.cpp TetrominoModel.hpp
	g++ -c -std=c++11 TetrominoModel.cpp -o TetrominoModel.o

TetrominoUI.o: TetrominoUI.cpp TetrominoUI.hpp
	g++ -c -std=c++11 TetrominoUI.cpp -o TetrominoUI.o

Main: Tetromino.o TetrominoModel.o TetrominoUI.o main.cpp
	g++ -o Tetromino -std=c++11 main.cpp Tetromino.o TetrominoModel.o TetrominoUI.o \
	-lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm Tetromino Tetromino.o TetrominoModel.o TetrominoUI.o
