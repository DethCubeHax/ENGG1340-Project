// Includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <random>
#include <chrono>
#include <string>
#include <cctype>
#include <ctime>
#include "Sudoku.h"
#include "GlobalVars.h"

// Saving energy for our fingers
using namespace std;
using namespace std::chrono;
using std::ostream;

random_device square; // obtain a random number from hardware
random_device number; // obtain a random number from hardware
mt19937 genSquare(square()); // seed the generator
mt19937 genNumber(number()); // seed the generator
uniform_int_distribution<> distrSquare(0, SIZE-1); // define the range
uniform_int_distribution<> distrNumber(1, SIZE); // define the range

// Link the board state to the variable in main.cpp
extern BoardState *playerBoardHead;
extern BoardState *computerBoardHead;

// Link the player and computer's steps to the variables in main.cpp
extern int player1Steps;
extern int computerSteps;

// Function to get the current time since 1970
uint64_t timeSinceBoot()
{
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

// Get the time at Runtime
uint64_t runTime = timeSinceBoot();

// Function to check if a number is valid at a given x, y
bool Sudoku::numberIsPossible(int number, int x, int y, int (&board)[SIZE][SIZE])
{
    if (checkRow(number, x, board) && checkColumn(number, y, board) && checkBlock(number, x, y, board) ) return true;
    return false;
}

// Function to display the welcome screen
// Handles user inputs to determine which state the game will be in
// at the next iteration

void Sudoku::welcome(){
    
    bool valid_input = false;
    cout<<"\x1B[38;5;30m========================================="<<endl;
    cout << "       Helloo! Welcome to sudoku!" << endl;
    cout<<"\x1B[38;5;66m=========================================\n"<<endl;
    
    while (!valid_input){
        cout << "Please choose an option:\n" << endl;
        cout << "\x1B[38;5;102m1. Load game" << endl;
        cout << "2. New game" << endl;
        cout << "\x1B[38;5;138m3. Instructions\n" << endl;
        cout<<"========================================="<<endl;
        cout << "\x1B[38;5;174mType [ exit ] to quit" << endl;
        cout<<"\x1B[38;5;210m=========================================\x1B[38;5;255m"<<endl;
        cin >> choice;
        cin.ignore();
        if (choice == "1" || choice == "2" || choice == "3" || choice == "exit"){
            valid_input = true;
        }
        else{
            valid_input = false;
            cout<<"========================================="<<endl;
            cout << "Invalid input. Please enter: [ 1 2 3 ]." <<endl;
            cout<<"========================================="<<endl;
        }
    }
}

// Function to handle the game during runtime
// Inputs: the player's board
// Outputs: an integer determining whether the user's input was valid
int Sudoku::gameHandler(int (&board)[SIZE][SIZE]){
    // If the board is solved, return 0
    if (isSolved(board)) 
    {
        choice = "4";
        return 0;
    }
    cout << "--------------------" << endl;
    cout << "Steps taken: " << player1Steps << endl;
    printBoard(board);
    cout << "" << endl;
    string control;
    cin >> control;
    toLowerCase(control);
    // If the user wants to exit, return 5
    if (control == "exit"){
        return 5;
    }
    // If the command is invalid, return 2
    if (control.length() > 1)
    {
        return 2;
    }
    // If the user wants to move the cursor, call the cursorInputHandler() function
    if (control == "w" || control == "a" || control == "s" || control == "d"){
        cursorInputHandler(control);
        return 0;
    }
    // If the user wants to erase a number
    // Verify that the number is not a preset number
    if (stoi(control) == 0)
    {
        if(playerBoardHead->board[cursorY][cursorX] != 0)
        {
            return 1;
        }
        board[cursorY][cursorX] = 0;
        addToList(playerBoardHead, board);
        readOrSaveBoard(board, 'w');
        return 0;
    }
    // If the user inputs a number too large or low, return 2
    else if(stoi(control) > 10 || stoi(control) < 0){
        return 2;
    }
    // If the number is not valid at square x,y return 3
    if(! numberIsPossible(stoi(control), cursorY, cursorX, board)){
        return 3;
    }
    // If the number is valid, add it to the board
    else{
        if (playerBoardHead->board[cursorY][cursorX] != 0)
        {
            return 4;
        }
        board[cursorY][cursorX] = stoi(control);
        addToList(playerBoardHead, board);
        readOrSaveBoard(board, 'w');
        player1Steps++;
        return 0;
    }
}

// Function to display the final screen
// Inputs: the player's board
// Outputs: Displays the number of steps and the time taken to solve,
//          and asks if the user wants to review the steps taken
void Sudoku::finalScreen(int (&board)[SIZE][SIZE]){
        cout << "\x1B[38;5;38m=========================================" << endl;
        cout << "Congratulations!" << endl;
        cout << "\x1B[38;5;74mYou have solved the puzzle (^･ω･^)" << endl;
        printBoard(board);
        cout << "\x1B[38;5;110m=========================================\n" << endl;
        cout << "\x1B[38;5;146mYour time is: " << timeSinceBoot() - runTime << " milliseconds." << endl;
        cout << "\x1B[38;5;182m=========================================" << endl;
        cout << "Your steps are: " << player1Steps << "compared to computer's: " << computerSteps << "." << endl;
        cout << "\x1B[38;5;218mWould you like to review the steps? (y/n)" << endl;
        cout << "=========================================" << endl;
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
            cout << "Thank you for playing! (^･ω･^)\x1B[38;5;255m" << endl;
        }
        choice = "exit";
}


