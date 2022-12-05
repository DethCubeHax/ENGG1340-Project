#include <iostream>
#include "Sudoku.h"
#include "GlobalVars.h"
using namespace std;
Sudoku sudoku;

int player1Board[SIZE][SIZE] = {0};
int tmpBoard[SIZE][SIZE] = {0};

BoardState *playerBoardHead = NULL;
BoardState *computerBoardHead = NULL;

int main()
{
    int err=0;
    char *cont;
    bool generated = false;
    while (choice != "exit"){
        system("clear");
        if (choice == "")
        {
            sudoku.welcome();
        }
        switch (err)
        {
        case 1:
            cout << "You cannot erase a pre-generated square." << endl;
            break;
        case 2:
            cout << "The command you entered is invalid." << endl;
            break;
        case 3:
            cout << "The number you entered is invalid." << endl;
            break;
        case 4:
            cout << "You cannot overwrite a pre-generated square." << endl;
            break;
        default:
            break;
        }
        if (choice == "2"){
            if (generated == false){
                sudoku.generateBoard(player1Board);
                generated = true;
            }
            err=sudoku.gameHandler(player1Board);
        }
        if (choice == "3"){
            
        }

        if (choice == "4"){
            sudoku.finalScreen(player1Board);
        }
    }
}