#include <iostream>
#include "Sudoku.h"
#include "GlobalVars.h"
using namespace std;
Sudoku sudoku;

int player1Board[SIZE][SIZE] = {0};
int player2Board[SIZE][SIZE] = {0};

int main()
{
    sudoku.readBoard(player1Board);
    sudoku.generateBoard(player1Board);
    //sudoku.printBoard(player1Board);
    //cout << "-----------------" << endl;
    //sudoku.solveBoard(player1Board, 0, 0);
    sudoku.printBoard(player1Board);
}