#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"
#include "useful_functions.h"
#include "grid.h"

#define NB_PIECES 4
bool test_equality_int(int expected, int value, char * msg){
    if (expected != value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d | Error from : %s\n", expected, value, msg);
    return expected == value;
}
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
    int nbmove=1;
    game g=set_game();
    new_grid(g);
    piece p_test=new_piece_rh(get_x(game_piece(g, 0)), get_y(game_piece(g, 0)), is_horizontal(game_piece(g, 0)), is_small(game_piece(g, 0)));
    result=test_equality_bool(true, play_move(g, 0, LEFT, 1), "play_move 1 in test_play_move") && result; // déplacement possible
    show_grid(g);
    result=test_equality_int(get_x(game_piece(g, 0)), 2, "get_x 1 in test_play_move") && result;
    result=test_equality_int(get_y(game_piece(g, 0)), 3, "get_y 1 in test_play_move") && result;
    result=test_equality_bool(false, play_move(g, 1, DOWN, 1), "play_move 2 in test_play_move") && result; // sortie de la grille de 1 : déplacement impossible
    show_grid(g);
    result=test_equality_int(get_x(game_piece(g, 1)), 3, "get_x 2 in test_play_move") && result;
    result=test_equality_int(get_y(game_piece(g, 1)), 0, "get_y 2 in test_play_move") && result;
    result=test_equality_bool(false, play_move(g, 2, LEFT, 1), "play_move 3 in test_play_move ") && result; // intersection de 2 et 1 : déplacement impossible
    show_grid(g);
    result=test_equality_int(get_x(game_piece(g, 2)), 4, "get_x 3 in test_play_move") && result;
    result=test_equality_int(get_y(game_piece(g, 2)), 1, "get_y 3 in test_play_move") && result;
    result=test_equality_bool(false, play_move(g, 3, DOWN, 2), "play_move 4 in test_play_move") && result; //intersection de 3 et 2 : déplacement impossible
    show_grid(g);
    result=test_equality_int(get_x(game_piece(g, 3)), 3, "get_x 4 in test_play_move") && result;
    result=test_equality_int(get_y(game_piece(g, 3)), 5, "get_y 4 in test_play_move") && result;
    result=test_equality_int(nbmove, game_nb_moves(g), "game_nb_moves in test_play_move") && result;
    result=!equals(p_test, game_piece(g, 0)) && result; // seule piece ayant fait un déplacement
    show_grid(g);
    delete_game(g);
    return result;
}
bool test_copy_game(){
    bool result=true;
    game g=set_game();
    piece empty_list[0];
    game gtest=new_game_hr(0, empty_list);
    copy_game(g, gtest);
    play_move(g, 0, LEFT, 1);
    result=test_equality_int(game_nb_pieces(g), game_nb_pieces(gtest), "nb_piece in test_copy_game") && result;
    for (int i=0; i < game_nb_pieces(g); ++i){
        result=test_equality_piece(game_piece(gtest, i), game_piece(g, i), "pieces comparisons in test_copy_game") && result;
    }
    delete_game(g);
    delete_game(gtest);
    return result;
}
bool test_game_over_rh(){
    bool result=true;
    game g=set_game();
    play_move(g, 0, LEFT, 2);
    result=test_equality_bool(false, game_over_hr(g), "game_over_hr 0 in test_game_over_rh") && result;
    play_move(g, 1, UP, 4);
    result=test_equality_bool(false, game_over_hr(g), "game_over_hr 1 in test_game_over_rh") && result;
    play_move(g, 2, LEFT, 1);
    result=test_equality_bool(false, game_over_hr(g), "game_over_hr 2 in test_game_over_rh") && result;
    play_move(g, 3, DOWN, 3);
    result=test_equality_bool(false, game_over_hr(g), "game_over_hr 3 in test_game_over_rh") && result;
    play_move(g, 0, RIGHT, 3);
    result=test_equality_bool(true, game_over_hr(g), "game_over_hr 4 in test_game_over_rh") && result;
    delete_game(g);
    return result;
}
int main(int argc, char *argv[]){
    bool result=true;
    result=test_equality_bool(true, test_new_game_hr(), "test_new_game_hr in main") && result;
    result=test_equality_bool(true, test_copy_game(), "test_copy_game in main") && result;
    result=test_equality_bool(true, test_play_move(), "test_play_move in main") && result;
    result=test_equality_bool(true, test_game_over_rh(), "test_game_over_rh in main") && result;

    if (result){
        printf("Ca marche c: !\n");
        return EXIT_SUCCESS;
    } else{
        printf("Ton code c'est de la merde !\n");
        return EXIT_FAILURE;
    }
}
