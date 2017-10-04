EXE = ms_cli

CFLAGS  = -Wall -Werror -O2 -Iinclude


all : bin $(EXE)

bin:
	mkdir bin

$(EXE): ./bin/ms_cli.o ./bin/mergesort.o
	gcc -Iinclude ./bin/ms_cli.o ./bin/mergesort.o -o $(EXE)

./bin/ms_cli.o: ./src/ms_cli.c
	gcc -c $(CFLAGS) ./src/ms_cli.c -o ./bin/ms_cli.o

./bin/mergesort.o: ./src/mergesort.c
	gcc -c $(CFLAGS) ./src/mergesort.c -o ./bin/mergesort.o
clean:
	rm -rf bin $(EXE)

.PHONY: all clean
