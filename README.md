# ENGG1340 Group Project - Sudoku

## Introduction
This is a Sudoku game written in C++ using standard libraries. The game is consistent with the traditional Sudoku game, whereby:
- The game is played on a 9x9 grid;
- No number can be repeated in a row, column and 3x3 grid.

The user is greeted with a menu, where they can choose to start a new game, load a saved game, or view the instructions. 
The user can also choose to exit the game at any time by typing "exit" and then hitting enter.
The game will automatically save the current state of the game when the user exits the game.

The player can win the game by filling in all the empty cells with numbers that satisfy the rules of Sudoku, and the number of steps required to win the game is fewer than the computer's. At the end of the game, the player will be prompted to review the game and the computer's solution, if they so choose.

## How to run the program
Before the program can be run, it must be compiled by typing the following command in the terminal:
<p>

```make sudoku```

<p>

If the program is run for the first time, the makefile will compile the program and create an executable file called "sudoku".
If the user chooses to compile a clean build, the user can type the following command in the terminal:
<p>

```make clean```

<p>
This will remove the executable file and the object files, following which the user can enter:
<p>

```make sudoku```

<p>
to compile the program again.
<p>
Then, the program can be run by typing the following command in the terminal:

<p>

```./sudoku```

<p>


## How to play the game
- The instructions to play the game can be viewed by typing "3" into the terminal and hitting enter. The instructions will be displayed on the terminal, and the user can press any key to return to the main menu.
- The user can start a new game by typing "2" into the terminal and hitting enter.
- Once the game is loaded, the user can navigate the grid using the w, a, s, d keys, followed by enter. 
- Once the user has selected a cell, they can enter a number from 1 to 9 into the cell by typing the number and then hitting enter.
- The number will be updated only if it is valid, i.e. it does not violate the rules of Sudoku. The user cannot enter a number into a cell that is already filled.
- Once the user has filled in all the empty cell, they will be congratulated and prompted to review the game and the computer's solution, if they so choose.

## Scoring system
- The user will be awarded 1 point for every step taken to complete the game.
- If the user erases a number, the number of steps will increase, but they will not be awarded a point.
- If the user wins the game, the number of steps taken will be compared to the number of steps taken by the computer to solve the game. If the user's number of steps is fewer than the computer's, the user will be informed of such on the last screen.

## Game functionality
The game is split into three parts, namely:
- The main.cpp file, which contains functions is responsible for displaying the menu and calling the appropriate functions to start a new game, load a saved game, or view the instructions.
- The Sudoku.cpp file, which contains the functions in the Sudoku class, which include:
  - The welcome() function, which displays the welcome message and the menu.
  - The gameHandler() function, which handles the game logic, such as user inputs, and calls the appropriate functions to display the game board, and check if the game is won.
  - The finalScreen() function, which displays the final screen, which includes the number of steps taken by the user and the computer, and the winner of the game. The user is also prompted to review the game and the computer's solution, if they so choose, by calling the printList() function, which prints the list of steps taken by the user and the computer.
  - The generateBoard() function, which generates a random Sudoku board and verifies with solveBoard() to ensure that the board is solvable.
  - The numberIsPossible() function, which calls the checkRow(), checkColumn() and checkBlock() functions, which check if the number entered by the user is valid.
  - The printBoard() function, which prints the game board whenever called by another function.
  - The addToList() function, which adds the user's input as well as the computer's solution steps to a linked list, which is used to print the list of steps taken by the user and the computer.
  - The copyBoard() and eraseBoard() functions, which are used to generate a random Sudoku board and erase a random number of cells.
  - The eraseList(), cursorInputHandler(), toLowerCase() and isSolved() functions, which are helper functions that erase the linked list, handle user inputs, convert the user's input to lowercase, and check if the game is won, respectively.
- The GlobalVars.h file, which contains the global variables used in throughout the game.

### <b>Function descriptions</b>
#### <b><u>main.cpp</u></b>

Contains the main function that drives the game, as well as the linked lists for the steps taken by the user and the computer.

