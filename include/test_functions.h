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
bool game_over_an(cgame g);

// @brief TO_DO
bool is_small(cpiece p);

// @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output 
// @return true if excepted==value
bool test_equality_int(int expected, int value, char * msg);

// @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output 
// @return true if excepted==value
bool test_equality_bool(bool expected, bool value, char * msg);

// @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output 
// @return true if excepted==value
bool test_equality_piece(cpiece expected, cpiece value, char * msg);

#endif

