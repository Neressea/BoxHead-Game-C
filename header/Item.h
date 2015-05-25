#ifndef item_h 
#define item_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "Globals.h"
#include "Spell.h"
#include "Character.h"

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

//On utilise une liste chainee qui contient tous les items sur la carte

void poseItem(ListItem *listitem, int x, int y);
//Fonction qui pose un item sur la carte.(On ajoute un item cree a la liste chainee)

Item* createItem(int id, int x, int y);
//Fonction qui alloue en memoire la place d'un item

void updateItem(ListItem *listitem, SDL_Renderer *rendu, SDL_Texture *tableau[], Move* move);
//Fonction qui recalcule la position sur l'ecran des items en fonction du deplacement de la carte

ListItem* init_listItem();
//Fonction qui initialise la liste d'items.

int catchItem(SDL_Rect* pos, ListItem *listitem, SDL_Rect *corner, int Itemcaught[]);
//Fonction qui gere les collisions du heros avec un item pour que celui-ci l'attrape

void effect_item(int Itemcaught[], TypeSpell **tab_typeSpell, Character * hero);
//Fonction qui applique l'effet de l'item aux caracteristiques du personnage

void destroyListItem(ListItem *li);
void destroyItem(Item *i);

//Fonction qui libere la place d'un item et d'une liste d'item en memoire

#endif
