#ifndef _GRID_H_
#define _GRID_H_
#include <stdbool.h>

#include "piece.h"
#include "game.h"

typedef struct grid_s* grid;


grid new_grid();
void show_grid(grid g);
void delete_grid(grid g);
void add_piece(grid g, int nb_piece);
void set_pieces(grid g);
game get_game(grid g);

#endif
