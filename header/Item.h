#ifndef item_h 
#define item_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "Globals.h"

typedef struct{
	int id;
	int time;	
	SDL_Rect *pitem;
}Item;

typedef struct ListItem ListItem;
struct ListItem{
	Item *current;
	struct ListItem* next;
};

void poseItem(ListItem *listitem, int x, int y);
Item* createItem(int id, int x, int y);
void updateItem(ListItem *listitem, SDL_Renderer *rendu, SDL_Texture *tableau[]);

#endif
