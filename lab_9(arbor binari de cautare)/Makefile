all: build run clean

build: TArb.c test.c
	gcc -g TArb.c test.c -o main -Wall -lm

run: 
	./main

clean:
	rm -rf main
