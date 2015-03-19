#ifndef carte_h 
#define carte_h
#endif

#include "Batiment.h"
#include "Perso.h"

/**
* Defines what the map is.
*/
typedef struct{

}Map;

/**
* Load a map from a text file.
*/
Map load(char* nom_fichier);

/**
* Print the map on the screen
*/
void show(Map c);

