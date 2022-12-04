
#ifndef GLOBALVARS_H
#define GLOBALVARS_H
#include <string>

using namespace std;

#define SIZE 9
extern string choice;
struct BoardState
{
    int board[SIZE][SIZE];
    BoardState *next;
    BoardState *previous;
    bool failed;
};

#endif
