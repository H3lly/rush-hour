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
void set_up(){
    pieces[0]=new_piece_rh(3, 3, true, true);
    pieces[1]=new_piece(3, 0, 1, 2, true, true);
    pieces[2]=new_piece(4, 1, 2, 1, true, true);
    pieces[3]=new_piece(5, 3, 1, 3, true, true);
}

void tear_down(){
    for (int i=0;i<NB_PIECES;i++)
        delete_piece(pieces[i]);
}

bool test_new_piece(){
    set_up();
    bool result=true;
    result=test_equality_int(3, get_x(pieces[0]), "get_x in test_new_piece");
    result=test_equality_int(3, get_y(pieces[0]), "get_y in test_new_piece")&&result;
    result=test_equality_int(2, get_width(pieces[0]), "get_width in test_new_piece")&&result;
    result=test_equality_int(1, get_height(pieces[0]), "get_height in test_new_piece")&&result;
    result=test_equality_bool(true, is_horizontal(pieces[0]), "is_horizontal in test_new_piece")&&result;
    result=test_equality_bool(true, is_small(pieces[0]), "is_small in test_new_piece")&&result;
    result=test_equality_bool(true, can_move_x(pieces[0]), "can_move_x in test_new_piece")&&result;
    result=test_equality_bool(false, can_move_y(pieces[0]), "can_move_y in test_new_piece")&&result;
    tear_down();
    return result;
}

bool test_intersect(){
    bool result=true;
    set_up();
    for (int i=0;i<NB_PIECES;i++)
        for (int j=0;j<NB_PIECES;j++){
            result=result&&test_equality_bool(i==j, intersect(pieces[i], pieces[j]), "intersect");
        }

    piece pb_piece1=new_piece_rh(3, 3, false, false);
    piece pb_piece2=new_piece_rh(3, 1, false, false);
    result=result&&test_equality_bool(true, intersect(pieces[0], pb_piece1), "intersect pb1");
    result=result&&test_equality_bool(true, intersect(pb_piece2, pb_piece1), "intersect pb2");
    delete_piece(pb_piece1);
    delete_piece(pb_piece2);
    tear_down();
    return result;
}

bool test_move(){
    bool result=true;
    piece p=new_piece_rh(0, 0, true, true);
    set_up();
    for (int dist=1;dist<NB_PIECES;dist++)
        for (int i=0;i<NB_PIECES;i++){
            copy_piece(pieces[i], p);
            move_piece(p, LEFT, dist);
            if (is_horizontal(pieces[i]))
                result=result&&test_equality_int(get_x(pieces[i])-dist, get_x(p), "move LEFT");
            else
                result=result&&test_equality_int(get_x(pieces[i]), get_x(p), "move LEFT");
            copy_piece(pieces[i], p);
            move_piece(p, RIGHT, dist);
            if (is_horizontal(pieces[i]))
                result=result&&test_equality_int(get_x(pieces[i])+dist, get_x(p), "move RIGHT");
            else
                result=result&&test_equality_int(get_x(pieces[i]), get_x(p), "move RIGHT");
            copy_piece(pieces[i], p);
            move_piece(p, UP, dist);
            if (!is_horizontal(pieces[i]))
                result=result&&test_equality_int(get_y(pieces[i])+dist, get_y(p), "move UP");
            else
                result=result&&test_equality_int(get_y(pieces[i]), get_y(p), "move UP");
            copy_piece(pieces[i], p);
            move_piece(p, DOWN, dist);
            if (!is_horizontal(pieces[i]))
                result=result&&test_equality_int(get_y(pieces[i])-dist, get_y(p), "move DOWN");
            else
                result=result&&test_equality_int(get_y(pieces[i]), get_y(p), "move DOWN");


        }
    tear_down();
    delete_piece(p);
    return result;
    return false;
}

bool test_copy(){
    piece p=new_piece_rh(0, 0, true, true);
    bool result=true;
    set_up();
    for (int i=0;i<NB_PIECES;i++){
        copy_piece(pieces[i], p);
        result=result&&test_equality_int(get_height(pieces[i]), get_height(p), "copy get_height");
        result=result&&test_equality_int(get_width(pieces[i]), get_width(p), "copy get_width");
        result=result&&test_equality_int(get_x(pieces[i]), get_x(p), "copy get_x");
        result=result&&test_equality_int(get_y(pieces[i]), get_y(p), "copy get_y");
        result=result&&test_equality_bool(is_horizontal(pieces[i]), is_horizontal(p), "copy is_horizontal");
    }
    tear_down();
    delete_piece(p);
    return result;
}

int main(int argc, char *argv[]){
    bool result=true;

    result=result&&test_equality_bool(true, test_new_piece(), "new_piece");
    result=result&&test_equality_bool(true, test_intersect(), "intersect");
    result=result&&test_equality_bool(true, test_move(), "move");
    result=result&&test_equality_bool(true, test_copy(), "copy");

    if (result){
        printf("Yay !\n");
        return EXIT_SUCCESS;
    } else
        printf("Meh\n");
    return EXIT_FAILURE;
}