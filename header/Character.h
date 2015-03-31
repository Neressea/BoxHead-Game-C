#ifndef char_h
#define char_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "Spell.h"
#include "Building.h"
#include "Globals.h"

/**
* This struct defines what a character is, for the main char and ennemies.
* hp : points of life. When comes to 0, the char dies.
* defense : 
* attack : attack points
* level : the current level of the character
* xp : the experience of the char
* pos_x, pos_y : the position of the character
*/
typedef struct{
	int hp;
	int defense;
	int attack;
	int level; //?
	int xp;
	int pos_x, pos_y;
	Spell* spell;
}Character;

typedef struct ListChar ListChar;
struct ListChar{
	Character current;
	struct ListChar* next;
};


/**
* Move the character
*/
void move(Character p, int x, int y);

/**
* p1 attacks p2
*/
void attackCharacter(Character p1, Character p2);

/**
* p attacks the building b
*/
void attackBuilding(Character p, Building b);

#endif
