#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "game.h"

struct game_s{
	int nb_pieces;
	int	nb_moves;
	//piece *liste_piece;
};

game new_game_hr (int nb_pieces, piece *pieces){
	game g = malloc(sizeof(struct game_s));
	g->nb_moves=0;
	g->nb_pieces=nb_pieces;
	//g->liste_piece
}

void delete_game (game g){
	free(g);
}

void copy_game (cgame src, game dst){
	dst->nb_pieces = src->nb_pieces;
	dst->nb_move = src->nb_move;
	//g->liste_piece
}

int game_nb_pieces(cgame g){
	return g->nb_pieces;
}

/*
cpiece game_piece(cgame g, int piece_num){

}
*/

/*
bool game_over_hr(cgame g){
	//return position voiture 0 == (4,3);
}
*/

/*
bool play_move(game g, int piece_num, dir d, int distance){

}
*/


int game_nb_moves(cgame g){
	return g->nb_moves;
}

/*
bout de code potentiellement utile :

bool can_move(piece p, dir d){
	switch(d){
		case RIGHT:
			if (movement_is_allowed(p,RIGHT)){
				piece tmp = malloc(sizeof(struct piece_s));	
				copy_piece(p, tmp);
				tmp -> abs += 1;
				for(int i=0;i<
					return !(intersect(tmp,v))
				}
			}
			return false;
	}
}
*/
