#include "HuffmanTest.h"
#include "Test.h"
#include <iostream>

int main() {
{
	std::cerr << "\n=============test 10 random files with max size of 500000 bytes=====================\n";
	HuffmanTest test(10, 500000);
	test.runAllTests();
	HuffmanTest::showFinalResult();
}

{
	std::cerr << "\n=============test empty file=====================\n";
	HuffmanTest test(5, 0);
	test.runAllTests();
	HuffmanTest::showFinalResult();
}

}