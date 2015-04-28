#include "../header/Character.h"

/**
* Move the character
*/
void move(Character p, int x, int y){

}

/**
* p1 attacks p2
*/
void attackCharacter(Character p1, Character p2){

}

/**
* p attacks the building b
*/
void attackBuilding(Character p, Building b){
	
}

Character *createChar(int hp, int defense, int attack, int level, int xp, int pos_x, int pos_y, ListSpell *spells){
	Character *c = malloc(sizeof(Character));
	c->hp = hp;
	c->defense = defense;
	c->attack = attack;
	c->level = level;
	c->xp = xp;
	c->pos = malloc(sizeof(SDL_Rect));
	c->pos->x = pos_x;
	c->pos->y = pos_y;
	c->spells = spells;

	return c;
}