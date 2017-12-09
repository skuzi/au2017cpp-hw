#include "Board.h"

bool Board::isCorrect(int x){
   	return x >= 0 && x < DIMENSION_SIZE;
}

void Board::move(int x, int y, char sgn) {
	board[x][y] = sgn;
	last_x = x;
	last_y = y;
	busy_cnt++;
}

bool Board::canMove(int x, int y, char sgn) {
	return isCorrect(x) && isCorrect(y) && (sgn == 'X' || sgn == 'O') && board[x][y] == '.';
}

bool Board::checkSign(int x, int y, char sgn) {
	return sgn == board[x][y];
}

void Board::add_horizontal(int &horizontal, int x, int y, char sgn) {
	for(int i = x - 1; isCorrect(i); i--) {
		if(!checkSign(i, y, sgn))
			break;
		horizontal++;
	}

	for(int i = x + 1; isCorrect(i); i++) {
		if(!checkSign(i, y, sgn))
			break;
		horizontal++;
	}
}

void Board::add_vertical(int &vertical, int x, int y, char sgn) {
	for(int i = y - 1; isCorrect(i); i--) {
		if(!checkSign(x, i, sgn)) {
			break;
		}
		vertical++;
	}

	for(int i = y + 1; i < DIMENSION_SIZE; i++) {
		if(!checkSign(x, i, sgn)) {
			break;
		}
		vertical++;
	}
}

void Board::add_diagonal(int &diagonal, int x, int y, char sgn) {
	int diagonal1 = 1;
	for(int i = x - 1, j = y - 1; isCorrect(i) && isCorrect(j); i--, j--) {
		if(!checkSign(i, j, sgn))
			break;
		diagonal1++;
	}
	for(int i = x + 1, j = y + 1; isCorrect(i) && isCorrect(j); i++, j++) {
		if(!checkSign(i, j, sgn))
			break;
		diagonal1++;
	}

	int diagonal2 = 1;
	for(int i = x + 1, j = y - 1; isCorrect(i) && isCorrect(j); i++, j--) {
		if(!checkSign(i, j, sgn))
			break;
		diagonal2++;
	}

	for(int i = x - 1, j = y + 1; isCorrect(i) && isCorrect(j); i--, j++) {
		if(!checkSign(i, j, sgn))
			break;
		diagonal2++;
	}

	diagonal = (diagonal1 > diagonal2 ? diagonal1 : diagonal2);
}

GAME_STATE Board::isWin() {
	int horizontal = 1;
	int vertical = 1; 
	int diagonal = 1;

	int x = last_x;
	int y = last_y;
	char sgn = board[x][y];
	add_horizontal(horizontal, x, y, sgn);
	add_vertical(vertical, x, y, sgn);
	add_diagonal(diagonal, x, y, sgn);
	if(horizontal >= COUNT_TO_END || vertical >= COUNT_TO_END || diagonal >= COUNT_TO_END){
		return sgn == 'X' ? X_WIN : O_WIN;
	}	
	else {
		return busy_cnt == BOARD_SIZE ? DRAW : NOT_OVER;
	}

}

Board::Board():
	last_x(0), last_y(0), busy_cnt(0)
{
	for(int i = 0; i < DIMENSION_SIZE; i++) {
		for(int j = 0; j < DIMENSION_SIZE; j++) {
			board[i][j] = '.';
		}
	}
}

char Board::getSign(int x, int y) {
	return board[x][y];
}