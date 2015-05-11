#ifndef main_h 
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "Map.h"
#include "Globals.h"
#include "IA.h"

int main();
void managing_event(SDL_Window * main_screen, SDL_Renderer *rendu);
void init_texture(SDL_Renderer *rendu, SDL_Texture *tableau[]);
void init_texture_attack(SDL_Renderer *rendu, SDL_Texture *tabl[]);
void init_type_attack(SDL_Renderer *rendu, SDL_Texture *tableau[]);
void test_key(int key[], SDL_Rect *position);
void destroy_texture(int taille, SDL_Texture *tableau[]);
void compute_tram(int *j, int *trame);
void changeTypeSpell (int key[], TypeSpell **tab_typeSpell, TypeSpell **current_type);
void init_texture_ennemy(SDL_Renderer *rendu, SDL_Texture *tabl[]);
void deleteSpell2(ListSpell *current_list, Map *map);

#endif
