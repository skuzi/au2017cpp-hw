EXE = main

CFLAGS  = -Wall -Werror -O2 -Iinclude -g


all : bin $(EXE)

bin:
	mkdir bin

$(EXE): ./bin/main.o ./bin/parser.o ./bin/phonebook.o
	gcc -Iinclude ./bin/main.o ./bin/parser.o ./bin/phonebook.o -o $(EXE) -lexpat

./bin/main.o: ./src/main.c
	gcc -c $(CFLAGS) ./src/main.c -o ./bin/main.o

./bin/parser.o: ./src/parser.c
	gcc -c $(CFLAGS) ./src/parser.c -o ./bin/parser.o

./bin/phonebook.o: ./src/phonebook.c
	gcc -c $(CFLAGS) ./src/phonebook.c -o ./bin/phonebook.o

clean:
	rm -rf bin $(EXE)

.PHONY: all clean
