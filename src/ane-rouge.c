#include <stdio.h>
#include <stdlib.h>

#include "useful_functions.h"

int main(void) {
    //actual configuration of the game
    
    /*
    1  0  0  2
    1  0  0  2
    3  5  5  4
    3  6  7  4
    8  .  .  9
    */
    
    piece liste [10];
    liste[0] = new_piece(1, 3, 2, 2, true, true);
    liste[1] = new_piece(0, 3, 1, 2, true, true);
    liste[2] = new_piece(3, 3, 1, 2, true, true);
    liste[3] = new_piece(0, 1, 1, 2, true, true);
    liste[4] = new_piece(3, 1, 1, 2, true, true);
    liste[5] = new_piece(1, 2, 2, 1, true, true);
    liste[6] = new_piece(1, 1, 1, 1, true, true);
    liste[7] = new_piece(2, 1, 1, 1, true, true);
    liste[8] = new_piece(0, 0, 1, 1, true, true);
    liste[9] = new_piece(3, 0, 1, 1, true, true);
    
    game game = new_game(4, 5, 10, liste);
    show_grid(game);
    int piece_num;
    dir d;
    int num;
    int distance;
    int test;
    while (!(game_over_an(game))) {
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
            } else{
                printf("Entrée invalide: veuillez saisir un entier superieur à 0.\n");
                while(fgetc(stdin)!='\n');
            }
        }
        play_move(game, piece_num, d, distance);
        show_grid(game);
    }
    printf("Game is over. Score : %d", game_nb_moves(game));
    return EXIT_SUCCESS;
}
