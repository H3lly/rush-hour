#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "piece.h"
#include "game.h"
#include "test_functions.h"

struct TreeGame{
	game node;
	game *children;
	int iChildren;
};

TreeGame createTree(g){
	TreeGame t = malloc(sizeof (struct TreeGame));
	t->node = g;
	t->iChildren = -1;
}

game getNode(){
	return t->base;
}

void addChild(t, g){
	if (t->iChildren == -1){
		t->children = malloc(sizeof (struct game));
	}
	else{
		t->children = realloc(t->children, (iChildren+2)*sizeof(struct game));
	}
	t->child[++iChild] = g;
}
/*
game solve(TreeGame t, game solved){
	game g = getNode();
	for (int p = 0; p<g->nb_pieces; ++p){
		if can_move_x()
	}
}
*/
bool hasChild(t){
	return (t->iChildren != -1);
}
/*
int resultSolve(g){
	t = createTree(g);
	game solved == NULL;
	solve(t, solved);
	if (solved == NULL){
		return -1;
	}
	return solved->nbMoves;
}
*/