#include <iostream>
#include "Sudoku.h"
#include "GlobalVars.h"
using namespace std;
Sudoku sudoku;

int player1Board[SIZE*SIZE] = {0};
int player2Board[SIZE*SIZE] = {0};

int main()
{
    sudoku.printBoard(player1Board);
}