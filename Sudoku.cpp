#include <iostream>
#include <fstream>
#include <sstream>
#include "Sudoku.h"
#include "GlobalVars.h"


using namespace std;

bool Sudoku::numberIsPossible(int number, int x, int y, int (&board)[SIZE][SIZE])
{
    if (checkBlock(number, x, y, board) && checkColumn(number, x, y, board) && checkColumn(number, x, y, board)) return true;
}

void Sudoku::printBoard(int (&board)[SIZE][SIZE])
{
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            cout<<board[i][j]<<' ';
        }
        cout<<endl;
    }
}

void Sudoku::readBoard(int (&board)[SIZE][SIZE])
{   
    ifstream fin("game.txt");                 // Open the file
    int yCount = 0;
    string line;
    while (getline(fin, line))
    {
        istringstream iss(line);
        char w;
        int xCount = 0;
        while (iss >> w)
        {
            board[yCount][xCount] = int(w) - 48;
            xCount++;
        }
        yCount++;
    }

}

bool Sudoku::checkRow(int number, int x, int y, int (&board)[SIZE][SIZE])
{

}

bool Sudoku::checkColumn(int number, int x, int y, int (&board)[SIZE][SIZE])
{

}

bool Sudoku::checkBlock(int number, int x, int y, int (&board)[SIZE][SIZE])
{

}