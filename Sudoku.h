#ifndef SUDOKU_H
#define SUDOKU_H
#include "GlobalVars.h"

class Sudoku
{
    public:
        bool numberIsPossible(int number, int x, int y, int (&board)[SIZE][SIZE]);
        void printBoard(int (&board)[SIZE][SIZE]);
        void readBoard(int (&board)[SIZE][SIZE]);
        void generateBoard (int (&board)[SIZE][SIZE]);
    private:
        bool checkRow(int number, int x, int y, int (&board)[SIZE][SIZE]);
        bool checkColumn(int number, int x, int y, int (&board)[SIZE][SIZE]);
        bool checkBlock(int number, int x, int y, int (&board)[SIZE][SIZE]);
};

#endif