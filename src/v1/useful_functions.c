#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "piece.h"
#include "useful_functions.h"

//returns if the piece is small
bool is_small(cpiece p){
    return get_height(p)==2||get_width(p)==2;
}

//returns true if p1 and p2 are the same piece, return false otherwise
bool equals(cpiece p1, cpiece p2) {
    return (get_x(p1) == get_x(p2))&&(get_y(p1) == get_y(p2))&&(get_width(p1) == get_width(p2))&&(get_height(p1) == get_height(p2));
}

//returns if the movement's direction and the piece's orientation match
bool movement_is_allowed(piece p, dir d){
    return ((d==LEFT || d==RIGHT)&&(is_horizontal(p))) || ((d == UP || d == DOWN)&&(!(is_horizontal(p))));
}
