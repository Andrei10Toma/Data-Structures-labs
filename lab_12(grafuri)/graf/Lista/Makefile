all: build run

build: graf-L.c test-graf.c graf.h graf-L.h
	gcc graf-L.c test-graf.c -o main

run:
	./main

clear:
	rm -rf main
