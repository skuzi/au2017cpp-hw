#pragma once
#include "Test.h"

class BoardTest: public Test {
public:
    void test_isWin();
    void test_isCorrect();
    void test_canMove();
    void test_getTurn();
    void test_move();
    void test_getSign();
    void runAllTests();
};