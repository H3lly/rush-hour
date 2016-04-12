#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "piece.h"
#include "game.h"
#include "test_functions.h"

int main(int argc, char** argv){
    //actual configuration of the game

    /*
    1  0  0  2
    1  0  0  2
    .  3  3  .
    .  .  .  .
    .  .  .  4
     */

    piece liste [5];
    liste[0]=new_piece(1, 3, 2, 2, true, true);
    liste[1]=new_piece(0, 3, 1, 2, true, true);
    liste[2]=new_piece(3, 3, 1, 2, true, true);
    liste[3]=new_piece(1, 2, 2, 1, true, true);
    liste[4]=new_piece(3, 0, 1, 1, true, true);

    game game=new_game(4, 5, 5, liste);
    if (argc==2&& !strcmp(argv[1], "test")){
        play_move(game, 3, DOWN, 2);
        play_move(game, 1, DOWN, 2);
        play_move(game, 1, RIGHT, 2);
        play_move(game, 0, LEFT, 1);
        play_move(game, 1, UP, 2);
        play_move(game, 3, UP, 2);
        play_move(game, 3, RIGHT, 1);
        play_move(game, 0, DOWN, 3);
        play_move(game, 0, RIGHT, 1);
        delete_game(game);
        return 1;
    } else{
        printf("\e[2J\e[H");//clean the shell
        printf("***** Welcome in RushHour ! *****\nYou need to drive the 0 car to the right !\nGood luck !\n\n");
        show_grid(game);
        int piece_num;
        dir d;
        int num;
        int distance;
        bool test;
        while (!(game_over_ar(game))){
            piece_num=-1;
            d=-1;
            distance=-1;
            test=false;
            printf("Please input the number of the piece you want to move :\n");
            while (!test){
                if (scanf("%d", &piece_num)==1){ //prompt the user for an int AND check if the input is an int
                    if (piece_num>=0&&piece_num<game_nb_pieces(game)) //check if the number is one of the piece
                        test=true;
                    else
                        printf("Invalid input: please write an integer between 0 and %d.\n", game_nb_pieces(game)-1);
                } else{ //case when the input isn't an int
                    printf("Invalid input: please write an integer between 0 and %d.\n", game_nb_pieces(game)-1);
                    while (fgetc(stdin)!='\n');
                    //if scanf works, it puts the input in the stdin buffer, convert it in an integer, removes it from the buffer and returns 1.
                    //but if it failed, the input will be left in the stdin buffer, so you need to "clean" the buffer,
                    //otherwise scanf will see that stdin isn't empty and won't ask for user input, will return 0, and loop again and again
                }
            }
            test=false;

            printf("Which direction ? (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
            while (!test){
                if (scanf("%d", &num)==1){
                    if (num==1){
                        d=UP;
                        test=true;
                    } else if (num==2){
                        d=DOWN;
                        test=true;
                    } else if (num==3){
                        d=LEFT;
                        test=true;
                    } else if (num==4){
                        d=RIGHT;
                        test=true;
                    } else{
                        printf("Invalid input: please write an integer between 1 and 4. (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
                    }
                } else{
                    printf("Invalid input: please write an integer between 1 and 4. (1=UP, 2=DOWN, 3=LEFT, 4=RIGHT)\n");
                    while (fgetc(stdin)!='\n');
                }
            }
            test=false;
            printf("How many times ?\n");
            while (!test){
                if (scanf("%d", &distance)==1){
                    if (distance>0)
                        test=true;
                    else
                        printf("Invalid input: please write an integer greater than 0.\n");
                } else{
                    printf("Invalid input: please write an integer greater than 0.\n");
                    while (fgetc(stdin)!='\n');
                }
            }
            printf("\e[2J\e[H");
            if (play_move(game, piece_num, d, distance)) printf("Piece %d moved.\n\n", piece_num);
            show_grid(game);
        }
        printf("Game is over. Score : %d", game_nb_moves(game));
        delete_game(game);
        return EXIT_SUCCESS;
    }
}
