#ifndef keybinds_h
#define keybinds_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Globals.h"

void keybinds(FILE* fichier, int* keyBindings);

int isTaken(int new, int pos, int* keyBindings);

int configureKeybind(int nb, int* keyBindings, int key);

int isWellFormed(int* keyBindings);

void createDefaultKeybinds();

void createCustomKeybinds();

int initialise_keybinds(int* keyBindings);

#endif
