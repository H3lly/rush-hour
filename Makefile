CFLAGS = -Wall -g -std=c99
INCLUDE = -I include/

all:
	@make --silent sub
	@make --silent clean

sub:
	@echo Make start.
	@echo
	@gcc $(CFLAGS) src/useful_functions.c src/game.c src/game_test2.c src/piece.c src/test_piece2.c src/affichage.c $(INCLUDE) -c
	@echo Make end.

lib:
	@rm -f lib/libgame.a
	@rm -d -f lib
	@mkdir lib
	@ar cr lib/libgame.a game.o piece.o

game_test2:
	@echo Make game_test2.
	@gcc $(CFLAGS) src/useful_functions.c src/game.c src/game_test2.c src/piece.c $(INCLUDE) -c
	@gcc useful_functions.o game.o piece.o game_test2.o -o $@-exe
	@make --silent clean-all-but-exe
	@echo
	@echo Executable $@-exe generated.

test_piece2:
	@echo Make test_piece2.
	@gcc $(CFLAGS) src/useful_functions.c src/piece.c src/test_piece2.c $(INCLUDE) -c
	@gcc useful_functions.o game.o piece.o test_piece2.o -o $@-exe
	@make --silent clean-all-but-exe
	@echo
	@echo Executable $@-exe generated.

affichage:
	@echo Make affichage.
	@gcc $(CFLAGS) src/useful_functions.c src/game.c src/piece.c src/affichage.c $(INCLUDE) -c
	@gcc useful_functions.o game.o piece.o affichage.o -o $@-exe
	@make --silent clean-all-but-exe
	@echo 
	@echo Executable $@-exe generated.

clean:
	@rm -f *-exe
	@make --silent clean-all-but-exe

clean-all-but-exe:
	@rm -f useful_functions.o game.o piece.o test_piece2.o test_piece2 lib/libgame.a affichage.o game_test2.o -d lib
	@echo Files cleaned.
