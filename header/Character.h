#ifndef char_h
#define char_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "Spell.h"
#include "Building.h"
#include "Globals.h"
#include "Main.h"


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
	SDL_Rect *pos;
	ListSpell* spells;
}Character;

typedef struct ListChar ListChar;
struct ListChar{
	Character *current;
	struct ListChar* next;
};


/**
* Move the character
*/
void move(Character *p, int key[]);

/**
* p1 attacks p2
*/
void attackCharacter(Character p1, Character p2);

/**
* p attacks the building b
*/
void attackBuilding(Character p, Building b);

Character* createChar(int hp, int defense, int attack, int level, int xp, int pos_x, int pos_y, int w, int h, ListSpell *spell);

int size(ListChar *characters);

void addChar(ListChar *characters, Character* ch);

void showCharacters(SDL_Renderer *rendu, ListChar* characters, SDL_Rect *corner, SDL_Texture*** texture_chara, int key[], int* direction);

SDL_Texture* update_texture(int key[], SDL_Texture *tableau[], int *trame, int *f);

int text_move(int *trame);

void compute_tram(int *j, int *trame);

ListChar* removeKilled(ListChar* characters);

void add_xp(Character* ch, int dam);

void destroyChara(Character* c);

void destroyListChara(ListChar *lc);

#endif
