#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solveur.h"

#include "piece.h"
#include "game.h"
#include "test_functions.h"

int main(int argc, char** argv){
    /*configurations of the games
     
    rush hour
    . . . . . .
    . . 4 . . .
    0 0 4 . . 7
    1 1 4 5 6 7
    2 3 3 5 6 .
    2 . . . 6 .
    
    ane rouge
    1 0 0 2
    1 0 0 2
    . 3 3 .
    . . . .
    . . . 4
    
     */

        if (argc==2 && !strcmp(argv[1], "solve")){
                piece toSolve [2];
                toSolve[0]=new_piece(0, 1, 1, 1, true, true);
                toSolve[1]=new_piece(0, 0, 1, 1, true, true);
                game testToSolve = new_game(2, 2, 2, toSolve);
                show_grid(testToSolve);
                int s = solve(testToSolve);
                printf("\nSolve : %d\n", s);
                return 1;
        }
      

    //asks the user which game he wants to play
    printf("\e[2J\e[H");//clean the shell
    printf("Which game do you want to play? Press 1 for Rush Hour, press 2 for Ane Rouge \n");
    int choice;
    while (true){
        if (scanf("%d", &choice)==1){ //prompt the user for an int AND check if the input is an int
            if (choice==1||choice==2) //check if the input matches what we expected
                break;
            else
                printf("Invalid input: please choose between 1 and 2.\n");
        } else{ //case when the input isn't an int
            printf("Invalid input: please choose between 1 and 2.\n");
            while (fgetc(stdin)!='\n');
            //if scanf works, it puts the input in the stdin buffer, convert it in an integer, removes it from the buffer and returns 1.
            //but if it failed, the input will be left in the stdin buffer, so you need to "clean" the buffer,
            //otherwise scanf will see that stdin isn't empty and won't ask for user input, will return 0, and loop again and again
        }
    }
    game game=NULL;
    if (choice==1){
        piece list [8];
        list[0]=new_piece_rh(0, 3, true, true);
        list[1]=new_piece_rh(0, 2, true, true);
        list[2]=new_piece_rh(0, 0, true, false);
        list[3]=new_piece_rh(1, 1, true, true);
        list[4]=new_piece_rh(2, 2, false, false);
        list[5]=new_piece_rh(3, 1, true, false);
        list[6]=new_piece_rh(4, 0, false, false);
        list[7]=new_piece_rh(5, 2, true, false);
        //list[8]=new_piece_rh(0, 5, false, true);

        game=new_game_hr(8, list);

    } else{
        piece list [5];
        list[0]=new_piece(1, 3, 2, 2, true, true);
        list[1]=new_piece(0, 3, 1, 2, true, true);
        list[2]=new_piece(3, 3, 1, 2, true, true);
        list[3]=new_piece(1, 2, 2, 1, true, true);
        list[4]=new_piece(3, 0, 1, 1, true, true);

        game=new_game(4, 5, 5, list);
    }

    //solves automatically if you need to use valgrind and don't want to play
    if (argc==2&& !strcmp(argv[1], "test")){
        if (choice==1){
            play_move(game, 7, UP, 2);
            play_move(game, 6, UP, 3);
            play_move(game, 5, UP, 3);
            play_move(game, 4, UP, 1);
            play_move(game, 1, RIGHT, 3);
            play_move(game, 3, RIGHT, 2);
            play_move(game, 4, DOWN, 3);
            play_move(game, 0, RIGHT, 1);
            play_move(game, 2, UP, 4);
            play_move(game, 0, LEFT, 1);
            play_move(game, 4, UP, 3);
            play_move(game, 1, LEFT, 3);
            play_move(game, 3, LEFT, 3);
            play_move(game, 6, DOWN, 3);
            play_move(game, 4, DOWN, 3);
            play_move(game, 0, RIGHT, 4);
            delete_game(game);
            return 1;
        } else{
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
        }
    }
    if (argc==2&& !strcmp(argv[1], "solve")){
        int s=solve(game);
        printf("Solve : %d\n", s);
        return 1;
    }
    int* t=malloc(sizeof (int)*(game_width(game)*game_height(game)));
    tableau_1D(t, game);
    printf("[");
    for (int i=0;i<game_width(game)*game_height(game);++i){
        printf("%d, ", t[i]);
    }
    printf("]");
    printf("\e[2J\e[H");//clean the shell
    printf("***** Welcome in RushHour ! *****\nYou need to drive the 0 car to the right !\nGood luck !\n\n");
    show_grid(game);

    int piece_num;
    dir d;
    int num;
    int distance;
    int test;

    while (((choice==1)&&!(game_over_hr(game)))|| ((choice==2)&&!(game_over_ar(game)))){
        piece_num= -1;
        d= -1;
        distance= -1;
        test=false;
        printf("Please input the number of the piece you want to move (press -1 to quit):\n");
        while (!test){
            if (scanf("%d", &piece_num)==1){
                if (piece_num== -1){
                    delete_game(game);
                    return 0;
                }
                if (piece_num>=0&&piece_num<game_nb_pieces(game))
                    test=true;
                else
                    printf("Invalid input: please write an integer between 0 and %d.\n", game_nb_pieces(game)-1);
            } else{
                printf("Invalid input: please write an integer between 0 and %d.\n", game_nb_pieces(game)-1);
                while (fgetc(stdin)!='\n');
            }
        }
        test=false;

        printf("Which direction ? (2=DOWN, 4=LEFT, 6=RIGHT, 8=UP)\n");
        while (!test){
            if (scanf("%d", &num)==1){
                if (num==2){
                    d=DOWN;
                    test=true;
                } else if (num==4){
                    d=LEFT;
                    test=true;
                } else if (num==6){
                    d=RIGHT;
                    test=true;
                } else if (num==8){
                    d=UP;
                    test=true;
                } else{
                    printf("Invalid input: please choose between 2, 4, 6 and 8 (2=DOWN, 4=LEFT, 6=RIGHT, 8=UP)\n");
                }
            } else{
                printf("Invalid input: please choose between 2, 4, 6 and 8 (2=DOWN, 4=LEFT, 6=RIGHT, 8=UP)\n");
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
        if (play_move(game, piece_num, d, distance))
            printf("Piece %d moved.\n\n", piece_num);
        show_grid(game);
    }
    printf("Game is over. Score : %d\n", game_nb_moves(game));
    free(t);
    delete_game(game);
    return EXIT_SUCCESS;
}
