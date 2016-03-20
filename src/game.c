#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"
#include "useful_functions.h"

struct game_s{
    int width;
    int height;
    int nb_pieces;
    int nb_moves;
    piece *piece_list;
};

game new_game(int width, int height, int nb_pieces, piece *pieces){
    game g=malloc(sizeof (struct game_s));
    g->width=width;
    g->height=height;
    g->nb_pieces=nb_pieces;
    g->nb_moves=0;
    g->piece_list=pieces;
    return g;
}

game new_game_hr(int nb_pieces, piece *pieces){
    return new_game(6, 6, nb_pieces, pieces);
}

void delete_game(game g){
    for (int i=0; i < g->nb_pieces; i++)
        delete_piece(g->piece_list[i]);
    free(g);
}
void copy_game(cgame src, game dst){
    dst->nb_pieces=src->nb_pieces;
    dst->nb_moves=src->nb_moves;
    dst->piece_list=src->piece_list;
    dst->width=src->width;
    dst->height=src->height;
}
int game_nb_pieces(cgame g){
    return g->nb_pieces;
}
cpiece game_piece(cgame g, int piece_num){
    return g->piece_list[piece_num];
}
bool game_over_hr(cgame g){
    return (get_x(g->piece_list[0]) == 4) && (get_y(g->piece_list[0]) == 3);
}
bool play_move(game g, int piece_num, dir d, int distance){
    piece p=g->piece_list[piece_num];
    if (!movement_is_allowed(p, d)){
        printf("Mouvement impossible : L'orientation de la pièce et la direciton de son déplacement sont incompatibles.\n\n");
        return false;
    }
    int travel=0;
    while (distance != 0){
        move_piece(p, d, 1);
        g->nb_moves+=1;
        distance--;
        travel++;
        for (int i=0; i < game_nb_pieces(g); ++i){
            if (p == g->piece_list[i]){
                i++;
                if (i >= game_nb_pieces(g))
                    break;
            }
            if (intersect(p, game_piece(g, i))){
                printf("Mouvement impossible : La voiture %d empêche le déplacement de la voiture %d.\n\n", i, piece_num);
                move_piece(p, d, travel*-1);
                g->nb_moves-=travel;
                return false;
            }
            if (out_of_grid(p, g)){
                printf("Mouvement impossible : La piece %d est au bord de la grille.\n\n", piece_num);
                move_piece(p, d, travel*-1);
                g->nb_moves-=travel;
                return false;
            }
        }
    }
    return true;
}
int game_nb_moves(cgame g){
    return g->nb_moves;
}
int game_width(cgame g){
    return g->width;
}
int game_height(cgame g){
    return g->height;
}
int game_square_piece(game g, int x, int y){
    for (int i=0; i < g->nb_pieces; i++){
        piece p=g->piece_list[i];
        for (int w=0; w < get_width(p); ++w){
            for (int h=0; h < get_height(p); ++h){
                if (get_x(p) + w == x && get_y(p) + h == y)
                    return i;
            }
        }
    }
    return -1;
}