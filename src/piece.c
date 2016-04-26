#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "piece.h"

struct piece_s {
    int px;
    int py;
    int width;
    int height;
    bool move_x;
    bool move_y;
};

piece new_piece_rh(int x, int y, bool small, bool horizontal) {
    int width;
    int height;
    if (horizontal) {
        if (small)
            width = 2;
        else
            width = 3;
        height = 1;
    } else {
        if (small)
            height = 2;
        else
            height = 3;
        width = 1;
    }
    return new_piece(x, y, width, height, horizontal, !horizontal);
}

piece new_piece(int x, int y, int width, int height, bool move_x, bool move_y) {
    piece p = malloc(sizeof (struct piece_s));
    p->px = x;
    p->py = y;
    p->width = width;
    p->height = height;
    p->move_x = move_x;
    p->move_y = move_y;

    return p;
}

void delete_piece(piece p) {
    free(p);
}

void copy_piece(cpiece src, piece dst) {
    dst->px = src->px;
    dst->py = src->py;
    dst->width = src->width;
    dst->height = src->height;
    dst->move_x = src->move_x;
    dst->move_y = src->move_y;
}

// @brief Returns true if the direction of the movement is compatible with the piece's orientation, returns false otherwise.
bool movement_is_allowed(cpiece p, dir d) {
    return ((d == LEFT || d == RIGHT)&&(can_move_x(p))) || ((d == UP || d == DOWN)&&(can_move_y(p)));
}

void move_piece(piece p, dir d, int distance) {
    if (movement_is_allowed(p, d)) {
        switch (d) {
            case UP:
                p->py += distance;
                break;
            case DOWN:
                p->py -= distance;
                break;
            case RIGHT:
                p->px += distance;
                break;
            case LEFT:
                p->px -= distance;
                break;
        }
    }
}

// @brief Returns the number of cells of the piece p.
int piece_area(cpiece p) {
    return get_width(p) * get_height(p);
}

// @brief Returns a if a>b, returns b otherwise.
int max_int(int a, int b) {
    //I'm not importing a whole library just for one function
    return ((a > b) ? a : b);
}

// Makes two arrays that list all the coordinates occupated by the pieces, compares them and returns whether they have common coordinates or not
bool intersect(cpiece a, cpiece b) {
    if (a == b) return true; //if it's the same piece
    return (get_x(a) < get_x(b) + get_width(b) && get_x(a) + get_width(a) > get_x(b) && get_y(a) < get_y(b) + get_height(b) && get_height(a) + get_y(a) > get_y(b));
}

int get_x(cpiece p) {
    return p->px;
}

int get_y(cpiece p) {
    return p->py;
}

int get_height(cpiece p) {
    return p->height;
}

int get_width(cpiece p) {
    return p->width;
}

bool can_move_x(cpiece p) {
    return p->move_x;
}

bool can_move_y(cpiece p) {
    return p->move_y;
}

//useless in v2
bool is_horizontal(cpiece p) {
    return can_move_x(p);
}

