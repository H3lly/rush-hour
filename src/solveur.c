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
	tree_game *children;
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
	t->children = malloc(4*game_nb_pieces(g)*sizeof (struct game_s));
	t->ind_children = -1;
	return t;
}

game get_node(tree_game t){
	return t->node;
}

tree_game get_child(tree_game t, int i){
	return t->children[i];
}

void add_child(tree_game t, game g){
	tree_game addTmp = create_tree(g);
	t->ind_children += 1;
	t->children[t->ind_children] = addTmp;
}

bool has_child(tree_game t){
	return (t->ind_children > -1);
}


int get_nb_children(tree_game t){
	return t->ind_children+1;
}


game sub_solve(tree_game t, int ind){
	game g = new_game(0,0,0,NULL);
	copy_game(get_node(t), g);
	if (ind >= 10){
		printf("Boucle infini. ind = %d", ind);
		return NULL;
	}
	game gL = new_game(0, 0, 0, NULL);
	game gR = new_game(0, 0, 0, NULL);
	game gU = new_game(0, 0, 0, NULL);
	game gD = new_game(0, 0, 0, NULL);
	printf("(%d) ", ind);
	for (int p = 0; p < game_nb_pieces(g); ++p){
			copy_game(g, gL);
			copy_game(g, gR);
			copy_game(g, gU);
			copy_game(g, gD);


			if (play_move(gL, p, LEFT, 1)){
				printf(" %d L ", p);
				add_child(t, gL);
				if (game_over_hr(gL)){
					show_grid(gL);
					return gL;
				}			
			}
			if (play_move(gR, p, RIGHT, 1)){
				printf(" %d R ", p);
				add_child(t, gR);
				if (game_over_hr(gR)){
					show_grid(gR);
					return gR;
				}		
			}				
			if (play_move(gU, p, UP, 1)){
				printf(" %d U ", p);
				add_child(t, gU);
				if (game_over_hr(gU)){
					show_grid(gU);
					return gU;
				}	
			}
			if (play_move(gD, p, DOWN, 1)){
				printf(" %d D ", p);
				add_child(t, gD);
				if (game_over_hr(gD)){
					show_grid(gD);
					return gD;
				}	
			}				


		
		printf(" | ");

	}
	if(ind==1) 	return NULL;
	printf("\n\n\n");
	if(has_child(t)){
		printf("t %d has %d child(ren).", ind, get_nb_children(t));
		ind++;
		for (int i = 0; i < get_nb_children(t);++i){
			printf("\nChild n°%d : ", i);
			sub_solve(t->children[i], ind);
		}
    }
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
	solved = sub_solve(t, -1);
	if (solved == NULL){
		return -1;
	}
	return game_nb_moves(solved);
}
