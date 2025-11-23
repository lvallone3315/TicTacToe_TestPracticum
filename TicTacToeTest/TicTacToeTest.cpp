#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../TicTacToe_TestPracticum/TicTacToeBoard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// TicTacToe automated unit test example (starting place)
//   ToDo: remove max board & column hardcoding (ideally - retrieve from source code)

namespace TicTacToeTest
{
	TEST_CLASS(TicTacToeTest)
	{
	public:
		TicTacToeBoard board;   // declare board here so all test cases can access the board object
		                        //   re-init prior to each test case (see below)

		TEST_CLASS_INITIALIZE(_Setup_BoardClassTest)
		{
			// this method is run once for the TicTacToeTest class
			//    intentionally blank (other than the log message) - nothing to initialize at this time
			Logger::WriteMessage("Test class initialized\n");
		}

		TEST_METHOD_INITIALIZE(_Setup_MethodTest) {
			// this method is run prior to EVERY test case inside the class (ie this file)
			Logger::WriteMessage("Initializing Board object.\n");
			// reinitialize board
			//   option to use board.resetBoard(), mimics starting new game after a previous win or draw
			board = TicTacToeBoard();
		}

		//                  ***   Unit tests ***
		// 
		//   verify X is first player after board initializes
		//   methods (used in the following test case):
		//      getPlayerName() - returns character representing player whose turn it is (should be 'X')
		TEST_METHOD(GameStartPlayerX)
		{
			Logger::WriteMessage("Testing X is selected as first player\n");
			// verify X is to play, O is NOT to play
			Assert::AreEqual(board.getPlayerName(), 'X', L"Expected X to be first player, but wasn't");
			Assert::AreNotEqual(board.getPlayerName(), 'O');
		}


		// Game start check - all squares should be empty & no-one has won
		//   methods:
		//      isWinner(player enum) - true if specified player has won, false in all other conditions
		//      isSquareEmpty(row, column) - true if specified location is empty, range [0-2] for both row & column
		TEST_METHOD(SquaresEmptyAndNoWonHasWon) {

			Logger::WriteMessage("Game start: testing neither X or O has won\n");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X), L"Game start: X should not have won");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O), L"Game start: O should not have won");

			Logger::WriteMessage("Verify all squares are empty\n");
			for (int row = 0; row < 2; row++) {
				for (int column = 0; column < 2; column++) {
					Assert::IsTrue(board.isSquareEmpty(0, 0), L"Square should be empty, but isn't");
				}
			}  // end verifying all game squares empty
		}

		TEST_METHOD(TestRandomMoves) {
			// Verify can mark a cell with a given player's move
			//    approach - try both corners of the grid, and then one in the middle
			//    row & column should be in range [0,2]
			// Methods:
			//    :writeSquare(int row, int col, char currentPlayer) - returns true if write successful, false otherwise
			//    :getSquareContents(int row, int col) - if square marked, returns player character; blank otherwise
			//    :isSquareEmpty(int row, int col) - true if the square is not marked, false otherwise
			Logger::WriteMessage("Testing we can write X & O into different cells\n");

			// write cell 0,0 & verify the cell is written correctly
			// note: pre-condition check(s), action (e.g. write the square) & then post-action verification
			Assert::AreEqual(' ', board.getSquareContents(0, 0), L"Expected a blank in 0,0, but received something else");
			Assert::IsTrue(board.isSquareEmpty(0, 0));
			board.writeSquare(0, 0, TicTacToeBoard::X);
			Assert::AreEqual('X', board.getSquareContents(0, 0), L"Expected X in 0,0, but received something else");
			Assert::IsFalse(board.isSquareEmpty(0, 0), L"Expected square to have a non-blank, but shown as not empty");

			// now test other extreme row 2, column 2, mix it up & write O into this square
			Assert::IsTrue(board.isSquareEmpty(2, 2));
			board.writeSquare(2, 2, TicTacToeBoard::O);
			Assert::AreEqual('O', board.getSquareContents(2, 2), L"Expected O in 2,2, but received something else");
			Assert::IsFalse(board.isSquareEmpty(2, 2));

			// now test something in the middle - e.g. 1, 1
			Assert::IsTrue(board.isSquareEmpty(1, 1));
			board.writeSquare(1,1, TicTacToeBoard::O);
			Assert::AreEqual('O', board.getSquareContents(2, 2), L"Expected O in 1,1, but received something else");
			Assert::IsFalse(board.isSquareEmpty(1,1));
		}

		// The following methods take range restricted arguments:
		//   writeSquare (row [0:2], column [0:2], player - but this is an enum, can't go out of range)
		//   isSquareEmpty (row [0:2], column [0:2])
		//   getSquareContents(row [0:2], column [0:2], )
		// 
		// All three methods should throw an invalid argument exception if the parameters are out of range
		//   Test case below is a sample
		//   
		//   Note - squashed catch blocks after the first for readability
		TEST_METHOD(Exception_Handling) {
			//  writeSquare - try invalid rows & columns, valid ranges are row [0:2] & column [0:2]
			try {
				Logger::WriteMessage("\nTesting invalid row, 3, passed to writeSquare\n");
				board.writeSquare(3, 0, TicTacToeBoard::X);
				// the above should throw an exception, triggering the catch block
				//    hence the Assert::Fail should never execute
				Assert::Fail(L"Expected std::invalid_argument not thrown");
			}
			catch (const std::invalid_argument& ex) {  // catch invalid arg execption thrown
				Logger::WriteMessage(ex.what());
			}
			catch (...) {   // if a different exception is thrown, will end up here, and the test case will fail
				Assert::Fail(L"Unexpected exception type thrown");
			}

			//  getSquareContents(row, column), valid range [0:2][0:2]
			//     far out of range, 2^16
			try {
				Logger::WriteMessage("\nTesting invalid column, 65536, passed to getSquareContents\n");
				board.getSquareContents(0, 65536);
				Assert::Fail(L"Expected std::invalid_argument not thrown");
			}
			catch (const std::invalid_argument& ex) { Logger::WriteMessage(ex.what()); }
			catch (...) { Assert::Fail(L"Unexpected exception type thrown"); }
		}
	}; 
}

