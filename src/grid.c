#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"
#include "grid.h"
#include "useful_functions.h"

struct grid_s {
        char matrice[6][6];
};
//faire un pointeur constant plus tard
grid new_grid(int *piece_list){
	grid grid = malloc(sizeof(struct grid_s));
        grid->g = game;
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			grid -> matrice[i][j]='.';
		}
	}
        set_pieces(grid, piece_list);
	return grid;
}

//affiche graphiquement la grille sur le terminal
void show_grid(grid grid){
	for(int abs=5;abs>=0;abs--){
		for(int ord=0; ord<6;ord++){
			char c = grid->matrice[ord][abs];
			printf("%c ", c);
		}
		printf("\n");
	}
        printf("\nNombre de mouvements : %d\n----------\n\n", game_nb_moves(grid->g));
        
}

//libère la mémoire allouée pour la grille
void delete_grid(grid grid){
    free(grid);
}

//ajouter graphiquement une piece sur la grille
void add_piece(grid grid, cpiece p, int piece_num){
    for (int i=get_x(p) ; i<get_width(p);++i){
        for (int j=get_y(p);j<get_height(p);++j){
            grid->matrice[i][j]=piece_num+48;
        }
    }
}
//mets les pieces du tableau sur la grille
void set_pieces(grid grid, int *piece_list){
    for (int i=0; i<sizeof(piece_list)/sizeof(piece_list[0]);i++){
        add_piece(grid, piece_list[i], i);
    }
}
//efface graphiquement une piece sur la grille
void delete_pieces(grid grid, cpiece p, int piece_num){
    for (int i=get_x(p) ; i<get_width(p);++i){
        for (int j=get_y(p);j<get_height(p);++j){
            grid->matrice[i][j]=piece_num+48;
        }
    }
}

//initialise graphiquement la case avec un int
void set_cell_int(grid grid, int x, int y, int val){
    grid->matrice[x][y]=val+48;
}

//reinitialise graphiquement la case
void set_cell_empty(grid grid, int x, int y){
    grid->matrice[x][y]='.';
}

//effectue le deplacement graphique de la piece
void move(grid grid, int piece_num, dir d, int distance){
    game g = grid->g;
    delete_piece_grid(grid, piece_num);
    if(play_move(g, piece_num, d, distance))
        add_piece(grid, piece_num);
    else
        add_piece(grid, piece_num);
    show_grid(grid);
}
