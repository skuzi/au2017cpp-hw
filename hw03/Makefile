EXE = huffman
TEST = "test"
COMPILER = g++

CFLAGS  = -Wall -Werror -O2 -Iinclude -g -std=c++11


all: bin $(EXE)
board_test: bin $(TEST)

bin:
	mkdir bin

$(EXE): ./bin/huffman.o ./bin/main.o
	$(COMPILER) $(CFLAGS) ./bin/main.o ./bin/huffman.o -o $(EXE)

#$(TEST): ./bin/test.o ./bin/Board.o ./bin/Test.o ./bin/BoardTest.o
#	$(COMPILER) $(CFLAGS) ./bin/test.o ./bin/Board.o ./bin/Test.o ./bin/BoardTest.o -o $(TEST)

./bin/main.o: ./src/main.cpp
	$(COMPILER) -c $(CFLAGS) ./src/main.cpp -o ./bin/main.o

./bin/huffman.o: ./src/huffman.cpp
	$(COMPILER) -c $(CFLAGS) ./src/huffman.cpp -o ./bin/huffman.o

#./bin/test.o: ./test/test.cpp
#	$(COMPILER) -c $(CFLAGS) ./test/test.cpp -o ./bin/test.o

#./bin/Test.o: ./test/Test.cpp
#	$(COMPILER) -c $(CFLAGS) ./test/Test.cpp -o ./bin/Test.o

clean:
	rm -rf bin $(EXE) $(TEST)

.PHONY: all board_test clean
