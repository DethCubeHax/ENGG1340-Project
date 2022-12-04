#include <iostream>
#include "Sudoku.h"
#include "GlobalVars.h"
using namespace std;
Sudoku sudoku;

int player1Board[SIZE][SIZE] = {0};
int tmpBoard[SIZE][SIZE] = {0};

int main()
{
    sudoku.generateBoard(player1Board);
    sudoku.printBoard(player1Board);
    sudoku.readOrSaveBoard(player1Board, 'w');
}