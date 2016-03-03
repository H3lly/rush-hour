#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"

struct grille_s {
        char tab[6][6];
};

//faireu n pointeur constant
//séparer la bibliothèque dans le make 

grid new_grille(){
	grid grid = malloc(sizeof(struct grille_s));
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

/*
void deplacement(game g, dir d, int distance){
    switch(d){
        case UP:
            if(game_piece(g,7))    
}*/
