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
void load(SDL_Renderer *rendu, Map* map, char* filepath){

	map->buildings = NULL;
	map->characters = NULL;
	map->textures = malloc(sizeof(SDL_Texture *) * NB_TEXTS_MAP);
	map->corner = malloc(sizeof(SDL_Rect));
	map->corner->x = 0;
	map->corner->y = 0;
	map->width = 0;
	map->height = 0;

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
		fprintf(stderr, "Non well-formated file (background) : %s\n", filepath);
		exit(2);
	}

	//We load the texture of the background
	char path [120] = "./images/sprites/";
	strcat(path, line);
	path[strlen(path)-1] = '\0';
	map->textures[0] = IMG_LoadTexture(rendu, path);

	if(map->textures[0] == NULL){
		fprintf(stderr, "Error loading the background : %s\n", SDL_GetError());
		exit(2);
	}

	fgets(line, 100, file);

	if(line == NULL){
		fprintf(stderr, "Non well-formated file (walls) : %s\n", filepath);
		exit(2);
	}

	char path2[120] = "./images/sprites/";
	strcat(path2, line);
	path2[strlen(path2)-1] = '\0';
	map->textures[1] = IMG_LoadTexture(rendu, path2);

	if(map->textures[1] == NULL){
		fprintf(stderr, "Error loading the background : %s\n", SDL_GetError());
		exit(2);
	}

	free(line);
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
				lb->next = map->buildings;
				map->buildings = lb;

			}
			i++;
			x++;
		}
		x=0;
		y++;
	}

	map->width=PX_W * x;
	map->height=PX_H * y;

	//We set the left up corner of the map
	map->corner->x = (int) (map->width / 2 - SCREEN_W/2);
	map->corner->y = (int) (map->height / 2 - SCREEN_H/2);

	fclose(file);
}

/**
* Free the map
*/
void destroyMap(Map* map){
	//We free the corner
	free(map->corner);

	//We free the textures
	int i=0;
	for (i = 0; i < NB_TEXTS_MAP; ++i){
		free(map->textures[i]);
	}

	free(map->textures);

	//We free the list of buildings
	ListBuilding *b = map->buildings;
	ListBuilding *nextB = NULL;
	while(b != NULL){
		nextB = b->next;
		free(b);
		b = nextB;
	}

	//We free the list of characters
	ListChar* lc = map->characters;
	ListChar* nextC = NULL;
	while(lc != NULL){
		nextC = lc->next;
		free(lc);
		lc = nextC;
	}
}

/**
* Print the map on the screen
*/
void show(SDL_Renderer *rendu, Map* map){
	
	//We go through all cases to flip.

	int begin_x = - FRAME * PX_W;
	int begin_y = - FRAME * PX_H;

	int end_x = SCREEN_W + FRAME * PX_W;
	int end_y = SCREEN_H + FRAME * PX_H;

	int i, j;
	SDL_Rect pos;
	for (i = begin_x; i <= end_x; i+=PX_W){
		for (j = begin_y; j <= end_y; j+=PX_H){
			pos.h=PX_H;
			pos.w=PX_W;
			pos.x = i;
			pos.y = j;

			if(isBuilding(map->buildings, pos)){
				SDL_RenderCopy(rendu, map->textures[1], NULL, &pos);
			}else{
				SDL_RenderCopy(rendu, map->textures[0], NULL, &pos);
			}	
		}
	}
}

int isBuilding(ListBuilding* buildings, SDL_Rect pos){
	int is = 0;

	ListBuilding* b = buildings;

	//We loop whilewe have not found if it is a building, or until we are to the end of the list 
	while(is==0 && b != NULL){

		if(b->current.pos_x * PX_W == pos.x && b->current.pos_y * PX_H == pos.y)
			is = 1;

		//If we are after the position of the case, it is not a building
		if(b->current.pos_x * PX_W < pos.x && b->current.pos_y * PX_H < pos.y)
			break;

		b = b->next;
	}

	return is;
}

void saveMap(Map *map){
	map->corner = NULL; //temp
}
	


