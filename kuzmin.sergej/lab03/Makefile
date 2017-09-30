EXE = pose_db

CFLAGS  = -Wall -Werror -O2


all : bin $(EXE)

bin:
	mkdir bin

$(EXE): ./bin/main.o
	gcc -Iinclude ./bin/main.o -o $(EXE)

./bin/main.o: ./src/main.c
	gcc -Iinclude -c $(CFLAGS) ./src/main.c -o ./bin/main.o

clean:
	rm -rf bin $(EXE)

.PHONY: all clean
