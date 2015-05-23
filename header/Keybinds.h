#ifndef keybinds_h
#define keybinds_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Globals.h"

void keybinds(FILE* fichier, int* keyBindings);

int isTaken(int new, int pos, int* keyBindings);

void configureKeybind(int nb, int* keyBindings);

void configureKeybinds(int* keyBindings);

int isWellFormed(int* keyBindings);

void createDefaultKeybinds();

int initialise_keybinds(int* keyBindings);

#endif
