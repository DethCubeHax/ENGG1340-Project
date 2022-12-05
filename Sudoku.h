// If this header file is not defined, define it
#ifndef SUDOKU_H
#define SUDOKU_H
// Includes
#include "GlobalVars.h"

// Class to define the function prototypes of the Sudoku game
// These functions are defined in Sudoku.cpp
class Sudoku
{
    public:
        void welcome();
        void toLowerCase(string &str);
        int gameHandler(int (&board)[SIZE][SIZE]);
        void finalScreen(int (&board)[SIZE][SIZE]);
        void showInstruction();
        bool numberIsPossible(int number, int x, int y, int (&board)[SIZE][SIZE]);
        void printBoard(int (&board)[SIZE][SIZE]);
        void readOrSaveBoard(int (&board)[SIZE][SIZE], char args);
        void generateBoard (int (&board)[SIZE][SIZE]);
        bool solveBoard(int (&board)[SIZE][SIZE]);
        void printList(BoardState *playerHead, BoardState *computerHead);
        void loadList(BoardState *&head, int (&board)[SIZE][SIZE], string fileName, int &steps);
        void saveBoard(int (&board)[SIZE][SIZE], BoardState *&head, string file);
        
    private:
        bool checkRow(int number, int y, int (&board)[SIZE][SIZE]);
        bool checkColumn(int number, int x, int (&board)[SIZE][SIZE]);
        bool checkBlock(int number, int x, int y, int (&board)[SIZE][SIZE]);
        void addToList(BoardState *&head, int (&board)[SIZE][SIZE]);
        void copyBoard(int (&board1)[SIZE][SIZE], int (&board2)[SIZE][SIZE]);
        void eraseBoard(int (&board)[SIZE][SIZE]);
        void eraseList(BoardState *&head);
        void cursorInputHandler(string control);
        bool isSolved(int (&board)[SIZE][SIZE]);   
};

#endif