#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#define SIZE 9

struct BoardState
{
    int board[SIZE][SIZE];
    BoardState *next;
    BoardState *previous;
    bool failed;
};

#endif