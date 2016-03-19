#include <stdio.h>
#include <stdlib.h>

#include "grid.h"
#include "useful_functions.h"

struct grid_s {
        char matrix[6][6];
        game g;
};

grid new_grid(game game){
	grid grid = malloc(sizeof(struct grid_s));
        grid->g = game;
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			grid -> matrix[i][j]='.';
		}
	}
        set_pieces(grid);
	return grid;
}

//show the grid on the terminal
void show_grid(grid grid){
	for(int abs=5;abs>=0;abs--){
		for(int ord=0; ord<6;ord++){
			char c = grid->matrix[ord][abs];
			printf("%c ", c);
		}
		printf("\n");
	}
        printf("\nNombre de mouvements : %d\n----------\n\n", game_nb_moves(grid->g));
        
}

//free the allocated memory for the grid
void delete_grid(grid grid){
    delete_game(get_game(grid));
    free(grid);
}

//returns the game
game get_game(grid grid){
    return grid->g;
}

//add a piece on the grid
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

//delete a piece that is on the grid
void delete_piece_grid(grid grid, int piece_num){
    cpiece p = game_piece(get_game(grid), piece_num);
    int x = get_x(p);
    int y = get_y(p);
    set_cell_empty(grid,x,y);
    if(is_horizontal(p)){
        set_cell_empty(grid,x+1,y);
        if(get_width(p)==3){
            set_cell_empty(grid,x+2,y);
        }
    }
    else{
        set_cell_empty(grid,x,y+1);
        if(get_height(p)==3){
            set_cell_empty(grid,x,y+2);
        }
    }
}

//add all the grid's game's piece on the grid grid
void set_pieces(grid grid){
    for (int i=0; i<game_nb_pieces(grid->g);i++){
        add_piece(grid, i);
    }
}

//set the ascii value of int val in the matrix at x,y
void set_cell_int(grid grid, int x, int y, int val){
    grid->matrix[x][y]=val+48;
}

//set a dot in the matrix at x,y
void set_cell_empty(grid grid, int x, int y){
    grid->matrix[x][y]='.';
}

//move the piece in the matrix
void move(grid grid, int piece_num, dir d, int distance){
    game g = grid->g;
    delete_piece_grid(grid, piece_num);
    if(play_move(g, piece_num, d, distance))
        add_piece(grid, piece_num);
    else
        add_piece(grid, piece_num);
    show_grid(grid);
}
