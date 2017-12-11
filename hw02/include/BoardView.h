#pragma once
class View {
public:
    View(Board &board, bool silent = 0);
    void showBoard();
    void doGameCycle();
    void setSilent(bool);

private:
	Board board;
	bool silent;
};