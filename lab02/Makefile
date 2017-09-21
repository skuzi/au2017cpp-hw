EXE = lab02

CFLAGS  = -Wall -Werror -O2


all : bin $(EXE)

bin:
	mkdir bin

$(EXE): ./bin/test.o ./bin/str.o ./bin/test_str.o
	gcc -Iinclude ./bin/test.o ./bin/str.o ./bin/test_str.o -o $(EXE)

./bin/test.o: ./src/test.c
	gcc -Iinclude -c $(CFLAGS) ./src/test.c -o ./bin/test.o

./bin/str.o: ./src/str.c
	gcc -Iinclude -c $(CFLAGS) ./src/str.c -o ./bin/str.o

./bin/test_str.o: ./src/test_str.c
	gcc -Iinclude -c $(CFLAGS) ./src/test_str.c -o ./bin/test_str.o

clean:
	rm -rf bin $(EXE)

.PHONY: all clean