First, we include the necessary libraries, and the Sudoku.h file, which contains the Sudoku class, as well as the GlobalVars.h file, which contains the global variables used throughout the game.

```C++
#include <iostream>
#include "Sudoku.h"
#include "GlobalVars.h"
using namespace std;
Sudoku sudoku;
```

Next, we create the linked lists for the steps taken by the user and the computer, and the board that is used to store the user's immediate input.

```C++
int player1Board[SIZE][SIZE] = {0};
int tmpBoard[SIZE][SIZE] = {0};

BoardState *playerBoardHead = NULL;
BoardState *computerBoardHead = NULL;
```
The ```struct``` BoardState is defined in the GlobalVars.h file, included previously.

```C++
int main()
{
    int err=0;
    char *cont;
    bool generate = true;
    bool madeAMove = false;
    while (choice != "exit"){
        if (choice == "")
        {
            system("clear");
            if (err != 0) err = 0;
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
                cout << "You cannot erase a pre-generate square." << endl;
                break;
            case 2:
                cout << "The command you entered is invalid." << endl;
                break;
            case 3:
                cout << "The number you entered is invalid." << endl;
                break;
            case 4:
                cout << "You cannot overwrite a pre-generate square." << endl;
                break;
            case 5:
                cout << "Game has been saved." << endl;
                choice = "";
            default:
                break;
        }

        if (choice == "1")
        {
            //sudoku.loadList(computerBoardHead, tmpBoard, "computerBoard.txt");
            sudoku.loadList(computerBoardHead, tmpBoard, "computerBoard.txt", computerSteps);
            sudoku.loadList(playerBoardHead, player1Board, "playerBoard.txt", player1Steps);
            choice = "run";
        }
        sudoku.toLowerCase(choice);
        if (choice == "2"){
            system("clear");
            sudoku.generateBoard(player1Board);
            generate = true;
            choice = "run";
        }
        if (choice == "3"){
            system("clear");
            sudoku.showInstruction();
        }
        if (choice == "4"){
            system("clear");
            sudoku.finalScreen(player1Board);
        }
        if (choice == "run")
        {
            system("clear");
            err=sudoku.gameHandler(player1Board);
            madeAMove = true;
        }
        if (choice == "exit"){
            break;
        }
    }
    cout << "\n\n\n\x1B[38;5;30m--\x1B[38;5;66m-。\x1B[38;5;102m--。\x1B[38;5;138m---";
    cout << "\x1B[38;5;174mBye \x1B[38;5;210mbye \x1B[38;5;210m(^･ω\x1B[38;5;174m･^)";
    cout << "\x1B[38;5;138m---\x1B[38;5;102m。--\x1B[38;5;66m。-\x1B[38;5;30m--\n\n\n" << endl;
}
```
<p>
It uses the choice variable to determine the game state the welcome() function is called when the game is first loaded, when the choice variable is "". If the choice variable is "2", the generateBoard() function is called, which generates the game board, which handles the game logic. If the choice variable is "3", the instructions are displayed. If the choice variable is "4", the finalScreen() function is called, which displays the final screen. Finally, the game functionality is driven by the gameHandler() function. The user can exit the game by typing "exit" into the terminal, which will set the choice variable to "exit", and the game will end.

<p>

#### <b><u>Sudoku.cpp</b></u>
</p>
Contains the functions in the Sudoku class, whose prototypes are defined in the Sudoku.h file as follows. This allows us to have header guards, which prevent the header file from being included more than once.

