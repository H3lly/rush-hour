#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#include "affichage.h"

typedef struct grille_s* grille;
grille new_grille();
void afficher_grille(grille g);



struct grille_s{
	char tab[6][6];
};


grille new_grille(){
	grille g = malloc(sizeof(struct grille_s));
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			g -> tab[i][j]='X';
		}
	}
	return g;
}

void afficher_grille(grille g){
	for(int i=5;i>=0;i--){
		for(int j=5; j>=0;j--){
			char c = g->tab[i][j];
			printf("%c", c);
		}
		printf("\n");
	}
}

int main (void){
	grille grid = new_grille();
	afficher_grille(grid);
	return EXIT_SUCCESS;
}

/*
void init_pieces(){
	
}


void show_case(abs, ord){
	

piece show_piece_petit_horizontal(p){
	show_case(p->abs, p->ord);
	show_case((p->abs)+1,p->ord);
}

piece show_piece_big_horizontal(p){
	show_case(p->abs, p->ord);
	show_case((p->abs)+1,p->ord);
	show_case((p->abs)+2,p->ord);
}

piece show_piece_small_vertical(p){
	show_case(p->abs, p->ord);
	show_case(p->abs,(p->ord)+1);
}

piece show_piece_big_vertical(p){
	show_case(p->abs, p->ord);
	show_case(p->abs,(p->ord)+1);
	show_case(p->abs,(p->ord)+2);
}

piece show_piece(piece p){
	if (p->estHorizontal){
		if(p->small)
			show_piece_petit_horizontal(p);
		show_piece_big_horizontal(p);
	}
	if(p->small)
		show_piece_small_vertical(p);
	show_piece_big_vertical(p);
}*/
