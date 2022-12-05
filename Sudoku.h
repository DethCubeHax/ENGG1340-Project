#ifndef SUDOKU_H
#define SUDOKU_H
#include "GlobalVars.h"

class Sudoku
{
    public:
        void welcome();
        int gameHandler(int (&board)[SIZE][SIZE]);
        void finalScreen(int (&board)[SIZE][SIZE]);
        void showInstruction();
        bool numberIsPossible(int number, int x, int y, int (&board)[SIZE][SIZE]);
        void printBoard(int (&board)[SIZE][SIZE]);
        void readOrSaveBoard(int (&board)[SIZE][SIZE], char args);
        void generateBoard (int (&board)[SIZE][SIZE]);
        bool solveBoard(int (&board)[SIZE][SIZE]);
        void printList(BoardState *playerHead, BoardState *computerHead);
        void loadList(BoardState *&head, int (&board)[SIZE][SIZE]);
    private:
        bool checkRow(int number, int y, int (&board)[SIZE][SIZE]);
        bool checkColumn(int number, int x, int (&board)[SIZE][SIZE]);
        bool checkBlock(int number, int x, int y, int (&board)[SIZE][SIZE]);
        void addToList(BoardState *&head, int (&board)[SIZE][SIZE]);
        void copyBoard(int (&board1)[SIZE][SIZE], int (&board2)[SIZE][SIZE]);
        void eraseBoard(int (&board)[SIZE][SIZE]);
        void eraseList(BoardState *&head);
        void cursorInputHandler(string control);
        void toLowerCase(string &str);
        bool isSolved(int (&board)[SIZE][SIZE]);
        void saveBoard(int (&board)[SIZE][SIZE], string file);
        
};

#endif