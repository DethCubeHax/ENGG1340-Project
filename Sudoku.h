#ifndef SUDOKU_H
#define SUDOKU_H
#include "GlobalVars.h"

class Sudoku
{
    public:
        bool numberIsPossible(int number, int x, int y, int (&board)[SIZE][SIZE]);
        void printBoard(int (&board)[SIZE][SIZE]);
        void readOrSaveBoard(int (&board)[SIZE][SIZE], char args);
        void generateBoard (int (&board)[SIZE][SIZE]);
        bool solveBoard(int (&board)[SIZE][SIZE]);
    private:
        bool checkRow(int number, int y, int (&board)[SIZE][SIZE]);
        bool checkColumn(int number, int x, int (&board)[SIZE][SIZE]);
        bool checkBlock(int number, int x, int y, int (&board)[SIZE][SIZE]);
};

#endif