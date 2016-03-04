#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"
#include "grid.h"

struct grid_s {
        char tab[6][6];
        game g;
        //marche pas
        //faire un pointeur sur g ???
};

//faireu n pointeur constant

grid new_grid(game game){
	grid grid = malloc(sizeof(struct grid_s));
        grid->g = game;
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
    set_cell_int(grid,x,y,piece_num);
    if(is_horizontal(p)){
        set_cell_int(grid,x+1,y,piece_num);
        if(get_width(p)==3){
            set_cell_int(grid,x+2,y,piece_num);
        }
    }
    else{
        set_cell_int(grid,x,y+1,piece_num);
        if(get_height(p)==3){
            set_cell_int(grid,x,y+2,piece_num);
        }
    }
}

void delete_piece_grid(grid grid, int piece_num){
    cpiece p = game_piece(get_game(grid), piece_num);
    int x = get_x(p);
    int y = get_y(p);
    set_cell_char(grid,x,y,'.');
    if(is_horizontal(p)){
        set_cell_char(grid,x+1,y,'.');
        if(get_width(p)==3){
            set_cell_char(grid,x+2,y,'.');
        }
    }
    else{
        set_cell_char(grid,x,y+1,'.');
        if(get_height(p)==3){
            set_cell_char(grid,x,y+2,'.');
        }
    }   
}

void set_pieces(grid grid){
    game g = get_game(grid);
    for (int i=0; i<game_nb_pieces(g);i++){
        add_piece(grid, i);
    }
}

void set_cell_int(grid grid, int x, int y, int val){
    grid->tab[x][y]=val+48;
}

void set_cell_char(grid grid, int x, int y, char c){
    grid->tab[x][y]=c;
}

void deplacement(grid grid, dir d, int distance, int piece_num){
    game g = grid->g;
    switch(d){
        case UP:
            printf("yolo");
            if(play_move(g, 7, UP, 1)){
                //delete_piece_grid(grid, piece_num);
                //add_piece(grid, piece_num);
                //show_grid(grid);
                //printf("Nombre de mouvements : %d", game_nb_moves(g));
            }
            break;
        case DOWN:
            break;
        case LEFT:
            break;
        case RIGHT:
            break;
    }
}
