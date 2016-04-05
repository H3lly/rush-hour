#include <stdio.h>
#include <stdlib.h>

#include "piece.h"
#include "game.h"
#include "test_functions.h"

#define NB_PIECES 2

game g;
piece pieces[NB_PIECES];

/* 

 final test configuratrion
. . . . . .
. . . . . .
1 1 0 0 . .
. . . . . .
. . . . . .
. . . . . .

 */

void set_game(){
    pieces[0]=new_piece(2, 3, 2, 1, true, true);
    pieces[1]=new_piece_rh(0, 3, true, false);
    g=new_game_hr(NB_PIECES, pieces);
}

void tear_down(){
//    for (int i = 0; i < NB_PIECES; i++)
//        delete_piece(pieces[i]); ??????????????????????????,
    delete_game(g);
}

void test_new_game(){
    bool result=true;
    set_game();
    result=test_equality_int(6, game_height(g), "game_height in test_new_game")&&result;
    result=test_equality_int(6, game_width(g), "game_width in test_new_game")&&result;
    result=test_equality_int(NB_PIECES, game_nb_pieces(g), "game_nb_pieces in test_new_game")&&result;
    result=test_equality_piece(pieces[0], game_piece(g, 0), "test_equality_piece 1 in test_new_game")&&result;
    result=test_equality_piece(pieces[1], game_piece(g, 1), "test_equality_piece 2 in test_new_game")&&result;
    tear_down();
    return result;
}

bool test_play_move(){
    bool result=true;
    set_game();
    piece p0_before, p0_after=malloc(sizeof (struct piece_s));
    copy_piece(game_piece(g, 0), p0_before);//p0_before = 0 piece before any play_move
    result=test_equality_bool(false, play_move(g, 0, LEFT, 1), "play_move 1 in test_play_move")&&result;// intersection between 0 and 1
    result=test_equality_bool(false, play_move(g, 1, UP, 1), "play_move 2 in test_play_move")&&result;// horizontal RH piece
    result=test_equality_bool(true, play_move(g, 0, UP, 1), "play_move 3 in test_play_move")&&result;
    result=test_equality_int(4, get_y(game_piece(g, 0)), "get_y in test_play_move")&&result;// checks if the piece
    result=test_equality_int(2, get_x(game_piece(g, 0)), "get_x in test_play_move")&&result;// moved properly
    result=test_equality_bool(true, play_move(g, 1, RIGHT, 1), "play_move 4 in test_play_move")&&result;
    copy_piece(game_piece(g, 0), p0_after);//p0_after = 0 piece after play_move ; avoids writing "game_piece(g,0)" multiple times
    result=test_equality_bool(false, equals(p0_before, p0_after), "equals in test_play_move");
    delete_piece(p0_before);
    delete_piece(p0_after);
    tear_down();
    return result;
}

void test_copy_game(){
    bool result=true;
    set_game();
    game g_cpy=malloc(sizeof (struct game_s));
    copy_game(g, g_cpy);// copy the first grid into the empty grid
    result=test_equality_int(game_nb_pieces(g), game_nb_pieces(g_cpy), "game_nb_pieces in test_copy_game")&&result;// we check whether both grids have the same number of pieces
    result=test_equality_pieces(g, g_cpy, "test_equality_pieces in test_copy_game")&&result;
    play_move(g, 0, RIGHT, 1);
    result=test_equality_bool(false, (equals(game_piece(g_cpy, 0), game_piece(g, 0), "equals in test_copy_game"))&&result);
    tear_down();
    delete_game(g_cpy);
    return result;
}

bool test_game_over_rh(){
    bool result=true;
    game g=set_game();
    play_move(g, 0, LEFT, 2);
    result=test_equality_bool(false, game_over_hr(g), "game_over_hr 0 in test_game_over_rh")&&result;
    play_move(g, 1, UP, 4);
    result=test_equality_bool(false, game_over_hr(g), "game_over_hr 1 in test_game_over_rh")&&result;
    play_move(g, 2, LEFT, 1);
    result=test_equality_bool(false, game_over_hr(g), "game_over_hr 2 in test_game_over_rh")&&result;
    play_move(g, 3, DOWN, 3);
    result=test_equality_bool(false, game_over_hr(g), "game_over_hr 3 in test_game_over_rh")&&result;
    play_move(g, 0, RIGHT, 3);// we bring the piece to the exit
    result=test_equality_bool(true, game_over_hr(g), "game_over_hr 4 in test_game_over_rh")&&result;
    delete_game(g);

    return result;
}

bool test_game_over_ar(){
    bool result=true;
    game g=set_game();
    play_move(g, 0, DOWN, 3);
    result=test_equality_bool(true, game_over_an(g), "game_over_an in test_game_over_ar")&&result;
    delete_game(g);

    return result;
}

bool test_game_square_piece(){
    game g=set_game();
    bool result=true;
    result=test_equality_int(5, game_square_piece(g, 0, 0), "game_square_piece in test_game_square_piece")&&result;
    result=test_equality_int(0, game_square_piece(g, 1, 3), "game_square_piece in test_game_square_piece")&&result;
    delete_game(g);

    return result;
}

int main(int argc, char *argv[]){
    bool result=true;

    // tests for the rh functions

    result=test_equality_bool(true, test_new_game_rh(), "test_new_game_rh in main")&&result;
    result=test_equality_bool(true, test_copy_game_rh(), "test_copy_game_rh in main")&&result;
    result=test_equality_bool(true, test_play_move_rh(), "test_play_move_rh in main")&&result;
    result=test_equality_bool(true, test_game_over_rh(), "test_game_over_rh in main")&&result;

    // tests for the ar functions

    result=test_equality_bool(true, test_new_game_ar(), "test_new_game_ar in main")&&result;
    result=test_equality_bool(true, test_copy_game_ar(), "test_copy_game_ar in main")&&result;
    result=test_equality_bool(true, test_play_move_ar(), "test_play_move_ar in main")&&result;
    result=test_equality_bool(true, test_game_over_ar(), "test_game_over_ar in main")&&result;
    result=test_equality_bool(true, test_game_square_piece(), "test_game_square_piece in main")&&result;

    if (result){
        printf("It works c: !\n");
        return EXIT_SUCCESS;
    } else{
        printf("Your code sucks !\n");
        return EXIT_FAILURE;
    }
}
