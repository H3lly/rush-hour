#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "piece.h"
#include "useful_functions.h"

#define NB_PIECES 7


bool test_equality_int(int expected, int value, char * msg){
    if (expected != value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d | Error from : %s\n", expected, value, msg);
    return expected == value;
}
bool test_equality_bool(bool expected, bool value, char * msg){
    if (expected != value)
        fprintf(stderr, "ERR: value expected %s ; value computed %s | Error from : %s\n", (expected ? "true" : "false"), (value ? "true" : "false"), msg);
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
1 0 0 2
1 0 0 2
3 . . 4
3 . . 4
5 . . 6
 */

game set_game(){
    pieces[0]=new_piece(1, 3, 2, 2, false, false); //la piece étant coincée, elle ne peut pas bouger-
    pieces[1]=new_piece(0, 3, 1, 2, false, false);
    pieces[2]=new_piece(3, 3, 1, 2, false, false);
    pieces[3]=new_piece(0, 1, 1, 2, false, false);
    pieces[4]=new_piece(3, 1, 1, 2, false, false);
    pieces[5]=new_piece(0, 0, 1, 1, true, false);
    pieces[6]=new_piece(3, 0, 1, 1, true, false);
    
    return new_game(4, 5, NB_PIECES, pieces);
}
bool test_new_game(){
    bool result=true;
    game g=set_game();
    result=result && test_equality_int(NB_PIECES, game_nb_pieces(g), "game_nb_pieces in test_new_game");
    for (int i=0; i < NB_PIECES; i++){
        result=result && equals(pieces[i], game_piece(g, i));
    }
    delete_game(g);
    return result;
}
// test play move entre g (jeu dans lequel seul 0 peut bouger) et gtest (jeu de base)
bool test_play_move(){
    bool result=true;
    int nbmove=1;
    game g=set_game();
    piece p_test=new_piece(get_x(game_piece(g, 0)), get_y(game_piece(g, 0)), get_height(game_piece(g, 0)), get_width(game_piece(g, 0)), can_move_x(game_piece(g, 0)), can_move_y(game_piece(g, 0)));
    result=test_equality_bool(true, play_move(g, 5, RIGHT, 1), "play_move 1 in test_play_move") && result; // déplacement possible
    result=test_equality_int(get_x(game_piece(g, 5)), 1, "get_x 1 in test_play_move") && result;
    result=test_equality_int(get_y(game_piece(g, 5)), 0, "get_y 1 in test_play_move") && result;
    result=test_equality_bool(false, play_move(g, 6, RIGHT, 1), "play_move 2 in test_play_move") && result; // sortie de la grille de la pièce 6 : déplacement impossible
    result=test_equality_int(get_x(game_piece(g, 6)), 3, "get_x 2 in test_play_move") && result; // on vérifie que la pièce n'a pas bougé
    result=test_equality_int(get_y(game_piece(g, 6)), 0, "get_y 2 in test_play_move") && result;
    result=test_equality_bool(false, play_move(g, 2, LEFT, 1), "play_move 3 in test_play_move ") && result; // pièce 2 complètement bloquée: déplacement impossible
    result=test_equality_int(get_x(game_piece(g, 2)), 3, "get_x 3 in test_play_move") && result; // idem
    result=test_equality_int(get_y(game_piece(g, 2)), 3, "get_y 3 in test_play_move") && result;
    result=test_equality_bool(false, play_move(g, 6, LEFT, 2), "play_move 4 in test_play_move") && result; // la pièce 6 peut se déplacer d'une case vers la gauche mais pas deux : déplacement impossible
    result=test_equality_int(get_x(game_piece(g, 6)), 3, "get_x 4 in test_play_move") && result; // idem
    result=test_equality_int(get_y(game_piece(g, 6)), 0, "get_y 4 in test_play_move") && result;
    result=test_equality_int(nbmove, game_nb_moves(g), "game_nb_moves in test_play_move") && result; // on vérifie qu'une seule pièce a bougé
    result=!equals(p_test, game_piece(g, 5)) && result; // seule piece ayant fait un déplacement
    delete_game(g);
    return result;
}
bool test_copy_game(){
    bool result=true;
    game g=set_game(); // on crée une grille comme dans la config de test
    piece empty_list[0];
    game gtest=new_game(4, 5, 0, empty_list); // on crée une grille vide
    copy_game(g, gtest); // on copie la grille de test dans la grille vide
    result=test_equality_int(game_nb_pieces(g), game_nb_pieces(gtest), "nb_piece in test_copy_game") && result; // on vérifie que les deux grilles ont bien le même nombre de pièces
    for (int i=0; i < game_nb_pieces(g); ++i){
        result=test_equality_piece(game_piece(gtest, i), game_piece(g, i), "pieces comparisons in test_copy_game") && result; // on vérifie que les pièces sont les mêmes
    }
    delete_game(g);
    delete_game(gtest);
    return result;
}
bool test_game_over(){
    bool result=true;
    game g=set_game();
    play_move(g, 0, DOWN, 3); //on mène la pièce vers la sortie
    result=test_equality_bool(true, game_over_hr(g), "game_over in test_game_over") && result;
    delete_game(g);
    return result;
}
int main(int argc, char *argv[]){
    bool result=true;
    result=test_equality_bool(true, test_new_game(), "test_new_game in main") && result;
    result=test_equality_bool(true, test_copy_game(), "test_copy_game in main") && result;
    result=test_equality_bool(true, test_play_move(), "test_play_move in main") && result;
    result=test_equality_bool(true, test_game_over(), "test_game_over in main") && result;

    if (result){
        printf("Ca marche c: !\n");
        return EXIT_SUCCESS;
    } else{
        printf("Ton code c'est de la merde !\n");
        return EXIT_FAILURE;
    }
}
