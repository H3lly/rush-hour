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
};



game sub_solve(game* t, game g, int ind, int ind_tab, dir* t0, dir* t1, dir* t2, dir* t3, dir* t4, dir* t5, dir* t6, dir* t7){
	if (ind == 10000){
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
	if (can_move_x(g->piece_list[p])){
		game gL = new_game(0, 0, 0, NULL);
		game gR = new_game(0, 0, 0, NULL);
		copy_game(g, gL);
		if (play_move(gL, p, LEFT, 1) && t0[0] != RIGHT){
			printf(" %d L \n", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gL;
			ind_tab++;
			t0[1] = LEFT;
			if (game_over_ar(gL)){
				return gL;
			}			
		}
		else{
			t0[1] = UP;
		}
		copy_game(g, gR);
		if (play_move(gR, p, RIGHT, 1) && t0[1] != LEFT){
			printf(" %d R ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gR;
			ind_tab++;
			t0[0] = RIGHT;
			if (game_over_ar(gR)){
				return gR;
			}		
		}		
		else{
			t0[0] = UP;
		}		
	}
	if (can_move_y(g->piece_list[p])){
		game gU = new_game(0, 0, 0, NULL);
		game gD = new_game(0, 0, 0, NULL);
		copy_game(g, gU);
		if (play_move(gU, p, UP, 1) && t0[2] != DOWN){
			printf(" %d U ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gU;
			ind_tab++;
			t0[3] = UP;
			if (game_over_ar(gU)){
				return gU;
			}	
		}
		else{
			t0[3] = LEFT;
		}	
		copy_game(g, gD);
		if (play_move(gD, p, DOWN, 1) && t0[3] != UP){
			printf(" %d D ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gD;
			ind_tab++;
			t0[2] = DOWN;
			if (game_over_ar(gD)){
				return gD;
			}	
		}	
		else{
			t0[2] = LEFT;
		}						
	}

	
	p = 1;
	if (can_move_x(g->piece_list[p])){
		game gL = new_game(0, 0, 0, NULL);
		game gR = new_game(0, 0, 0, NULL);
		copy_game(g, gL);
		if (play_move(gL, p, LEFT, 1) && t1[0] != RIGHT){
			printf(" %d L \n", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gL;
			ind_tab++;
			t1[1] = LEFT;
			if (game_over_ar(gL)){
				return gL;
			}			
		}
		else{
			t1[1] = UP;
		}
		copy_game(g, gR);
		if (play_move(gR, p, RIGHT, 1) && t1[1] != LEFT){
			printf(" %d R ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gR;
			ind_tab++;
			t1[1] = RIGHT;
			if (game_over_ar(gR)){
				return gR;
			}		
		}		
		else{
			t1[0] = UP;
		}			
	}
	if (can_move_y(g->piece_list[p])){
		game gU = new_game(0, 0, 0, NULL);
		game gD = new_game(0, 0, 0, NULL);
		copy_game(g, gU);
		if (play_move(gU, p, UP, 1) && t1[2] != DOWN){
			printf(" %d U ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gU;
			ind_tab++;
			t1[3] = UP;
			if (game_over_ar(gU)){
				return gU;
			}	
		}
		else{
			t1[3] = LEFT;
		}	
		copy_game(g, gD);
		if (play_move(gD, p, DOWN, 1) && t1[3] != UP){
			printf(" %d D ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gD;
			ind_tab++;
			t1[2] = DOWN;
			if (game_over_ar(gD)){
				return gD;
			}	
		}			
		else{
			t1[2] = LEFT;
		}				
	}

	
	p = 2;
	if (can_move_x(g->piece_list[p])){
		game gL = new_game(0, 0, 0, NULL);
		game gR = new_game(0, 0, 0, NULL);
		copy_game(g, gL);
		if (play_move(gL, p, LEFT, 1) && t2[0] != RIGHT){
			printf(" %d L \n", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gL;
			ind_tab++;
			t2[1] = LEFT;
			if (game_over_ar(gL)){
				return gL;
			}			
		}
		else{
			t2[1] = UP;
		}
		copy_game(g, gR);
		if (play_move(gR, p, RIGHT, 1) && t2[1] != LEFT){
			printf(" %d R ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gR;
			ind_tab++;
			t2[0] = RIGHT;
			if (game_over_ar(gR)){
				return gR;
			}		
		}	
		else{
			t2[0] = UP;
		}				
	}
	if (can_move_y(g->piece_list[p])){
		game gU = new_game(0, 0, 0, NULL);
		game gD = new_game(0, 0, 0, NULL);
		copy_game(g, gU);
		if (play_move(gU, p, UP, 1) && t2[2] != DOWN){
			printf(" %d U ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gU;
			ind_tab++;
			t2[3] = UP;
			if (game_over_ar(gU)){
				return gU;
			}	
		}
		else{
			t2[3] = LEFT;
		}	
		copy_game(g, gD);
		if (play_move(gD, p, DOWN, 1) && t2[3] != UP){
			printf(" %d D ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gD;
			ind_tab++;
			t2[2] = DOWN;
			if (game_over_ar(gD)){
				return gD;
			}	
		}	
		else{
			t2[2] = LEFT;
		}						
	}

	
	p = 3;
	if (can_move_x(g->piece_list[p])){
		game gL = new_game(0, 0, 0, NULL);
		game gR = new_game(0, 0, 0, NULL);
		copy_game(g, gL);
		if (play_move(gL, p, LEFT, 1) && t3[0] != RIGHT){
			printf(" %d L \n", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gL;
			ind_tab++;
			t3[1] = LEFT;
			if (game_over_ar(gL)){
				return gL;
			}			
		}
		else{
			t3[1] = UP;
		}
		copy_game(g, gR);
		if (play_move(gR, p, RIGHT, 1) && t3[1] != LEFT){
			printf(" %d R ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gR;
			ind_tab++;
			t3[0] = RIGHT;
			if (game_over_ar(gR)){
				return gR;
			}		
		}		
		else{
			t3[0] = UP;
		}			
	}
	if (can_move_y(g->piece_list[p])){
		game gU = new_game(0, 0, 0, NULL);
		game gD = new_game(0, 0, 0, NULL);
		copy_game(g, gU);
		if (play_move(gU, p, UP, 1) && t3[2] != DOWN){
			printf(" %d U ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gU;
			ind_tab++;
			t3[3] = UP;
			if (game_over_ar(gU)){
				return gU;
			}	
		}
		else{
			t3[3] = LEFT;
		}	
		copy_game(g, gD);
		if (play_move(gD, p, DOWN, 1) && t3[3] != UP){
			printf(" %d D ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gD;
			ind_tab++;
			t3[2] = DOWN;
			if (game_over_ar(gD)){
				return gD;
			}	
		}			
		else{
			t3[2] = LEFT;
		}				
	}

	
	p = 4;
	if (can_move_x(g->piece_list[p]) && t4[0] != RIGHT){
		game gL = new_game(0, 0, 0, NULL);
		game gR = new_game(0, 0, 0, NULL);
		copy_game(g, gL);
		if (play_move(gL, p, LEFT, 1)){
			printf(" %d L \n", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gL;
			ind_tab++;
			t4[1] = LEFT;
			if (game_over_ar(gL)){
				return gL;
			}			
		}
		else{
			t4[1] = UP;
		}
		copy_game(g, gR);
		if (play_move(gR, p, RIGHT, 1) && t4[1] != LEFT){
			printf(" %d R ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gR;
			ind_tab++;
			t4[0] = RIGHT;
			if (game_over_ar(gR)){
				return gR;
			}		
		}	
		else{
			t4[0] = UP;
		}				
	}
	if (can_move_y(g->piece_list[p])){
		game gU = new_game(0, 0, 0, NULL);
		game gD = new_game(0, 0, 0, NULL);
		copy_game(g, gU);
		if (play_move(gU, p, UP, 1) && t4[2] != DOWN){
			printf(" %d U ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gU;
			ind_tab++;
			t4[3] = UP;
			if (game_over_ar(gU)){
				return gU;
			}	
		}
		else{
			t4[3] = LEFT;
		}	
		copy_game(g, gD);
		if (play_move(gD, p, DOWN, 1) && t4[3] != UP){
			printf(" %d D ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gD;
			ind_tab++;
			t4[2] = UP;
			if (game_over_ar(gD)){
				return gD;
			}	
		}			
		else{
			t4[2] = LEFT;
		}				
	}

	
	p = 5;
	if (can_move_x(g->piece_list[p])){
		game gL = new_game(0, 0, 0, NULL);
		game gR = new_game(0, 0, 0, NULL);
		copy_game(g, gL);
		if (play_move(gL, p, LEFT, 1) && t5[0] != RIGHT){
			printf(" %d L \n", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gL;
			ind_tab++;
			t5[1] = LEFT;
			if (game_over_ar(gL)){
				return gL;
			}			
		}
		else{
			t5[1] = UP;
		}
		copy_game(g, gR);
		if (play_move(gR, p, RIGHT, 1) && t5[1] != LEFT){
			printf(" %d R ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gR;
			ind_tab++;
			t5[0] = RIGHT;
			if (game_over_ar(gR)){
				return gR;
			}		
		}		
		else{
			t5[0] = UP;
		}			
	}
	if (can_move_y(g->piece_list[p])){
		game gU = new_game(0, 0, 0, NULL);
		game gD = new_game(0, 0, 0, NULL);
		copy_game(g, gU);
		if (play_move(gU, p, UP, 1) && t5[2] != DOWN){
			printf(" %d U ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gU;
			ind_tab++;
			t5[3] = UP;
			if (game_over_ar(gU)){
				return gU;
			}	
		}
		else{
			t5[3] = LEFT;
		}	
		copy_game(g, gD);
		if (play_move(gD, p, DOWN, 1) && t5[3] != UP){
			printf(" %d D ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gD;
			ind_tab++;
			t5[2] = DOWN;
			if (game_over_ar(gD)){
				return gD;
			}	
		}		
		else{
			t5[2] = LEFT;
		}					
	}

	
	p = 6;
	if (can_move_x(g->piece_list[p])){
		game gL = new_game(0, 0, 0, NULL);
		game gR = new_game(0, 0, 0, NULL);
		copy_game(g, gL);
		if (play_move(gL, p, LEFT, 1) && t6[0] != RIGHT){
			printf(" %d L \n", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gL;
			ind_tab++;
			t6[1] = LEFT;
			if (game_over_ar(gL)){
				return gL;
			}			
		}
		else{
			t6[1] = UP;
		}
		copy_game(g, gR);
		if (play_move(gR, p, RIGHT, 1) && t6[1] != LEFT){
			printf(" %d R ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gR;
			ind_tab++;
			t6[0] = RIGHT;
			if (game_over_ar(gR)){
				return gR;
			}		
		}		
		else{
			t6[0] = UP;
		}			
	}
	if (can_move_y(g->piece_list[p])){
		game gU = new_game(0, 0, 0, NULL);
		game gD = new_game(0, 0, 0, NULL);
		copy_game(g, gU);
		if (play_move(gU, p, UP, 1) && t6[2] != DOWN){
			printf(" %d U ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gU;
			ind_tab++;
			t6[3] = UP;
			if (game_over_ar(gU)){
				return gU;
			}	
		}
		else{
			t6[3] = LEFT;
		}	
		copy_game(g, gD);
		if (play_move(gD, p, DOWN, 1) && t6[3] != UP){
			printf(" %d D ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gD;
			ind_tab++;
			t6[2] = DOWN;
			if (game_over_ar(gD)){
				return gD;
			}	
		}			
		else{
			t6[2] = LEFT;
		}				
	}

	
	p = 7;
	if (can_move_x(g->piece_list[p])){
		game gL = new_game(0, 0, 0, NULL);
		game gR = new_game(0, 0, 0, NULL);
		copy_game(g, gL);
		if (play_move(gL, p, LEFT, 1) && t7[0] != RIGHT){
			printf(" %d L \n", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gL;
			ind_tab++;
			t7[1] = LEFT;
			if (game_over_ar(gL)){
				return gL;
			}			
		}
		else{
			t7[1] = UP;
		}
		copy_game(g, gR);
		if (play_move(gR, p, RIGHT, 1) && t7[1] != LEFT){
			printf(" %d R ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gR;
			ind_tab++;
			t7[0] = RIGHT;
			if (game_over_ar(gR)){
				return gR;
			}		
		}	
		else{
			t7[0] = UP;
		}				
	}
	if (can_move_y(g->piece_list[p])){
		game gU = new_game(0, 0, 0, NULL);
		game gD = new_game(0, 0, 0, NULL);
		copy_game(g, gU);
		if (play_move(gU, p, UP, 1) && t7[2] != DOWN){
			printf(" %d U ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gU;
			ind_tab++;
			t7[3] = UP;
			if (game_over_ar(gU)){
				return gU;
			}	
		}
		else{
			t7[3] = LEFT;
		}	
		copy_game(g, gD);
		if (play_move(gD, p, DOWN, 1) && t7[3] != UP){
			printf(" %d D ", p);
			t = realloc(t, (ind_tab+1)*sizeof(struct game_s));
			t[ind_tab] = gD;
			ind_tab++;
			t7[2] = DOWN;
			if (game_over_ar(gD)){
				return gD;
			}	
		}			
		else{
			t7[2] = LEFT;
		}				
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
	printf("\n");
	printf(" (%d : %d) ", p, ind_tab);
	printf("\nnb moves : %d", game_nb_moves(g));
	show_grid(g);
	int ind_next = ind+1;
	sub_solve(t, t[ind_next], ind_next, ind_tab, t0, t1, t2, t3, t4, t5, t6, t7);
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
	dir t0[4] = {UP, UP, LEFT, LEFT};
	dir t1[4] = {UP, UP, LEFT, LEFT};
	dir t2[4] = {UP, UP, LEFT, LEFT};
	dir t3[4] = {UP, UP, LEFT, LEFT};
	dir t4[4] = {UP, UP, LEFT, LEFT};
	dir t5[4] = {UP, UP, LEFT, LEFT};
	dir t6[4] = {UP, UP, LEFT, LEFT};
	dir t7[4] = {UP, UP, LEFT, LEFT};
	game solved = new_game(0, 0, 0, NULL);
	solved = sub_solve(t, g, -1, 0, t0, t1, t2, t3, t4, t5, t6, t7);
	printf("fini");
	if (solved == NULL){
		printf("dans le if ?");
		return -1;
	}
	return game_nb_moves(solved);
}
