#ifndef USEFUL_FUNCTIONS_H
#define	USEFUL_FUNCTIONS_H

#include <stdbool.h>

#include "game.h"
#include "piece.h"

// @brief Returns true if the piece are the same, return false otherwise.
bool equals(cpiece p1, cpiece p2);

// @brief Show the grid of the game g on the shell
void show_grid(game g);

// @brief TO_DO
bool game_over_an(cgame g);

// @brief TO_DO
bool is_small(cpiece p);

#endif

