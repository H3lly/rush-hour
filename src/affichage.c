#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"
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
    int test = false;
    while (!(game_over_hr(game))) {
        printf("Veuillez saisir le numéro de la pièce à déplacer :\n");
        scanf("%d", &piece_num);
        printf("Quelle direction ? (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
        while (!test) {
            scanf("%d", &num);
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
                printf("Entrée invalide, veuilez saisir un entier entre 1 et 4. (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
            }
        }

        printf("De combien de cases ?\n");
        scanf("%d", &distance);
        //printf("Piece_num = %d, d=%s, distance=%d\n", piece_num, afficher_direction(d), distance);
        move(grid, piece_num, d, distance);
        return 1;
        //move(grid, 0, UP, 2);
    }

    if (game_over_hr(game)) printf("Game is over. Score : %d", game_nb_moves(game));
    return EXIT_SUCCESS;
}
