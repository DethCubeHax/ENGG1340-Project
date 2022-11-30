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
    bool notIn = true;
    for ( int i = 0 ; i < SIZE ; i++){
        if ( board[x][i] == number ){
            notIn = false;
        }
    }
    return notIn;
}

bool Sudoku::checkColumn(int number, int x, int y, int (&board)[SIZE][SIZE])
{
    bool notIn = true;
    for ( int i = 0 ; i < SIZE ; i++){
        if ( board[i][y] == number ){
            notIn = false;
        }
    }
    return notIn;
}

bool Sudoku::checkBlock(int number, int x, int y, int (&board)[SIZE][SIZE])
{
    int startRow = 0, startColumn = 0;
    if ( 0 <= x <= 2 ){
        startRow = 0;
    }
    else if ( 3 <= x <= 5 ){
        startRow = 3;
    }
    else{
        startRow = 6;
    }

    if ( 0 <= y <= 2 ){
        startColumn = 0;
    }
    else if ( 3 <= y <= 5 ){
        startColumn = 3;
    }
    else{
        startColumn = 6;
    }
    
    bool notIn = true;
    for ( int i = startRow ; i < startRow+3 ; i++){
        for ( int j = startColumn ; j < startColumn+3 ; j++){
            if ( board[i][j] == number ){
            notIn = false;
            break;
            }
        }
    }
    return notIn;
}