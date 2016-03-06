#ifndef USEFUL_FUNCTIONS_H
#define	USEFUL_FUNCTIONS_H

#include <stdbool.h>

#include "game.h"
#include "grid.h"
#include "piece.h"


char* afficher_direction(dir direction);
bool equals(cpiece p1, cpiece p2);
bool movement_is_allowed(piece p, dir d);



#endif	/* USEFUL_FUNCTIONS_H */

