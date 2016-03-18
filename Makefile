CFLAGS = -Wall -g -std=c99
INCLUDEV1 = -I rush-hour_v1/include/
SRCV1 = rush-hour_v1/src/
INCLUDEV2 = -I ane-rouge_v2/include/
SRCV2 = ane-rouge_v2/src/

all:
	@echo Make all start.
	@echo
	#@gcc $(CFLAGS) src/useful_functions.c src/game.c src/game_test2.c src/piece.c src/test_piece2.c src/affichage.c $(INCLUDE) -c
	@echo Make all end.
	@make --silent clean

#
# --------- RUSH-HOUR -----------
#

game_test1:
	@echo Make $@.
	@gcc $(CFLAGS) $(SRCV1)useful_functions.c $(SRCV1)game.c $(SRCV1)game_test1.c $(SRCV1)piece.c $(INCLUDEV1) -c
	@gcc useful_functions.o game.o piece.o game_test1.o -o $@-exe
	@make --silent clean-all-but-exe
	@echo
	@echo Executable $@-exe generated.
	
test_piece1:
	@echo Make $@.
	@gcc $(CFLAGS) $(SRCV1)useful_functions.c $(SRCV1)piece.c $(SRCV1)test_piece1.c $(INCLUDE) -c
	@gcc useful_functions.o game.o piece.o test_piece1.o -o $@-exe
	@make --silent clean-all-but-exe
	@echo
	@echo Executable $@-exe generated.
	
rush-hour:
	@echo Make $@.
	@gcc $(CFLAGS) $(SRCV1)useful_functions.c $(SRCV1)game.c $(SRCV1)piece.c $(SRCV1)grid.c $(SRCV1)affichage_rush-hour.c $(INCLUDEV1) -c
	@gcc useful_functions.o game.o grid.o piece.o affichage_rush-hour.o -o $@-exe
	@make --silent clean-all-but-exe
	@echo 
	@echo Executable $@-exe generated.
	
#
# --------- ÂNE ROUGE ----------
#

game_test2:
	@echo Make game_test2.
	@gcc $(CFLAGS) $(SRCV2)useful_functions.c $(SRCV2)game.c $(SRCV2)game_test2.c $(SRCV2)piece.c $(INCLUDEV2) -c
	@gcc useful_functions.o game.o piece.o game_test2.o -o $@-exe
	@make --silent clean-all-but-exe
	@echo
	@echo Executable $@-exe generated.

test_piece2:
	@echo Make test_piece2.
	@gcc $(CFLAGS) $(SRCV2)useful_functions.c $(SRCV2)piece.c $(SRCV2)test_piece2.c $(INCLUDE) -c
	@gcc useful_functions.o game.o piece.o test_piece2.o -o $@-exe
	@make --silent clean-all-but-exe
	@echo
	@echo Executable $@-exe generated.

lib:
	@rm -f lib/libgame.a
	@rm -d -f lib
	@mkdir lib
	@ar cr lib/libgame.a game.o piece.o

clean:
	@rm -f *-exe
	@make --silent clean-all-but-exe

clean-all-but-exe:
	@rm -f useful_functions.o game.o piece.o test_piece2.o test_piece2 lib/libgame.a affichage.o game_test2.o -d lib
	@echo Files cleaned.
