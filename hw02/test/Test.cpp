#include "Test.h"
#include "stdio.h"

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::showFinalResult() {
    if(!failedNum) {
        puts("All tests passed");
    }
    else {
        printf("Passed %d of %d tests.\n", totalNum - failedNum, totalNum);
    }
}

bool Test::check(bool expr, const char *func, const char *filename, std::size_t lineNum) {
	Test::totalNum++;
    if(!expr) {
        printf("TEST FAILURE: function %s in %s:%zu\n", func, filename, lineNum);
        Test::failedNum++;
    }
    return !expr;
}