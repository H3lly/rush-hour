#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"
#include "grid.h"

struct grid_s {
        char tab[6][6];
};

//faireu n pointeur constant
//séparer la bibliothèque dans le make 

grid new_grille(){
	grid grid = malloc(sizeof(struct grid_s));
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			grid -> tab[i][j]='.';
		}
	}
	return grid;
}

void afficher_grille(grid grid){
	for(int i=5;i>=0;i--){
		for(int j=5; j>=0;j--){
			char c = grid->tab[i][j];
			printf("%c ", c);
		}
		printf("\n");
	}
}

void delete_grille(grid grid){
    free(grid);
}
//demander au prof
void set_piece(game g, grid grid, int piece_num){
    piece p = game_piece(g, piece_num);
    int max = get_height(p);
    int min = get_width(p);
    if(get_width(p)>get_height(p)){
        int max = get_width(p);
        int min = get_height(p);
    }
    for(int i=0;i<=max;i++){
        grid->tab[min][i]=piece_num;
    }
    
}
/*
void deplacement(game g, dir d, int distance){
    switch(d){
        case UP:
            if(game_piece(g,7))    
}*/
