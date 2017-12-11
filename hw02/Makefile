EXE = main
TEST = board_tests
COMPILER = g++

CFLAGS  = -Wall -Werror -O2 -Iinclude -g -std=c++17


all: bin $(EXE)
board_test: bin $(TEST)

bin:
	mkdir bin

$(EXE): ./bin/main.o ./bin/Board.o ./bin/BoardView.o
	$(COMPILER) $(CFLAGS) ./bin/main.o ./bin/Board.o ./bin/BoardView.o -o $(EXE)

$(TEST): ./bin/test.o ./bin/Board.o ./bin/Test.o ./bin/BoardTest.o
	$(COMPILER) $(CFLAGS) ./bin/test.o ./bin/Board.o ./bin/Test.o ./bin/BoardTest.o -o $(TEST)

./bin/main.o: ./src/main.cpp
	$(COMPILER) -c $(CFLAGS) ./src/main.cpp -o ./bin/main.o

./bin/Board.o: ./src/Board.cpp
	$(COMPILER) -c $(CFLAGS) ./src/Board.cpp -o ./bin/Board.o

./bin/BoardView.o: ./src/BoardView.cpp
	$(COMPILER) -c $(CFLAGS) ./src/BoardView.cpp -o ./bin/BoardView.o

./bin/test.o: ./test/test.cpp
	$(COMPILER) -c $(CFLAGS) ./test/test.cpp -o ./bin/test.o

./bin/Test.o: ./test/Test.cpp
	$(COMPILER) -c $(CFLAGS) ./test/Test.cpp -o ./bin/Test.o

./bin/BoardTest.o: ./test/BoardTest.cpp
	$(COMPILER) -c $(CFLAGS) ./test/BoardTest.cpp -o ./bin/BoardTest.o

clean:
	rm -rf bin $(EXE) $(TEST)

.PHONY: all board_test clean
