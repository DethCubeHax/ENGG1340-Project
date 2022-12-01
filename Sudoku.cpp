#include <iostream>
#include <fstream>
#include <sstream>
#include "Sudoku.h"
#include "GlobalVars.h"


using namespace std;

bool Sudoku::numberIsPossible(int number, int x, int y, int (&board)[SIZE][SIZE])
{
    if (checkRow(number, x, y, board) && checkColumn(number, x, y, board) && checkBlock(number, x, y, board) ) return true;
}

void Sudoku::generateBoard(int (&board)[SIZE][SIZE]){
    for ( int i = 0 ; i < 9 ; i++){
        //cout<<i<<endl;
        for ( int j = 0 ; j < 9 ; j++ ){
            //cout<<j;
            for ( int k = 1; k < 10 ; k++){
                if ( numberIsPossible( k, j, i, board ) ){
                    board[i][j]=k;
                    break;
                }
                //else if ( k ==1 and j == 6 and i == 1 and checkBlock( k, j, i, board )){
                    //cout<<j<<i<<endl;
                    //break;
            //}
            }
            
        }
        //cout<<endl;
    }
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
    ifstream fin("test.txt");                 // Open the file
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
        if ( board[i][x] == number ){
            notIn = false;
            break;
        }
    }
    return notIn;
}

bool Sudoku::checkColumn(int number, int x, int y, int (&board)[SIZE][SIZE])
{
    bool notIn = true;
    for ( int i = 0 ; i < SIZE ; i++){
        if ( board[y][i] == number ){
            notIn = false;
            break;
        }
    }
    return notIn;
}

bool Sudoku::checkBlock(int number, int x, int y, int (&board)[SIZE][SIZE])
{
    int startRow = 0, startColumn = 0;
    if ( 0 <= y and y <= 2 ){
        startRow = 0;
    }
    else if ( 3 <= y and y <= 5 ){
        startRow = 3;
    }
    else if ( 6 <= y and y <= 8 ) {
        startRow = 6;
    }

    if ( 0 <= x and x <= 2 ){
        startColumn = 0;
    }
    else if ( 3 <= x and x <= 5 ){
        startColumn = 3;
    }
    else if ( 6 <= x and x<= 8 ){
        startColumn = 6;
    }
    //cout<<y<<x<<' '<<startColumn<<startRow<<endl;
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