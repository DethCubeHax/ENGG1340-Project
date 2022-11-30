#include "Sudoku.h"
#include "GlobalVars.h"

bool Sudoku::numberIsPossible(int number, int x, int y, int (&board)[SIZE])
{
    if (checkBlock(number, x, y, board) && checkColumn(number, x, y, board) && checkColumn(number, x, y, board)) return true;
}

void Sudoku::printBoard(int (&board)[SIZE])
{

}

void Sudoku::readBoard(int (&board)[SIZE])
{

}

bool Sudoku::checkRow(int number, int x, int y, int (&board)[SIZE])
{

}

bool Sudoku::checkColumn(int number, int x, int y, int (&board)[SIZE])
{

}

bool Sudoku::checkBlock(int number, int x, int y, int (&board)[SIZE])
{

}