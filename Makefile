CFLAGS = -Wall -g -std=c99
INCLUDE = -I include/
all:
	@echo Make all start.
	@echo
	@make --silent test_piece test_game play
	@echo 
	@echo Make all end.
#caca
#pipi
#yolo

sub:
	@echo Make $(MAKEARG).
	@gcc $(CFLAGS) src/piece.c src/game.c src/test_functions.c src/solveur.c src/$(MAKEARG).c -lm $(INCLUDE) -o $(MAKEARG)
	@echo Executable $(MAKEARG) generated.

test_piece:
	@make --silent sub MAKEARG=$@
	
test_game:
	@make --silent sub MAKEARG=$@
	
play:
	@make --silent sub MAKEARG=$@
	
lib:
	@echo Make $@ start.
	@rm -f lib/libgame.a
	@rm -d -f lib
	@mkdir lib
	@gcc $(CFLAGS) src/game.c src/piece.c $(INCLUDE) -c
	@ar cr lib/libgame.a game.o piece.o
	@rm game.o piece.o
	@echo The library libgame.a is in the directory lib.
	@echo Make $@ end.

clean:
	@rm -f -r *.dSYM
	@rm -f *.o test_piece test_game play solveur lib/libgame.a -d lib 
	@echo Files cleaned.
	
