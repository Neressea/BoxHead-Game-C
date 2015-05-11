#ifndef map_h
#define map_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Building.h"
#include "Character.h"
#include "Main.h"
#include "Globals.h"

/**
* Defines what the map is.
* buildings : List of the buildings on the map
* characters : List of the characters on the map
* textures : Array of textures (0 : background, 1 : tower)
* width, length : size of the map in pixels
* corner_split : position of the map that is in the left-up corner in pixels
*/
typedef struct{
	ListBuilding *buildings;
	ListChar *characters;
	SDL_Texture **textures;
	int width, height;
	SDL_Rect *corner;
}Map;


/**
* Load a map from a text file.
* rendu : the renderer for which we load a map
* file_name : load a map from a file_name
*/
void load(SDL_Renderer *rendu, Map* map, char* file_name);

/**
* Free all the pointers of a map
* map : the map to destroy
*/
void destroyMap(Map* map);

/**
* Print the map on the screen
* rendu : the renderer where we blit the map
* map : the map tp blit on the renderer
*/
void showMap(SDL_Window* screen, SDL_Renderer *rendu, Map* map);

/**
* buildings : the lst of the buildings of the map
* pos : the position to check
* Return 1 if pos is a building, else 0.
*/
int isBuilding(ListBuilding* buildings, SDL_Rect* pos);

/**
* This function check the folder of maps, determines the name of the file 
* in which it will save the map, create and fill it up.
* m : the map to save in a text file
*/
void save(Map* m);

/**
* Move the map to "follow" the player
* map : the map to move
* key : the input events
*/
void moveMap(SDL_Window *screen,Map* map, int key[], Move* move);

void addWall(Map *map, int x, int y);

/**
* Encircle a map whose size are defined
*/
void encircleMap(Map* map);

int cantMove(ListBuilding* lb, SDL_Rect* pos);

void loadSprite(FILE *file, SDL_Renderer *rendu, SDL_Texture **text, int i);

void turret(Map *map, int x, int y, TypeSpell *current_type, int key[]);

int cantMoveSpell(ListBuilding* lb, SDL_Rect* pos, Spell *spell);

void updateWall(ListBuilding* lb);

#endif

