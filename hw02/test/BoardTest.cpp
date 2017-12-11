#include "Test.h"
#include "BoardTest.h"
#include "Board.h"
#define DO_CHECK(EXPR) BoardTest::check(EXPR, __FUNCTION__, __FILE__, __LINE__)

BoardTest::BoardTest() {}
BoardTest::~BoardTest() {}

void BoardTest::test_isWin() {
	{
		BoardTest::totalNum++;
		Board b;
		b.move(0, 0, 'X');
		b.move(0, 1, 'O');
		b.move(0, 2, 'X');
		b.move(0, 3, 'X');
		BoardTest::failedNum += DO_CHECK(b.isWin() == NOT_OVER);
	}

	{
		BoardTest::totalNum++;
		Board b;
		b.move(0, 0, 'X');
		b.move(1, 1, 'X');
		b.move(10, 10, 'X');
		b.move(9, 9, 'X');
		b.move(5, 5, 'X');
		b.move(0, 1, 'O');
		b.move(0, 2, 'O');
		b.move(0, 3, 'O');
		b.move(0, 4, 'O');
		b.move(1, 4, 'O');
		b.move(2, 2, 'X');
		b.move(3, 3, 'X');
		b.move(4, 4, 'X');
		BoardTest::failedNum += DO_CHECK(b.isWin() == X_WIN);
	}

	{
		BoardTest::totalNum++;
		Board b;
		b.move(0, 0, 'O');
		b.move(0, 1, 'O');
		b.move(1, 1, 'X');
		b.move(0, 2, 'O');
		b.move(0, 3, 'O');
		b.move(1, 2, 'X');
		b.move(0, 4, 'O');
		BoardTest::failedNum += DO_CHECK(b.isWin() == O_WIN);
	}
}

void BoardTest::test_isCorrect() {
	Board b;
	BoardTest::failedNum += DO_CHECK(b.isCorrect(-1) == false);
	BoardTest::failedNum += DO_CHECK(b.isCorrect(10) == false);
	BoardTest::failedNum += DO_CHECK(b.isCorrect(1000000000) == false);
	BoardTest::failedNum += DO_CHECK(b.isCorrect(3) == true);

	BoardTest::totalNum += 4;
}

void BoardTest::test_canMove() {
	{
		BoardTest::totalNum++;
		Board b;
		b.move(0, 0, 'X');
		BoardTest::failedNum += DO_CHECK(!b.canMove(0, 0, 'O'));
	}

	{
		BoardTest::totalNum++;
		Board b;
		b.move(0, 0, 'X');
		BoardTest::failedNum += DO_CHECK(!b.canMove(0, 0, 'X'));
	}

	{
		BoardTest::totalNum++;
		Board b;
		b.move(0, 0, 'X');
		BoardTest::failedNum += DO_CHECK(!b.canMove(0, 0, 'A'));
	}

	{
		BoardTest::totalNum++;
		Board b;
		BoardTest::failedNum += DO_CHECK(b.canMove(0, 0, 'O'));
	}

	{
		BoardTest::totalNum++;
		Board b;
		BoardTest::failedNum += DO_CHECK(!b.canMove(0, 0, 'A'));
	}

	{
		BoardTest::totalNum++;
		Board b;
		BoardTest::failedNum += DO_CHECK(!b.canMove(-1, 0, 'O'));
	}

	{
		BoardTest::totalNum++;
		Board b;
		BoardTest::failedNum += DO_CHECK(!b.canMove(10, 10, 'O'));
	}
}

void BoardTest::test_checkSign() {
	{
		BoardTest::totalNum++;
		Board b;
		b.move(0, 0, 'X');
		BoardTest::failedNum += DO_CHECK(b.checkSign(0, 0, 'X'));
	}

	{
		BoardTest::totalNum++;
		Board b;
		b.move(5, 6, 'O');
		BoardTest::failedNum += DO_CHECK(b.checkSign(5, 6, 'O'));
	}

	{
		BoardTest::totalNum++;
		Board b;
		BoardTest::failedNum += DO_CHECK(b.checkSign(4, 8, '.'));
	}
}

void BoardTest::test_move() {
	/*{
		BoardTest::totalNum++;
		Board b;
		b.
	}*/
}

void BoardTest::test_getSign() {
	{
		BoardTest::totalNum++;
		Board b;
		b.move(0, 9, 'X');
		BoardTest::failedNum += DO_CHECK(b.getSign(0, 9) == 'X');
	}

	{
		BoardTest::totalNum++;
		Board b;
		b.move(7, 2, 'O');
		BoardTest::failedNum += DO_CHECK(b.getSign(7, 2) == 'O');
	}

	{
		BoardTest::totalNum++;
		Board b;
		BoardTest::failedNum += DO_CHECK(b.getSign(6, 9) == '.');
	}
}

void BoardTest::runAllTests() {
	test_move();
	test_isWin();
	test_getSign();
	test_checkSign();
	test_canMove();
	test_isCorrect();
}