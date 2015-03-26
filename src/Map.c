#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/Map.h"

//To test the functions
/*int main(int argc, char** argv){

	if(argc != 2){
		fprintf(stderr, "Wrong number of args\n");
		exit (42);
	}
	Map m;
	m = load(argv[1]);

	printf("%s\n", m.background);

	ListBuilding *lb = m.buildings;
	while(lb != NULL){
		printf("%d %d %d %d %d\n", lb->current.hp, lb->current.pos_x, lb->current.pos_y, lb->current.attack, lb->current.defense);

		lb = lb->next;
	}
}*/

/**
* Load a map from a text file.
* filepath : the path to the file
*/
Map load(SDL_Renderer *rendu, char* filepath){

	Map map;
	map.buildings = NULL;
	map.characters = NULL;
	map.textures = malloc(sizeof(SDL_Texture *) * 2);
	map.corner_x = 0;
	map.corner_y = 0;
	map.width = 0;
	map.height = 0;

	//We open the file containing the map
	FILE* file = NULL;
	file = fopen(filepath, "r");

	if(!file){
		fprintf(stderr, "Can't open file %s\n", filepath);
		exit(1);
	}

	//We read the file line by line : the first line is the name of the background
	char* line = malloc(sizeof(char) * 100);
	fgets(line, 100, file);

	if(line == NULL){
		fprintf(stderr, "Non well-formated file : %s\n", filepath);
		exit(2);
	}

	//We load the texture of the background
	char path [120] = "./images/sprites/";
	strcat(path, line);
	map.textures[0] = IMG_LoadTexture(rendu, path);

	if(!map.textures[0]){
		fprintf(stderr, "Error loading the background\n");
		exit(2);
	}

	line = malloc(sizeof(char) * 101); //We keep a char for the '\0'

	//Then we read the other lines that represents each "line" of the map
	int x=0, y=0;
	while(fgets(line, 100, file) != NULL){
		line[strlen(line)] = '\0';
		int i=0;
		while(line[i] != '\0'){
			if(line[i] == '1'){
				ListBuilding* lb = malloc(sizeof(ListBuilding));
				Building b;

				//We add the new buuilding to the list
				b.hp = -1; //They are unbreakable
				b.attack = -1; //They don't attack
				b.defense = -1;
				b.pos_x = x;
				b.pos_y = y;

				lb->current = b;

				//We change the head of the list
				lb->next = map.buildings;
				map.buildings = lb;

			}
			i++;
			x++;
		}
		x=0;
		y++;
	}

	map.width=PX_W * x;
	map.height=PX_H * y;

	//We set the left up corner of the map
	map.corner_x = (int) (map.width / 2 - SCREEN_W/2);
	map.corner_y = (int) (map.height / 2 - SCREEN_H/2);

	fclose(file);

	return map;
}

/**
* Print the map on the screen
*/
void show(SDL_Renderer *rendu, Map c){
	
	
	
}


