OPT = -Wall -ansi -pedantic -ggdb

terrain.out: case.o terrain.o 
	gcc bin/terrain.o bin/\case.o -o bin/terrain.out

terrain.o: src/terrain.c src/terrain.h src/case.h
	gcc -c $(OPT) -o bin/terrain.o src/terrain.c

case.o: src/case.c src/case.h
	gcc -c $(OPT) -o bin/\case.o src/\case.c


