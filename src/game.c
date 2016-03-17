#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "useful_functions.h"

struct game_s {
    int width;
    int height;
    int nb_pieces;
    int nb_moves;
    piece *piece_list;
    char** grid;
};

typedef const struct game_s* cgame;

game new_game (int width, int height, int nb_pieces, piece *pieces){
    game g = malloc(sizeof (struct game_s));
    g->width = width;
    g->height = height;
    g->nb_pieces = nb_pieces;
    g->nb_moves = 0;
    g->piece_list = pieces;
    g->grid = new_grid(width, height, pieces);
    return g;
}

void delete_game(game g) {
    for (int i = 0 ; i < g->nb_pieces; i++)
        delete_piece(g->piece_list[i]);
    delete_grid(g->grid);
    free(g);
}

void copy_game(cgame src, game dst) {
    dst->nb_pieces = src->nb_pieces;
    dst->nb_moves = src->nb_moves;
    dst->piece_list = src->piece_list;
    dst->width = src->width;
    dst->height = src->height;
}

int game_nb_pieces(cgame g) {
    return g->nb_pieces;
}

cpiece game_piece(cgame g, int piece_num) {
    return g->piece_list[piece_num];
}

bool game_over_hr(cgame g) {
    return (get_x(g->piece_list[0]) == g->width/2) && (get_y(g->piece_list[0]) == 0);
}
//vérifie que la pièce ne se déplace pas hors de la grille
bool out_of_grid(cpiece p, cgame g) {         
    int abs = get_x(p);
    int ord = get_y(p);
    return (abs < 0 || abs+get_width(p) > game_width(g)||(ord < 0 || ord+get_height(p) > game_height(g)));      
    //exemple : game_width(g) = 6 -> tableau de 0 à 5, get_width = 2 donc piece occupe case 4 et 5 (donc get_width(g)-2)
}

//ajouter vérification pour pas depasser les bords
bool play_move(game g, int piece_num, dir d, int distance) {
    piece p = g->piece_list[piece_num];
    if(!movement_is_allowed(p, d)){
        printf("Mouvement impossible : L'orientation de la pièce et la direciton de son déplacement sont incompatibles.\n\n");
        return false;
    }
    int distance_parcourue =0;
    while (distance != 0) {
        move_piece(p, d, 1);
        g->nb_moves += 1;
        distance--;
        distance_parcourue++;
        for (int i = 0; i < game_nb_pieces(g); ++i) {
            if (p == g->piece_list[i]){
                i++;
                if(i>=game_nb_pieces(g))
                    break;
            }
            if (intersect(p, game_piece(g, i))) {
                printf("Mouvement impossible : La voiture %d empêche le déplacement de la voiture %d.\n\n", i, piece_num);
                move_piece(p, d, distance_parcourue*-1);
                g->nb_moves -= distance_parcourue;
                return false;
            }
            if (out_of_grid(p, g)) {
                printf("Mouvement impossible : La piece %d est au bord de la grille.\n\n", piece_num);
                move_piece(p, d, distance_parcourue*-1);
                g->nb_moves -= distance_parcourue;
                return false;
            }
        }
    }
    return true;
}

int game_nb_moves(cgame g) {
    return g->nb_moves;
}

int game_width(cgame g){
    return g->width;
}

int game_height(cgame g){
    return g->height;
}

int game_square_piece (game g, int x, int y){
    for (int i = 0; i < g->nb_pieces; i++){
        piece p = g->piece_list[i];
        if (get_x(p) <= x && get_y(p) <= y){
            if (get_x(p)+get_width(p)-1 >= x && get_y(p)+get_height(p)-1 >= y){         // [x,y] compris entre coordonnée bottom/left et top/right de la piece
                return i;
            }
        }
    }
    return -1;
}

//--------------------------------
//---------### GRID ###-----------
//--------------------------------

char** new_grid(int width, int height, piece *piece_list){
    char** grid [width][height];
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			grid[i][j]='.';
		}
	}
        set_pieces(grid, piece_list);
	return grid;
}

//affiche graphiquement la grille sur le terminal
void show_grid(char** grid){
	for(int abs=5;abs>=0;abs--){
		for(int ord=0; ord<6;ord++){
			char c = grid[ord][abs];
			printf("%c ", c);
		}
		printf("\n");
	}
        printf("\nNombre de mouvements : %d\n----------\n\n", game_nb_moves(grid->g));
}
//mets les pieces du tableau sur la grille
void set_pieces(char** grid, piece *piece_list){
    for (int i=0; i<sizeof(piece_list)/sizeof(piece_list[0]);i++){
        add_piece(grid, piece_list[i], i);
    }
}

//ajouter graphiquement une piece sur la grille
void add_piece(char** grid, cpiece p, int piece_num){
    for (int i=get_x(p) ; i<get_width(p);++i){
        for (int j=get_y(p);j<get_height(p);++j){
            grid[i][j]=piece_num+48;
        }
    }
}

//efface graphiquement une piece sur la grille
void delete_pieces(char** grid, cpiece p, int piece_num){
    for (int i=get_x(p) ; i<get_width(p);++i){
        for (int j=get_y(p);j<get_height(p);++j){
            grid[i][j]=piece_num+48;
        }
    }
}

//initialise graphiquement la case avec un int
void set_cell_int(char** grid, int x, int y, int val){
    grid[x][y]=val+48;
}

//reinitialise graphiquement la case
void set_cell_empty(char** grid, int x, int y){
    grid[x][y]='.';
}

//effectue le deplacement graphique de la piece
void move(cgame g, char** grid, int piece_num, dir d, int distance){
    delete_piece_grid(grid, piece_num);
    if(play_move(g, piece_num, d, distance))
        add_piece(grid, piece_num);
    else
        add_piece(grid, piece_num);
    show_grid(grid);
}