#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"
#include "grid.h"

struct grid_s {
        char tab[6][6];
        game g;
};

//faireu n pointeur constant

grid new_grid(game g){
	grid grid = malloc(sizeof(struct grid_s));
        grid->g=g;
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			grid -> tab[i][j]='.';
		}
	}
	return grid;
}

void show_grid(grid grid){
	for(int abs=5;abs>=0;abs--){
		for(int ord=0; ord<6;ord++){
			char c = grid->tab[ord][abs];
			printf("%c ", c);
		}
		printf("\n");
	}
}

void delete_grid(grid grid){
    free(grid);
}

game get_game(grid grid){
    return grid->g;
}
//demander au prof
void add_piece(grid grid, int piece_num){
    cpiece p = game_piece(get_game(grid), piece_num);
    int x = get_x(p);
    int y = get_y(p);
    int car = piece_num+48;
    grid->tab[x][y]=car;
    if(is_horizontal(p)){
        grid->tab[x+1][y]=car;
        if(get_width(p)==3){
            grid->tab[x+2][y]==car;
        }
    }
    else{
        grid->tab[x][y+1]=car;
        if(get_height(p)==3){
            grid->tab[x][y+2]=car;
        }
    }
}

void set_pieces(grid grid){
    game g = get_game(grid);
    for (int i=0; i<game_nb_pieces(g);i++){
        add_piece(grid, i);
    }
}
/*
void deplacement(game g, dir d, int distance){
    switch(d){
        case UP:
            if(game_piece(g,7))    
}*/
