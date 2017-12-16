#pragma once
#include <cstdlib>

class Test {
public:
	static void showFinalResult();
	static bool check(bool expr, const char *func, const char *filename, std::size_t lineNum);
	virtual void runAllTests() = 0;

protected:
	static int failedNum;
	static int totalNum;
};