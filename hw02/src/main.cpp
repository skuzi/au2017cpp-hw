#include "Board.h"
#include "BoardView.h"
#include "stdio.h"
#include "string.h"
#include <algorithm>

int main(int argc, char *argv[]) {
    Board brd;
    View view(brd);
    
    view.setSilent(argc > 1 && !strcmp(argv[1], "silent"));

    view.doGameCycle();
}