#ifndef building_h
#define building_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "Globals.h"

/**
* Struct that defines the buildings of the map.
* hp : health points if the building
* x, y : the position of the building in pixels
* attack : the attack if it is a tower. If it is only a defense, set at -1.
* defense : the defense of the building.
*/
typedef struct{
	int hp;
	int x, y;
	int attack;
	int defense;
}Building;

/**
* Defines a list of buildings.
* current : the current building of the list
* next : the next building of the list. 
*/
typedef struct ListBuilding ListBuilding;
struct ListBuilding{
	Building* current;
	struct ListBuilding* next;
};

/**
* Constructor  of Building.
* x, y : the position of the building
* hp : health points if the building
* attack : the attack if it is a tower. If it is only a defense, set at -1.
* defense : the defense of the building.
*/
Building* createBuilding(int x, int y, int hp, int attack, int defense);

/**
*/
void destroyListBuild(ListBuilding* lb);

#endif
