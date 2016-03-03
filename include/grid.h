#ifndef _GRID_H_
#define _GRID_H_
#include <stdbool.h>

#include "piece.h"
#include "game.h"

typedef struct grid_s* grid;


grid new_grid(game g);
void deplacement(grid grid, dir d, int piece_num, int distance);
void show_grid(grid g);
void delete_grid(grid g);
void add_piece(grid g, int piece_num);
void delete_piece_grid(grid grid, int piece_num);
void set_cell_int(grid grid, int x, int y, int val);
void set_cell_char(grid grid, int x, int y, char c);

void set_pieces(grid g);
game get_game(grid g);

#endif
