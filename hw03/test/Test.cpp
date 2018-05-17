#include "Test.h"
#include "iostream"

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::showFinalResult() {
    if(!failedNum) {
    	std::cout << "All tests passed.\n";
    }
    else {
        std::cout << "Passed" << totalNum - failedNum << " of " << totalNum << " tests.\n";
    }
}

bool Test::check(bool expr, const char *func, const char *filename, std::size_t lineNum) {
	Test::totalNum++;
    if(!expr) {
        std::cout << "TEST FAILURE: function " << func << " in " << filename << ":" << lineNum << "\n";
        Test::failedNum++;
    }
    return !expr;
}