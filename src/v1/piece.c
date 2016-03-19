#include <stdio.h>
#include <stdlib.h>
#include "useful_functions.h"

struct piece_s {
    int abs;
    int ord;
    bool small; //if true, size=2, else size=3
    bool horizontal;
};

piece new_piece_rh(int x, int y, bool small, bool horizontal) {
    piece p = malloc(sizeof (struct piece_s));
    p -> abs = x;
    p -> ord = y;
    p -> small = small;
    p -> horizontal = horizontal;
    return p;
}

void delete_piece(piece p) {
    free(p);
}

void copy_piece(cpiece src, piece dst) {
    dst -> abs = src -> abs;
    dst -> ord = src -> ord;
    dst -> small = src -> small;
    dst -> horizontal = src -> horizontal;
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
bool intersect(cpiece a, cpiece b) {
    if (a == b) return true; //if it's the same piece
    int amax = get_width(a);
    if (get_height(a) > amax) amax = get_height(a);
    int ta[amax];
    int bmax = get_width(b);
    if (get_height(b) > bmax) bmax = get_height(b);
    int tb[bmax];
    for (int i = 0; i < amax; i++) {
        if (get_width(a) > get_height(a))
            ta[i] = 10 * (get_x(a) + i) + get_y(a); //the tens is the abscissa, the unit is the ordinate
        else
            ta[i] = 10 * get_x(a) + get_y(a) + i;
    }
    for (int i = 0; i < bmax; i++) {
        if (get_width(b) > get_height(b))
            tb[i] = 10 * (get_x(b) + i) + get_y(b);
        else
            tb[i] = 10 * get_x(b) + get_y(b) + i;
    }
    for (int i = 0; i < (sizeof (ta) / sizeof (ta[0])); i++) {
        for (int j = 0; j < (sizeof (tb) / sizeof (tb[0])); j++) {
            if (ta[i] == tb[j])
                return true;
        }
    }
    return false;
}

int get_x(cpiece p) {
    return p->abs;
}

int get_y(cpiece p) {
    return p->ord;
}

int get_height(cpiece p) {
    if (!(p->horizontal)) {
        if (p->small) {
            return 2;
        }
        return 3;
    }
    return 1;
}

int get_width(cpiece p) {
    if (p->horizontal) {
        if (p->small) {
            return 2;
        }
        return 3;
    }
    return 1;
}

bool is_horizontal(cpiece p) {
    return p->horizontal;
}