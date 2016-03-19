#ifndef USEFUL_FUNCTIONS_H
#define	USEFUL_FUNCTIONS_H

#include <stdbool.h>

#include "game.h"
#include "piece.h"


char* afficher_direction(dir direction);
bool equals(cpiece p1, cpiece p2);
bool movement_is_allowed(piece p, dir d);
bool is_small(cpiece p);


#endif	/* USEFUL_FUNCTIONS_H */

