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
	int id;
}TypeSpell;

typedef struct{
	int direction;
	int time;	
	TypeSpell *type;
	SDL_Rect *pspell;
}Spell;

typedef struct ListSpell ListSpell;
struct ListSpell{
	Spell *currentSpell;
	struct ListSpell* nextSpell;
};

Spell* createSpell(TypeSpell *type, int *direction, int x, int y);
void updateSpell(ListSpell *current_list, Move* move, SDL_Window *main_screen);
void deleteSpell(ListSpell *current_list);
void lanceattack(ListSpell *current_list, int *f, TypeSpell *current_type, int key[]);
TypeSpell *init_typeSpell(int attack, int id, int rate);
void Blit_attack(ListSpell *current_list,SDL_Renderer *rendu, SDL_Texture *tableau[]);
ListSpell *init_listspell();
void update_blitmap (Move* move, SDL_Rect *position);

#endif