```C++
#ifndef SUDOKU_H
#define SUDOKU_H
#include "GlobalVars.h"

class Sudoku
{
    public:
        void welcome();
        void toLowerCase(string &str);
        int gameHandler(int (&board)[SIZE][SIZE]);
        void finalScreen(int (&board)[SIZE][SIZE]);
        void showInstruction();
        bool numberIsPossible(int number, int x, int y, int (&board)[SIZE][SIZE]);
        void printBoard(int (&board)[SIZE][SIZE]);
        void readOrSaveBoard(int (&board)[SIZE][SIZE], char args);
        void generateBoard (int (&board)[SIZE][SIZE]);
        bool solveBoard(int (&board)[SIZE][SIZE]);
        void printList(BoardState *playerHead, BoardState *computerHead);
        void loadList(BoardState *&head, int (&board)[SIZE][SIZE], string fileName, int &steps);
        void saveBoard(int (&board)[SIZE][SIZE], BoardState *&head, string file);
        
    private:
        bool checkRow(int number, int y, int (&board)[SIZE][SIZE]);
        bool checkColumn(int number, int x, int (&board)[SIZE][SIZE]);
        bool checkBlock(int number, int x, int y, int (&board)[SIZE][SIZE]);
        void addToList(BoardState *&head, int (&board)[SIZE][SIZE]);
        void copyBoard(int (&board1)[SIZE][SIZE], int (&board2)[SIZE][SIZE]);
        void eraseBoard(int (&board)[SIZE][SIZE]);
        void eraseList(BoardState *&head);
        void cursorInputHandler(string control);
        bool isSolved(int (&board)[SIZE][SIZE]);
};

#endif
```

The welcome() function displays the welcome message and the menu.

```C++
void Sudoku::welcome(){
    
    bool valid_input = false;
    cout << "Hello! Welcome to sudoku!" << endl;
    
    while (!valid_input){
        cout << "Please choose an option:" << endl;
        cout << "1. Load game" << endl;
        cout << "2. New game" << endl;
        cout << "3. Instructions" << endl;
            cin >> choice;
            cin.ignore();
            valid_input = true;
            if (choice == "1"){
                valid_input = true;
            }
            else if (choice == "2"){
                valid_input = true;
            }
            else if (choice == "3"){
                showInstruction();
                valid_input = true;
            }
            else{
                cout<<"========================================="<<endl;
                cout << "Invalid input. Please enter: [ 1 2 3 ]." <<endl;
                cout<<"========================================="<<endl;
                valid_input = false;
            }           
    }
    system("clear");
}
```
First, we display the welcome message and the menu. We then use a while loop to check if the user's input is valid. If the user's input is valid, we set the valid_input variable to true, and the while loop will end. If the user's input is invalid, we display an error message and ask the user to enter a valid input. The user can exit the game by typing "exit" into the terminal, which will set the choice variable to "exit", and the game will end. Afterwards, the system("clear") function is called to clear the terminal.

The gameHandler() function handles the game logic.

```C++
int Sudoku::gameHandler(int (&board)[SIZE][SIZE]){
    if (isSolved(board)) 
    {
        choice = "4";
        return 0;
    }
    printBoard(board);
    cout << "" << endl;
    string control;
    cin >> control;
    toLowerCase(control);
    if (control.length() > 1)
    {
        return 2;
    }
    if (control == "w" || control == "a" || control == "s" || control == "d"){
        cursorInputHandler(control);
        return 0;
    }
    if (stoi(control) == 0)
    {
        if(playerBoardHead->board[cursorY][cursorX] != 0)
        {
            return 1;
        }
        board[cursorY][cursorX] = 0;
        addToList(playerBoardHead, board);
        return 0;
    }

    else if(stoi(control) > 10 || stoi(control) < 0){
        return 2;
    }
    if(! numberIsPossible(stoi(control), cursorY, cursorX, board)){
        return 3;
    }
    else{
        if (playerBoardHead->board[cursorY][cursorX] != 0)
        {
            return 4;
        }
        board[cursorY][cursorX] = stoi(control);
        addToList(playerBoardHead, board);
        return 0;
    }
}
```
First, we check if the board is solved. If it is, we set the choice variable to "4", and the game will end. We then print the board, and ask the user to enter a control. We then check if the control is valid. If it is, we call the cursorInputHandler() function, which handles the cursor movement. If the control is invalid, we return an error code. The error codes are as follows:
* 0: No error
* 1: The user tried to erase a number that was already erased
* 2: The user entered an invalid control (e.g. "zasdlfjas")
* 3: The user tried to enter a number that is not possible
* 4: The user tried to enter a number that was already generated
Finally, once a valid control is entered, we add the board to the player's board list to keep track of the player's moves.

