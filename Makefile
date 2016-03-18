CFLAGS = -Wall -g -std=c99
INCLUDEV1 = -I rush-hour_v1/include/
SRCV1 = rush-hour_v1/src/
INCLUDEV2 = -I ane-rouge_v2/include/
SRCV2 = ane-rouge_v2/src/

all:
	@echo Make all start.
	@echo
	@make --silent test_game1 test_piece1 rush-hour #test_game2 test_piece2 ane-rouge
	@echo Make all end.
	@make --silent clean

#
# --------- RUSH-HOUR -----------
#

test_game1:
	@echo Make $@.
	@gcc $(CFLAGS) $(SRCV1)useful_functions1.c $(SRCV1)game.c $(SRCV1)test_game1.c $(SRCV1)piece.c $(INCLUDEV1) -c
	@gcc useful_functions1.o game.o piece.o test_game1.o -o $@
	@make --silent clean-outfile
	@echo
	@echo Executable $@ generated.
	
test_piece1:
	@echo Make $@.
	@gcc $(CFLAGS) $(SRCV1)useful_functions1.c $(SRCV1)piece.c $(SRCV1)test_piece1.c $(INCLUDEV1) -c
	@gcc useful_functions1.o game.o piece.o test_piece1.o -o $@
	@make --silent clean-outfile
	@echo
	@echo Executable $@ generated.
	
rush-hour:
	@echo Make $@.
	@gcc $(CFLAGS) $(SRCV1)useful_functions1.c $(SRCV1)game.c $(SRCV1)piece.c $(SRCV1)grid.c $(SRCV1)affichage_rush-hour.c $(INCLUDEV1) -c
	@gcc useful_functions1.o game.o grid.o piece.o affichage_rush-hour.o -o $@
	@make --silent clean-outfile
	@echo Executable $@ generated.
	
#
# --------- ÂNE ROUGE ----------
#

test_game2:
	@echo Make $@.
	@gcc $(CFLAGS) $(SRCV2)useful_functions2.c $(SRCV2)game.c $(SRCV2)test_game2.c $(SRCV2)piece.c $(INCLUDEV2) -c
	@gcc useful_functions2.o game.o piece.o test_game2.o -o $@
	@make --silent clean-outfile
	@echo
	@echo Executable $@ generated.

test_piece2:
	@echo Make test_piece2.
	@gcc $(CFLAGS) $(SRCV2)useful_functions2.c $(SRCV2)piece.c $(SRCV2)test_piece2.c $(INCLUDE) -c
	@gcc useful_functions2.o game.o piece.o test_piece2.o -o $@
	@make --silent clean-outfile
	@echo
	@echo Executable $@ generated.

lib:
	@rm -f lib/libgame.a
	@rm -d -f lib
	@mkdir lib
	@ar cr lib/libgame.a game.o piece.o

clean:
	@rm -f  test_piece1 test_piece2 test_game1 test_game2 rush-hour ane-rouge
	@make --silent clean-outfile

clean-outfile:
	@rm -f *.o -d lib
	@echo Files cleaned.
#useful_functions.o game.o piece.o test_piece2.o test_piece1.o test_piece1 test_piece2 lib/libgame.a affichage_rush-hour.o affichage_ane-rouge.o game_test2.o 