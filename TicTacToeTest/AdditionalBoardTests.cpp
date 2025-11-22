#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../TicTacToe_TestPracticum/TicTacToeBoard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TicTacToeTest
{
	TEST_CLASS(TicTacToeAdditionalBoardTests)
	{
		TicTacToeBoard board;

	public:

		TEST_CLASS_INITIALIZE(_Setup_BoardClassTest)
		{
			// this method is run once for the TicTacToeTest class
			//    intentionally blank (other than the log message) - nothing to initialize at this time
			Logger::WriteMessage("Test class initialized\n");
		}

		TEST_METHOD_INITIALIZE(_Setup_MethodTest) {
			// this method is run prior to EVERY test case inside the class (ie this file)
			Logger::WriteMessage("Initializing Board object for additional tests.\n");
			board.resetBoard();          // reinitialize board via method, rather than creating a new board object
		}

		TEST_METHOD(HelloAdditionalTests) {
			Logger::WriteMessage("Running additional tests on the Board object");
		}

		// the following test expands on the test verifying player X starts
		//   and verifies 
		//      getPlayer() returns the correct enum &
		//      nextPlayer() correctly switches from X to O &
		//        also correctly switches from O back to X
		TEST_METHOD(ExpandedGameStartPlayerX)
		{
			Logger::WriteMessage("Testing X is selected as first player\n");
			// verify X is to play, O is NOT to play
			Assert::AreEqual(board.getPlayerName(), 'X');
			Assert::AreNotEqual(board.getPlayerName(), 'O');

			// expanding test to verify the enum returned is X
			Logger::WriteMessage("Testing enum returned by getPlayer() is also X\n");
			Assert::AreEqual(static_cast<int>(TicTacToeBoard::X),
				static_cast<int>(board.getPlayer()));

			// test switching to player O
			Logger::WriteMessage("Switch players via board.nextPlayer() to O, and verify all methods\n");
			board.nextPlayer();
			//    getPlayer() enum
			Assert::AreEqual(static_cast<int>(TicTacToeBoard::O),
				static_cast<int>(board.getPlayer()));
			Assert::AreNotEqual(static_cast<int>(TicTacToeBoard::X),
				static_cast<int>(board.getPlayer()));
			//    getPlayerName() character
			Assert::AreEqual(board.getPlayerName(), 'O');
			Assert::AreNotEqual(board.getPlayerName(), 'X');

			// test switching back to player X
			Logger::WriteMessage("Switch players via board.nextPlayer() back to X, and verify all methods\n");
			board.nextPlayer();
			//    getPlayer() enum
			Assert::AreEqual(static_cast<int>(TicTacToeBoard::X),
				static_cast<int>(board.getPlayer()));
			Assert::AreNotEqual(static_cast<int>(TicTacToeBoard::O),
				static_cast<int>(board.getPlayer()));
			//    getPlayerName() character
			Assert::AreEqual(board.getPlayerName(), 'X');
			Assert::AreNotEqual(board.getPlayerName(), 'O');
		}

		// 	the following tests the draw logic for one scenario
		//   and verifies 
		//      there is no draw up until the last square is filled in
		//      neither X or O has won the game - at start, after the 8th move & after the final move
		TEST_METHOD(TestDrawLV1) {
			Logger::WriteMessage("Draw scenario - v1, all spaces marked, no one wins");
			// verify no one has won & there isn't a draw
			// Precondition checks - no draw, no one-has won
			Assert::IsFalse(board.isDraw());
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O));
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X));
			// Create a draw condition   X O X
			//                           O X O
			//                           O X O
			board.writeSquare(0, 0, TicTacToeBoard::X);
			board.writeSquare(0, 1, TicTacToeBoard::O);
			board.writeSquare(0, 2, TicTacToeBoard::X);
			board.writeSquare(1, 0, TicTacToeBoard::O);
			board.writeSquare(1, 1, TicTacToeBoard::X);
			board.writeSquare(1, 2, TicTacToeBoard::O);
			board.writeSquare(2, 0, TicTacToeBoard::O);
			board.writeSquare(2, 1, TicTacToeBoard::X);
			// Prior to final move - rerun precondition checks
			Assert::IsFalse(board.isDraw());
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O));
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X));
			// Create the draw
			board.writeSquare(2, 2, TicTacToeBoard::O);
			// Verify no winner, and there exists a draw
			Assert::IsTrue(board.isDraw(), L"Post final move: expect a Draw, but isDraw() returned false");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O), L"Post final move, expect no one has won, but O did win");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X), L"Post final move, expect no one has won, but X did win");
		}
		
		// Testing X winning a game
		// scenario:   X  O  X
		//             O  X  X
		//             X  X  X
		//   Note: in this scenario - X wins on 7th move, but continues to fill in additional cells
		// LV - adding precondition checks & also checks b4 and after first winning move
		//   Add error messages if asserts fail
		TEST_METHOD(TestWinX_LV) {
			Logger::WriteMessage("Testing Win X Validation - updated with pre & post asserts");
			// reset the board & verify no winner and no draw
			board.resetBoard();
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X), L"board reset, but X showing as winner");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O), L"board reset, but O showing as winner");
			Assert::IsFalse(board.isDraw(), L"board reset, but game showing a draw");

			board.writeSquare(0, 0, TicTacToeBoard::X);
			board.writeSquare(0, 2, TicTacToeBoard::O);
			board.writeSquare(0, 1, TicTacToeBoard::X);
			board.writeSquare(1, 0, TicTacToeBoard::O);
			board.writeSquare(1, 1, TicTacToeBoard::X);
			board.writeSquare(1, 2, TicTacToeBoard::X);
			// verify no winner yet
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X), L"Expecting no winner after 6 moves, but showing X won");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O), L"Expecting no winner after 6 moves, but showing O won");
			Assert::IsFalse(board.isDraw(), L"Expecting no draw after 6 moves, but isDraw returned true!");

			board.writeSquare(2, 1, TicTacToeBoard::X);  // this should be the first winning move (X)
			// now verify that X has won, O hasn't won & there isn't a draw
			Assert::IsTrue(board.isWinner(TicTacToeBoard::X), L"Expecting X as winner, but isWinner() returned false");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O), L"Expecting only X has won, not O, but showing O won");
			Assert::IsFalse(board.isDraw(), L"Expecting no draw after 7 moves, but isDraw returned true!");

			// write X into the remaining open squares - shouldn't affect outcome
			board.writeSquare(2, 2, TicTacToeBoard::X);
			board.writeSquare(2, 0, TicTacToeBoard::X);

			// verify that X still showing as the winner & O is not
			//   consider that given the Board class doesn't deny moves once a player has won
			//   that X & O can both be showing as winners
			// Net: we should consider improving the class to deny moves after the game is won
			Assert::IsTrue(board.isWinner(TicTacToeBoard::X), L"Expecting X as winner, but isWinner() returned false");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O), L"Expecting only X has won, not O, but showing O won");
			Assert::IsFalse(board.isDraw(), L"Expecting no draw since X won, but isDraw returned true!");
		}

		// Testing O winning a game in column 2, no moves by X
		// scenario:   -  -  O
		//             -  -  O
		//             -  -  O
		TEST_METHOD(TestWinO_Column2_LV) {
			Logger::WriteMessage("Testing O winning in 2nd column, no moves by X");
			// reset the board & verify no winner and no draw
			board.resetBoard();
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X), L"board reset, but X showing as winner");
			Assert::IsFalse(board.isWinner(TicTacToeBoard::O), L"board reset, but O showing as winner");
			Assert::IsFalse(board.isDraw(), L"board reset, but game showing a draw");
			board.writeSquare(2, 2, TicTacToeBoard::O);  // for grins start from bottom of game grid
			board.writeSquare(1, 2, TicTacToeBoard::O);
			board.writeSquare(0, 2, TicTacToeBoard::O);
			Assert::IsFalse(board.isWinner(TicTacToeBoard::X), L"expected O to win, but X showing as a winner");
			Assert::IsTrue(board.isWinner(TicTacToeBoard::O), L"expecting O to win, but isWinner() returned false for O");
			Assert::IsFalse(board.isDraw(), L"game showing a draw, but only 3 moves!");
		}
	};
}
