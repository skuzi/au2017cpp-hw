#pragma once
const int DIMENSION_SIZE = 10;
const int COUNT_TO_END = 5;
const int BOARD_SIZE = DIMENSION_SIZE * DIMENSION_SIZE;
enum GameState {X_WIN = 2, O_WIN = 1, DRAW = 0, NOT_OVER = -1};
class  Board {
public:
    void move(int x, int y, char sign); //сделать ход
    bool canMove(int x, int y, char sign); //корректен ли ход
    GameState isWin(); // текущее состояние: играем дальше; ничья; 0 выиграли; X выиграли
    //Можно добавлять методы при необходимости.
    bool isCorrect(int x);
    bool checkSign(int x, int y, char sign);
    char getSign(int x, int y);
    Board();

private:
	char board[DIMENSION_SIZE][DIMENSION_SIZE];
	int last_x;
	int last_y;
	int busy_cnt;
	void add(int &val, int x, int y, char sign, int *dx, int *dy);
};