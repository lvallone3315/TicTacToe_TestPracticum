#pragma once
/*****************************************************************//**
 * \file   TicTacToeBoard.h
 * \brief  board class - TicTacToeBoard
 *     Scope - all aspects of the board, including defining the # rows & columns, win conditions, current/starting player
 *        supports retrieving data elements for displaying the board
 *
 * \author Lee
 * \date   updated: November 2025
 *
 * Implementation notes:
 *     - Player enum is used for both the name of the player & for the player's move
 *     - lots of Technical debt in this implementation, including need to consistently use BOARD_NUM_ROWS and BOARD_NUM_COLS
 *     - the range for valid rows & columns is [0,2], all other values are invalid (note: max = BOARD_NUM_... - 1)
 *     - if row or column is out of range, all methods should throw an invalid argument exception
 *
 * constructor                                 - initializes board via resetBoard() method
 * resetBoard()                                - initializes board & number of turns played in current game
 *                                               (note: no method currently implemented returns # of cells played)
 * bool isSquareEmpty(int row, int column)     - returns true = square empty, false otherwise
 * bool writeSquare(int row, int column, Player player) - if cell empty, writes enum into square & returns true, returns false if square !empty
 * char getSquareContents(int row, int column) - returns character in specified square (e.g. 'X', 'O', ' ')
 * 
 * Player getPlayer()                          - returns player (enum) whose turn it is
 * char getPlayerName()                        - returns player (character) whose turn it is
 * Player nextPlayer()                         - swaps player whose turn it is &
 *                                                 returns Player (ie enum) of the new player (e.g. if O playing, returns X)
 * bool isWinner(Player playerToCheck)         - true if the specified player has won, false otherwise
 * bool isDraw()                               - true if no-one has won & no open squares, false otherwise (e.g. consider - no spaces empty)
 **/

class TicTacToeBoard
{

public:
	enum Player { X, O, EMPTY};    // define player enums, map to display character

	// define some constants for public consumption, note initial player defined here in the Board class
	static constexpr int BOARD_NUM_ROWS = 3;
	static constexpr int BOARD_NUM_COLS = 3;
	static constexpr Player INITIAL_PLAYER = Player::X;


	TicTacToeBoard();
	void resetBoard();										// resets the squares to EMPTY as the # of turns played in the current game
	bool isSquareEmpty(int row, int col) const;				// returns true if given space is empty, false if already occupied
	bool writeSquare(int row, int col, Player currentPlayer);  // returns true if successfully written, false on failure (e.g. space not empty)
	char getSquareContents(int row, int col) const;       // used for displaying board, return player character
	Player getPlayer() const;								// returns internal ID (ie enum) of the player
	char getPlayerName() const;							  // returns name of the player - hardcoded as 'X' or 'O'
	Player nextPlayer();					              // swap player for next move, returns new player
	bool isWinner(Player playerToCheck) const;           // check if specified player has won
	bool isDraw() const; // check if a draw



private:  // reserve memory for board & current player
	Player board[BOARD_NUM_ROWS][BOARD_NUM_COLS];      // board storage, indexed by row [0-2] and column [0-2]
	Player player = INITIAL_PLAYER;                    // tracks the current player, ie next symbol placed
	int takenSquareCount = 0;                        // # of spaces played in current game, reset for new games
	char playerMap(Player playerEnum) const;		// map player enum to player character - ToDo - create mapping list rather than switch statement

};