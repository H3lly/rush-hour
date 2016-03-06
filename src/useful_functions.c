#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "grid.h"
#include "piece.h"
#include "useful_functions.h"

char* afficher_direction(dir d) {
    if (d == UP)
        return "UP";
    if (d == DOWN)
        return "DOWN";
    if (d == LEFT)
        return "LEFT";
    if (d == RIGHT)
        return "RIGHT";
    return "wtf?";
}

bool equals(cpiece p1, cpiece p2) {
    return (get_x(p1) == get_x(p2))&&(get_y(p1) == get_y(p2))&&(get_width(p1) == get_width(p2))&&(get_height(p1) == get_height(p2));
}

bool movement_is_allowed(piece p, dir d){
    return ((d==LEFT || d==RIGHT)&&(is_horizontal(p))) || ((d == UP || d == DOWN)&&(!is_horizontal(p)));
}