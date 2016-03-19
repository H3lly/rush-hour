#include <stdio.h>
#include <stdlib.h>

#include "grid.h"
#include "useful_functions.h"

int main(void) {
    piece liste [8];
    liste[0] = new_piece_rh(0, 3, true, true);
    liste[1] = new_piece_rh(0, 2, true, true);
    liste[2] = new_piece_rh(0, 0, true, false);
    liste[3] = new_piece_rh(1, 1, true, true);
    liste[4] = new_piece_rh(2, 2, false, false);
    liste[5] = new_piece_rh(3, 1, true, false);
    liste[6] = new_piece_rh(4, 0, false, false);
    liste[7] = new_piece_rh(5, 2, true, false);
    game game = new_game_hr(8, liste);
    grid grid = new_grid(game);
    set_pieces(grid);
    show_grid(grid);

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
            if (scanf("%d", &piece_num) == 1) { // on récupère la valeur donnée en entrée par l'utilisateur et on vérifie si c'est un entier
                if(piece_num>=0 && piece_num<game_nb_pieces(game)) // si la valeur entrée est un numéro valable de pièce
                  test=true;
                else
                    printf("Entrée invalide: veuillez saisir un entier entre 0 et %d.\n", game_nb_pieces(game)-1);
            }
            else{
                printf("Entrée invalide: veuillez saisir un entier entre 0 et %d.\n", game_nb_pieces(game)-1);
                while(fgetc(stdin)!='\n');
                //fflush(stdin); didn't work (I don't know why)
                //if scanf works, it puts the input in the stdin buffer, convert it in an integer, removes it from the buffer and returns 1.
                //but if it failed, the input will be left in the stdin buffer, so you need to "clean" the buffer,
                //otherwise scanf will see that stdin isn't empty and won't ask for user input, will return 0, and loop again and again
            }
        }
        test=false;
        
        printf("Quelle direction ? (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
        while (!test) {
            if (scanf("%d", &num) == 1) { // on récupère la valeur donnée en entrée par l'utilisateur et on vérifie si c'est un entier
                if (num == 1) { // la valeur de direction doit être 1, 2, 3, ou 4 (je propose d'ailleurs de changer pour 2=DOWN, 4=LEFT, 6=RIGHT, 8=UP)
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
            if (scanf("%d", &distance)==1){ // on récupère la valeur donnée en entrée par l'utilisateur et on vérifie si c'est un entier
                if(distance>0) // la distance doit être positive
                    test=true;
                else
                    printf("Entrée invalide: veuillez saisir un entier supérieur à 0.\n");
            }
            else{
                printf("Entrée invalide: veuillez saisir un entier superieur à 0.\n");
                while(fgetc(stdin)!='\n');
            }
        }
        move(grid, piece_num, d, distance);
    }

    if (game_over_hr(game)) printf("Game over. Score : %d", game_nb_moves(game));
    return EXIT_SUCCESS;
}
