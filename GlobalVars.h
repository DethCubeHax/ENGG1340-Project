// If this header file is not defined, define it
#ifndef GLOBALVARS_H
#define GLOBALVARS_H
// Includes
#include <string>

// Save energy for our fingers
using namespace std;

// Global variables
#define SIZE 9
#define CURSORCHAR "X" // 0_0 -_- *_* +_+ !_! /_\ \_/ Q_Q A_A

extern string choice;
extern int cursorX, cursorY;

// Struct to hold the board state at a certain position in the linked list
struct BoardState
{
    int board[SIZE][SIZE];
    BoardState *next;
    BoardState *previous;
    bool failed;
};

#endif
