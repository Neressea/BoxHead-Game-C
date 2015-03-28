#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
		x=0;
		while(line[i] != '\0'){
			if(line[i] == '1'){
				ListBuilding* lb = malloc(sizeof(ListBuilding));
				Building b;

				//We add the new building to the list
				b.hp = -1; //They are unbreakable
				b.attack = -1; //They don't attack
				b.defense = -1;
				b.pos_x = x * PX_W;
				b.pos_y = y * PX_H;

				lb->current = b;

				//We change the head of the list
				lb->next = map->buildings;
				map->buildings = lb;
			}
			i++;
			x++;
		}
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
	int i;
	for(i = 0; i < NB_TEXTS_MAP; i++){
		SDL_DestroyTexture(map->textures[i]);
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

	//We compute the shift bewteen the map and the view
	int shift_x = map->corner->x % PX_W;
	int shift_y = map->corner->y % PX_H;

	//We compute the position of the case in the map (the bounds)
	SDL_Rect* map_pos = malloc(sizeof(SDL_Rect));

	int begin_x = map->corner->x - shift_x - (NB_SPRITES_BLITTED * PX_W);
	int begin_y = map->corner->y - shift_y - (NB_SPRITES_BLITTED * PX_H);

	int end_x = begin_x + (SCREEN_W - SCREEN_W % PX_W) + NB_SPRITES_BLITTED * PX_W;
	int end_y = begin_y + (SCREEN_H - SCREEN_H % PX_H) + NB_SPRITES_BLITTED * PX_H;

	//We compute the position where we blit the surface
	SDL_Rect* blit_pos = malloc(sizeof(SDL_Rect));
	blit_pos->x = - (NB_SPRITES_BLITTED * PX_W);
	blit_pos->y = - (NB_SPRITES_BLITTED * PX_H);
	blit_pos->w = PX_W;
	blit_pos->h = PX_H;

	//We blit all the necessary textures
	int i=0, j=0;
	for (i = begin_x; i < end_x; i+=PX_W){

		//We reinitialize y
		blit_pos->y=- (NB_SPRITES_BLITTED * PX_H);

	 	for (j = begin_y; j < end_y; j+=PX_H){

	 		//We check the type of the case to blit
	 		if(isBuilding(map->buildings, map_pos)){
	 			SDL_RenderCopy(rendu, map->textures[1], NULL, blit_pos);
	 		}else{
	 			SDL_RenderCopy(rendu, map->textures[0], NULL, blit_pos);
	 		}

	 		map_pos->y = j;
	 		blit_pos->y += PX_H;

	 	}

	 	blit_pos->x += PX_W;
	 	map_pos->x = i;

	 }

	 free(map_pos);
	 free(blit_pos);
}

int isBuilding(ListBuilding* buildings, SDL_Rect* pos){
	int is = 0;

	ListBuilding* b = buildings;

	//We loop whilewe have not found if it is a building, or until we are to the end of the list 
	while(is==0 && b != NULL){

		if(b->current.pos_x == pos->x && b->current.pos_y == pos->y){
			is = 1;
		}

		//If we are after the position of the case, it is not a building
		if(b->current.pos_x < pos->x && b->current.pos_y < pos->y)
			break;

		b = b->next;
	}

	return is;
}

void saveMap(Map *map){
	map->corner = NULL; //temp
}

void moveMap(Map* map, int key[]){

	if (key[0] && key[2]){
		map->corner->y -= SPEED;
		map->corner->x -= SPEED;
	}
	if (key[0] && key[3]){
		map->corner->y -= SPEED;
		map->corner->x += SPEED;
	}
	if (key[0] && !key[3] && !key[2]){
		map->corner->y -= SPEED;
	}
	
	if (key[1] && key[2]){
		map->corner->y += SPEED;
		map->corner->x -= SPEED;
	}
	if (key[1] && key[3]){
		map->corner->y += SPEED;
		map->corner->x += SPEED;
	}
	if (key[1] && !key[3] && !key[2]){
		map->corner->y += SPEED;
	}
		
	if (key[2] && !key[0] && !key[1]){
		map->corner->x -= SPEED;
	}
	if (key[3] && !key[0] && !key[1]){
		map->corner->x += SPEED;
	}
}
	


