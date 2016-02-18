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
	piece p = malloc(sizeof(struct piece_s));								// <=> piece p = new piece();
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
	if (movement_is_allowed(p,d)){
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
}

bool movement_is_allowed(piece p, dir d){
	if (((d==UP || d==DOWN)&&(p->estHorizontal))||((d==LEFT || d==RIGHT)&&(!(p->estHorizontal)))){	
		return false;
	}
	return true;
}


bool intersect(cpiece a, cpiece b){
	//faire un add différent si tall
	int ax = a->abs;
	int ay = a->ord;
	int bx = b->abs;
	int by = b->ord;
	if(a->small){
		if(b->small){
			if(a->estHorizontal){
				if(b->estHorizontal){
					return (ay==by)&&(ax==bx||(ax+1)==bx||ax==(bx+1));							//a small, b small, a hor, b hor
				}
				return (ay==by||ay==(by+1))&&(ax==bx||(ax+1)==bx);								//a small, b small, a hor, b ver
			}
			if(b->estHorizontal){
				return (ay==by||(ay+1)==by)&&(ax==bx||ax==(bx+1));  							//a small, b small, a ver, b hor
			}
			return (ax==bx)&&(ay==by||ay==(by+1)||(ay+1)==by);									//a small, b small, a ver, b ver
		}	
		if(a->estHorizontal){
			if(b->estHorizontal){
				return (ay==by)&&(ax==bx||ax==(bx+1)||ax==(bx+2)||(ax+1)==bx);		//a small, b tall, a hor, b hor
			}
			return (ax==bx||(ax+1)==bx)&&(ay==by||ay==(by+1)||ay==(by+2));			//a small, b tall, a hor, b ver
		}
		if(b->estHorizontal){
			return (ay==by||(ay+1)==by)&&(ax==bx||ax==(bx+1)||ax==(bx+2));			//a small, b tall, a ver, b hor
		}
		return (ax==by)&&(ay==by||ay==(by+1)||ay==(by+2)||(ay+1)==by);				//a small, b tall, a ver, b ver
	}

	if(b->small){
		if(a->estHorizontal){
			if(b->estHorizontal){
				return (ay==by)&&(bx==ax||bx==(ax+1)||bx==(ax+2)||(bx+1)==ax);//a tall, b small, a hor, b hor
			}
			return (ay==by||ax==(bx+1))&&(ay==by||by==(ay+1)||by==(ay+2));//a tall, b small, a hor, b ver
		}
		if(b->estHorizontal){
			return (ay==by||(ay+1)==by||(ay+2)==by)&&(ax==bx||ax==(bx+1));//a tall, b small, a ver, b hor
		}
		return (ax==bx)&&(ay==by||(ay+1)==by||ay==(by+1)||(ay+2)==by);//a tall, b small, a ver, b ver
	}

	if(a->estHorizontal){
		if(b->estHorizontal){
			return (ay==by)&&((ax+2)==bx||(ax+1)==bx||ax==bx||ax==(bx+1)||ax==(bx+2));//a tall, b tall, a hor, b hor
		}
		return (ay==by||ay==(by+1)||ay==(by+2))&&(ax==bx||(ax+1)==bx||(ax+2)==bx);//a tall, b tall, a hor, b ver
	}
	if(b->estHorizontal){
		return (by==ay||by==(ay+1)||by==(ay+2))&&(bx==ax||(bx+1)==ax||(bx+2)==ax);//a tall, b tall, a ver, b hor
	}
	return (ax==bx)&&((by+2)==ay||(by+1)==ay||by==ay|by==(ay+1)||by==(ay+2));//a tall, b tall, a ver, b ver
}
/*
int get_x(cpiece p);

int get_y(cpiece p);

int get_height(cpiece p);

int get_width(cpiece p);

bool is_horizontal(cpiece p);
*/
