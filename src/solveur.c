#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solveur.h"
#include "piece.h"
#include "game.h"
#include "test_functions.h"

//Ne fonctionne pas

struct tree_game_s{
	game node;
	game *children;
	int ind_children;
};


struct game_s{
	int width;
	int height;
	int nb_pieces;
	int nb_moves;
	piece *piece_list;
};

tree_game create_tree(game g){
	tree_game t = malloc(sizeof (struct tree_game_s));
	t->node = g;
	t->children = malloc(100*sizeof (struct game_s));
	t->ind_children = -1;
	return t;
}

game get_node(tree_game t){
	return t->node;
}
game get_children(tree_game t, int i){
	return t->children[i];
}

void add_child(tree_game t, game g){
	t->ind_children += 1;
	t->children[t->ind_children] = g;
}

bool has_child(tree_game t){
	return (t->ind_children != -1);
}

game sub_solve(tree_game t, game g, int ind){
	if (ind == 100){
		return NULL;
	}
	game gL = new_game(0, 0, 0, NULL);
	game gR = new_game(0, 0, 0, NULL);
	game gU = new_game(0, 0, 0, NULL);
	game gD = new_game(0, 0, 0, NULL);
	printf("\nchildren n°%d \n", t->ind_children);
	printf("ind n°%d \n", ind);
	for (int p = 0; p<g->nb_pieces; ++p){
		if (can_move_x(g->piece_list[p])){
			copy_game(g, gL);
			if (play_move(gL, p, LEFT, 1)){
				play_move(gL, p, LEFT, 1);
				printf(" %d L ", p);
				add_child(t, gL);
				if (game_over_hr(gL)){
					return gL;
				}			
			}
			copy_game(g, gR);
			if (play_move(gR, p, RIGHT, 1)){
				play_move(gR, p, RIGHT, 1);
				printf(" %d R ", p);
				add_child(t, gR);
				if (game_over_hr(gR)){
					return gR;
				}		
			}				
		}
		if (can_move_y(g->piece_list[p])){
			copy_game(g, gU);
			if (play_move(gU, p, UP, 1)){
				play_move(gU, p, UP, 1);
				printf(" %d U ", p);
				add_child(t, gU);
				if (game_over_hr(gU)){
					return gU;
				}	
			}
			copy_game(g, gD);
			if (play_move(gD, p, DOWN, 1)){
				play_move(gD, p, DOWN, 1);
				printf(" %d D ", p);
				add_child(t, gD);
				if (game_over_hr(gD)){
					return gD;
				}	
			}						
		}
		printf(" | ");
	}
	for (int i = 0; i <= t->ind_children;++i)
		sub_solve(t, t->children[i], t->ind_children);
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
	tree_game t;
	t = create_tree(g);
	game solved = NULL;
	solved = sub_solve(t, g, 0);
	if (solved == NULL){
		return -1;
	}
	return game_nb_moves(solved);
}