The cursorInputHandler() function handles the cursor movement.

```C++
void Sudoku::cursorInputHandler(string control){
    if (control == "a" && cursorX != 0){
        cursorX--;
    }
    if (control == "d" && cursorX != 8){
        cursorX++;
    }
    if (control == "w" && cursorY != 0){
        cursorY--;
    }
    if (control == "s" && cursorY != 8){
        cursorY++;
    }
}
```
We use if statements to check if the cursor can move in the direction specified by the control. If it can, we move the cursor in that direction. If it can't, that is, if the user tries to move the cursor out of the board, we do nothing.

The showInstruction() function displays the instructions. It displays the controls and the rules of the game.

```C++ 
cout << "Instructions in the Sudoku.cpp file" << endl;
```

The numberIsPossible() function checks if a number is possible in a certain position.

```C++
bool Sudoku::numberIsPossible(int number, int x, int y, int (&board)[SIZE][SIZE])
{
    if (checkRow(number, x, board) && checkColumn(number, y, board) && checkBlock(number, x, y, board) ) return true;
    return false;
}
```
We use the checkRow(), checkColumn(), and checkBlock() functions to check if the number is possible in the row, column, and block. If all three of them are true, we return true. If it isn't, we return false.

The checkRow(), checkColumn() and checkBlock functions are defined as follows:

<u>checkRow()</u>

```C++
bool Sudoku::checkRow(int number, int y, int (&board)[SIZE][SIZE])
{
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        if ( board[y][i] == number ) return false;
    }
    return true;
}
```

<u>checkColumn()</u>

```C++
bool Sudoku::checkColumn(int number, int x, int (&board)[SIZE][SIZE])
{
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        if ( board[i][x] == number ) return false;
    }
    return true;
}
```

<u>checkBlock()</u>

```C++
bool Sudoku::checkBlock(int number, int x, int y, int (&board)[SIZE][SIZE])
{
    bool notIn = true;
    int xBlock = x/3;
    int yBlock = y/3;
    for ( int i = 0 ; i < 3 ; i++){
        for ( int j = 0 ; j < 3 ; j++){
            if ( board[xBlock*3+i][yBlock*3+j] == number ){
                notIn = false;
                break;
            }
        }
    }
    return notIn;
}
```

The generateBoard() function generates a random board.

```C++
bool Sudoku::solveBoard(int (&board)[SIZE][SIZE])
{
    if (timeSinceBoot() - runTime > 100)
    {
        eraseList(computerBoardHead);
        return false;
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                for (int k = 1; k <= SIZE; k++)
                {
                    if (numberIsPossible(k, i, j, board))
                    {
                        board[i][j] = k;
                        addToList(computerBoardHead, board);
                        if (solveBoard(board))
                        {
                            return true;
                        }
                        else
                        {
                            board[i][j] = 0;
                            addToList(computerBoardHead, board);
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}
```
We use a linear backtracking algorithm to solve the board. We first check if the board is solved. If it is, we return true. If it isn't, we loop through the board. If we find a 0, we loop through the numbers 1 to 9. If the number is possible, we set the 0 to that number, and add the board to the computer's board list. We then call the solveBoard() function again. If the board is solved, we return true. If it isn't, we set the number back to 0, and add the board to the computer's board list. If none of the numbers are possible, we return false.

However, this process can take a long time. To prevent the program from taking too long, we use the timeSinceBoot() function to check if the program has been running for more than 100 milliseconds. If it has, we return false.

The finalScreen() function displays the final screen.

```C++
void Sudoku::finalScreen(int (&board)[SIZE][SIZE]){
    if (choice == "4"){
        cout << "Congratulations! You have solved the puzzle!" << endl;
        cout << "------------------------------------------" << endl;
        printBoard(board);
        cout << "------------------------------------------" << endl;
        cout << "Your time is: " << timeSinceBoot() - runTime << " milliseconds." << endl;
        cout << "Would you like to review your steps? (y/n)" << endl;
        string control;
        cin >> control;
        while(control.length() > 1 || (control != "y" && control != "n")){
            cout << "Invalid input. Please enter: [ y n ]." << endl;
            cin >> control;
        }
        if (control == "y"){
            printList(playerBoardHead, computerBoardHead);
        }
        else{
            cout << "Thank you for playing!" << endl;
        }
    }
    else{
        cout << "You have quit the game." << endl;
        choice = "exit";
    }
}
```
We first check if the user has solved the puzzle. If they have, we congratulate them, display the board, and display their taken to solve. We then ask if they want to review their steps. If they do, we call the printList() function. If they don't, we thank them for playing and exit the game.

