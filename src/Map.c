#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>

#include "../header/Map.h"

/**
* Load a map from a text file.
*/
Map load(char* filename){
	Map map;
	map.buildings = NULL;
	map.characters = NULL;
	map.background = NULL;
	map.split_pos = 0;
	map.width = 0;
	map.length = 0;

	//We open the file containing the map
	FILE* file = NULL;
	file = fopen(strcat("./maps/", filename), "r");

	if(!file){
		fprintf(stderr, "Can't open file %s\n", filename);
		exit(1);
	}

	//We read the file line by line : the first line is the name of the background
	char* line;
	fgets(line, 100, file);

	if(line == NULL){
		fprintf(stderr, "Non well-formated file : %s\n", filename);
		exit(2);
	}

	map.background = line;

	//Then we read the other lines that represents each "line" of the map
	int x=0, y=0;
	while(fgets(line, 100, file) != NULL){
		int i=0;
		while(line[i] != '\0'){
			if(line[i] == '1'){
				ListBuilding* lb;
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
			x++;
		}
		y++;
	}

	fclose(file);

	return map;
}

/**
* Print the map on the screen
*/
void show(Map c){
	
}


