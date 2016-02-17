#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "piece.h"

struct piece_s{
	int abs;
	int ord;
	bool small;				//if true, size=2, else size=3
	bool estHorizontal;
};

piece new_piece_rh (int x, int y, bool small, bool horizontal){	// inversion de x et y
	piece p = malloc(sizeof(struct piece));								// <=> piece p = new piece();
	p -> abs = x;
	p -> ord = y;
	p -> small = small;
	p -> estHorizontal = horizontal;
  return p;
}

void delete_piece (piece p){
	free(p);
}

void copy_piece (cpiece src, piece dst){
	dst -> abs = src -> abs;
	dst -> ord = src -> ord;
	dst -> small = src -> small;
	dst -> estHorizontal = src -> estHorizontal;
}

void move_piece (piece p, dir d, int distance){
	if movement_is_allowed(p, d){
		switch (d) {
			case UP:
				p -> ord += distance;
				break;
			case DOWN:
				p -> ord -= distance;
				break;
			case RIGHT:
				p -> abs += distance;
				break;
			case LEFT:
				p -> abs -= distance;
				break;
		}
	}
	printf("Not moved");
	break;
}

bool movement_is_allowed(piece p, dir d){
	if (((d==UP || d==DOWN)&&(p.estHorizontal))||((d==LEFT || d==RIGHT)&&(!p.estHorizontal))){	
		return false;
	return true;
}


bool intersect(cpiece a, cpiece b){
	int ax = a->abs;
	int ay = a->ord;
	int bx = b->abs;
	int by = b->ord;
	if(a->small){
		if(b->small){
			if(a->estHorizontal){
				if(b->estHorizontal){
					return (ay==by)&&(ax==bx||(ax+1)==bx||ax==(bx+1));
				}
				return (ay==by||ay==(by+1))&&(ax==bx||(ax+1)==bx||ax==(bx+1)||(ax+1)==(bx+1));
			}
		}
		//code si p2 grand
	}
	if(p2->small){
		//code
	}
	//si ils sont tous grand
}

/*
int get_x(cpiece p);

int get_y(cpiece p);

int get_height(cpiece p);

int get_width(cpiece p);

bool is_horizontal(cpiece p);
*/
