
#ifndef GLOBALVARS_H
#define GLOBALVARS_H
#include <string>
#define SIZE 9

using namespace std;

string choice = "";
struct BoardState
{
    int board[SIZE][SIZE];
    BoardState *next;
    BoardState *previous;
    bool failed;
};

#endif