#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "piece.h"
//yolo
//ofijoifjoiefjezoijez
//sdofkjsdoikdsfo

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
	if(movement_is_allowed(p,d){
		switch (d) {
			case UP:
				while (distance !=0){
					if (!can_move(p, UP)){
						break;
					}
					//code bouger
					distance-=1;
					}
				break;


			case DOWN:
				while (distance !=0){
					if (!can_move(p, DOWN)){
						break;					}
					//code bouger
					distance-=1;
				}
				break;


			case RIGHT:
				while (distance !=0){
					if (!can_move(p, RIGHT)){
						break;
					}
					//code bouger
					distance-=1;
				}
				break;


			case LEFT:
				while (distance !=0){
					if (!can_move(p, LEFT)){
						break;
					}
					//code bouger
					distance-=1;
				}
				break;
			}
		}
	}	
	printf("Not moved");
	break;
}

bool can_move(piece p, dir d){
	switch(d){
		case UP:
			
			
	}
	
}

bool movement_is_allowed(piece p, dir d){
	if (((d==UP || d==down)&&(p.estHorizontal))||((d==LEFT || d==RIGHT)&&(!p.estHorizontal))){	
		return false;
	return true;
}


/*	
int i = 1;
if (!p.small){		//prend en compte la taille de la pièce pour faire les tests de déplacements
	i+=1;
}	
if ((d==UP)&&(p.ord==5-i)||(d==DOWN)&&(p.ord==0)||(d==LEFT)&&(p.abs==0)||(d==RIGHT)&&(p.abs==5-i)){
	return false;
}
*/



/*
bool intersect(cpiece p1, cpiece p2);

int get_x(cpiece p);

int get_y(cpiece p);

int get_height(cpiece p);

int get_width(cpiece p);

bool is_horizontal(cpiece p);
*/
