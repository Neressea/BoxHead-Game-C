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

//Tous les sorts sont stockes dans un liste chainee pour faciliter leur "collage sur l'ecran". Chaque sort possède sa position actuelle et sa direction. 

Spell* createSpell(TypeSpell *type, int *direction, int x, int y);
//Fonction qui alloue un nouveau Spell en memoire
void deleteSpell(ListSpell *current_list);
//Fonction qui detruit un spell en memoire tout en laissant intact la structure de la ligne chainee contenant les sorts
void lanceattack(ListSpell *current_list, int *f, TypeSpell *current_type, int key[], int x, int y);
//Fonction qui selon la direction actuelle et les touches appuyées ajoute un sort dans la liste chainee des sorts
TypeSpell *init_typeSpell(int attack, int id, int rate, int ammo);
//Fonction qui creer un nouveau type de sort
void Blit_attack(ListSpell *current_list,SDL_Renderer *rendu, SDL_Texture *tableau[]);
//Fonction qui parcourt une liste chaine contenant les sorts et les colle sur l'ecran
ListSpell *init_listspell();
//Fonction qui initialise la liste de sorts lancees
void update_blitmap (Move* move, SDL_Rect *position);
//Fonction qui recalcule une position sur l'ecran en fonction du mouvement de la carte
void manageSpellType(TypeSpell *current_type, SDL_Renderer *rendu, SDL_Texture *texture_type[], TTF_Font* font);
//Fonction qui gere l'affiche du type de sort actuelle ainsi que l'affiche du nombre de sort restant
void updateSpell(ListSpell *current_list, Move* move, SDL_Window *main_screen);
//Fonction qui calcule les mouvements des sorts en fonction de leur direction et des mouvements de la carte
void destroyListSpell(ListSpell* ls);
void destroySpell(Spell* s);
//Fonction qui libere la memoire utilise par la liste et par un sort

#endif
