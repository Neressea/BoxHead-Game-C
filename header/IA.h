#ifndef ia_h
#define ia_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Map.h"
#include "Character.h"

void manageEnnemies(Map* map);
void createEnnemy(Map* m, int level);
int numberOfEnnemies(Map* map);
void moveEnnemy(ListBuilding* b, Character* heros, Character *ennemy, int key[]);
void deplaceEnnemy(ListBuilding* b, int key[], SDL_Rect* position);

#endif