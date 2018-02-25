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

static const int dx[8] = {0, 0, -1, 1, -1, 1, -1, 1};
static const int dy[8] = {-1, 1, 0, 0, -1, 1, 1, -1};

GameState Board::isWin() {
    int cnt = 0;

    int x = last_x;
    int y = last_y;
    char sgn = board[x][y];

    for(int pos = 0; pos < 8; pos += 2) {
        int cur = 1;

        for(int t = 0; t < 2; t++) {
            for(int i = x + dx[pos + t], j = y + dy[pos + t]; isCorrect(i) && isCorrect(j); i += dx[pos + t], j += dy[pos + t]) {
                if(!checkSign(i, j, sgn))
                    break;
                cur++;
            }
        }

        if(cur > cnt) {
            cnt = cur;
        }
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