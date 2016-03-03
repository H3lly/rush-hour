#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"
#include "grid.h"



void init_pieces(grid grid){
    grid->tab[3][5]='0';
    grid->tab[3][4]='0';
    grid->tab[2][5]='1';
    grid->tab[2][4]='1';
    grid->tab[0][5]='2';
    grid->tab[1][5]='2';
    grid->tab[1][4]='3';
    grid->tab[1][3]='3';
    grid->tab[2][3]='4';
    grid->tab[3][3]='4';
    grid->tab[4][3]='4';
    grid->tab[1][2]='5';
    grid->tab[2][2]='5';
    grid->tab[0][1]='6';
    grid->tab[1][1]='6';
    grid->tab[2][1]='6';
    grid->tab[2][0]='7';
    grid->tab[3][0]='7';
}


int main (void){
	grid grid = new_grille();
	init_pieces(grid);
	afficher_grille(grid);
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
