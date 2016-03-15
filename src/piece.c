#include <stdio.h>
#include <stdlib.h>
#include "piece.h"
#include "useful_functions.h"

struct piece_s{
    int abs;
    int ord;
    int width;
    int height;
    bool move_x;
    bool move_y;
};
 
 piece new_piece(int x, int y, int width, int height, bool move_x, bool move_y){
    piece p=malloc(sizeof (struct piece_s));
    p->abs=x;
    p->ord=y;
    p->width=width;
    p->height=height;
    p->move_x = move_x;
    p->move_y = move_y;
    
    return p;
}

void delete_piece(piece p){
    free(p);
}
void copy_piece(cpiece src, piece dst){
    dst -> abs=src -> abs;
    dst -> ord=src -> ord;
    dst -> width=src -> width;
    dst -> height=src -> height;
    dst -> move_x=src -> move_x;
    dst -> move_y=src -> move_y;
}

//ne bougera que d'une case dans tous les cas
void move_piece(piece p, dir d, int distance){
    if (movement_is_allowed(p, d)){
        switch (d){
            case UP:
                p -> ord+=distance;
                break;
            case DOWN:
                p -> ord-=distance;
                break;
            case RIGHT:
                p -> abs+=distance;
                break;
            case LEFT:
                p -> abs-=distance;
                break;
        }
    }
}

//Retourne true si les pièces a et b se croisent, retourne false sinon.
//Créé deux tableaux de taille de la taille de a et de b, et les comparent
//ne marche que si les pièces ont une longueur et une largeur strictement inferieur à 10
//pas très optimisé, peut être fait avec un tableau a une dimension normalement
bool intersect(cpiece a, cpiece b){
    if (a == b) return true; //si c'est la même référence c'est la même piece 
    int ta[get_width(a)][get_height(a)];
    int tb[get_width(b)][get_height(b)];
    for (int i=0; i < get_width(a); ++i){
        for (int j=0; j < get_height(a); ++j)
            ta[i][j]=10 * (get_x(a) + i) + get_y(a) + j;
    }
    for (int i=0; i < get_width(b); ++i){
        for (int j=0; j < get_height(b); ++j)
            tb[i][j]=10 * (get_x(b) + i) + get_y(b) + j;
    }
    for (int i=0; i < get_width(a);i++){
        for (int j=0; j < get_height(a); j++){
            for (int k=0; k < get_width(b); ++k){
                for (int l=0; l < get_height(b);++l){
                    if (ta[i][j] == tb[i][j])
                        return true;
                }
            }
        }
    }
    return false;
}
int get_x(cpiece p){
    return p->abs;
}
int get_y(cpiece p){
    return p->ord;
}
int get_height(cpiece p){
    return p->height;
}
int get_width(cpiece p){
    return p->width;
}

bool can_move_x(cpiece p){
    return p->move_x;
}

bool can_move_y(cpiece p){
    return p->move_y;
}

