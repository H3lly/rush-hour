#ifndef _GRID_H_
#define _GRID_H_
#include <stdbool.h>

#include "piece.h"
#include "game.h"

typedef struct grid_s* grid;


grid new_grille();
void afficher_grille(grid g);

#endif
