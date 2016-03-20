#include <stdio.h>
#include <stdlib.h>

#include "piece.h"

struct piece_s{
    int abs;
    int ord;
    int width;
    int height;
    bool move_x;
    bool move_y;
};

//à moi

// @brief Returns the number of cells of the piece p.
int piece_area (cpiece p){
    return get_width(p)*get_height(p);
}

// @brief TO_DO
bool movement_is_allowed (cpiece p, dir d){
    return ((d==LEFT || d==RIGHT)&&(can_move_x(p))) || ((d == UP || d == DOWN)&&(can_move_y(p)));
}

piece new_piece_rh(int x, int y, bool small, bool horizontal){
    int width;
    int height;
    if (horizontal){
        if (small)
            width = 2;
        else
            width = 3;
        height =1;
    }
    else{
        if (small)
            height = 2;
        else
            height = 3;
        width = 1;
    }
    return new_piece(x, y, width, height, horizontal, !horizontal);
}
piece new_piece(int x, int y, int width, int height, bool move_x, bool move_y){
    piece p=malloc(sizeof (struct piece_s));
    p->abs=x;
    p-> ord=y;
    p-> width=width;
    p-> height=height;
    p-> move_x=move_x;
    p-> move_y=move_y;

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
void move_piece(piece p, dir d, int distance) {
    if (movement_is_allowed(p, d)) {
        switch (d) {
            case UP:
                p -> ord += distance;
                break;
            case DOWN:
                p -> ord -= distance;
                break;
            case RIGHT:
                p -> abs += distance;
                break;
            case LEFT:
                p -> abs -= distance;
                break;
        }
    }
}

//Make two arrays that list all the coordinates occupated by the pieces, compare them and return if they have common coordinates
//ne marche que si les pièces ont une longueur et une largeur strictement inferieur à 10
//##################################################### A MODIFIER ###############################################################
bool intersect(cpiece a, cpiece b){
    //the tens is the abscissa, the unit is the ordinate
    if (a==b) return true; //if it's the same piece
    int ta[piece_area(a)];
    int tb[piece_area(b)];
    int cpt=0;
    for (int i=0; i < get_width(a); i++){
        for (int j=0; j < get_height(a); j++)
            ta[cpt++]=10 * (get_x(a) + i) + get_y(a) + j;
    }
    cpt=0;
    for (int i=0; i < get_width(b); i++){
        for (int j=0; j < get_height(b); j++)
            tb[cpt++]=10 * (get_x(b) + i) + get_y(b) + j;
    }
    for (int i=0; i < piece_area(a); i++){
        for (int j=0; j < piece_area(b); j++){
            if (ta[i] == tb[j])
                return true;
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

//useless in v2
bool is_horizontal(cpiece p) {
    return can_move_x(p);
}