/* Board class - method description
* Implementation notes :
* -Player enum is used for both the name of the player& for the player's move
* -lots of Technical debt in this implementation, including need to consistently use BOARD_NUM_ROWS and BOARD_NUM_COLS
* - the range for valid rows & columns is [0,2], all other values are invalid
*
* constructor - initializes board via resetBoard() method
* resetBoard() - initializes board & number of turns played in current game
* bool isSquareEmpty(int row, int column) - returns true = empty, false otherwise
* bool writeSquare(int row, int column, Player player) - returns false if can’t write square
* char getSquareContents(int row, int column) - returns character in specified square(e.g. 'X', 'O', ' ')
* Player getPlayer() - returns player(enum) whose turn it is
* char getPlayerName() - returns player(character) whose turn it is
* Player nextPlayer() - returns Player(ie enum) of the next player(e.g. if O playing, returns X)
* bool isWinner(Player playerToCheck) - true if the specified player has won, false otherwise
* bool isDraw() - true if no - one has won, false otherwise(e.g.consider - no spaces empty)
**/

/*
Common Test Automation Asserts including Examples
•	Assert::AreEqual(expected, actual, message): Checks if two values are equal.
		 Assert::AreEqual(5, my_function(2, 3), L"my_function should return 5 for inputs 2 and 3");
•	Assert::AreNotEqual(expected, actual, message): Checks if two values are not equal.
		 Assert::AreNotEqual(0, my_function(1, 0), L"my_function should not return 0 for inputs 1 and 0");
•	Assert::IsTrue(condition, message): Checks if a condition is true.
		Assert::IsTrue(my_object.IsValid(), L"my_object should be valid after initialization");
•	Assert::IsFalse(condition, message): Checks if a condition is false.
		Assert::IsFalse(my_object.IsEmpty(), L"my_object should not be empty after adding elements");
•	Assert::IsNull(pointer, message): Checks if a pointer is null.
		Assert::IsNull(my_pointer, L"my_pointer should be null after deletion");
•	Assert::IsNotNull(pointer, message): Checks if a pointer is not null.
		Assert::IsNotNull(my_pointer, L"my_pointer should not be null after allocation");
•	Assert::Fail(message): Forces a test failure with a specified message.
		Assert::Fail(L"This code path should never be reached");

Important Notes:
•	The message parameter in these methods is optional but highly recommended for providing context about the assertion's purpose, especially when a test fails.
•	The string literals used for messages should be wide-character strings (prefixed with L) to be compatible with the framework.
•	These assertions are part of the Microsoft::VisualStudio::CppUnitTestFramework namespace. You typically include the necessary header and use this namespace in your test files.
C++
	#include "CppUnitTest.h"
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
*/
