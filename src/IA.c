#include "../header/IA.h"

void manageEnnemies(Map* map){

	int level = map->characters->current->level; //We get the level of the player to define the difficulty
	int numberOfEnnemies = size(map->characters) - 1;

	//If there is not enough ennemies, we add them
	if(numberOfEnnemies < level * level){
		int numberToAdd = level * 2 - numberOfEnnemies;
		
		int i;
		for(i = 0; i < numberToAdd; ++i){
			createEnnemy(map, level);
		}
	}
}

void createEnnemy(Map* map, int level){

	//We select the position where the ennemy will appear
	int width = map->width;
	int height = map->height;

	SDL_Rect *pos = malloc(sizeof(SDL_Rect));

	do{
		pos->x = (rand() * PX_W)%width;
		pos->y = (rand() * PX_H)%height;
	}while(!isBuilding(map->buildings, pos));

	printf("%d %d\n", pos->x, pos->y);

	Character* ch = createChar(10 * level, 10 * (level-1), 5 * level, 0, 0, pos->x, pos->y, PX_W, PX_H, NULL);
	addChar(map->characters, ch);
}