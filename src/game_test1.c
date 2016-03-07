#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"
#include "useful_functions.h"

#define NB_PIECES 4

//On teste si value == expected avec des int
bool test_equality_int(int expected, int value, char * msg){
    if (expected != value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d | Error from : %s\n", expected, value, msg);
    return expected == value;
}

//On teste si value == expected avec des bool
bool test_equality_bool(bool expected, bool value, char * msg){
    if (expected != value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d | Error from : %s\n", expected, value, msg);
    return expected == value;
}
bool test_equality_piece(cpiece expected, cpiece value, char * msg){
    if (!equals(expected, value)){
        fprintf(stderr, "ERR: Pieces are different | Error from : %s\n", msg);
    }
    return equals(expected, value);
}

//création d'un tableau de pièces
piece pieces[NB_PIECES];

//supprime le tableau de pièces
void tear_down(){
    for (int i=0; i < NB_PIECES; i++)
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

game set_game(){
    pieces[0]=new_piece_rh(3, 3, true, true);
    pieces[1]=new_piece_rh(3, 0, true, false);
    pieces[2]=new_piece_rh(4, 1, true, true);
    pieces[3]=new_piece_rh(5, 3, false, false);
    return new_game_hr(NB_PIECES, pieces);
}
bool test_new_game_hr(){
    bool result=true;
    game g=set_game();
    result=result && test_equality_int(NB_PIECES, game_nb_pieces(g), "game_nb_pieces in test_new_game_hr");
    for (int i=0; i < NB_PIECES; i++){
        result=result && equals(pieces[i], game_piece(g, i));
    }
    delete_game(g);
    return result;
}
// test play move etnre g (jeu dans lequel seul 0 peut bouger) et gtest(jeu de base)
bool test_play_move(){
    bool result=true;
    int nbmove=2;
    game g=set_game();
    piece p_test=new_piece_rh(get_x(game_piece(g,0)), get_y(game_piece(g,0)), is_horizontal(game_piece(g,0)), is_small(game_piece(g,0)));
    result=result && test_equality_bool(true, play_move(g, 0, LEFT, 1), "play_move in test_play_move 1"); // déplacement possible
    result=result && test_equality_bool(false, play_move(g, 1, DOWN, 1), "play_move in test_play_move 2"); // sortie de la grille de 1 : déplacement impossible
    result=result && test_equality_bool(false, play_move(g, 2, LEFT, 1), "play_move in test_play_move 3"); // intersection de 2 et 1 : déplacement impossible
    result=result && test_equality_bool(true, play_move(g, 3, DOWN, 1), "play_move in test_play_move 4"); //déplacement possible
    result=result && test_equality_bool(false, play_move(g, 3, DOWN, 1), "play_move in test_play_move 5"); // intersection de 3 et 2 : déplacement impossible
    result=result && test_equality_int(nbmove, game_nb_moves(g), "game_nb_moves in test_play_move");
    result=result && !equals(p_test, game_piece(g, 0)); // seule piece ayant fait un déplacement
    tear_down();
    delete_game(g);
    return result;
}
bool test_copy_game(){
    bool result=true;
    game g=set_game();
    play_move(g, 0, LEFT, 1);
    game gtest=new_game_hr(NB_PIECES, pieces);
    copy_game(g, gtest);
    result=result && test_equality_int(game_nb_pieces(g), game_nb_pieces(gtest), "nb_piece in test_copy_game");
    for (int i=0; i < game_nb_pieces(g); ++i){
        result=result && test_equality_piece(game_piece(gtest, i), game_piece(g, i), "pieces comparisons in test_copy_game");
    }
    delete_game(g);
    delete_game(gtest);
    return result;
}
int main(int argc, char *argv[]){
    bool result=true;
    game g=set_game();
    result=result && test_equality_bool(true, test_new_game_hr(), "new_game_hr in main");
    result=result && test_equality_bool(true, test_copy_game(), "copy_game in main");
    result=result && test_equality_bool(true, test_play_move(), "play_move in main"); //bug
    play_move(g, 0, LEFT, 2);
    result=result && test_equality_bool(true, !game_over_hr(g), "game_over_hr 0 in main");
    play_move(g, 1, UP, 4);
    result=result && test_equality_bool(true, !game_over_hr(g), "game_over_hr 1 in main");
    play_move(g, 2, LEFT, 1);
    result=result && test_equality_bool(true, !game_over_hr(g), "game_over_hr 2 in main");
    play_move(g, 3, DOWN, 3);
    result=result && test_equality_bool(true, !game_over_hr(g), "game_over_hr 3 in main");
    play_move(g, 0, RIGHT, 3);
    result=result && test_equality_bool(true, game_over_hr(g), "game_over_hr 4 in main");

    if (result){
        printf("Ca marche c: !\n");
        return EXIT_SUCCESS;
    } else{
        printf("Ton code c'est de la merde !\n");
        return EXIT_FAILURE;
    }
}
