#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solveur.h"
#include "piece.h"
#include "game.h"
#include "test_functions.h"

struct game_s{
	int width;
	int height;
	int nb_pieces;
	int nb_moves;
	piece *piece_list;
	int *dir_prev;
};

int get_dir_prev(game g, int ind){
	return g->dir_prev[ind];
}

void set_dir_prev(game g, int ind, int dir){//0:no prev_dir; 1:Left; 2:Right; 3:Up; 4;:Down
	g->dir_prev[ind] = dir;
}

game sub_solve(game* t, game g, unsigned long ind, unsigned long ind_tab){//if the game can be solved, it will return the game solved
	if (ind == 100000){
		return NULL;
	}
	printf("ind n°%lu \n", ind);
	for (int p = 0; p<game_nb_pieces(g); ++p){
		int reinit = 0;
		if (can_move_x(g->piece_list[p])){
			game gL = new_game(0, 0, 0, NULL);
			game gR = new_game(0, 0, 0, NULL);
			copy_game(g, gL);
			if (play_move(gL, p, LEFT, 1) && get_dir_prev(gL,p) != 2){
				t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
				t[ind_tab] = gL;
				ind_tab++;
				reinit++;
				set_dir_prev(gL, p, 1);
				if (can_move_y(g->piece_list[0])){//piece 0 can only move UP or DOWN in l'âne rouge
					if (game_over_ar(gL)){
						return gL;
					}			
				}
				else if (game_over_hr(gL)){
					return gL;
				}
			}
			copy_game(g, gR);
			if (play_move(gR, p, RIGHT, 1) && get_dir_prev(gR, p) != 1){
				t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
				t[ind_tab] = gR;
				ind_tab++;
				reinit++;
				set_dir_prev(gR, p, 2);
				if (can_move_y(g->piece_list[0])){
					if (game_over_ar(gR)){
						return gR;
					}			
				}
				else if (game_over_hr(gR)){
					return gR;
				}
			}				
		}
		if (can_move_y(g->piece_list[p])){
			game gU = new_game(0, 0, 0, NULL);
			game gD = new_game(0, 0, 0, NULL);
			copy_game(g, gU);
			if (play_move(gU, p, UP, 1) && get_dir_prev(gU, p) != 4){
				t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
				t[ind_tab] = gU;
				ind_tab++;
				reinit++;
				set_dir_prev(gU, p, 3);
				if (can_move_y(g->piece_list[0])){
					if (game_over_ar(gU)){
						return gU;
					}			
				}
				else if (game_over_hr(gU)){
					return gU;
				}
			}

			copy_game(g, gD);
			if (play_move(gD, p, DOWN, 1) && get_dir_prev(gD, p) != 3){
				t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
				t[ind_tab] = gD;
				ind_tab++;
				reinit++;
				set_dir_prev(gD, p, 4);
				if (can_move_y(g->piece_list[0])){
					if (game_over_ar(gD)){
						return gD;
					}			
				}
				else if (game_over_hr(gD)){
					return gD;
				}
			}	
		}						

		if(reinit == 0){//if the piece can't move, initialization of prev_dir
			set_dir_prev(g, p, 0);
		}
	}
	unsigned long ind_next = ind+1;
	sub_solve(t, t[ind_next], ind_next, ind_tab);
    return NULL; //this line is here only to avoid errors due to the fact that returns are only in "if" loops
}

void usage(char *name) {
	fprintf(stderr, "Usage: %s <a|r> <filename>\n", name);
	exit(1);
}

int solve(game g){
	game* t = malloc (sizeof (struct game_s));
	game solved = new_game(0, 0, 0, NULL);
	g->dir_prev = malloc(sizeof (int)*game_nb_pieces(g));
	for (int i = 0; i<game_nb_pieces(g); ++i){//initialization of all prev_dir for each piece
		set_dir_prev(g, i, 0);
	}
	solved = sub_solve(t, g, -1, 0);
	if (solved == NULL){
		return -1;
	}
	return game_nb_moves(solved);
}
