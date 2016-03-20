CFLAGS = -Wall -g -std=c99
INCLUDE = -I include/

all:
	@echo Make all start.
	@echo
	@make --silent test_game1 test_piece1 rush-hour test_game2 test_piece2 ane-rouge 
	@echo 
	@echo Make all end.

#
# --------- RUSH-HOUR -----------
#

test_game1:
	@echo Make $@.
	@gcc $(CFLAGS) src/useful_functions.c src/game.c src/test_game1.c src/piece.c $(INCLUDE) -o $@
	@echo Executable $@ generated.
	
test_piece1:
	@echo Make $@.
	@gcc $(CFLAGS) src/useful_functions.c src/piece.c src/test_piece1.c $(INCLUDE) -o $@
	@echo Executable $@ generated.
	
rush-hour:
	@echo Make $@.
	@gcc $(CFLAGS) src/useful_functions.c src/game.c src/piece.c src/grid.c src/rush-hour.c $(INCLUDE) -o $@
	@echo Executable $@ generated.
	
#
# --------- ÂNE ROUGE ----------
#

test_game2:
	@echo Make $@.
	@gcc $(CFLAGS) src/useful_functions.c src/game.c src/test_game2.c src/piece.c $(INCLUDE) -o $@
	@echo Executable $@ generated.
	
test_piece2:
	@echo Make $@.
	@gcc $(CFLAGS) src/useful_functions.c src/piece.c src/test_piece2.c $(INCLUDE) -o $@
	@echo Executable $@ generated.
	
ane-rouge:
	@echo Make $@.
	@gcc $(CFLAGS) src/useful_functions.c src/game.c src/piece.c src/ane-rouge.c $(INCLUDE) -o $@
	@echo Executable $@ generated.

lib:
	@rm -f lib/libgame.a
	@rm -d -f lib
	@mkdir lib
	@ar cr lib/libgame.a game.o piece.o

clean:
	@rm -f *.o test_piece1 test_piece2 test_game1 test_game2 rush-hour ane-rouge -d lib 
	@echo Files cleaned.