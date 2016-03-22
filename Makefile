CFLAGS = -Wall -g -std=c99
INCLUDE = -I include/

#%:
#	@echo Make $@
#	@gcc $(CFLAGS) src/piece.c src/game.c src/test_functions.c src/$@.c $(INCLUDE) -o $@
#	@echo Executable $@ generated.
#	#"Make all" will do target "%:" AND target "all:" (but strangely works on the shell)
#	#Also, will do target "%:" all the time, even if you put "potato" or "dogs", will only says that src/dogs.c doesn't exist
#	#Left in commentary for the moment

sub:
	@echo Make $(MAKEARG).
	@gcc $(CFLAGS) src/piece.c src/game.c src/test_functions.c src/$(MAKEARG).c -lm $(INCLUDE) -o $(MAKEARG)
	@echo Executable $(MAKEARG) generated.

all:
	@echo Make all start.
	@echo
	@make --silent test_game1 test_piece1 rush-hour test_game2 test_piece2 ane-rouge 
	@echo 
	@echo Make all end.


test_game1:
	@make --silent sub MAKEARG=$@
	
test_piece1:
	@make --silent sub MAKEARG=$@
	
rush-hour:
	@make --silent sub MAKEARG=$@
	
test_game2:
	@make --silent sub MAKEARG=$@
	
test_piece2:
	@make --silent sub MAKEARG=$@
	
ane-rouge:
	@make --silent sub MAKEARG=$@
	
	
#MARCHE PROBABLEMENT PLUS
lib:
	@rm -f lib/libgame.a
	@rm -d -f lib
	@mkdir lib
	@ar cr lib/libgame.a game.o piece.o

clean:
	@rm -f *.o test_piece1 test_piece2 test_game1 test_game2 rush-hour ane-rouge -d lib 
	@echo Files cleaned.