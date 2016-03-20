#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game.h"
#include "piece.h"
#include "test_functions.h"

bool equals(cpiece p1, cpiece p2) {
    if(p1==p2) return true; //if it's the same reference it's the sam piece.
    return (get_x(p1) == get_x(p2))&&(get_y(p1) == get_y(p2))&&(get_width(p1) == get_width(p2))&&(get_height(p1) == get_height(p2)&&(can_move_x(p1)==can_move_x(p2))&&(can_move_y(p1)==can_move_y(p2)));
}

//returns if the piece is small
bool is_small(cpiece p){
    return get_height(p)==2||get_width(p)==2;
}

//##################################################### A MODIFIER ###############################################################
//ne marche QUE POUR MOINS DE 11 PIECES
void show_grid(game g){
    for (int ord=game_height(g)-1; ord >= 0; ord--){
        for (int abs=0; abs < game_width(g); abs++){
            if (game_square_piece(g, abs, ord) == -1)
                printf(".  ");
            else
                printf("%d  ", game_square_piece(g, abs, ord));
        }
        printf("\n");
    }
    printf("\nNombre de mouvements : %d\n----------\n\n", game_nb_moves(g));
}


bool game_over_an(cgame g){
    return (get_x(game_piece(g, 0)) == (game_width(g) / 2) - 1) && (get_y(game_piece(g, 0)) == 0);
}

bool test_equality_int(int expected, int value, char * msg){
    if (expected != value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
    return expected == value;
}

bool test_equality_bool(bool expected, bool value, char * msg){
    if (expected != value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
    return expected == value;
}

bool test_equality_piece(cpiece expected, cpiece value, char * msg){
    if (!equals(expected, value)){
        fprintf(stderr, "ERR: Pieces are different | Error from : %s\n", msg);
    }
    return equals(expected, value);
}