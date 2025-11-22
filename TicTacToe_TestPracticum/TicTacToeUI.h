#pragma once

#include <string>
#include "TicTacToeBoard.h"

using namespace std;  // fair programming practice, as could create scope issues, but don't feel like qualifying all reads & writes

/*
 * Header file for Fall 2023 Tic Tac Toe program UI
 *    getUserInput() prompts user with specified string and returns user input
 *    writeOutput() writes output to console and returns success (0)
 *    writeTicTacToeBoard(board) displays the board based on the contents maintained in the board class
 */

class TicTacToeUI
{
public:
	TicTacToeUI();
	int writeOutput(char* output, char arg) const;
	int writeOutput(char* output, int arg1, int arg2) const;
	int writeOutput(char* output) const;
	int writeOutput(char* output, bool clearScreenPriorToWrite) const;
	string getUserInput(char* prompt) const;

	int writeTicTacToeBoard(TicTacToeBoard board) const;
};

