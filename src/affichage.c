#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"
#include "grid.h"

int main (void){
    piece liste [8];
    liste[0]=new_piece_rh(0, 3, true, true);
    liste[1]=new_piece_rh(0, 2, true, true);
    liste[2]=new_piece_rh(0, 0, true, false);
    liste[3]=new_piece_rh(1, 1, true, true);
    liste[4]=new_piece_rh(2, 2, false, false);
    liste[5]=new_piece_rh(3, 1, true, false);
    liste[6]=new_piece_rh(4, 0, false, false);
    liste[7]=new_piece_rh(5, 2, true, false);
    game game = new_game_hr(8, liste);    
    grid grid = new_grid(game);    
    set_pieces(grid);
    show_grid(grid);    
//    while(!(game_over_hr(game))){
//      //boucle de jeu    
//    }
    deplacement(grid, 7, UP, 2);
    deplacement(grid, 6, UP, 3);
    deplacement(grid, 5, UP, 3);
    deplacement(grid, 3, RIGHT, 3);
    deplacement(grid, 4, UP, 1);
    deplacement(grid, 1, RIGHT, 4);
    deplacement(grid, 4, DOWN, 3);
    deplacement(grid, 0, RIGHT, 1);
    deplacement(grid, 2, UP, 4);
    deplacement(grid, 0, LEFT, 1);
    deplacement(grid, 4, UP, 3);
    deplacement(grid, 1, LEFT, 4);
    deplacement(grid, 3, LEFT, 4);
    deplacement(grid, 4, DOWN, 3);
    deplacement(grid, 6, DOWN, 3);
    deplacement(grid, 0, RIGHT, 4);
    //deplacement(grid, DOWN, 3, 4);
    deplacement(grid, RIGHT, 4, 0);
    if(game_over_hr(game)) printf("Game is over. Score : %d", game_nb_moves(game));
    return EXIT_SUCCESS;
}



/* 
void show_case(grille g, int abs, int ord, int number){
    grid->tab[abs][ord] = number;
}

piece show_piece_petit_horizontal(grille g, piece p, int number){
	show_case(g, p->abs, p->ord, number);
	show_case(g, (p->abs)+1,p->ord, number);
}

piece show_piece_big_horizontal(grille g, piece p, int number){
	show_case(g, p->abs, p->ord, number);
	show_case(g, (p->abs)+1,p->ord, number);
	show_case(g, (p->abs)+2,p->ord, number);
}

piece show_piece_small_vertical(grille g, piece p, int number){
	show_case(g, p->abs, p->ord, number);
	show_case(g, p->abs,(p->ord)+1, number);
}

piece show_piece_big_vertical(grille g, piece p, int number){
	show_case(g, p->abs, p->ord, number);
	show_case(g, p->abs,(p->ord)+1, number);
	show_case(g, p->abs,(p->ord)+2, number);
}

piece show_piece(grille g, piece p, int number){
	if (p->estHorizontal){
		if (p->small){
			show_piece_petit_horizontal(g, p, number);
                }
		show_piece_big_horizontal(g, p, number);
	}
	if(p->small){
		show_piece_small_vertical(g, p, number);
        }
	show_piece_big_vertical(g, p, number);

 }
 */
