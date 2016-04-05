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
    pieces[1]=new_piece_rh(0, 3, true, true);
    g=new_game_hr(NB_PIECES, pieces);
}

void tear_down(){
    //    for (int i = 0; i < NB_PIECES; i++)
    //        delete_piece(pieces[i]); ??????????????????????????
    delete_game(g);
}

bool test_new_game(){
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
    piece p0_before=new_piece(0, 0, 2, 2, false, false);
    show_grid(g);
    piece p0_after=new_piece(0, 0, 2, 2, false, false);
    show_grid(g);
    copy_piece(game_piece(g, 0), p0_before);//p0_before = 0 piece before any play_move
    result=test_equality_bool(false, play_move(g, 0, LEFT, 1), "play_move 1 in test_play_move")&&result;// intersection between 0 and 1
    result=test_equality_bool(false, play_move(g, 1, UP, 1), "play_move 2 in test_play_move")&&result;// horizontal RH piece
    result=test_equality_bool(true, play_move(g, 0, UP, 1), "play_move 3 in test_play_move")&&result;
    result=test_equality_int(4, get_y(game_piece(g, 0)), "get_y in test_play_move")&&result;// checks if the piece
    result=test_equality_int(2, get_x(game_piece(g, 0)), "get_x in test_play_move")&&result;// moved properly
    result=test_equality_bool(true, play_move(g, 1, RIGHT, 1), "play_move 4 in test_play_move")&&result;
    copy_piece(game_piece(g, 0), p0_after);//p0_after = 0 piece after play_move ; avoids writing "game_piece(g,0)" multiple times
    result=test_equality_bool(false, equals(p0_before, p0_after), "equals in test_play_move")&&result;
    delete_piece(p0_before);
    delete_piece(p0_after);
    tear_down();
    return result;
}

bool test_copy_game(){
    bool result=true;
    set_game();
    game g_cpy=new_game(0, 0, 0, NULL);
    copy_game(g, g_cpy);
    result=test_equality_int(game_nb_pieces(g), game_nb_pieces(g_cpy), "game_nb_pieces in test_copy_game")&&result;// we check whether both grids have the same number of pieces
    result=test_equality_piece(game_piece(g, 0), game_piece(g_cpy, 0), "test_equality_piece 1 in test_copy_game")&&result;
    result=test_equality_piece(game_piece(g, 1), game_piece(g_cpy, 1), "test_equality_piece 2 in test_copy_game")&&result;
    play_move(g, 0, RIGHT, 1);
    result=test_equality_bool(false, equals(game_piece(g, 0), game_piece(g_cpy, 0)), "equals in test_copy_game")&&result;
    tear_down();
    delete_game(g_cpy);
    return result;
}

bool test_game_over(){
    bool result=true;
    set_game();
    play_move(g, 0, DOWN, 3);
    result=test_equality_bool(true, game_over_ar(g), "game_over_ar in test_game_over")&&result;
    play_move(g, 0, UP, 3);
    play_move(g, 0, RIGHT, 2);
    result=test_equality_bool(true, game_over_hr(g), "game_over_hr in test_game_over")&&result;
    tear_down();
    return result;
}

bool test_game_square_piece(){
    set_game();
    bool result=true;
    result=test_equality_int(0, game_square_piece(g, 2, 3), "game_square_piece 1 in test_game_square_piece")&&result;
    result=test_equality_int(0, game_square_piece(g, 3, 3), "game_square_piece 2 in test_game_square_piece")&&result;
    result=test_equality_int(1, game_square_piece(g, 0, 3), "game_square_piece 3 in test_game_square_piece")&&result;
    result=test_equality_int(1, game_square_piece(g, 1, 3), "game_square_piece 4 in test_game_square_piece")&&result;
    result=test_equality_int(-1, game_square_piece(g, 4, 3), "game_square_piece 5 in test_game_square_piece")&&result;//nothing here
    result=test_equality_int(-1, game_square_piece(g, 0, 2), "game_square_piece 6 in test_game_square_piece")&&result;//nothing here
    tear_down();
    return result;
}

int main(int argc, char *argv[]){
    bool result=true;
    result=test_equality_bool(true, test_new_game(), "test_new_game in main")&&result;
    result=test_equality_bool(true, test_copy_game(), "test_copy_game in main")&&result;
    result=test_equality_bool(true, test_play_move(), "test_play_move in main")&&result;
    result=test_equality_bool(true, test_game_over(), "test_game_over in main")&&result;
    result=test_equality_bool(true, test_game_square_piece(), "test_game_square_piece in main")&&result;
    if (result){
        printf("It works c: !\n");
        return EXIT_SUCCESS;
    } else{
        printf("Your code sucks !\n");
        return EXIT_FAILURE;
    }
}
