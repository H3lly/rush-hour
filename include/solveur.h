#ifndef SOLVEUR_H
#define	SOLVEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "piece.h"
#include "game.h"
#include "test_functions.h"

typedef struct tree_game_s* tree_game;
tree_game create_tree(game g);
game get_node(tree_game t);
tree_game get_child(tree_game t, int i);
void add_child(tree_game t, game g);
bool has_child(tree_game t);
void set_dir_prev(game g, int ind, int dir);
game sub_solve(game* t, game g, unsigned long ind, unsigned long ind_tab);
int get_nb_children(tree_game t);
int solve(game g);

#endif	
/* SOLVEUR_H */

