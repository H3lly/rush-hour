#include <stdio.h>
#include <stdlib.h>

#include "piece.h"
#include "game.h"

#define RH_WIDTH 6
#define RH_HEIGHT 6

struct game_s{
    int width;
    int height;
    int nb_pieces;
    int nb_moves;
    piece *piece_list;
};

game new_game(int width, int height, int nb_pieces, piece *pieces){
    bool test=false;
    for (int i=0;i<nb_pieces;++i){
        for (int j=0;j<nb_pieces;++j){
            if (i!=j&&pieces[i]==pieces[j]){
                printf("It seems there is the same piece twice. (piece %d)\n", i);
                test=true;
                break;
            } else if (i!=j&&intersect(pieces[i], pieces[j])){
                printf("It seems that the pieces %d and %d are crossing each other. \n", i, j);
                test=true;
                break;
            }
        }
        if (get_x(pieces[i])<0||get_x(pieces[i])>=width||get_y(pieces[i])<0||get_y(pieces[i])>=height){
            fprintf(stderr, "It seems that the piece %d of the pieces are out of the grid. \n", i);
            test=true;
            break;
        }
    }
    if (test) fprintf(stderr, "Are you sure that what you wanted to do ?\n");
    game g=malloc(sizeof (struct game_s));
    g->width=width;
    g->height=height;
    g->nb_pieces=nb_pieces;
    g->nb_moves=0;
    g->piece_list=pieces;
    return g;
}

game new_game_hr(int nb_pieces, piece *pieces){
    return new_game(RH_WIDTH, RH_HEIGHT, nb_pieces, pieces);
}

void delete_game(game g){
    for (int i=0;i<g->nb_pieces;i++)
        delete_piece(g->piece_list[i]);
    free(g);
}

void copy_game(cgame src, game dst){
    dst->nb_pieces=src->nb_pieces;
    dst->nb_moves=src->nb_moves;
    dst->piece_list=src->piece_list;
    dst->width=src->width;
    dst->height=src->height;
}

int game_nb_pieces(cgame g){
    return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num){
    return g->piece_list[piece_num];
}

bool game_over_hr(cgame g){
    return (get_x(g->piece_list[0])==4) && (get_y(g->piece_list[0])==3);
}

// @brief Check if the piece p is out of the grid of the game g.

bool out_of_grid(cpiece p, cgame g){
    //used only once but enhances readibility 
    return (get_x(p)<0||get_x(p)+get_width(p)>game_width(g)||(get_y(p)<0||get_y(p)+get_height(p)>game_height(g)));
}

bool play_move(game g, int piece_num, dir d, int distance){
    piece p=g->piece_list[piece_num];
    int travel=0;
    while (distance!=0){
        move_piece(p, d, 1);
        g->nb_moves+=1;
        distance--;
        travel++;
        for (int i=0;i<game_nb_pieces(g);++i){
            if (p==g->piece_list[i]){
                i++;
                if (i>=game_nb_pieces(g))
                    break;
            }
            if (intersect(p, game_piece(g, i))){
                //fprintf(stderr, "Unauthorized move: Piece %d is preventing %d from moving.\n\n", i, piece_num);
                move_piece(p, d, travel*-1);
                g->nb_moves-=travel;
                return false;
            }
            if (out_of_grid(p, g)){
                //fprintf(stderr, "Unauthorized move: %d would be out of bounds.\n\n", piece_num);
                move_piece(p, d, travel*-1);
                g->nb_moves-=travel;
                return false;
            }
        }
    }
    return true;
}

int game_nb_moves(cgame g){
    return g->nb_moves;
}

int game_width(cgame g){
    return g->width;
}

int game_height(cgame g){
    return g->height;
}

int game_square_piece(game g, int x, int y){
    for (int i=0;i<g->nb_pieces;i++){
        piece p=g->piece_list[i];
        for (int w=0;w<get_width(p);++w){
            for (int h=0;h<get_height(p);++h){
                if (get_x(p)+w==x&&get_y(p)+h==y)
                    return i;
            }
        }
    }
    return -1;
}