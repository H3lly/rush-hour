#include <stdio.h>
#include <stdlib.h>

#include "affichage.h"


struct grille_s {
        char tab[6][6];
};


grille new_grille(){
	grille g = malloc(sizeof(struct grille_s));
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			g -> tab[i][j]='.';
		}
	}
	return g;
}

void afficher_grille(grille g){
	for(int i=5;i>=0;i--){
		for(int j=5; j>=0;j--){
			char c = g->tab[i][j];
			printf("%c ", c);
		}
		printf("\n");
	}
}

void delete_grille(grille g){
    free(g);
}

void init_pieces(grille g){
    g->tab[3][5]='0';
    g->tab[3][4]='0';
    g->tab[2][5]='1';
    g->tab[2][4]='1';
    g->tab[0][5]='2';
    g->tab[1][5]='2';
    g->tab[1][4]='3';
    g->tab[1][3]='3';
    g->tab[2][3]='4';
    g->tab[3][3]='4';
    g->tab[4][3]='4';
    g->tab[1][2]='5';
    g->tab[2][2]='5';
    g->tab[0][1]='6';
    g->tab[1][1]='6';
    g->tab[2][1]='6';
    g->tab[2][0]='7';
    g->tab[3][0]='7';
}

/*
void deplacement(grille g, dir d){
    switch(d){
        case UP:
            if(game_piece(g,7))
    }
}
*/
int main (void){
	grille grid = new_grille();
	init_pieces(grid);
	afficher_grille(grid);
	return EXIT_SUCCESS;
}


/* 
 * void show_case(grille g, int abs, int ord, int number){
    g->tab[abs][ord] = number;
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
*/