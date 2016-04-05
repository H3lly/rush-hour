#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "piece.h"
#include "game.h"
#include "test_functions.h"

/*
int solve (cgame g, int nb_pieces, int piece_num, int height, int width){
	if (piece_num == nb_pieces){
		return g->nb_moves;
	}
	piece p = g->piece_list[piece_num];
	if (can_move_x(p)){
		for (int i = 5; i<=0; --i){
			piece p = g->piece_list[piece_num];
			play_move(g, piece_num, LEFT, i);
			solve (g, nb_pieces, piece_num, height, width)

		}
	}
	if (can_move_y(p)){

	}
}


int result_solve (cgame g, int nb_pieces){
	int result;//contains the optimal number of movements
	for (int i = 0; piece_num<nb_pieces; ++piece_num){
		result = solve (g, bn_pieces, i, game_height(g), game_width(g))

	}
	return result
}
*/