#pragma once

#include <string>
#include "TicTacToeBoard.h"

using namespace std;  // fair programming practice, as could create scope issues, but don't feel like qualifying all reads & writes

/*
 * Header file for Fall 2023 Tic Tac Toe program UI
 *    getUserInput() prompts user with specified string and returns user input
 *    writeOutput() writes output to console and returns success (0) - 4 versions, all use character arrays
 *        1) one parameter - character array to write -> output it
 *        2) char array incl sprintf formatting (e.g. %c) + char arg -> uses sprintf to add arg to string -> outputs
 *        3) char array + two format items (e.g. %d ... %d) -> sprintf to add args -> outputs
 *        4) char array + option to clear screen -> if true, clears screen & outputs
 * 
 *    writeTicTacToeBoard(board) displays the board based on the contents maintained in the board class
 */

class TicTacToeUI
{
public:
	TicTacToeUI();
	int writeOutput(const char* output) const;
	int writeOutput(const char* output, char arg) const;
	int writeOutput(const char* output, int arg1, int arg2) const;
	int writeOutput(const char* output, bool clearScreenPriorToWrite) const;
	string getUserInput(const char* prompt) const;

	int writeTicTacToeBoard(TicTacToeBoard board) const;
};

