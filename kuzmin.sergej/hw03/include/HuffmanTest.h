#include "Test.h"
#include "huffman.h"
#include <sstream>
#include <fstream>
#include <ctime>
#include <iostream>
#include <string>
#define DO_CHECK(EXPR) HuffmanTest::check(EXPR, __FUNCTION__, __FILE__, __LINE__)

class HuffmanTest : public Test {
public:
	HuffmanTest(std::size_t cnt, std::size_t sz) : cnt(cnt), max_size(sz) {}
	void test_all() {
		std::cerr<<"===================\ntest decoding\n=================\n";
		std::ifstream input("/dev/urandom", std::ios::in | std::ios::binary);
		for(std::size_t test_n = 1; test_n <= cnt; test_n++) {
			HuffmanTree tree_pack;
			HuffmanTree tree_unpack;
			std::stringstream in;
			std::stringstream packed;
			std::stringstream unpacked;

			std::size_t size = rand() % (max_size + 1);
			
			in.str("");
			packed.str("");
			unpacked.str("");

			for(std::size_t j = 0; j < size; j++) {
				char c = '\0';
				input.read(&c, 1);
				in << c;
			}
			std::cerr << "test " << test_n << '\n';

			std::cerr << "packing...\n";
			tree_pack.encode(in, packed);
			std::cerr << "packed.\n============\n";
			std::size_t time0 = time(NULL);
			std::cerr << "unpacking...\n";
			tree_unpack.decode(packed, unpacked);
			std::cerr << "unpacked.\n===========\n";
			std::size_t time1 = time(NULL);
			//std::cerr << "not there?" << '\n';
			DO_CHECK(unpacked.str() == in.str() && time1 - time0 < 5);
		}
	}
	void runAllTests() {
		test_all();
	}
private:
	std::size_t cnt;
	std::size_t max_size;
};