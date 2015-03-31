#include "../header/Building.h"


Building* createBuilding(int x, int y, int hp, int attack, int defense){
	Building* b = malloc(sizeof(Building));
	b->hp = hp;
	b->x=x;
	b->y=y;
	b->attack=attack;
	b->defense=defense;

	return b;
}
