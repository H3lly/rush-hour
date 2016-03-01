CFLAGS = -std=c99
INCLUDE = -I include/

all:
	gcc $(CFLAGS) src/game.c src/game_test1.c src/piece.c src/test_piece1.c src/affichage.c $(INCLUDE) -c #-o test_piece1
	rm -f lib/libgame.a
	rm -d -f lib
	mkdir lib
	ar cr lib/libgame.a game.o piece.o

game_test1:
	gcc game.o piece.o game_test1.o -o game_test1

test_piece1:
	gcc game.o piece.o test_piece1.o -o test_piece1

affichage:
	gcc game.o piece.o affichage.o -o affichage

clean:
	rm -f game.o piece.o test_piece1.o test_piece1 lib/libgame.a affichage affichage.o game_test1.o -d lib
