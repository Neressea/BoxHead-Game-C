#ifndef perso_h
#define perso_h
#endif

#include "Weapon.h"
#include "Building.h"

/**
* This struct defines what a character is, for the main char and ennemies.
* hp : points of life. When comes to 0, the char dies.
* defense : 
* attack : attack points
* level : the current level of the character
* xp : the experience of the char
* pos_x, pos_y : the position of the character
*/
typdef struct
{
	int hp;
	int defense;
	int attack;
	int level; //?
	int xp;
	int pos_x, pos_y;
	Arme weapon;
}Character;

typedef struct ListChar{
	Character current;
	struct ListChar* next;
};


/**
* Move the character
*/
void move(Character p, x, y);

/**
* p1 attacks p2
*/
void attack(Character p1, Character p2);

/**
* p attacks the building b
*/
void attack(Character p, Building b);