#ifndef TEST_FUNCTIONS_H
#define	TEST_FUNCTIONS_H

#include <stdbool.h>

#include "game.h"
#include "piece.h"

// @brief Returns true if the piece are the same, return false otherwise.
bool equals(cpiece p1, cpiece p2);

// @brief Show the grid of the game g on the shell
void show_grid(game g);

// @brief TO_DO
bool game_over_ar(cgame g);

// @brief Returns if the piece is small or not.
bool is_small(cpiece p);

// @brief Tests if value is equal to expected; if not, displays an error message containing msg to standard error output 
// @return true if excepted==value
bool test_equality_int(int expected, int value, char * msg);

// @brief Tests if value is equal to expected; if not, displays an error message containing msg to standard error output 
// @return true if excepted==value
bool test_equality_bool(bool expected, bool value, char * msg);

// @brief Tests if value is equal to expected; if not, displays an error message containing msg to standard error output 
// @return true if excepted==value
bool test_equality_piece(cpiece expected, cpiece value, char * msg);

// @brief Fill a 1D tab with its game's pieces.
void tableau_1D(int *t, game g);
#endif
