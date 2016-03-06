#ifndef _GRID_H_
#define _GRID_H_
#include <stdbool.h>

#include "piece.h"
#include "game.h"

typedef struct grid_s* grid;


grid new_grid(game game);
char get_cell(grid grid, int x, int y);
void move(grid grid, int piece_num, dir d, int distance);
void show_grid(grid grid);
void delete_grid(grid grid);
void add_piece(grid grid, int piece_num);
void delete_piece_grid(grid grid, int piece_num);
void set_cell_int(grid grid, int x, int y, int val);
void set_cell_empty(grid grid, int x, int y);

void set_pieces(grid grid);
game get_game(grid grid);

#endif
