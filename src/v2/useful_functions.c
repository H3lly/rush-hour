#include <stdio.h>
#include <stdlib.h>

#include "useful_functions.h"

bool equals(cpiece p1, cpiece p2) {
    if(p1==p2) return true; //if it's the same reference it's the sam piece.
    return (get_x(p1) == get_x(p2))&&(get_y(p1) == get_y(p2))&&(get_width(p1) == get_width(p2))&&(get_height(p1) == get_height(p2)&&(can_move_x(p1)==can_move_x(p2))&&(can_move_y(p1)==can_move_y(p2)));
}

int piece_area (cpiece p){
    return get_width(p)*get_height(p);
}

bool out_of_grid(cpiece p, cgame g){
    return (get_x(p) < 0 || get_x(p) + get_width(p) > game_width(g) || (get_y(p) < 0 || get_y(p) + get_height(p) > game_height(g)));
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