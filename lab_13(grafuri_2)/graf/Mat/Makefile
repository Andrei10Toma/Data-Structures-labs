all: build run

build: graf.h graf-M.h graf-M.c test-graf.c
	gcc graf-M.c test-graf.c -o main

run:
	./main

clear:
	rm -rf main
