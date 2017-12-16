#include "Test.h"
#include "BoardTest.h"
#include "Board.h"
#define DO_CHECK(EXPR) BoardTest::check(EXPR, __FUNCTION__, __FILE__, __LINE__)

void BoardTest::test_isWin() {
    {
        
        Board b;
        b.move(0, 0, 'X');
        b.move(0, 1, 'O');
        b.move(0, 2, 'X');
        b.move(0, 3, 'X');
        DO_CHECK(b.isWin() == NOT_OVER);
    }

    {
        
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
        DO_CHECK(b.isWin() == X_WIN);
    }

    {
        
        Board b;
        b.move(0, 0, 'O');
        b.move(0, 1, 'O');
        b.move(1, 1, 'X');
        b.move(0, 2, 'O');
        b.move(0, 3, 'O');
        b.move(1, 2, 'X');
        b.move(0, 4, 'O');
        DO_CHECK(b.isWin() == O_WIN);
    }
}

void BoardTest::test_isCorrect() {
    Board b;
    DO_CHECK(b.isCorrect(-1) == false);
    DO_CHECK(b.isCorrect(10) == false);
    DO_CHECK(b.isCorrect(1000000000) == false);
    DO_CHECK(b.isCorrect(3) == true);
}

void BoardTest::test_canMove() {
    {
        Board b;
        b.move(0, 0, 'X');
        DO_CHECK(!b.canMove(0, 0, 'O'));
    }

    {
        Board b;
        b.move(0, 0, 'X');
        DO_CHECK(!b.canMove(0, 0, 'X'));
    }

    {
        Board b;
        b.move(0, 0, 'X');
        DO_CHECK(!b.canMove(0, 0, 'A'));
    }

    {
        Board b;
        DO_CHECK(b.canMove(0, 0, 'O'));
        DO_CHECK(!b.canMove(0, 0, 'A'));
        DO_CHECK(!b.canMove(-1, 0, 'O'));
        DO_CHECK(!b.canMove(10, 10, 'O'));
    }
}

void BoardTest::test_getTurn() {
    {
        
        Board b;
        b.move(0, 0, 'O');
        DO_CHECK(b.getTurn() == X_TURN);
    }

    {
        
        Board b;
        b.move(5, 6, 'O');
        b.move(0, 0, 'X');
        DO_CHECK(b.getTurn() == O_TURN);
    }

    {
        
        Board b;
        DO_CHECK(b.getTurn() == O_TURN);
    }
}


void BoardTest::test_getSign() {
    {
        
        Board b;
        b.move(0, 9, 'X');
        DO_CHECK(b.getSign(0, 9) == 'X');
    }

    {
        
        Board b;
        b.move(7, 2, 'O');
        DO_CHECK(b.getSign(7, 2) == 'O');
    }

    {
        
        Board b;
        DO_CHECK(b.getSign(6, 9) == '.');
    }
}

void BoardTest::runAllTests() {
//Considering Board::move() method correct. Otherwise we must test is using other methods which, for their part, are tested via Board::move()
    test_isWin();
    test_getSign();
    test_getTurn();
    test_canMove();
    test_isCorrect();
}