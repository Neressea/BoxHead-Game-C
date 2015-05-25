#ifndef keybinds_h
#define keybinds_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Globals.h"

/**
* Load the keybinds in the file.
* fichier : the file where the keybindings are stored.
* keyBindings : Array containing the key bindings.
*/
void keybinds(FILE* fichier, int* keyBindings);

/**
* Check if a key binding is already taken. 
* Returns 0 if that's the case, 1 otherwise.
*/
int isTaken(int new, int pos, int* keyBindings);

/**
* Configure a key and write in the custom key binding file.
*/
int configureKeybind(int nb, int* keyBindings, int key);

/**
* Check the form of the current key binding.
* Returns 0 if it is not well-formed, or else 1.
*/
int isWellFormed(int* keyBindings);

/**
* Create the default file if it is corrupted or missing.
*/
void createDefaultKeybinds();

/**
* Create a basic custom file if it is corrupted or missing.
*/
void createCustomKeybinds();

/**
* Load the key bindings. Check if there is a custom, or else load the default file.
* It also check the formatinon of the file. If it is not well-formed, a new default 
* file is created and loaded.
*/
int initialise_keybinds(int* keyBindings);

#endif
