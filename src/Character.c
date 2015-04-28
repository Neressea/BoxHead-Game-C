#include "../header/Character.h"

/**
* Move the character
*/
void move(Character *p, int key[]){
	if (key[0] && key[2]){
		p->pos->y -= SPEED;
		p->pos->x -= SPEED;
	}
	if (key[0] && key[3]){
		p->pos->y -= SPEED;
		p->pos->x += SPEED;
	}
	if (key[0] && !key[3] && !key[2]){
		p->pos->y -= SPEED;
	}
	
	if (key[1] && key[2]){
		p->pos->y += SPEED;
		p->pos->x -= SPEED;
	}
	if (key[1] && key[3]){
		p->pos->y += SPEED;
		p->pos->x += SPEED;
	}
	if (key[1] && !key[3] && !key[2]){
		p->pos->y += SPEED;
	}
		
	if (key[2] && !key[0] && !key[1]){
		p->pos->x -= SPEED;
	}
	if (key[3] && !key[0] && !key[1]){
		p->pos->x += SPEED;
	}
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

int size(ListChar *characters){
	int nb=0;

	ListChar* ch = characters;
	while(ch != NULL){
		ch = ch->next;
		nb++;
	}

	return nb;
}

void addChar(ListChar *characters, Character* ch){

	ListChar *ennemy = malloc(sizeof(ListChar));

	while(characters->next != NULL) characters = characters->next;

	ennemy->current = ch;
	ennemy->next = NULL;

	characters->next = ennemy;
}