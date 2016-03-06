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

//On test l'égalité entre 2 pieces
bool equals_piece(cpiece p1, cpiece p2) {
    return (get_x(p1) == get_x(p2))&&(get_y(p1) == get_y(p2))&&(get_width(p1) == get_width(p2))&&(get_height(p1) == get_height(p2));
}

bool test_equality_piece(cpiece expected, cpiece value, char * msg){
    if (!equals_piece(expected, value)){
        fprintf(stderr, "ERR: Pieces are different. %s\n", msg);
    }
    return equals_piece(expected, value);
}
    
//création d'un tableau de pièces
piece pieces[NB_PIECES];

//supprime le tableau de pièces
void tear_down() {
    for (int i = 0; i < NB_PIECES; i++)
        delete_piece(pieces[i]);
}

/* config de test
. . . . . 3
. . . . . 3
. . . 0 0 3
. . . . . .
. . . 1 2 2
. . . 1 . .
 */

game set_game() {
    pieces[0] = new_piece_rh(3, 3, true, true);
    pieces[1] = new_piece_rh(3, 0, true, false);
    pieces[2] = new_piece_rh(4, 1, true, true);
    pieces[3] = new_piece_rh(5, 3, false, false);
    return new_game_hr(NB_PIECES, pieces);
}


bool test_new_game_hr() {
    bool result = true;
    game g = set_game();
    result = result && test_equality_int(NB_PIECES, game_nb_pieces(g), "game_nb_pieces");
    for (int i = 0; i < NB_PIECES; i++) {
        result = result && equals_piece(pieces[i], game_piece(g, i + 1));
    }
    delete_game(g);
    return result;
}
// test play move etnre g (jeu dans lequel seul 0 peut bouger) et gtest(jeu de base)

bool test_play_move(){
    bool result = true;
    int nbmove = 1;
    game g = set_game();
    cpiece p_test = new_piece_rh(2, 3, true, true);
    game gtest = set_game();
    play_move(g, 0, LEFT, 1);           // déplacement vers la gauche de 0
    play_move(g, 1, DOWN, 1);           // sortie de la grille de 1 : déplacement impossible
    play_move(g, 2, LEFT, 1);           // intersection de 2 et 1 : déplacement impossible
    play_move(g, 3, DOWN, 2);           // intersection de 3 et 2 : déplacement impossible
    result = result && test_equality_int(nbmove, game_nb_moves(g), "game_nb_moves");
    result = result && !test_equality_piece(p_test, game_piece(g, 0), "play_move de 0");                // seule piece ayant fait un déplacement
    for (int i = 1; i < game_nb_pieces(g); ++i){
        result = result && test_equality_piece(game_piece(gtest, i), game_piece(g, i), "play_move");    // déplacements impossible : pieces identiques à la configuration de départ
    }
    tear_down();
    delete_game(g);
    return result;
}

bool test_copy_game(){
    bool result = true;
    game g = set_game();
    play_move(g, 0, LEFT, 1);
    game gtest = new_game_hr(NB_PIECES,pieces);
    copy_game(g, gtest);
    result = result && test_equality_int(game_nb_pieces(g), game_nb_pieces(gtest), "nb_piece copy");
    for (int i = 0; i < game_nb_pieces(g); ++i){
        result = result && test_equality_piece(game_piece(gtest, i), game_piece(g, i), "play_move");
    }
    delete_game(g);
    delete_game(gtest);
    return result;
}


int main (int argc, char *argv[])
{
  bool result= true;
  printf("YOLO?\n");

  game g = set_game();
  result = result && test_equality_bool(true, test_new_game_hr(), "new_game_hr");
  printf("1\n");
  result = result && test_equality_bool(true, test_copy_game(), "copy_game");
  printf("2\n");
  result = result && test_equality_bool(true, test_play_move(), "play_move");
  play_move(g, 0, LEFT, 2);
  printf("3\n");
  result = result && test_equality_bool(true, !game_over_hr(g), "game_over_hr : premier play_move 0");
  play_move(g, 1, UP, 4);
  result = result && test_equality_bool(true, !game_over_hr(g), "game_over_hr : play_move 1");
  play_move(g, 2, LEFT, 1);
  printf("5\n");
  result = result && test_equality_bool(true, !game_over_hr(g), "game_over_hr : play_move 2"); //plante ici
  play_move(g, 3, DOWN, 3);
  result = result && test_equality_bool(true, !game_over_hr(g), "game_over_hr : play_move 3");
  play_move(g, 0, RIGHT, 3);
  result = result && test_equality_bool(true, game_over_hr(g), "game_over_hr : deuxième play_move 0");

  if (result) {
    printf("Ca marche c: !\n");
    return EXIT_SUCCESS;
  }
  else
    return EXIT_FAILURE;
}
