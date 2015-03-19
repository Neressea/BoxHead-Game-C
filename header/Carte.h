#ifndef carte_h 
#define carte_h
#endif

#include "Batiment.h"
#include "Perso.h"

/**
* Defines what the map is.
* list_buildings : List of the buildings on the map
* lit_char : List of the characters on the map
* width, length : size of the map
*/
typedef struct{
	ListBuilding *list_buildings;
	ListChar *lit_char;
	int width, length;
}Map;

/**
* Load a map from a text file.
*/
Map load(char* nom_fichier);

/**
* Print the map on the screen
*/
void show(Map c);

