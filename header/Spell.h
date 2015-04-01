#ifndef spell_h
#define spell_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "Globals.h"


/**
* Defines what a spell is.
* attack : points of attack
* ammo : number of ammo left
* rate : rate of fire if a gun, -1 else.
*/

typedef struct{
	int attack;
	int ammo;
	int rate;
}TypeSpell;

typedef struct{
	int direction;
	int time;	
	TypeSpell *type;
	SDL_Rect *pspell; //?
}Spell;

typedef struct ListSpell ListSpell;
struct ListSpell{
	Spell *currentSpell;
	struct ListSpell* nextSpell;
};

Spell* createSpell(TypeSpell *type, int direction, int x, int y);
void updateSpell(ListSpell *current_list);

#endif
