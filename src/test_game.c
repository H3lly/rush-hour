#include <stdio.h>
#include <stdlib.h>

#include "piece.h"
#include "game.h"
#include "test_functions.h"

#define NB_PIECES_RH 4
#define NB_PIECES_AR 7

piece pieces_ar[NB_PIECES_AR];
piece pieces_rh[NB_PIECES_RH];

/* 

test configuration rush hour
. . . . . 3
. . . . . 3
. . . 0 0 3
. . . . . .
. . . 1 2 2
. . . 1 . .

test configuration ane rouge 
1 0 0 2
1 0 0 2
3 . . 4
3 . . 4
5 . . 6
 


 */

game set_game_rh(){
    pieces_rh[0]=new_piece_rh(3, 3, true, true);
    pieces_rh[1]=new_piece_rh(3, 0, true, false);
    pieces_rh[2]=new_piece_rh(4, 1, true, true);
    pieces_rh[3]=new_piece_rh(5, 3, false, false);

    return new_game_hr(NB_PIECES_RH, pieces_rh);
}

game set_game_ar(){
    pieces_ar[0]=new_piece(1, 3, 2, 2, true, true);
    pieces_ar[1]=new_piece(0, 3, 1, 2, true, true);
    pieces_ar[2]=new_piece(3, 3, 1, 2, true, true);
    pieces_ar[3]=new_piece(0, 1, 1, 2, true, true);
    pieces_ar[4]=new_piece(3, 1, 1, 2, true, true);
    pieces_ar[5]=new_piece(0, 0, 1, 1, true, true);
    pieces_ar[6]=new_piece(3, 0, 1, 1, true, true);

    return new_game(4, 5, NB_PIECES_AR, pieces_ar);
}

bool test_new_game_rh(){
    game g=set_game_rh();
    return test_equality_bool(test_new_game(g, 6, 6, true), true, "test_new_game in test_new_game_rh");
}

bool test_new_game_ar(){
    game g=set_game_ar();
    return test_equality_bool(test_new_game(g, 4, 5, false), true, "test_new_game in test_new_game_ar");
}

void test_new_game(game g, int w, int h, bool rh){
    bool result=true;
    result=test_equality_int(h, game_height(g), "game_height in test_new_game")&&result;
    result=test_equality_int(w, game_width(g), "game_width in test_new_game")&&result;
    result=test_equality_int(NB_PIECES, game_nb_pieces(g), "game_nb_pieces in test_new_game")&&result;
    for (int i=0;i<NB_PIECES;i++){
        result=equals(pieces[i], game_piece(g, i))&&result;
    }
    delete_game(g);
    return result;
}

bool test_play_move_rh(){
    bool result=true;
    game g=set_game();
    piece p_test=new_piece_rh(get_x(game_piece(g, 0)), get_y(game_piece(g, 0)), is_horizontal(game_piece(g, 0)), is_small(game_piece(g, 0)));
    result=test_equality_bool(true, play_move(g, 0, LEFT, 1), "play_move 1 in test_play_move")&&result;// possible movement
    result=test_equality_int(get_x(game_piece(g, 0)), 2, "get_x 1 in test_play_move")&&result;
    result=test_equality_int(get_y(game_piece(g, 0)), 3, "get_y 1 in test_play_move")&&result;
    result=test_equality_bool(false, play_move(g, 1, DOWN, 1), "play_move 2 in test_play_move")&&result;// 1 is out of the grid
    result=test_equality_int(get_x(game_piece(g, 1)), 3, "get_x 2 in test_play_move")&&result;
    result=test_equality_int(get_y(game_piece(g, 1)), 0, "get_y 2 in test_play_move")&&result;
    result=test_equality_bool(false, play_move(g, 2, LEFT, 1), "play_move 3 in test_play_move ")&&result;// intersection between 2 and 1
    result=test_equality_int(get_x(game_piece(g, 2)), 4, "get_x 3 in test_play_move")&&result;
    result=test_equality_int(get_y(game_piece(g, 2)), 1, "get_y 3 in test_play_move")&&result;
    result=test_equality_bool(false, play_move(g, 3, DOWN, 2), "play_move 4 in test_play_move")&&result;// intersection between 3 and 2 
    result=test_equality_int(get_x(game_piece(g, 3)), 5, "get_x 4 in test_play_move")&&result;
    result=test_equality_int(get_y(game_piece(g, 3)), 3, "get_y 4 in test_play_move")&&result;
    result=test_equality_int(nbmove, game_nb_moves(g), "game_nb_moves in test_play_move")&&result;
    result=!equals(p_test, game_piece(g, 0))&&result;// this is the only piece that moved
    delete_piece(p_test);
    delete_game(g);
    return result;
}

