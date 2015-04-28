#ifndef main_h 

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Map.h"
#include "Globals.h"

int main();
void managing_event();
void init_texture(SDL_Renderer *rendu, SDL_Texture *tableau[]);
void init_texture_attack(SDL_Renderer *rendu, SDL_Texture *tabl[]);
void init_type_attack(SDL_Renderer *rendu, SDL_Texture *tableau[]);
void test_key(int key[], SDL_Rect *position);
void destroy_texture(int taille, SDL_Texture *tableau[]);
SDL_Texture* update_heros(int key[], SDL_Texture *tableau[], int *trame, int *f);
void compute_tram(int *j, int *trame);
int text_move(int *trame);
void changeTypeSpell (int key[], TypeSpell **tab_typeSpell, TypeSpell **current_type);

#endif
