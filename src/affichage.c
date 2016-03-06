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
    
    int piece_num;
    dir d;
    int int_d;
    int distance;
    int test=true;
    while(!(game_over_hr(game))){
        printf("Veuillez saisir le numéro de la pièce à déplacer :\n");
        piece_num = scanf("%d", &piece_num);
        printf("Quelle direction ? (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
        int_d = scanf("%d", &int_d);
        while (!test) {
            test=true;
            if(int_d==1) d=UP;
            else if (int_d==2) d=DOWN;
            else if (int_d==3) d=LEFT;
            else if (int_d==4) d=RIGHT;
            else{
                printf("Entrée invalide, veuilez saisir un entier entre 1 et 4. (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
                test=false;
            }
        }
        printf("De combien de cases ?\n");
        distance = scanf("%d", &distance);
        deplacement(grid, piece_num, d, distance);
    }
    if (game_over_hr(game)) printf("Game is over. Score : %d", game_nb_moves(game));
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
