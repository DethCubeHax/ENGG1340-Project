#ifndef SUDOKU_H
#define SUDOKU_H
#include "GlobalVars.h"

class Sudoku
{
    public:
        bool numberIsPossible(int number, int x, int y, int (&board)[SIZE]);
        void printBoard(int (&board)[SIZE]);
        void readBoard(int (&board)[SIZE]);
    private:
        bool checkRow();
        bool checkColumn();
        bool checkBlock();
};

#endif