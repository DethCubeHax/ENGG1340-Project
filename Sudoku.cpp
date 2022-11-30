#include <iostream>
#include "Sudoku.h"
#include "GlobalVars.h"
using namespace std;

bool Sudoku::numberIsPossible(int number, int x, int y, int (&board)[SIZE*SIZE])
{
    if (checkBlock(number, x, y, board) && checkColumn(number, x, y, board) && checkColumn(number, x, y, board)) return true;
}

void Sudoku::printBoard(int (&board)[SIZE*SIZE])
{
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            cout<<board[i+j]<<' ';
        }
        cout<<endl;
    }
}

void Sudoku::readBoard(int (&board)[SIZE*SIZE])
{

}

bool Sudoku::checkRow(int number, int x, int y, int (&board)[SIZE*SIZE])
{

}

bool Sudoku::checkColumn(int number, int x, int y, int (&board)[SIZE*SIZE])
{

}

bool Sudoku::checkBlock(int number, int x, int y, int (&board)[SIZE*SIZE])
{

}