// Function to convert a string to lowercase
// Inputs: a string
void Sudoku::toLowerCase(string &str){
    for (int i = 0; i < str.length(); i++){
        str[i] = tolower(str[i]);
    }
}

// Function to handle the user's input when moving the cursor
// Inputs: the user's input
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

// Function to display the instructions
// Inputs: none
// Outputs: Displays the instructions to the screen
void Sudoku::showInstruction(){
    system("clear");
    cout << "\x1B[38;5;30m============= Instructions ===============" << endl;
    cout << "\x1B[38;5;66m\nWelcome to sudoku! The objective of this\n";
    cout << "game is to fill a 9 × 9 grid with digits\n";
    cout << "so that each column, each row, and each\n";
    cout << "of the nine 3 × 3 subgrids that compos\n";
    cout << "the grid contain all of the digits from\n";
    cout << "1 to 9.\n\n";
    cout << "\x1B[38;5;102mControls:\n\n";
    cout << "The cursor X shows your current position.\n\n";
    cout << "\x1B[38;5;138mW -> Move up one block\n";
    cout << "A -> Move left one block\n";
    cout << "S -> Move down one block\n";
    cout << "D -> Move right one block\n\n";
    cout << "\x1B[38;5;174mPress enter after every move, then insert\n";
    cout << "a number.\n\n";


    cout << "=========================================" << endl;
    cout << "\x1B[38;5;210mPress Enter to continue" << endl;
    cout << "=========================================\x1B[38;5;255m\n" << endl;
    // cin.ignore();
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    choice = "";
    
}

// Function to generate a random sudoku board
// Inputs: the board
// Outputs: a random sudoku board
void Sudoku::generateBoard(int (&board)[SIZE][SIZE])
{
    // Get 17 random numbers at 17 random positions
    for (int i = 0; i<18; i++)
    {
        int x = distrSquare(genSquare);
        int y = distrSquare(genSquare);
        int num = distrNumber(genNumber);
        // If the number is valid at square x,y, add it to the board
        if (numberIsPossible(num, x, y, board) && board[x][y] == 0)
        {
            board[x][y] = num;
        }
        // Else, generate a new number
        else
        {
            i--;
        }
    }

    // Create a copy of the board
    int tmpBoard[SIZE][SIZE] = {0};
    copyBoard(tmpBoard, board);

    // Get the current time
    runTime = timeSinceBoot();
    // If the board is not solvable, generate a new board
    if (!solveBoard(tmpBoard))
    {
        eraseBoard(board);
        generateBoard(board);
    }
    // If the board has been generated, save it
    remove("computerBoard.txt");
    remove("playerBoard.txt");
    saveBoard(board, computerBoardHead, "computerBoard.txt");
    addToList(playerBoardHead, board);
    readOrSaveBoard(board, 'w');
}

