#ifndef building_h
#define building_h

//#include "Character.h"

/**
* Struct that defines the buildings of the map.
* hp : health points if the building
* pos_x, pos_y : the position of the building (in cases and not pixels)
* attack : the attack if it is a tower. If it is only a defense, -1.
* defense : the defense of the building
*/
typedef struct{
	int hp;
	int pos_x, pos_y;
	int attack;
	int defense;
}Building;

typedef struct ListBuilding ListBuilding;
struct ListBuilding{
	Building current;
	struct ListBuilding* next;
};

//void attackFromBuildToChar(Building b, Character p);

#endif