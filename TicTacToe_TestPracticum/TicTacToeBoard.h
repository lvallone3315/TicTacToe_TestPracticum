#pragma once
/*****************************************************************//**
 * \file   TicTacToeBoard.h
 * \brief  board class - TicTacToeBoard
 *     Scope - all aspects of the board, including defining the # rows & columns, win conditions, current/starting player
 *        supports retrieving data elements for displaying the board
 *
 * \author Lee
 * \date   updated: October 2026
 *
 * Implementation notes:
 *     - Player enum is used for both the name of the player & for the player's move
 *       getPlayerName() returns a character representation for the enum (e.g. enum X returns 'X')
 *     - lots of Technical debt in this implementation, including need to consistently use BOARD_NUM_ROWS and BOARD_NUM_COLS
 *     - the range for valid rows & columns is [0,2], all other values are invalid (note: max = BOARD_NUM_... - 1)
 *     - if row or column is out of range, all methods should throw an invalid argument exception
 *     - Board tracks # of squares played, but no method currently returns this value
 *     - Every public method with row & column arguments should validate the arguments and throw an invalid argument exception if out of range
 *
 * constructor                                 - initializes board via resetBoard() method
 * resetBoard()                                - initializes all squares to EMPTY and number of turns played to 0
 *												 the current player remains unchanged (e.g. if X is playing, X remains player after resetBoard)
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
	enum Player { X, O, EMPTY };    // define player enums, map to display character, ToDo: use "class" for type safety

	// define some constants for public consumption, note initial player defined here in the Board class
	static constexpr int BOARD_NUM_ROWS = 3;
	static constexpr int BOARD_NUM_COLS = 3;
	static constexpr Player INITIAL_PLAYER = Player::X;


	TicTacToeBoard();
	void resetBoard();										// resets the squares to EMPTY and # of turns played in the current game
		                                                    //   Note: reset board DOES NOT reinitialize the player whose turn it is
	bool isSquareEmpty(int row, int col) const;				// returns true if given space is empty, false if already occupied
	bool writeSquare(int row, int col, Player currentPlayer);  // returns true if successfully written, false if square !empty
	char getSquareContents(int row, int col) const;       // used for displaying board, return player character
	Player getPlayer() const;								// returns internal ID (ie enum) of the player
	char getPlayerName() const;							  // returns name of the player as a character (e.g. 'X', 'O')
	Player nextPlayer();					              // swap player for next move, returns new player
	bool isWinner(Player playerToCheck) const;           // check if specified player has won
	bool isDraw() const;								// check if a draw



private:  // reserve memory for board & current player
	Player board[BOARD_NUM_ROWS][BOARD_NUM_COLS];      // board storage, indexed by row [0-2] and column [0-2]
	Player player = INITIAL_PLAYER;                    // tracks the current player, ie next symbol placed, only initialized when board created
	int takenSquareCount = 0;                        // # of spaces played in current game, reset for new games

	  // map player enum to player character - used as a helper function
	char playerMap(Player playerEnum) const;		// ToDo - create mapping list rather than switch statement
	  // validates arguments against BOARD_NUM_..., throws invalid arg exception
	void validateRowsAndColumns(int row, int column) const;
};