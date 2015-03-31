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
	int rate; //?
}Spell;

void compute_attack(SDL_Rect *pattack[],int *f, int key[]);
void blit_attack(SDL_Rect *pattack[], SDL_Renderer *rendu, SDL_Texture *tableau[]);
void init_attack(SDL_Rect *pattack[]);


#endif