CFLAGS = -Wall -g -std=c99
INCLUDE = -I include/

sub:
	@echo Make $@.
	@gcc $(CFLAGS) src/piece.c src/game.c src/test_functions.c src/$(MAKEARG).c $(INCLUDE) -o $(MAKEARG)
	@echo Executable $@ generated.

all:
	@echo Make all start.
	@echo
	@make --silent test_game1 test_piece1 rush-hour test_game2 test_piece2 ane-rouge 
	@echo 
	@echo Make all end.


#RUSH_HOUR
test_game1:
	@make --silent sub MAKEARG=$@
	
test_piece1:
	@make --silent sub MAKEARG=$@
	
rush-hour:
	@make --silent sub MAKEARG=$@
	
#ANE-ROUGE
test_game2:
	@make --silent sub MAKEARG=$@
	
test_piece2:
	@make --silent sub MAKEARG=$@
	
ane-rouge:
	@make --silent sub MAKEARG=$@
	
	
#marche probablement plus
lib:
	@rm -f lib/libgame.a
	@rm -d -f lib
	@mkdir lib
	@ar cr lib/libgame.a game.o piece.o

clean:
	@rm -f *.o test_piece1 test_piece2 test_game1 test_game2 rush-hour ane-rouge -d lib 
	@echo Files cleaned.