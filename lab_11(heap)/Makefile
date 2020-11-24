all: build run clean

build: heap.c heap.h
	gcc heap.c test.c TArb.c -o test -Wall -Wextra -lm

run:
	./test

clean:
	rm -rf test


