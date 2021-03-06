#include "Board.h"
#include "BoardView.h"
#include "stdio.h"

View::View(Board &board, bool silent) {
    this->board = board;
    this->silent = silent;
}

void changeTurn(Turn &turn) {
    turn = turn == O_TURN ? X_TURN : O_TURN;
}

void View::showBoard() {
    printf("\n");
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
    do {
        if(!silent)
            showBoard();

        int x = 0;
        int y = 0;
        char sgn = board.getTurn() == O_TURN ? 'O' : 'X';

        do {
            printf("%c move: ", sgn);
            int ret = scanf("%d %d", &x, &y);
            if(x == -1 && y == -1) {
                return;
            }
            if(ret == 2 && board.canMove(x, y, sgn)) {
                board.move(x, y, sgn);
                break;
            }
            else {
                printf("Bad move!\n");
            }
        } while(1);

    } while(board.isWin() == NOT_OVER);
    
    showBoard();

    GameState state = board.isWin();

    if(state == DRAW) {
        printf("Draw.");
    }
    else if(state == X_WIN) {
        printf("X wins!");
    }
    else if(state == O_WIN) {
        printf("O wins!");
    }
    printf("\n");
}