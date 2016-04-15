#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solveur.h"
#include "piece.h"
#include "game.h"
#include "test_functions.h"



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
	t->children = NULL;
	t->ind_children = -1;
	return t;
}

game get_node(tree_game t){
	return t->node;
}

void add_child(tree_game t, game g){
	if (t->ind_children == -1){
		t->children = malloc(sizeof (struct game_s));
	}
	else{
		t->children = realloc(t->children, (t->ind_children+2)*sizeof(struct game_s));
	}
	t->children[++t->ind_children] = g;
}

bool has_child(tree_game t){
	return (t->ind_children != -1);
}


game sub_solve(tree_game t, dir* prev){
	game gc = NULL;
	cgame g = get_node(t);
	for (int p = 0; p<g->nb_pieces; ++p){
		if (can_move_x(g->piece_list[p])){
			if (prev[0] != LEFT){
				copy_game(g, gc);
				play_move(gc, p, LEFT, 1);
				add_child(t, gc);
				if (game_over_hr(gc)){		//game over pour ane rouge?
					return gc;
				}
				prev[0] = LEFT;
			}
			if (prev[1] != RIGHT){
				copy_game(g, gc);
				play_move(gc, p, RIGHT, 1);
				add_child(t, gc);
				if (game_over_hr(gc)){		//game over pour ane rouge?
					return gc;
				}
				prev[1] = RIGHT;

			}
		}
		if (can_move_y(g->piece_list[p])){
			if (prev[2] != UP){
				copy_game(g, gc);
				play_move(gc, p, UP, 1);
				add_child(t, gc);
				if (game_over_hr(gc)){		//game over pour ane rouge?
					return gc;
				}
				prev[2] = UP;
			}
			if (prev[3] != DOWN){
				copy_game(g, gc);
				play_move(gc, p, DOWN, 1);
				add_child(t, gc);
				if (game_over_hr(gc)){		//game over pour ane rouge?
					return gc;
				}
				prev[3] = DOWN;
			}
		}
	}
	if (has_child(t)){
		for (int ge = 0; ge < t->ind_children+2; ++ge){
			sub_solve(t, prev);
		}
	}
	return NULL;
}


int solve(game g){
	printf("1");
	tree_game t;
	printf("2");
	t = create_tree(g);
	printf("3");
	dir prev[4] = {RIGHT, LEFT, LEFT, LEFT};
	printf("4");
	game solved = NULL;
	printf("5");
	solved = sub_solve(t, prev);
	printf("6");
	if (solved == NULL){
		return -1;
	}
	return solved->nb_moves;
}
