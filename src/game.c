#include <stdio.h>
#include <stdlib.h>

#include "game.h"

struct game_s{
	int nb_pieces;
	int nb_moves;
	piece *liste_piece;
};

typedef const struct game_s* cgame;

game new_game_hr (int nb_pieces, piece *pieces){
	game g = malloc(sizeof(struct game_s));
	g->nb_moves=0;
	g->nb_pieces=nb_pieces;
	g->liste_piece = pieces;
    return g;
}

void delete_game (game g){
	free(g);
}

void copy_game (cgame src, game dst){
	dst->nb_pieces = src->nb_pieces;
	dst->nb_moves = src->nb_moves;
	dst->liste_piece=src->liste_piece;
}

int game_nb_pieces(cgame g){
	return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num){
    return g->liste_piece[piece_num-1];
}

bool game_over_hr(cgame g){
    return (get_x(g->liste_piece[0])== 4) && (get_y(g->liste_piece[0])==3);
}

bool equals(cpiece p1, cpiece p2){
    return (get_x(p1)==get_x(p2))&&(get_y(p1)==get_y(p2))&&(get_width(p1)==get_width(p2))&&(get_height(p1)==get_height(p2));
}

bool play_move(game g, int piece_num, dir d, int distance){
    piece p = g->liste_piece[piece_num];
    switch(d){
        case UP:
            move_piece(p, UP, distance);
            for (int i=0;i< g->nb_pieces;++i){
                if (!(equals(p,(game_piece(g,i))))&&intersect(p, game_piece(g, i))){
                    move_piece(p, DOWN, distance);
                    return false;
                }
            }
            g->nb_moves+=distance;
            return true;
        case DOWN:
            move_piece(p, DOWN, distance);
            for (int i=0;i< g->nb_pieces;++i){
                if (!(equals(p,(game_piece(g,i))))&&intersect(p, game_piece(g, i))){
                    move_piece(p, UP, distance);
                    return false;
                }
            }
            g->nb_moves+=distance;
            return true;
        case LEFT:
            move_piece(p, LEFT, distance);
            for (int i=0;i< g->nb_pieces;++i){
                if (!(equals(p,(game_piece(g,i))))&&intersect(p, game_piece(g, i))){
                    move_piece(p, RIGHT, distance);
                    return false;
                }
            }
            g->nb_moves+=distance;
            return true;
        case RIGHT:
            move_piece(p, RIGHT, distance);
            for (int i=0;i< g->nb_pieces;++i){
                if (!(equals(p,(game_piece(g,i))))&&intersect(p, game_piece(g, i))){
                    move_piece(p, LEFT, distance);
                    return false;
                }
            }
            g->nb_moves+=distance;
            return true;      
    }
}


int game_nb_moves(cgame g){
	return g->nb_moves;
}