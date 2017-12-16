#include "Board.h"
#include "BoardView.h"
#include "string.h"

int main(int argc, char *argv[]) {
    Board brd;
    View view(brd);
    
    view.setSilent(argc > 1 && !strcmp(argv[1], "silent"));

    view.doGameCycle();
}