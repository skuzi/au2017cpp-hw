EXE = lab01

CFLAGS  = -Wall -Werror -O2


all : bin $(EXE)

bin:
	mkdir bin

$(EXE): ./bin/main.o ./bin/io.o ./bin/algorithm.o ./bin/util.o
	gcc -Iinclude ./bin/main.o ./bin/io.o ./bin/algorithm.o ./bin/util.o -o $(EXE)

./bin/io.o: ./src/io.c
	gcc -Iinclude -c $(CFLAGS) ./src/io.c -o ./bin/io.o

./bin/main.o: ./src/main.c
	gcc -Iinclude -c $(CFLAGS) ./src/main.c -o ./bin/main.o

./bin/algorithm.o: ./src/algorithm.c
	gcc -Iinclude -c $(CFLAGS) ./src/algorithm.c -o ./bin/algorithm.o

./bin/util.o: ./src/util.c
	gcc -Iinclude -c $(CFLAGS) ./src/util.c -o ./bin/util.o

clean:
	rm -rf bin $(EXE)

.PHONY: all clean
