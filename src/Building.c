#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../header/Building.h"


Building* createBuilding(int hp, int x, int y, int attack, int defense){
	Building* b = malloc(sizeof(Building));
	b->hp = hp;
	b->x=x;
	b->y=y;
	b->attack=attack;
	b->defense=defense;

	return b;
}
