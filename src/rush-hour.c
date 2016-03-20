#include <stdio.h>
#include <stdlib.h>

#include "piece.h"
#include "game.h"
#include "test_functions.h"
int main(void){
    //actual configuration of the game
    /*
     . . . . . .
     . . 4 . . .
     0 0 4 . . 7
     1 1 4 5 6 7
     2 3 3 5 6 .
     2 . . . 6 .
     */

    piece list [8];
    list[0]=new_piece_rh(0, 3, true, true);
    list[1]=new_piece_rh(0, 2, true, true);
    list[2]=new_piece_rh(0, 0, true, false);
    list[3]=new_piece_rh(1, 1, true, true);
    list[4]=new_piece_rh(2, 2, false, false);
    list[5]=new_piece_rh(3, 1, true, false);
    list[6]=new_piece_rh(4, 0, false, false);
    list[7]=new_piece_rh(5, 2, true, false);
    game game=new_game_hr(8, list);
    printf("\e[2J\e[H");
    
    //printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Bienvenu(e) sur RushHour ! Le but de ce jeu est de déplacer la voiture 0 jusqu'au bord droit ! Bonne chance !\n\n");
    show_grid(game);

    int piece_num;
    dir d;
    int num;
    int distance;
    int test;
    while (!(game_over_hr(game))){
        piece_num=-1;
        d=-1;
        distance=-1;
        test=false;

        printf("Veuillez saisir le numéro de la pièce à déplacer :\n");
        while (!test){
            if (scanf("%d", &piece_num) == 1){ //prompt the user for an int AND check if the input is an int
                if (piece_num >= 0 && piece_num < game_nb_pieces(game)) //check if the number is one of the piece
                    test=true;
                else
                    printf("Entrée invalide: veuillez saisir un entier entre 0 et %d.\n", game_nb_pieces(game) - 1);
            } else{ //case when the input isn't an int
                printf("Entrée invalide: veuillez saisir un entier entre 0 et %d.\n", game_nb_pieces(game) - 1);
                while (fgetc(stdin) != '\n');
                //if scanf works, it puts the input in the stdin buffer, convert it in an integer, removes it from the buffer and returns 1.
                //but if it failed, the input will be left in the stdin buffer, so you need to "clean" the buffer,
                //otherwise scanf will see that stdin isn't empty and won't ask for user input, will return 0, and loop again and again
            }
        }
        test=false;

        printf("Quelle direction ? (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
        while (!test){
            if (scanf("%d", &num) == 1){
                if (num == 1){
                    d=UP;
                    test=true;
                } else if (num == 2){
                    d=DOWN;
                    test=true;
                } else if (num == 3){
                    d=LEFT;
                    test=true;
                } else if (num == 4){
                    d=RIGHT;
                    test=true;
                } else{
                    printf("Entrée invalide: veuillez saisir un entier entre 1 et 4. (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
                }
            } else{
                printf("Entrée invalide: veuillez saisir un entier entre 1 et 4. (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
                while (fgetc(stdin) != '\n');
            }
        }
        test=false;
        printf("De combien de cases ?\n");
        while (!test){
            if (scanf("%d", &distance) == 1){
                if (distance > 0)
                    test=true;
                else
                    printf("Entrée invalide: veuillez saisir un entier supérieur à 0.\n");
            } else{
                printf("Entrée invalide: veuillez saisir un entier superieur à 0.\n");
                while (fgetc(stdin) != '\n');
            }
        }
        play_move(game, piece_num, d, distance);
        //printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("\e[2J\e[H");
        show_grid(game);
    }
    printf("Game over. Score : %d", game_nb_moves(game));
    return EXIT_SUCCESS;
}