bool test_play_move_ar(){
    bool result=true;
    game g=set_game();
    piece p_test=new_piece(get_x(game_piece(g, 0)), get_y(game_piece(g, 0)), get_height(game_piece(g, 0)), get_width(game_piece(g, 0)), can_move_x(game_piece(g, 0)), can_move_y(game_piece(g, 0)));
    result=test_equality_bool(true, play_move(g, 5, RIGHT, 1), "play_move 1 in test_play_move")&&result;// possible movement
    result=test_equality_int(get_x(game_piece(g, 5)), 1, "get_x 1 in test_play_move")&&result;
    result=test_equality_int(get_y(game_piece(g, 5)), 0, "get_y 1 in test_play_move")&&result;
    result=test_equality_bool(false, play_move(g, 6, RIGHT, 1), "play_move 2 in test_play_move")&&result;// impossible movement: 6 would be out of bounds
    result=test_equality_int(get_x(game_piece(g, 6)), 3, "get_x 2 in test_play_move")&&result;
    result=test_equality_int(get_y(game_piece(g, 6)), 0, "get_y 2 in test_play_move")&&result;
    result=test_equality_bool(false, play_move(g, 2, LEFT, 1), "play_move 3 in test_play_move ")&&result;// intersection between 2 and 1
    result=test_equality_int(get_x(game_piece(g, 2)), 3, "get_x 3 in test_play_move")&&result;
    result=test_equality_int(get_y(game_piece(g, 2)), 3, "get_y 3 in test_play_move")&&result;
    result=test_equality_bool(false, play_move(g, 6, LEFT, 2), "play_move 4 in test_play_move")&&result;// intersection between 6 and 2
    result=test_equality_int(get_x(game_piece(g, 6)), 3, "get_x 4 in test_play_move")&&result;
    result=test_equality_int(get_y(game_piece(g, 6)), 0, "get_y 4 in test_play_move")&&result;
    result=test_equality_int(1, game_nb_moves(g), "game_nb_moves in test_play_move")&&result;
    result=!equals(p_test, game_piece(g, 5))&&result;// this is the only piece that moved
    delete_game(g);
    return result;
}

bool test_copy_game_rh(){
    bool rh=true;
    test_copy_game_common();
    delete_game(g);
    delete_game(g_test);
    return result;

    /* ceci est le code original de la fonction, je le laisse au cas où
    bool result=true;
    game g=set_game();
    piece empty_list[0];
    game g_test=new_game_hr(0, empty_list); // empty grid
    copy_game(g, g_test); // copy the first grid into the empty grid
    result=test_equality_int(game_nb_pieces(g), game_nb_pieces(g_test), "game_nb_pieces in test_copy_game_rh") && result; // we check whether both grids have the same number of pieces
    for (int i=0; i < game_nb_pieces(g); ++i){
        result=test_equality_piece(game_piece(g_test, i), game_piece(g, i), "pieces comparisons in test_copy_game_rh") && result; // we check whether both have the same pieces
    }
    play_move(g, 0, DOWN, 1); // g is now different than g_test
    result=test_equality_bool(false, (test_equality_piece(game_piece(g_test, 0), game_piece(g, 0), "pieces comparisons in test_copy_game_rh")) && result; // we check whether both games are different
    delete_game(g);
    delete_game(g_test);
    return result;*/
}

bool test_copy_game_ar(){
    bool rh=false;
    test_copy_game_common();
    delete_game(g);
    delete_game(g_test);
    return result;

    /* ceci est le code original de la fonction, je le laisse au cas où
    bool result=true;
    game g=set_game();
    piece empty_list[0];
    game g_test=new_game(4, 5, 0, empty_list);
    copy_game(g, g_test);
    result=test_equality_int(game_nb_pieces(g), game_nb_pieces(g_test), "game_nb_pieces in test_copy_game_ar") && result;
    for (int i=0; i < game_nb_pieces(g); ++i){
        result=test_equality_piece(game_piece(g_test, i), game_piece(g, i), "pieces comparisons in test_copy_game_ar") && result;
    }
    play_move(g, 0, LEFT, 1);
    result=test_equality_bool(false, (test_equality_piece(game_piece(g_test, 0), game_piece(g, 0), "pieces comparisons in test_copy_game_ar")) && result;
    delete_game(g);
    delete_game(g_test);
    return result;*/
}

void test_copy_game_common(){
    bool result=true;
    game g=set_game();
    game g_test;
    piece empty_list[0];
    if (rh){
        g_test=new_game_hr(0, empty_list);
    } else{
        g_test=new_game(4, 5, 0, empty_list);
    } // empty grid
    copy_game(g, g_test);// copy the first grid into the empty grid
    result=test_equality_int(game_nb_pieces(g), game_nb_pieces(g_test), "game_nb_pieces in test_copy_game")&&result;// we check whether both grids have the same number of pieces
    for (int i=0;i<game_nb_pieces(g);++i){
        result=test_equality_piece(game_piece(g_test, i), game_piece(g, i), "pieces comparisons in test_copy_game")&&result;// we check whether both have the same pieces
    }
    if (rh){
        play_move(g, 0, DOWN, 1);
    } else{
        play_move(g, 0, LEFT, 1);
    }

    result=test_equality_bool(false, (test_equality_piece(game_piece(g_test, 0), game_piece(g, 0), "pieces comparisons in test_copy_game"))&&result;
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
