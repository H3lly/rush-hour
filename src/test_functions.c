#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "game.h"
#include "piece.h"
#include "test_functions.h"

bool equals(cpiece p1, cpiece p2){
    if (p1==p2) return true;//if it's the same reference then it's the same piece.
    return (get_x(p1)==get_x(p2))&&(get_y(p1)==get_y(p2))&&(get_width(p1)==get_width(p2))&&(get_height(p1)==get_height(p2)&&(can_move_x(p1)==can_move_x(p2))&&(can_move_y(p1)==can_move_y(p2)));
}

bool is_small(cpiece p){
    return get_height(p)==2||get_width(p)==2;
}

void show_grid(game g){
    printf("\n");
    for (int ord=game_height(g)-1;ord>=0;ord--){
        for (int abs=0;abs<game_width(g);abs++){
            if (game_square_piece(g, abs, ord)== -1)
                printf(" ·    ");
            else
                printf("%2d    ", game_square_piece(g, abs, ord));
        }
        printf("\n\n\n");
    }
    //printf("\nMoves : %d\n----------\n\n", game_nb_moves(g));
}

bool game_over_ar(cgame g){
    //printf("Exit : (%d,%d)|0: (%d,%d)\n", (game_width(g)/2)-1, 0, get_x(game_piece(g, 0)), get_y(game_piece(g, 0)));
    return get_x(game_piece(g, 0))==0 && get_y(game_piece(g, 0))==0;
    //return (get_x(game_piece(g, 0))==(game_width(g)/2)) && (get_y(game_piece(g, 0))==0);
}

bool test_equality_int(int expected, int value, char * msg){
    if (expected!=value)
        fprintf(stderr, "ERR: value expected %d ; value computed %d | Error from : %s\n", expected, value, msg);
    return expected==value;
}

bool test_equality_bool(bool expected, bool value, char * msg){
    if (expected!=value)
        fprintf(stderr, "ERR: value expected %s ; value computed %s | Error from : %s\n", (expected?"true":"false"), (value?"true":"false"), msg);
    return expected==value;
}

bool test_equality_piece(cpiece expected, cpiece value, char * msg){
    if (!equals(expected, value)){
        fprintf(stderr, "ERR: Pieces are different | Error from : %s\n", msg);
    }
    return equals(expected, value);
}

bool valid_piece_list(piece* list, int length, int game_width, int game_height){
    bool isValid=true;
    for (int i=0;i<length;++i){
        for (int j=i;j<length;++j){
            if (i!=j){
                if (list[i]==list[j]){
                    if(isValid) fprintf(stderr, "The list you gave isn't valid : \n");
                    fprintf(stderr, "- It seems there is the same piece twice : piece %d and %d. \n", i, j);
                    isValid=false;
                } else if (intersect(list[i], list[j])){
                    if(isValid) fprintf(stderr, "The list you gave isn't valid : \n");
                    fprintf(stderr, "- It seems that the pieces %d and %d are crossing each other. \n", i, j);
                    isValid=false;
                }
            }
        }
        if (get_x(list[i])<0||get_x(list[i])>=game_width||get_y(list[i])<0||get_y(list[i])>=game_height){
            if(isValid) fprintf(stderr, "The list you gave isn't valid : \n");
            fprintf(stderr, "- It seems that the piece %d is out of the grid. \n", i);
            isValid=false;
        }
    }
    return isValid;
}

void tableau_1D(int *t, game g){
    int taille_tab = game_height(g)*game_width(g);
    for (int i = 0; i<taille_tab; ++i){
        t[i] = -1;
    }
    for (int num_piece = 0; num_piece<game_nb_pieces(g); ++num_piece){
        cpiece p=game_piece(g, num_piece);
        t[get_x(p)+(get_y(p)*6)] = num_piece;
        if (get_width(p)>1){
            for (int i = 1; i<get_width(p); ++i){
                t[get_x(p)+(get_y(p)*6)+i] = num_piece;
            }
        }
        if (get_height(p)>1){
            for (int j = 1; j<get_height(p); ++j){
                t[get_x(p)+((get_y(p)*6)+(j*6))] = num_piece;
            }
        }
    }
}