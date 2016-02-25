#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"

#define NB_PIECES 4

bool test_equality_int(int expected, int value, char * msg);
bool test_equality_bool(bool expected, bool value, char * msg);
void set_up();
void tear_down();
void set_game();
bool test_new_game_hr();
/**
 * On teste si value == expected
 */
bool test_equality_int(int expected, int value, char * msg) {
  if (expected != value)
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
  return expected == value;
}

/**
 * On teste si value == expected
 */
bool test_equality_bool(bool expected, bool value, char * msg) {
  if (expected != value)
    fprintf(stderr,"ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
  return expected == value;
}

//----------------

piece pieces[NB_PIECES];
/* configue de test
.....3
.....3
...003
......
...122
...1..
 */
void set_up() {
  pieces[0] = new_piece_rh(3, 3, true, true);
  pieces[1] = new_piece_rh(3, 0, true, false);
  pieces[2] = new_piece_rh(4, 1, true, true);
  pieces[3] = new_piece_rh(5, 3, false, false);
}
void tear_down() {
  for (int i = 0 ; i < NB_PIECES; i++)
    delete_piece(pieces[i]);
}

void set_game(){
  set_up();
  game g = new_game_hr(NB_PIECES, pieces);
}

bool test_new_game_hr(){
  bool result = true;
  set_up();
  for (int i= 0 ; i < NB_PIECES, i++){
    game g = new_game_rh(NB_PIECES, pieces);
    result = result && test_equality_int(NB_PIECES, game_nb_pieces(g), "game_nb_pieces");
    result = result && equals(pieces[i], game_piece(g, i+1));
  }
  return result;
}
/*
bool test_game_over_hr(){
*/
