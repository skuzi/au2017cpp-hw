EXE = main

CFLAGS  = -std=c99 -Wall -Werror -O2


all : bin $(EXE)

bin:
	mkdir bin

$(EXE): ./bin/main.o ./bin/bmp.o
	gcc -Iinclude ./bin/main.o ./bin/bmp.o -o $(EXE)

./bin/main.o: ./src/main.c
	gcc -Iinclude -c $(CFLAGS) ./src/main.c -o ./bin/main.o

./bin/bmp.o: ./src/bmp.c
	gcc -Iinclude -c $(CFLAGS) ./src/bmp.c -o ./bin/bmp.o

clean:
	rm -rf bin $(EXE)

.PHONY: all clean
