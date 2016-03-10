#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "useful_functions.h"
//#include "grid.h"

/*
struct game_s {
    int nb_pieces;
    int nb_moves;
    piece *liste_piece;
    //grille grid;
};
*/

struct game_s {
    int width;
    int height;
    int nb_pieces;
    int nb_moves;
    piece *liste_piece;
    //grille grid;
};

typedef const struct game_s* cgame;

/*
game new_game_hr(int nb_pieces, piece *pieces) {
    game g = malloc(sizeof (struct game_s));
    g->nb_moves = 0;
    g->nb_pieces = nb_pieces;
    g->liste_piece = pieces;
    return g;
}
*/

void delete_game(game g) {
    for (int i = 0 ; i < g->nb_pieces; i++)
        delete_piece(g->liste_piece[i]);
    free(g);
}

void copy_game(cgame src, game dst) {                       //MODIFICATIONS V2
    dst->nb_pieces = src->nb_pieces;
    dst->nb_moves = src->nb_moves;
    dst->liste_piece = src->liste_piece;
    dst->width = src->width;
    dst->height = src->height;
}

int game_nb_pieces(cgame g) {
    return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num) {
    return g->liste_piece[piece_num];
}

bool game_over_hr(cgame g) {
    return (get_x(g->liste_piece[0]) == 4) && (get_y(g->liste_piece[0]) == 3);
}
//vérifie que la pièce ne dépace pas de la grille

bool out_of_grid(cpiece p, cgame g) {                       //MODIFICATIONS V2
    int abs = get_x(p);
    int ord = get_y(p);
    if (can_move_x(p)) {
        return (abs < 0 || abs > game_width(g)-get_width(p));      //exemple : game_width(g) = 6 -> tableau de 0 à 5, get_width = 2 donc piece occupe case 4 et 5 (donc get_width(g)-2)
    }
    return (ord < 0 || ord > game_height(g)-get_height(p));
}

//ajouter vérification pour pas depasser les bords
bool play_move(game g, int piece_num, dir d, int distance) {
    piece p = g->liste_piece[piece_num];
    if(!movement_is_allowed(p, d)){
        //printf("Mouvement impossible : L'orientation de la pièce et la direciton de son déplacement sont incompatibles.\n\n");
        return false;
    }
    int distance_parcourue =0;
    while (distance != 0) {
        move_piece(p, d, 1);
        g->nb_moves += 1;
        distance--;
        distance_parcourue++;
        for (int i = 0; i < game_nb_pieces(g); ++i) {
            if (p == g->liste_piece[i]){
                i++;
                if(i>=game_nb_pieces(g))
                    break;
            }
            if (intersect(p, game_piece(g, i))) {
                //printf("Mouvement impossible : La voiture %d empêche le déplacement de la voiture %d.\n\n", i, piece_num);
                move_piece(p, d, distance_parcourue*-1);
                g->nb_moves -= distance_parcourue;
                return false;
            }
            if (out_of_grid(p, g)) {                                //MODIFICATIONS : ajout de g
                //printf("Mouvement impossible : La piece %d est au bord de la grille.\n\n", piece_num);
                move_piece(p, d, distance_parcourue*-1);
                g->nb_moves -= distance_parcourue;
                return false;
            }
        }
    }
    return true;
}

//retourne le nombre de mouvements effectués

int game_nb_moves(cgame g) {
    return g->nb_moves;
}

///////////// version 2 /////////////////



game new_game (int width, int height, int nb_pieces, piece *pieces){
    game g = malloc(sizeof (struct game_s));
    g->width = width;
    g->height = height;
    g->nb_pieces = nb_pieces;
    g->nb_moves = 0;
    g->liste_piece = pieces;
    return g;
}


/**
 *@brief return the width of the grid
 */
int game_width(cgame g){
    return g->width;
}

/**
 *@brief return the height of the grid
 */
int game_height(cgame g){
    return g->height;
}

/**
 * @brief return the number of then piece located on this square (-1 if no piece is present)
 * @param game
 * @param x-coor of the square
 * @param y-coor of the square
 */
int game_square_piece (game g, int x, int y){
    for (int i = 0; i < g->nb_pieces; i++){
        piece p = g->liste_piece[i];
        if (get_x(p) <= x && get_y(p) <= y){
            if (get_x(p)+get_width(p)-1 >= x && get_y(p)+get_height(p)-1 >= y){         // [x,y] compris entre coordonnée bottom/left et top/right de la piece
                return i;
            }
        }
    }
    return -1;
}