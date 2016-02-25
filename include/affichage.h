#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_
#include <stdbool.h>
#include "piece.h"
#include "game.h"

typedef struct grille_s* grille;


grille new_grille();
void afficher_grille(grille g);

#endif
