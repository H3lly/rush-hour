#include <stdio.h>
#include <stdlib.h>

#include "game.h"   //inutile mais au cas ou
#include "piece.h"  //inutile mais au cas ou
#include "useful_functions.h"

//--------------------------------
//---------### GRID ###-----------
//--------------------------------

//affiche graphiquement la grille sur le terminal
void show_grid(){
	for(int ord=HEIGHT;ord>=0;ord--){
		for(int abs=0; abs<WIDTH;abs++){
                    if(game_square_piece(g, abs, ord)==-1)
                        printf(". ");
                    else
                        printf("%d ", game_square_piece(g, abs, ord));
		}
		printf("\n");
	}
        printf("\nNombre de mouvements : %d\n----------\n\n", game_nb_moves(grid->g));
}
//
////mets les pieces du tableau sur la grille
//void set_pieces(char** grid, cpiece *piece_list){
//    for (int i=0; i<sizeof (piece_list) / sizeof (piece_list[0]); i++){
//        add_piece(grid, piece_list[i], i);
//    }
//}
//
////ajouter graphiquement une piece sur la grille
//void add_piece(char** grid, piece p, int piece_num){
//    for (int i=get_x(p); i < get_width(p); ++i){
//        for (int j=get_y(p); j < get_height(p); ++j){
//            grid[i][j]=piece_num + 48;
//        }
//    }
//}
//
////efface graphiquement une piece sur la grille
//void delete_pieces(char** grid, piece p, int piece_num){
//    for (int i=get_x(p); i < get_width(p); ++i){
//        for (int j=get_y(p); j < get_height(p); ++j){
//            grid[i][j]=piece_num + 48;
//        }
//    }
//}
//
////initialise graphiquement la case avec un int
//void set_cell_int(char** grid, int x, int y, int val){
//    grid[x][y]=val + 48;
//}
//
////reinitialise graphiquement la case
//void set_cell_empty(char** grid, int x, int y){
//    grid[x][y]='.';
//}
//
////effectue le deplacement graphique de la piece
//void move(cgame g, char** grid, int piece_num, dir d, int distance){
//    delete_piece_grid(grid, piece_num);
//    if (play_move(g, piece_num, d, distance))
//        add_piece(grid, piece_num);
//    else
//        add_piece(grid, piece_num);
//    show_grid(grid);
//}
//



int main(void) {
    /*
    1 0 0 2
    1 0 0 2
    3 5 5 4
    3 6 7 4
    8 . . 9
    */
    piece liste [9];
    liste[0] = new_piece(1, 3, 2, 2, false, false);
    liste[1] = new_piece(0, 3, 1, 2, false, false);
    liste[2] = new_piece(3, 3, 1, 2, false, false);
    liste[3] = new_piece(0, 1, 1, 2, false, false);
    liste[4] = new_piece(3, 1, 1, 2, false, false);
    liste[5] = new_piece(1, 2, 2, 1, false, false);
    liste[6] = new_piece(1, 1, 1, 1, false, true);
    liste[7] = new_piece(2, 1, 1, 1, false, true);
    liste[8] = new_piece(0, 0, 1, 1, true, false);
    liste[9] = new_piece(3, 0, 1, 1, true, false);
    game game = new_game_hr(9, liste);
    int piece_num;
    dir d;
    int num;
    int distance;
    int test;
    while (!(game_over_hr(game))) {
        piece_num=-1;
        d=-1;
        distance=-1;
        test = false;
        
        printf("Veuillez saisir le numéro de la pièce à déplacer :\n");
        //commenter plus tard ces fonctions
        while(!test){
            if (scanf("%d", &piece_num) == 1) {
                if(piece_num>=0&&piece_num<game_nb_pieces(game))
                  test=true;
                else
                    printf("Entrée invalide: veuillez saisir un entier 0 et %d.\n", game_nb_pieces(game)-1);
            }
            else{
                printf("Entrée invalide: veuillez saisir un entier 0 et %d.\n", game_nb_pieces(game)-1);
                while(fgetc(stdin)!='\n');
            }
        }
        test=false;
        
        printf("Quelle direction ? (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
        while (!test) {
            if (scanf("%d", &num) == 1) {
                if (num == 1) {
                    d = UP;
                    test = true;
                } else if (num == 2) {
                    d = DOWN;
                    test = true;
                } else if (num == 3) {
                    d = LEFT;
                    test = true;
                } else if (num == 4) {
                    d = RIGHT;
                    test = true;
                } else {
                    printf("Entrée invalide: veuillez saisir un entier entre 1 et 4. (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
                }
            }
            else{
                printf("Entrée invalide: veuillez saisir un entier entre 1 et 4. (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
                while(fgetc(stdin)!='\n');
            }
        }
        test=false;
        printf("De combien de cases ?\n");
        while(!test){
            if (scanf("%d", &distance)==1){
                if(distance>0)
                    test=true;
                else
                    printf("Entrée invalide: veuillez saisir un entier entre 0.\n");
            }
            else{
                printf("Entrée invalide: veuillez saisir un entier superieur à 0.\n");
                while(fgetc(stdin)!='\n');
            }
        }
        move(grid, piece_num, d, distance);
    }

    if (game_over_hr(game)) printf("Game is over. Score : %d", game_nb_moves(game));
    return EXIT_SUCCESS;
}
