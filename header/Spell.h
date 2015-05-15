#ifndef spell_h
#define spell_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
	int time;
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
void deleteSpell(ListSpell *current_list);
void lanceattack(ListSpell *current_list, int *f, TypeSpell *current_type, int key[], int x, int y);
TypeSpell *init_typeSpell(int attack, int id, int rate, int ammo);
void Blit_attack(ListSpell *current_list,SDL_Renderer *rendu, SDL_Texture *tableau[]);
ListSpell *init_listspell();
void update_blitmap (Move* move, SDL_Rect *position);
void manageSpellType(TypeSpell *current_type, SDL_Renderer *rendu, SDL_Texture *texture_type[], TTF_Font* font);
void updateSpell(ListSpell *current_list, Move* move, SDL_Window *main_screen);
void destroyListSpell(ListSpell* ls);
void destroySpell(Spell* s);

#endif
