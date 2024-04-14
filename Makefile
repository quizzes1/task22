all:
	gcc -o result main.c painting.c count.c -lmingw32 -lSDL2main -lSDL2 --pedantic -Wall
	./result