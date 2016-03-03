#include <stdio.h>
#include <stdlib.h>

#include "affichage.h"


struct grille_s {
        char tab[6][6];
};

//faireu n pointeur constant
//séparer la bibliothèque dans le make 

grille new_grille(){
	grille grid = malloc(sizeof(struct grille_s));
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			grid -> tab[i][j]='.';
		}
	}
	return grid;
}

void afficher_grille(grille grid){
	for(int i=5;i>=0;i--){
		for(int j=5; j>=0;j--){
			char c = grid->tab[i][j];
			printf("%c ", c);
		}
		printf("\n");
	}
}

void delete_grille(grille grid){
    free(grid);
}

/*
void deplacement(game g, dir d, int distance){
    switch(d){
        case UP:
            if(game_piece(g,7))    
}*/

void init_pieces(grille grid){
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
	grille grid = new_grille();
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
