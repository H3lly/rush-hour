#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solveur.h"
#include "piece.h"
#include "game.h"
#include "test_functions.h"

//Ne fonctionne pas


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

void set_dir_prev(game g, int ind, int dir){	//0:pas de prev_dir; 1:Left; 2:Right; 3:Up; 4;:Down
	g->dir_prev[ind] = dir;
}

game sub_solve(game* t, game g, int ind, int ind_tab){
	if (ind == 100000){
		return NULL;
	}
	
	
	
	printf("\nchildren n°%d \n", ind_tab);
	printf("ind n°%d \n", ind);
	/*int iL = 0;
	int iR = 0;
	int iU = 0;
	int iD = 0;
	game* tmp = malloc(sizeof (struct game_s));
	int ind_tmp = 0;*/
	int p;
	p = 0;
	for (int p = 0; p<game_nb_pieces(g); ++p){
		if (can_move_x(g->piece_list[p])){
			game gL = new_game(0, 0, 0, NULL);
			game gR = new_game(0, 0, 0, NULL);
			copy_game(g, gL);
			if (play_move(gL, p, LEFT, 1) && get_dir_prev(gL,p) != 2){
				printf(" %d L \n", p);
				t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
				t[ind_tab] = gL;
				ind_tab++;
				set_dir_prev(gL, p, 1);
				if (game_over_ar(gL)){
					return gL;
				}			
			}
			copy_game(g, gR);
			if (play_move(gR, p, RIGHT, 1) && get_dir_prev(gR, p) != 1){
				printf(" %d R ", p);
				t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
				t[ind_tab] = gR;
				ind_tab++;
				set_dir_prev(gR, p, 2);
				if (game_over_ar(gR)){
					return gR;
				}		
			}				
		}
		else if (can_move_y(g->piece_list[p])){
			game gU = new_game(0, 0, 0, NULL);
			game gD = new_game(0, 0, 0, NULL);
			copy_game(g, gU);
			if (play_move(gU, p, UP, 1) && get_dir_prev(gU, p) != 4){
				printf(" %d U ", p);
				t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
				t[ind_tab] = gU;
				ind_tab++;
				set_dir_prev(gU, p, 3);
				if (game_over_ar(gU)){
					return gU;
				}	
			}

			copy_game(g, gD);
			if (play_move(gD, p, DOWN, 1) && get_dir_prev(gD, p) != 3){
				printf(" %d D ", p);
				t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
				t[ind_tab] = gD;
				ind_tab++;
				set_dir_prev(gD, p, 4);
				if (game_over_ar(gD)){
					return gD;
				}	
			}	
		}						

		else set_dir_prev(g, p, 0);
	}

	
/*
	int add = 0;
	if (iL != 0){
		t[ind_tab+add] = tmp[add];
		add++;
	}
	if (iR != 0){
		t[ind_tab+add] = tmp[add];
		add++;
	}
	if (iU != 0){
		t[ind_tab+add] = tmp[add];
		add++;
	}
	if (iD != 0){
		t[ind_tab+add] = tmp[add];
		add++;
	}
	*/
	//ind_tab += add;
	//printf("\n");
	//printf(" (%d : %d) ", p, ind_tab);
	//printf("\nnb moves : %d", game_nb_moves(g));
	show_grid(g);
	int ind_next = ind+1;
	sub_solve(t, t[ind_next], ind_next, ind_tab);
    return NULL; //this line is here only to avoid errors due to the fact that returns are only in "if" loops
}

void usage(char *name) {
	fprintf(stderr, "Usage: %s <a|r> <filename>\n", name);
	exit(1);
}

int solve(game g){
/*	if(argc != 3){
		usage(argv[0]);
	}

	FILE * file;
	file = fopen(argv[2], "r");

	if (file == NULL){
		printf("Impossible d'ouvrir ce fichier.");
		exit(EXIT_FAILURE);
	}
	int grid_width, grid_height, nbPieces, x, y, width, height, can_move_x, can_move_y;
	bool move_x, move_y;
	fscanf(file,"%d %d %d ",&grid_width, &grid_height, &nbPieces);
	piece t_piece[nbPieces];
	for(int i = 0; i<nbPieces; ++i){
		fscanf(file, "%d %d %d %d %d %d", &x, &y, &width, &height, &can_move_x, &can_move_y);
		if (can_move_x==0){
			move_x = false;
		}
		else{
			move_x = true;
		}
		if (can_move_y==0){
			move_y = false;
		}
		else{
			move_y = true;
		}
		t_piece[i] = new_piece(x, y, width, height, move_x, move_y);
	}
	game g = new_game(grid_width, grid_height, nbPieces, t_piece);
	fclose(file);
	*/
	game* t = malloc (sizeof (struct game_s));
	game solved = new_game(0, 0, 0, NULL);
	g->dir_prev = malloc(sizeof (int)*game_nb_pieces(g));
	for (int i = 0; i<game_nb_pieces(g); ++i){
		set_dir_prev(g, i, 0);
	}
	solved = sub_solve(t, g, -1, 0);
	printf("fini");
	if (solved == NULL){
		printf("dans le if ?");
		return -1;
	}
	return game_nb_moves(solved);
}
