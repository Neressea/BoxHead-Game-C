#ifndef main_h 
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include <string.h>
#include "Map.h"
#include "Globals.h"
#include "IA.h"
#include "Item.h"
#include "Keybinds.h"

int main();
int managing_event(SDL_Window * main_screen, SDL_Renderer *rendu);
// Fonction qui gere les differents evenements du programme, notamment l'ecran du jeu lui-meme avec la gestion des touches, des differents sprites et les differents ecran

int managing_keybinds(SDL_Window * main_screen, SDL_Renderer *rendu);
// Gestion de la configuration des touches. Le joueur peut choisir grâce à un ecran de selection les differents touches qu'il souhaite assigner à un evenement

void init_texture(SDL_Renderer *rendu, SDL_Texture *tableau[]);
void init_texture_attack(SDL_Renderer *rendu, SDL_Texture *tabl[]);
void init_type_attack(SDL_Renderer *rendu, SDL_Texture *tableau[]);
// Ces fonctions chargent au début de la fonction managing_event les differents sprites necessaires au jeu. Ils n'ont donc plus besoin d'etre recharge ensuite.

void destroy_texture(int taille, SDL_Texture *tableau[]);
//Cette fonction libere la place des differents textures pour eviter notamment les fuites memoires.

void compute_tram(int *j, int *trame);
//Cette fonction calcule la trame actuelle pour donner une impression de mouvement des membres lors du deplacement d'un personnage

void changeTypeSpell (int key[], TypeSpell **tab_typeSpell, TypeSpell **current_type);
//Cette fonction change le type de sort courant selon le type de sort selectionne

void init_texture_ennemy(SDL_Renderer *rendu, SDL_Texture *tabl[]);
//Charge en debut de partie les sprites pour les monstres
void deleteSpell2(ListSpell *current_list, Map *map, ListItem *listitem);
void hero_stat(SDL_Renderer *rendu, TTF_Font* font, Map *map);

#endif
