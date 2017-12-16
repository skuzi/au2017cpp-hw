#include "Board.h"

bool Board::isCorrect(int x){
    return x >= 0 && x < DIMENSION_SIZE;
}

void Board::move(int x, int y, char sgn) {
    board[x][y] = sgn;
    last_x = x;
    last_y = y;
    busy_cnt++;
    changeTurn();
}

bool Board::canMove(int x, int y, char sgn) {
    return isCorrect(x) && isCorrect(y) && (sgn == 'X' || sgn == 'O') && board[x][y] == '.';
}

bool Board::checkSign(int x, int y, char sgn) {
    return sgn == board[x][y];
}

void Board::recalc(int &val, int x, int y, char sgn, int *dx, int *dy) {
    int cur = 0;
    for(int t = 0; t < 2; t++) {
        for(int i = x + dx[t], j = y + dy[t]; isCorrect(i) && isCorrect(j); i += dx[t], j += dy[t]) {
            if(!checkSign(i, j, sgn))
                break;
            cur++;
        }
    }
    if(cur > val) {
        val = cur;
    }
}


GameState Board::isWin() {
    int cnt = 0;

    int x = last_x;
    int y = last_y;
    char sgn = board[x][y];
    int dx[8] = {0, 0, -1, 1, -1, 1, -1, 1};
    int dy[8] = {-1, 1, 0, 0, -1, 1, 1, -1};

    for(int i = 0; i < 8; i += 2) {
        recalc(cnt, x, y, sgn, dx + i, dy + i);
    }

    if(cnt >= COUNT_TO_END){
        return sgn == 'X' ? X_WIN : O_WIN;
    }    
    else {
        return busy_cnt == BOARD_SIZE ? DRAW : NOT_OVER;
    }

}

Board::Board():
    last_x(0), last_y(0), busy_cnt(0), turn(O_TURN)
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

void Board::changeTurn() {
    if(turn == O_TURN) {
        turn = X_TURN;
    }
    else {
        turn = O_TURN;
    }
}

Turn Board::getTurn() {
    return turn;
}