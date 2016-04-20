#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "game.h"
#include "piece.h"
#include "test_functions.h"

#define NB_PIECES 4

piece pieces[NB_PIECES];

/* 
 
test configuration rush hour
. . . . . 3
. . . . . 3
. . . 0 0 3
. . . . . .
. . . 1 2 2
. . . 1 . .

 */
void set_up() {
    pieces[0] = new_piece_rh(3, 3, true, true);
    pieces[1] = new_piece(3, 0, 1, 2, true, true);
    pieces[2] = new_piece(4, 1, 2, 1, true, true);
    pieces[3] = new_piece(5, 3, 1, 3, true, true);
}

void tear_down() {
    for (int i = 0; i < NB_PIECES; i++)
        delete_piece(pieces[i]);
}

bool test_new_piece() {
    set_up();
    bool result = true;
    result = test_equality_int(3, get_x(pieces[0]), "get_x in test_new_piece");
    result = test_equality_int(3, get_y(pieces[0]), "get_y in test_new_piece") && result;
    result = test_equality_int(2, get_width(pieces[0]), "get_width in test_new_piece") && result;
    result = test_equality_int(1, get_height(pieces[0]), "get_height in test_new_piece") && result;
    result = test_equality_bool(true, is_horizontal(pieces[0]), "is_horizontal in test_new_piece") && result;
    result = test_equality_bool(true, is_small(pieces[0]), "is_small in test_new_piece") && result;
    result = test_equality_bool(true, can_move_x(pieces[0]), "can_move_x in test_new_piece") && result;
    result = test_equality_bool(false, can_move_y(pieces[0]), "can_move_y in test_new_piece") && result;
    tear_down();
    return result;
}

bool test_intersect() {
    bool result = true;
    set_up();
    for (int i = 0; i < NB_PIECES; i++) {
        for (int j = 0; j < NB_PIECES; j++)
            result = result && test_equality_bool(i == j, intersect(pieces[i], pieces[j]), "intersect loop in test_intersect");
    }
    piece pb_piece1 = new_piece_rh(3, 3, false, false);
    piece pb_piece2 = new_piece_rh(3, 1, false, false);
    result = result && test_equality_bool(true, intersect(pieces[0], pb_piece1), "intersect 1 in test_intersect");
    result = result && test_equality_bool(true, intersect(pb_piece2, pb_piece1), "intersect 2 in test_intersect");
    delete_piece(pb_piece1);
    delete_piece(pb_piece2);
    tear_down();
    return result;
}

bool test_move_piece() {
    bool result = true;
    set_up();
    move_piece(pieces[0], LEFT, 1);
    result = test_equality_int(2, get_x(pieces[0]), "move_piece p0 1 in test_move_piece"); //moved
    move_piece(pieces[0], UP, 1);
    result = test_equality_int(3, get_y(pieces[0]), "move_piece p0 2 in test_move_piece") && result; //didn't move
    move_piece(pieces[2], UP, 1);
    result = test_equality_int(2, get_y(pieces[2]), "move_piece p2 1 in test_move_piece") && result; //moved
    move_piece(pieces[2], LEFT, 4);
    result = test_equality_int(0, get_x(pieces[2]), "move_piece p2 2 in test_move_piece") && result; //moved
    tear_down();
    return result;
}

bool test_copy_piece() {
    piece tmp = new_piece_rh(0, 0, true, true);
    bool result_final = true;
    set_up();
    for (int i = 0; i < NB_PIECES; i++) {
        bool result = true;
        copy_piece(pieces[i], tmp);
        result = test_equality_int(get_height(pieces[i]), get_height(tmp), "get_height in test_copy_piece") && result;
        result = test_equality_int(get_width(pieces[i]), get_width(tmp), "get_width in test_copy_piece") && result;
        result = test_equality_int(get_x(pieces[i]), get_x(tmp), "get_x in test_copy_piece") && result;
        result = test_equality_int(get_y(pieces[i]), get_y(tmp), "get_y in test_copy_piece") && result;
        result = test_equality_bool(is_horizontal(pieces[i]), is_horizontal(tmp), "is_horizontal in test_copy_piece") && result;
        result = test_equality_bool(can_move_x(pieces[i]), can_move_x(tmp), "can_move_x in test_copy_piece") && result;
        result = test_equality_bool(can_move_y(pieces[i]), can_move_y(tmp), "can_move_y in test_copy_piece") && result;
        if (!result) fprintf(stderr, " -> in iteration %d\n", i);
        result_final = result_final && result;
    }
    tear_down();
    delete_piece(tmp);
    return result_final;
}

int main(int argc, char *argv[]) {
    bool result = true;
    result = test_equality_bool(true, test_new_piece(), "test_new_piece in main");
    result = test_equality_bool(true, test_intersect(), "test_intersect in main") && result;
    result = test_equality_bool(true, test_move_piece(), "test_move_piece in main") && result;
    result = test_equality_bool(true, test_copy_piece(), "test_copy_piece in main") && result;

    if (result) {
        printf("Yay !\n");
        return EXIT_SUCCESS;
    } else
        printf("Meh\n");
    return EXIT_FAILURE;
}