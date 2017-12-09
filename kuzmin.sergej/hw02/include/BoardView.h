#pragma once
class View {
public:
    View(Board &board, bool silent = 0);
    void showBoard(); //вывод доски на экран
    void doGameCycle(); //основной цикл игры: ввод хода, вывод на экран доски, проверка текущего состояния
    void setSilent(bool);
private:
	Board board;
	bool silent;
};