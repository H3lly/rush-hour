CFLAGS = -std=c99
INCLUDE = -I include/

all:
	gcc $(CFLAGS) src/game.c src/piece.c src/test_piece1.c $(INCLUDE) -c #-o test_piece1
	rm -f lib/libgame.a
	rm -d -f lib
	mkdir lib
	ar cr lib/libgame.a game.o piece.o
	gcc game.o piece.o test_piece1.o -o test_piece1

clean:
	rm -f game.o piece.o test_piece1.o test_piece1 lib/libgame.a -d lib
