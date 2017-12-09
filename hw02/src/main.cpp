#include "Board.h"
#include "BoardView.h"
#include "stdio.h"
#include "string.h"
#include <algorithm>

int main(int argc, char *argv[]) {
	if(freopen("ss", "r", stdin));
	Board brd;
	View view(brd);
	if(argc > 1 && !strcmp(argv[1], "silent"))
		view.setSilent(1);
	view.doGameCycle();
}