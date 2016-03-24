#include <stdio.h>
#include <stdlib.h>

#include "piece.h"
#include "game.h"
#include "test_functions.h"

#define NB_PIECES 7

piece pieces[NB_PIECES];
/* test configuration
1 0 0 2
1 0 0 2
3 . . 4
3 . . 4
5 . . 6
 */

game set_game(){
    pieces[0]=new_piece(1, 3, 2, 2, true, true);
    pieces[1]=new_piece(0, 3, 1, 2, true, true);
    pieces[2]=new_piece(3, 3, 1, 2, true, true);
    pieces[3]=new_piece(0, 1, 1, 2, true, true);
    pieces[4]=new_piece(3, 1, 1, 2, true, true);
    pieces[5]=new_piece(0, 0, 1, 1, true, true);
    pieces[6]=new_piece(3, 0, 1, 1, true, true);
    
    return new_game(4, 5, NB_PIECES, pieces);
}
bool test_new_game(){
    bool result=true;
    game g=set_game();
    result=test_equality_int(5, game_height(g), "game_height in test_game_height") && result;
    result=test_equality_int(4, game_width(g), "game_width in test_game_width") && result;
    result=test_equality_int(NB_PIECES, game_nb_pieces(g), "game_nb_pieces in test_new_game") && result;
    for (int i=0; i < NB_PIECES; i++){
        result=result && equals(pieces[i], game_piece(g, i));
    }
    delete_game(g);
    return result;
}

bool test_play_move(){
    bool result=true;
    int nbmove=1;
    game g=set_game();
    piece p_test=new_piece(get_x(game_piece(g, 0)), get_y(game_piece(g, 0)), get_height(game_piece(g, 0)), get_width(game_piece(g, 0)), can_move_x(game_piece(g, 0)), can_move_y(game_piece(g, 0)));
    result=test_equality_bool(true, play_move(g, 5, RIGHT, 1), "play_move 1 in test_play_move") && result; // possible movement
    result=test_equality_int(get_x(game_piece(g, 5)), 1, "get_x 1 in test_play_move") && result;
    result=test_equality_int(get_y(game_piece(g, 5)), 0, "get_y 1 in test_play_move") && result;
    result=test_equality_bool(false, play_move(g, 6, RIGHT, 1), "play_move 2 in test_play_move") && result; // impossible movement: 6 would be out of bounds
    result=test_equality_int(get_x(game_piece(g, 6)), 3, "get_x 2 in test_play_move") && result; 
    result=test_equality_int(get_y(game_piece(g, 6)), 0, "get_y 2 in test_play_move") && result;
    result=test_equality_bool(false, play_move(g, 2, LEFT, 1), "play_move 3 in test_play_move ") && result; // intersection between 2 and 1
    result=test_equality_int(get_x(game_piece(g, 2)), 3, "get_x 3 in test_play_move") && result; 
    result=test_equality_int(get_y(game_piece(g, 2)), 3, "get_y 3 in test_play_move") && result;
    result=test_equality_bool(false, play_move(g, 6, LEFT, 2), "play_move 4 in test_play_move") && result; // intersection between 6 and 2
    result=test_equality_int(get_x(game_piece(g, 6)), 3, "get_x 4 in test_play_move") && result; 
    result=test_equality_int(get_y(game_piece(g, 6)), 0, "get_y 4 in test_play_move") && result;
    result=test_equality_int(nbmove, game_nb_moves(g), "game_nb_moves in test_play_move") && result; // this is the only piece that moved
    result=!equals(p_test, game_piece(g, 5)) && result; // seule piece ayant fait un déplacement
    delete_game(g);
    return result;
}
bool test_copy_game(){
    bool result=true;
    game g=set_game(); // we create the "test configuration" grid
    piece empty_list[0];
    game gtest=new_game(4, 5, 0, empty_list); // empty grid
    copy_game(g, gtest); // copy the first grid into the empty grid
    result=test_equality_int(game_nb_pieces(g), game_nb_pieces(gtest), "nb_piece in test_copy_game") && result; // we check whether both grids have the same number of pieces
    for (int i=0; i < game_nb_pieces(g); ++i){
        result=test_equality_piece(game_piece(gtest, i), game_piece(g, i), "pieces comparisons in test_copy_game") && result; // we check whether both have the same pieces
    }
    delete_game(g);
    delete_game(gtest);
    return result;
}
bool test_game_over(){
    bool result=true;
    game g=set_game();
    play_move(g, 0, DOWN, 3); // we bring the piece to the exit
    result=test_equality_bool(true, game_over_an(g), "game_over in test_game_over") && result;
    delete_game(g);
    return result;
}

/* ce qui suit est très surement inutile
 
    bool test_game_height(){
    game g=set_game();
    bool result=true;
    result=test_equality_int(5, game_height(g), "game_height in test_game_height") && result; 
    delete_game(g);
    return result;
}
bool test_game_width(){
    game g=set_game();
    bool result=true;
    result=test_equality_int(4, game_width(g), "game_width in test_game_width") && result; 
    delete_game(g);
    return result;
}
*/


bool test_game_square_piece(){
    game g=set_game();
    bool result=true;
    result=test_equality_int(5, game_square_piece(g, 0, 0), "game_square_piece in test_game_square_piece") && result;
    result=test_equality_int(0, game_square_piece(g, 1, 3), "game_square_piece in test_game_square_piece") && result;
    // ajouter d'autres tests si besoin
    delete_game(g);
    return result;
}

int main(int argc, char *argv[]){
    bool result=true;
    result=test_equality_bool(true, test_new_game(), "test_new_game in main") && result;
    result=test_equality_bool(true, test_copy_game(), "test_copy_game in main") && result;
    result=test_equality_bool(true, test_play_move(), "test_play_move in main") && result;
    result=test_equality_bool(true, test_game_over(), "test_game_over in main") && result;
    result=test_equality_bool(true, test_game_height(), "test_game_height in main") && result;
    result=test_equality_bool(true, test_game_width(), "test_game_width in main") && result;
    result=test_equality_bool(true, test_game_square_piece(), "test_game_square_piece in main") && result;

    if (result){
        printf("It works c: !\n");
        return EXIT_SUCCESS;
    } else{
        printf("Your code sucks !\n");
        return EXIT_FAILURE;
    }
}
