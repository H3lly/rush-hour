#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "useful_functions.h"

struct game_s {
    int nb_pieces;
    int nb_moves;
    piece *piece_list;
};

typedef const struct game_s* cgame;

game new_game_hr(int nb_pieces, piece *pieces) {
    game g = malloc(sizeof (struct game_s));
    g->nb_moves = 0;
    g->nb_pieces = nb_pieces;
    g->piece_list = pieces;
    return g;
}

void delete_game(game g) {
    for (int i = 0 ; i < g->nb_pieces; i++)
        delete_piece(g->piece_list[i]);
    free(g);
}

void copy_game(cgame src, game dst) {
    dst->nb_pieces = src->nb_pieces;
    dst->nb_moves = src->nb_moves;
    dst->piece_list = src->piece_list;
}

int game_nb_pieces(cgame g) {
    return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num) {
    return g->piece_list[piece_num];
}

bool game_over_hr(cgame g) {
    return (get_x(g->piece_list[0]) == 4) && (get_y(g->piece_list[0]) == 3);
}

bool out_of_grid(cpiece p) {
    int abs = get_x(p);
    int ord = get_y(p);
    if (is_horizontal(p)) {
        if (get_width(p) == 2)
            return (abs < 0 || abs > 4);
        return (abs < 0 || abs > 3);
    }
    if (get_height(p) == 2)
        return (ord < 0 || ord > 4);
    return (ord < 0 || ord > 3);
}

bool play_move(game g, int piece_num, dir d, int distance) {
    piece p = g->piece_list[piece_num];
    if(!movement_is_allowed(p, d)){
        printf("Mouvement impossible : L'orientation de la pièce et la direciton de son déplacement sont incompatibles.\n\n");
        return false;
    }
    int travel =0;
    while (distance != 0) {
        move_piece(p, d, 1);
        g->nb_moves += 1;
        distance--;
        travel++;
        for (int i = 0; i < game_nb_pieces(g); ++i) {
            if (p == g->piece_list[i]){
                i++;
                if(i>=game_nb_pieces(g))
                    break;
            }
            if (intersect(p, game_piece(g, i))) {
                printf("Mouvement impossible : La voiture %d empêche le déplacement de la voiture %d.\n\n", i, piece_num);
                move_piece(p, d, travel*-1);
                g->nb_moves -= travel;
                return false;
            }
            if (out_of_grid(p)) {
                printf("Mouvement impossible : La piece %d est au bord de la grille.\n\n", piece_num);
                move_piece(p, d, travel*-1);
                g->nb_moves -= travel;
                return false;
            }
        }
    }
    return true;
}

int game_nb_moves(cgame g) {
    return g->nb_moves;
}