#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"

#define NB_PIECES 4

 //On teste si value == expected avec des int
bool test_equality_int(int expected, int value, char * msg) {
    if (expected != value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
    return expected == value;
}


//On teste si value == expected avec des bool
bool test_equality_bool(bool expected, bool value, char * msg) {
    if (expected != value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
    return expected == value;
}

piece pieces[NB_PIECES];

/* config de test
. . . . . 3
. . . . . 3
. . . 0 0 3
. . . . . .
. . . 1 2 2
. . . 1 . .
 */
void set_up() {
    pieces[0] = new_piece_rh(3, 3, true, true);
    pieces[1] = new_piece_rh(3, 0, true, false);
    pieces[2] = new_piece_rh(4, 1, true, true);
    pieces[3] = new_piece_rh(5, 3, false, false);
}


void tear_down() {
    for (int i = 0; i < NB_PIECES; i++)
        delete_piece(pieces[i]);
}

void set_game() {
    set_up();
    game g = new_game_hr(NB_PIECES, pieces);
}

bool equals(cpiece p1, cpiece p2) {
    return (get_x(p1) == get_x(p2))&&(get_y(p1) == get_y(p2))&&(get_width(p1) == get_width(p2))&&(get_height(p1) == get_height(p2));
}

bool test_new_game_hr() {
    bool result = true;
    set_up();
    for (int i = 0; i < NB_PIECES; i++) {
        game g = new_game_hr(NB_PIECES, pieces);
        result = result && test_equality_int(NB_PIECES, game_nb_pieces(g), "game_nb_pieces");
        result = result && equals(pieces[i], game_piece(g, i + 1));
    }
    return result;
}

//test si le jeu est fini
bool test_game_over_hr(game g){
  return game_over_hr(g);
}

/*
bool test_play_move(){
    bool result = true;
    set_up()
    game g = new_game_hr(NB_PIECES, pieces);
    play_move(g, 0, LEFT, 1);
    play_move(g, 1, DOWN, 1)
}


 bool test_new_game() {
  bool result = true;
  for (int x= 0 ; x < 5; x++)
    for (int y= 0 ; y < 5; y++)
      for (bool small=false; !small ; small= !small)
        for (bool horizontal=false; !horizontal ; horizontal= !horizontal) {
          int size;
          if (small)
            size = 2;
          else
            size = 3;
          piece p = new_piece_rh(x, y, small, horizontal);
          result = result && test_equality_int(x, get_x(p),"get_x");
          result = result && test_equality_int(y, get_y(p),"get_y");
          if (horizontal) {
            result = result && test_equality_int(1, get_height(p), "get_height");
            result = result && test_equality_int(size, get_width(p), "get_width");
          }
          else {
            result = result && test_equality_int(size, get_height(p), "get_height");
            result = result && test_equality_int(1, get_width(p), "get_width");
          }
          delete_piece(p);
        }
  return result;
}
 */
/*
int main (int argc, char *argv[])
{
  bool result= true;

  result = result && test_equality_bool(true, test_new_piece(), "new_piece");
  result = result && test_equality_bool(true, test_intersect(), "intersect");
  result = result && test_equality_bool(true, test_move(), "move");
  result = result && test_equality_bool(true, test_copy(), "copy");

  if (result) {
    printf("Ca marche c: !\n");
    return EXIT_SUCCESS;
  }
  else
    return EXIT_FAILURE;
}

 */
//tester new game
