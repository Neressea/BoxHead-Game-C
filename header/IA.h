#ifndef ia_h
#define ia_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Map.h"
#include "Character.h"

/**
* Manage the number and the diffculty of the ennemies.
*/
void manageEnnemies(Map* map);

/**
* Create a new ennemy on the map. Called by manageEnnemies()
*/
void createEnnemy(Map* m, int level);

/**
* Get the number of ennemies there is on the map.
*/
int numberOfEnnemies(Map* map);

/**
* Move all the ennemies in function of the position of th hero.
* At the beginning, we wanted to use Dijkstra, but unfortunately we hadn't enough time to.
*/
void moveEnnemy(ListBuilding* b, Character* heros, Character *ennemy, int key[]);

/**
* Deplace a particular ennemy. Check the collisions.
*/
void deplaceEnnemy(ListBuilding* b, int key[],Character *ennemy);

#endif