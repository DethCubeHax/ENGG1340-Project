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
            if (choice == "exit")
            {
                system("clear");
                break;
            }
        }
        switch (err)
        {
        case 1:
            cout << "\nYou cannot erase a pre-generated square.\n" << endl;
            break;
        case 2:
            cout << "\nThe command you entered is invalid.\n" << endl;
            break;
        case 3:
            cout << "\nThe number you entered is invalid.\n" << endl;
            break;
        case 4:
            cout << "\nYou cannot overwrite a pre-generated square.\n" << endl;
            break;
        case 5:
            cout << "\nGame has been saved.\n" << endl;
            choice = "";
        default:
            break;
        }
        sudoku.toLowerCase(choice);
        if (choice == "2"){
            if (generated == false){
                system("clear");
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
        if (choice == "exit"){
            
            break;
        }
    }
    cout << "\n\n\n\x1B[38;5;30m--\x1B[38;5;66m-。\x1B[38;5;102m--。\x1B[38;5;138m---";
    cout << "\x1B[38;5;174mBye \x1B[38;5;210mbye \x1B[38;5;210m(^･ω\x1B[38;5;174m･^)";
    cout << "\x1B[38;5;138m---\x1B[38;5;102m。--\x1B[38;5;66m。-\x1B[38;5;30m--\n\n\n" << endl;
}