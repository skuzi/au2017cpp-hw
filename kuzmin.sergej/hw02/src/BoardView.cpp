#include "Board.h"
#include "BoardView.h"
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

enum TURN {O_TURN = 0, X_TURN = 1};

View::View(Board &board, bool silent) {
	this->board = board;
	this->silent = silent;
}

void changeTurn(TURN &turn) {
	if(turn == O_TURN) {
		turn = X_TURN;
	}
	else {
		turn = O_TURN;
	}
}

void View::showBoard() {
	for(int i = 0; i < DIMENSION_SIZE; i++) {
		for(int j = 0; j < DIMENSION_SIZE; j++) {
			printf("%c", board.getSign(i, j));
		}
		printf("\n");
	}
}

void View::setSilent(bool val) {
	silent = val;
}

void View::doGameCycle() {
	TURN turn = X_TURN;
	do {
		if(!silent)
			showBoard();
		int x = 0;
		int y = 0;
		char sgn = 0;
		do {
			printf(turn == O_TURN ? "O" : "X");
			printf(" move: ");
			if(scanf("%d %d", &x, &y) != 2 || (x == -1 && y == -1)) {
				exit(0);
				return;
			}
			if(scanf(" %c", &sgn) && board.canMove(x, y, sgn) && sgn == (turn == X_TURN ? 'X' : 'O')) {
				board.move(x, y, sgn);
				break;
			}
			else {
				printf("Bad move!\n");
			}
		} while(1);
		changeTurn(turn);
	} while(board.isWin() == NOT_OVER);
	
	showBoard();

	GAME_STATE state = board.isWin();

	if(state == DRAW) {
		printf("Draw.");
	}
	else if(state == X_WIN) {
		printf("X wins!");
	}
	else if(state == O_WIN) {
		printf("O wins!");
	}
}