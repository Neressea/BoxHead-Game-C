#ifndef map_h
#define map_h

#include "Building.h"
#include "Character.h"
#include "Main.h"

/**
* Defines what the map is.
* list_buildings : List of the buildings on the map
* lit_char : List of the characters on the map
* width, length : size of the map
* background : name of the background of the map
* split_pos : position of the map that is in the left-up corner
*/
typedef struct{
	ListBuilding *buildings;
	ListChar *characters;
	int width, length; //?
	char* background;
	int split_pos;
}Map;

/**
* Load a map from a text file.
*/
Map load(char* nom_fichier);

/**
* Print the map on the screen
*/
void show(Map c);

#endif

