#include <iostream>
#include "Sudoku.h"
#include "GlobalVars.h"
using namespace std;
Sudoku sudoku;

int player1Board[SIZE][SIZE] = {0};
int player2Board[SIZE][SIZE] = {0};

int main()
{

    sudoku.readOrSaveBoard(player1Board, 'r');
    bool possible = sudoku.numberIsPossible(5, 2, 5, player1Board);
    if (possible) player1Board[2][5] = 5;
    cout<<possible<<endl;
    //sudoku.printBoard(player1Board);
    //cout << "-----------------" << endl;
    //sudoku.solveBoard(player1Board, 0, 0);
    sudoku.printBoard(player1Board);
}