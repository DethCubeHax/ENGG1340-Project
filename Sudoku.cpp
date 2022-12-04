#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include "Sudoku.h"
#include "GlobalVars.h"

struct BoardState
{
    int board[SIZE][SIZE];
    BoardState *next;
    BoardState *previous;
    bool failed;
};

using namespace std;

bool Sudoku::numberIsPossible(int number, int x, int y, int (&board)[SIZE][SIZE])
{
    if (checkRow(number, x, board) && checkColumn(number, y, board) && checkBlock(number, x, y, board) ) return true;
    return false;
}

void Sudoku::generateBoard(int (&board)[SIZE][SIZE])
{
    random_device square; // obtain a random number from hardware
    random_device number; // obtain a random number from hardware
    mt19937 genSquare(square()); // seed the generator
    mt19937 genNumber(number()); // seed the generator
    uniform_int_distribution<> distrSquare(0, SIZE-1); // define the range
    uniform_int_distribution<> distrNumber(1, SIZE); // define the range

    for (int i = 0; i<17; i++)
    {
        int x = distrSquare(genSquare);
        int y = distrSquare(genSquare);
        int num = distrNumber(genNumber);
        if (numberIsPossible(num, x, y, board))
        {
            board[x][y] = num;
        }
        else
        {
            i--;
        }
    }
}

void Sudoku::printBoard(int (&board)[SIZE][SIZE])
{
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        for ( int j = 0 ; j < SIZE ; j++ )
        {
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

bool Sudoku::checkRow(int number, int y, int (&board)[SIZE][SIZE])
{
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        if ( board[y][i] == number ) return false;
    }
    return true;
}

bool Sudoku::checkColumn(int number, int x, int (&board)[SIZE][SIZE])
{
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        if ( board[i][x] == number ) return false;
    }
    return true;
}

bool Sudoku::checkBlock(int number, int x, int y, int (&board)[SIZE][SIZE])
{
    bool notIn = true;
    int xBlock = x/3;
    int yBlock = y/3;
    for ( int i = 0 ; i < 3 ; i++){
        for ( int j = 0 ; j < 3 ; j++){
            if ( board[yBlock*3+i][xBlock*3+j] == number ){
                notIn = false;
                break;
            }
        }
    }
    return notIn;
}

bool Sudoku::solveBoard(int (&board)[SIZE][SIZE], int x, int y)
{
    printBoard(board);
    cout << "-----------------" << endl;
    cout << "Iteration: " << x << ", " << y << endl;
    BoardState *head = NULL;
    if (board[y][x] == 0)
    {
        for (int i = 1; i < 10; i++)
        {
            if (numberIsPossible(i, x, y, board))
            {
                board[y][x] = i;
                if (x == 8 && y == 8)
                {
                    return true;
                }
                else if (x == 8)
                {
                    if (solveBoard(board, 0, y + 1))
                    {
                        return true;
                    }
                }
                else
                {
                    if (solveBoard(board, x + 1, y))
                    {
                        return true;
                    }
                }
            }
        }
        board[y][x] = 0;
        return false;
    }
    else
    {
        if (x == 8 && y == 8)
        {
            return true;
        }
        else if (x == 8)
        {
            if (solveBoard(board, 0, y + 1))
            {
                return true;
            }
        }
        else
        {
            if (solveBoard(board, x + 1, y))
            {
                return true;
            }
        }
    }
    return false;
}