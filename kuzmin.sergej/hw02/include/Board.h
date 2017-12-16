#pragma once
const int DIMENSION_SIZE = 10;
const int COUNT_TO_END = 5;
const int BOARD_SIZE = DIMENSION_SIZE * DIMENSION_SIZE;

enum GameState {X_WIN, O_WIN, DRAW, NOT_OVER};
enum Turn {O_TURN, X_TURN};

class  Board {
public:
    void move(int x, int y, char sign);
    bool canMove(int x, int y, char sign);
    GameState isWin();
    bool isCorrect(int x);
    char getSign(int x, int y);
    Turn getTurn();
    Board();

private:
    char board[DIMENSION_SIZE][DIMENSION_SIZE];
    int last_x;
    int last_y;
    int busy_cnt;
    Turn turn;
    bool checkSign(int x, int y, char sign);
    void changeTurn();
};