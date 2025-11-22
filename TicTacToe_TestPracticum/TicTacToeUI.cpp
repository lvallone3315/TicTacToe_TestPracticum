

// TicTacToeUI.cpp
//   Encapsulates the methods to read & write to the UI (for now, the console)
//   <blank line>

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "TicTacToeUI.h"
#include "TicTacToeBoard.h"  // required for displaying board which is maintained by the board class

/* Tic Tac Toe UI Class
 * Scope:
 *   Handles all reads & writes to console (or in the future, a graphical window)
 *   Singleton class (for now) - uses console
 *
 * Methods:
 *      getUserInput() writes prompt to console, blocks on user input (terminated by new line), returns input
 *      writeOutput()  writes output to console & returns 0 indicating no error,
 *        in future write errors may contain an error code
 *      writeTicTacToeBoard(board) displays current board to console
 *
 * Instance Variables:
 *   None
 */


 // empty constructor
TicTacToeUI::TicTacToeUI() {

}


// getUserInput() - writes string to output and returns subsequent user input as a lower case string
//   prompts user with string included in call
//   waits for user input, echoes the input & returns it to caller
//   note: does not trim leading white space
//
string TicTacToeUI::getUserInput(char* prompt) const {
    string userInput;

    writeOutput(prompt);
    getline(cin, userInput);
        // convert to lower case, requires algorithm library
    transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
    return userInput;
}

// writeOutput() - writes parameter to output
//   
int TicTacToeUI::writeOutput(char* output) const {
    cout << output;
    return 0;
}

// refactor to improve console handling ...
// overload of writeOutput() giving option to clear screen
// writeOutput() - writes parameter to output
//   
int TicTacToeUI::writeOutput(char* output, bool clearScreenPrior) const {
    if (clearScreenPrior)
        system("cls");
    cout << output;
    return 0;
}

int TicTacToeUI::writeOutput(char *output, char arg) const {
    const int MAX_CHARS = 128;
    char userString[MAX_CHARS];

    sprintf_s(userString, MAX_CHARS, output, arg);
    writeOutput(userString);
    return 0;
}

int TicTacToeUI::writeOutput(char* output, int arg1, int arg2) const {
    const int MAX_CHARS = 128;
    char userString[MAX_CHARS];

    sprintf_s(userString, MAX_CHARS, output, arg1, arg2);
    writeOutput(userString);
    return 0;
}

// Draws board based on data from board class
// ToDo - find alternative to hard coding last row & column to avoid drawing delimiter - e.g. |
//
int TicTacToeUI::writeTicTacToeBoard(TicTacToeBoard board) const {
    // loop thru all rows and all columns, retrieving contents from board class & displaying
    cout << "\n";
    for (int r = 0; r < TicTacToeBoard::BOARD_NUM_ROWS; r++) {
        cout << "\t\t\t\t";
        for (int c = 0; c < TicTacToeBoard::BOARD_NUM_COLS; c++) {
            cout << " " << board.getSquareContents(r,c);
            if (c < TicTacToeBoard::BOARD_NUM_COLS - 1)
                cout << " |";
        }
        if (r < TicTacToeBoard::BOARD_NUM_ROWS - 1)
            cout << "\n\t\t\t\t------------\n";
        else
            cout << "\n\n";
    }
    return 0;
}
