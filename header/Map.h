#ifndef map_h
#define map_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Building.h"
#include "Character.h"
#include "Main.h"

#define FRAME 2

/**
* Defines what the map is.
* buildings : List of the buildings on the map
* characters : List of the characters on the map
* textures : Array of textures (0 : background, 1 : tower)
* width, length : size of the map
* corner_split : position of the map that is in the left-up corner
*/
typedef struct{
	ListBuilding *buildings;
	ListChar *characters;
	SDL_Texture **textures;
	int width, height; //?
	int corner_x, corner_y;
}Map;

/**
* Load a map from a text file.
*/
Map load(SDL_Renderer *rendu, char* nom_fichier);

/**
* Print the map on the screen
*/
void show(SDL_Renderer *rendu, Map c);

#endif

