#ifndef USEFUL_FUNCTIONS_H
#define	USEFUL_FUNCTIONS_H

#include <stdbool.h>

#include "game.h"
#include "piece.h"

// @brief Returns true if the piece are the same, return false otherwise.
bool equals(cpiece p1, cpiece p2);

// @brief Returns the number of cells of the piece p.
int piece_area (cpiece p);

// @brief Check if the piece p is out of the grid of the game g.
bool out_of_grid(cpiece p, cgame g);

// @brief Show the grid of the game g on the shell
void show_grid(game g);

#endif

