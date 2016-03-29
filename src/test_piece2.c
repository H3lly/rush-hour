#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "game.h"
#include "piece.h"
#include "test_functions.h"

#define NB_PIECES 4

piece pieces[NB_PIECES];

/* test configuration

. . . . . .
. . . . . .
0 0 . . . .
3 3 . . 2 2
3 3 . 1 2 2
3 3 . 1 . .

 */
void set_up(){
    pieces[0]=new_piece(0, 3, 2, 1, true, true);//Can move horizontaly
    pieces[1]=new_piece(3, 0, 1, 2, true, true);//Can move horizontaly
    pieces[2]=new_piece(4, 1, 2, 2, true, true);//Can move horizontaly and vertically
    pieces[3]=new_piece(0, 0, 2, 3, true, true);//Can't move
}

void tear_down(){
    for (int i=0;i<NB_PIECES;i++)
        delete_piece(pieces[i]);
}

bool test_new_piece(){
    bool result=true;
    for (int x=0;x<5;x++)
        for (int y=0;y<5;y++)
            for (int i=0;i<5;i++)
                for (int j=0;j<5;j++)
                    for (bool move_x=false;!move_x;move_x=!move_x)
                        for (bool move_y=false;!move_y;move_y= !move_y){
                            piece p=new_piece(x, y, i, j, move_x, move_y);
                            result=test_equality_int(x, get_x(p), "get_x in test_new_piece")&&result;
                            result=test_equality_int(y, get_y(p), "get_y in test_new_piece")&&result;
                            result=test_equality_int(i, get_width(p), "get_width in test_new_piece")&&result;
                            result=test_equality_int(j, get_height(p), "get_height in test_new_piece")&&result;
                            result=test_equality_bool(move_x, can_move_x(p), "can_move_x in test_new_piece")&&result;
                            result=test_equality_bool(move_y, can_move_y(p), "can_move_y in test_new_piece")&&result;
                            delete_piece(p);
                        }
    return result;
}

bool test_intersect(){ 
    bool result=true;
    set_up();
    for (int i=0;i<NB_PIECES;i++)
        for (int j=0;j<NB_PIECES;j++){
            result=result&&test_equality_bool(i==j, intersect(pieces[i], pieces[j]), "intersect in test_intersect");
        }
    piece pb_piece1=new_piece(0, 1, 1, 1, false, false);
    piece pb_piece2=new_piece(3, 3, 1, 1, false, false);
    result=result&&test_equality_bool(true, intersect(pieces[3], pb_piece1), "intersect pb1 in test_intersect");
    result=result&&test_equality_bool(false, intersect(pb_piece2, pb_piece1), "intersect pb2 in test_intersect");
    delete_piece(pb_piece1);
    delete_piece(pb_piece2);
    tear_down();
    return result;
}

bool test_move(){ 
    bool result=true;
    piece p=new_piece(0, 0, 1, 1, true, true);
    set_up();
    for (int dist=1;dist<NB_PIECES;dist++)
        for (int i=0;i<NB_PIECES;i++){
            copy_piece(pieces[i], p);
            move_piece(p, LEFT, dist);
            if (can_move_x(pieces[i]))
                result=test_equality_int(get_x(pieces[i])-dist, get_x(p), "move LEFT 1 in test_move")&&result;
            else
                result=test_equality_int(get_x(pieces[i]), get_x(p), "move LEFT 2  in test_move")&&result; // code non executé selon gcov
            copy_piece(pieces[i], p);
            move_piece(p, RIGHT, dist);
            if (can_move_x(pieces[i]))
                result=test_equality_int(get_x(pieces[i])+dist, get_x(p), "move RIGHT 1  in test_move")&&result;
            else
                result=test_equality_int(get_x(pieces[i]), get_x(p), "move RIGHT 2  in test_move")&&result; // code non executé selon gcov
            copy_piece(pieces[i], p);
            move_piece(p, UP, dist);
            if (can_move_y(pieces[i]))
                result=test_equality_int(get_y(pieces[i])+dist, get_y(p), "move UP 1  in test_move")&&result;
            else
                result=test_equality_int(get_y(pieces[i]), get_y(p), "move UP 2  in test_move")&&result; // code non executé selon gcov
            copy_piece(pieces[i], p);
            move_piece(p, DOWN, dist);
            if (can_move_y(pieces[i]))
                result=test_equality_int(get_y(pieces[i])-dist, get_y(p), "move DOWN 1  in test_move")&&result;
            else
                result=test_equality_int(get_y(pieces[i]), get_y(p), "move DOWN 2  in test_move")&&result; // code non executé selon gcov


        }
    tear_down();
    delete_piece(p);
    return result;
    return false;
}

bool test_copy(){
    piece p=new_piece(0, 0, 0, 0, true, true);
    bool result=true;
    set_up();
    for (int i=0;i<NB_PIECES;i++){
        copy_piece(pieces[i], p);
        result=test_equality_int(get_height(pieces[i]), get_height(p), "get_height in test_copy")&&result;
        result=test_equality_int(get_width(pieces[i]), get_width(p), "get_width in test_copy")&&result;
        result=test_equality_int(get_x(pieces[i]), get_x(p), "get_x in test_copy")&&result;
        result=test_equality_int(get_y(pieces[i]), get_y(p), "get_y in test_copy")&&result;
        result=test_equality_bool(can_move_x(pieces[i]), can_move_x(p), "can_move_x in test_copy")&&result;
        result=test_equality_bool(can_move_y(pieces[i]), can_move_y(p), "can_move_y in test_copy")&&result;
    }
    tear_down();
    delete_piece(p);
    return result;
}

int main(int argc, char *argv[]){
    bool result=true;

    result=test_equality_bool(true, test_new_piece(), "test_new_piece in main")&&result;
    result = result && test_equality_bool(true, test_intersect(), "intersect in main");
    result=test_equality_bool(true, test_move(), "test_move in main")&&result;
    result=test_equality_bool(true, test_copy(), "test_copy in main")&&result;

    if (result){
        printf("Yay !\n");
        return EXIT_SUCCESS;
    } else
        return EXIT_FAILURE; // code non executé selon gcov
}