// Function to print the board
// Inputs: the board
// Outputs: the board with the borders
//         and the cursor
void Sudoku::printBoard(int (&board)[SIZE][SIZE])
{
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        if ( i % 3 == 0 && i != 0 )
        {
            cout << "\u001b[36m";
            cout << "------x-------x------" << endl;
        }
        for ( int j = 0 ; j < SIZE ; j++ )
        {
            if (playerBoardHead->board[i][j] != 0)
            {
                cout << "\033[1;31m";
            }
                if (j == 3 || j == 6)
                {
                    cout << "\u001b[36m";
                    cout << "| ";
                    if (playerBoardHead->board[i][j] != 0)
                    {
                        cout << "\033[1;31m";
                    }
                    else
                    {
                        cout << "\033[0m";
                    }
                }
                if (cursorX == j && cursorY == i)
                {
                    if (playerBoardHead->board[i][j] != 0)
                    {
                        cout << "\033[1;31m";
                    }
                    else
                    {
                        cout << "\u001b[32m";
                        if (board[i][j] != 0)
                        {
                            cout << "\u001b[32m" << board[i][j] << ' ';
                            cout << "\033[0m";
                            continue;
                        }
                    }
                    cout << CURSORCHAR << ' ';
                    cout << "\033[0m";
                    continue;
                }
                if (playerBoardHead->board[i][j] == 0)
                {
                    cout << "\033[0m";
                }
                cout<<board[i][j]<<' ';
            if (playerBoardHead->board[i][j] != 0)
            {
                cout << "\033[0m";
            }
        }
        cout<<endl;
    }
}

// Function to save the user board to the disk
// Inputs: the board
// Outputs: the board saved to the disk
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


// Function to check if the number is possible at the row
bool Sudoku::checkRow(int number, int y, int (&board)[SIZE][SIZE])
{
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        if ( board[y][i] == number ) return false;
    }
    return true;
}

// Function to check if the number is possible at the column
bool Sudoku::checkColumn(int number, int x, int (&board)[SIZE][SIZE])
{
    for ( int i = 0 ; i < SIZE ; i++ )
    {
        if ( board[i][x] == number ) return false;
    }
    return true;
}

// Function to check if the number is possible at the square
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

// Function the computer to solve the board
// Inputs: the board
// Outputs: the board solved
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

// Function to add a board to the list
// Inputs: the head of the list and the board
// Outputs: the board added to the list
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

// Function to copy the board
// Inputs: the board to be copied and the board to be copied to
// Outputs: the board copied
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

// Function to erase the board
// Inputs: the board
// Outputs: the board erased
void Sudoku::eraseBoard(int (&board)[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = 0;
        }
    }
}

// Function to erase the list
// Inputs: the head of the list
// Outputs: the list erased
void Sudoku::eraseList(BoardState *&head)
{
    BoardState *traverser = head;
    if (head == NULL)
    {
        return;
    }
    while (traverser != NULL)
    {
        BoardState *tmp = traverser;
        traverser = traverser->next;
        delete tmp;
    }
    head = NULL;
}


// Function to print the user board list and the computer board list
// Inputs: the head of the user board list and the head of the computer board list
// Outputs: the user board list and the computer board list printed
void Sudoku::printList(BoardState *playerHead, BoardState *computerHead)
{
    BoardState *playerTraverser = playerHead;
    BoardState *computerTraverser = computerHead;;
    int count = 0;
    while (playerTraverser != NULL || computerTraverser != NULL)
    {
        if (playerTraverser == NULL || computerTraverser == NULL)
        {
            break;
        }
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


// Check if the board is solved
// Inputs: the board
// Outputs: true if the board is solved, false otherwise
bool Sudoku::isSolved(int (&board)[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

// Function to save the computer's steps
// Inputs: the head of the list for the computer's steps
// Outputs: the computer's steps saved
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


// Function to load the computer or user's steps
// Inputs: the head of the list for the computer or user's steps
// Outputs: the computer or user's steps loaded
void Sudoku::loadList(BoardState *&head, int (&board)[SIZE][SIZE], string fileName, int &steps) //tmpBoard
{
    if (head!=NULL)
    {
        eraseList(head);
    }
    ifstream fin(fileName);
    if (fin.is_open())
    {
        eraseBoard(board);
        while (!fin.eof())
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    fin >> board[i][j];
                }
            }
            addToList(head, board);
            steps++;
        }
    }
    fin.close();
}
