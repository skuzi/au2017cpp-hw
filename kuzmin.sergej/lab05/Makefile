EXE = main

CFLAGS  = -Wall -Werror -O2 -Iinclude


all : bin $(EXE)

bin:
	mkdir bin

$(EXE): ./bin/main.o ./bin/clist.o ./bin/position.o
	gcc -Iinclude ./bin/main.o ./bin/clist.o ./bin/position.o -o $(EXE)

./bin/main.o: ./src/main.c
	gcc -c $(CFLAGS) ./src/main.c -o ./bin/main.o

./bin/clist.o: ./src/clist.c
	gcc -c $(CFLAGS) ./src/clist.c -o ./bin/clist.o

./bin/position.o: ./src/position.c
	gcc -c $(CFLAGS) ./src/position.c -o ./bin/position.o

clean:
	rm -rf bin $(EXE)

.PHONY: all clean