The saveBoard() function saves the computer board to a file.

```C++
void Sudoku::saveBoard(int (&board)[SIZE][SIZE], BoardState *&head, string file)
{
    ofstream fout;
    fout.open(file);
    BoardState *traverser = head;
    while (traverser != NULL)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                fout << traverser->board[i][j] << ' ';
            }
            fout << endl;
        }
        fout << endl;
        traverser = traverser->next;
    }
    fout.close();
}
```
It traverses through the linked list, and saves each board stored in the struct to a file called "computerBoard.txt".

The readOrSaveBoard() function can both read or write the player board from a file.

```C++
void Sudoku::readOrSaveBoard(int (&board)[SIZE][SIZE], char args)
{   
    if (args == 'r')
    {
        ifstream fin("steps.txt");                 // Open the file
        if (!fin)                                 // If the file does not exist
        {
            cout << "File does not exist." << endl;
        }

    }

    if (args == 'w')
    {
        ofstream fout("playerBoard.txt", ios::app);
        for ( int i = 0 ; i < SIZE ; i++ )
        {
            for ( int j = 0 ; j < SIZE ; j++ )
            {
                fout<<board[i][j]<<' ';
            }
            fout<<endl;
        }
        fout.close();
    }
}
```
This function allows us to save the user's board to a file called "playerBoard.txt" or read the user's board from a file, each time the user makes a move.

#### Helper Functions
The timeSinceBoot() function returns the time since the program started.

```C++
uint64_t timeSinceBoot()
{
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
```

The addToList() function adds a board to a list.

```C++
void Sudoku::addToList(BoardState *&head, int (&board)[SIZE][SIZE])
{
    BoardState *newState = new BoardState();
    copyBoard(newState->board, board);
    newState->next = NULL;
    if (head == NULL)
    {
        head = newState;
        return;
    }
    
    BoardState *traverser = head;

    while (traverser->next != NULL)
    {
        traverser = traverser->next;
    }
    traverser->next = newState;
    newState->previous = traverser;
}
```

The eraseList() function erases a list.

```C++
void Sudoku::eraseList(BoardState *&head)
{
    BoardState *traverser = head;
    while (traverser != NULL)
    {
        BoardState *temp = traverser;
        traverser = traverser->next;
        delete temp;
    }
    head = NULL;
}
```

The copyBoard() function copies a board.

```C++
void Sudoku::copyBoard(int (&board1)[SIZE][SIZE], int (&board2)[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board1[i][j] = board2[i][j];
        }
    }
}
```

The printBoard() function prints a board.

```C++
void Sudoku::printBoard(int (&board)[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
```

The printList() function prints both the player's board list and the computer's board list, once the game is over.

```C++
void Sudoku::printList(BoardState *playerHead, BoardState *computerHead)
{
    BoardState *playerTraverser = playerHead;
    BoardState *computerTraverser = computerHead;;
    int count = 0;
    while (playerTraverser != NULL || computerTraverser != NULL)
    {
        cout << "--------------------" << endl;
        cout << "Your move number " << count << " :" << endl;
        cout << "--------------------" << endl;
        printBoard(playerTraverser->board);
        playerTraverser = playerTraverser->next;
        cout << "--------------------" << endl;
        cout << "Computer move number " << count << " :" << endl;
        cout << "--------------------" << endl;
        printBoard(computerTraverser->board);
        computerTraverser = computerTraverser->next;
        cout << "--------------------" << endl;
        cout << "Press enter to continue" << endl;
        cout << "--------------------" << endl;
        cin.ignore();
        count++;
    }
}
```