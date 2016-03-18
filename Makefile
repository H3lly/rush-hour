CFLAGS = -Wall -g -std=c99
INCLUDEV1 = -I include/v1
SRCV1 = src/v1/
INCLUDEV2 = -I include/v2
SRCV2 = src/v2/

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
	@gcc $(CFLAGS) $(SRCV1)useful_functions.c $(SRCV1)game.c $(SRCV1)test_game1.c $(SRCV1)piece.c $(INCLUDEV1) -o $@
	@echo Executable $@ generated.
	
test_piece1:
	@echo Make $@.
	@gcc $(CFLAGS) $(SRCV1)useful_functions.c $(SRCV1)piece.c $(SRCV1)test_piece1.c $(INCLUDEV1) -o $@
	@echo Executable $@ generated.
	
rush-hour:
	@echo Make $@.
	@gcc $(CFLAGS) $(SRCV1)useful_functions.c $(SRCV1)game.c $(SRCV1)piece.c $(SRCV1)grid.c src/rush-hour.c $(INCLUDEV1) -o $@
	@echo Executable $@ generated.
	
#
# --------- ÂNE ROUGE ----------
#

test_game2:
	@echo Make $@.
	@gcc $(CFLAGS) $(SRCV2)useful_functions.c $(SRCV2)game.c $(SRCV2)test_game2.c $(SRCV2)piece.c $(INCLUDEV2) -o $@
	@echo Executable $@ generated.
	
test_piece2:
	@echo Make $@.
	@gcc $(CFLAGS) $(SRCV2)useful_functions.c $(SRCV2)piece.c $(SRCV2)test_piece2.c $(INCLUDEV2) -o $@
	@echo Executable $@ generated.
	
ane-rouge:
	@echo Make $@.
	@gcc $(CFLAGS) $(SRCV2)useful_functions.c $(SRCV2)game.c $(SRCV2)piece.c src/ane-rouge.c $(INCLUDEV2) -o $@
	@echo Executable $@ generated.

lib:
	@rm -f lib/libgame.a
	@rm -d -f lib
	@mkdir lib
	@ar cr lib/libgame.a game.o piece.o

clean:
	@rm -f *.o test_piece1 test_piece2 test_game1 test_game2 rush-hour ane-rouge -d lib 
	@echo Files cleaned.