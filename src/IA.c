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
		pos->x = abs((rand() * PX_W)%width);
		pos->y = abs((rand() * PX_H)%height);
	}while(cantMove(map->buildings, pos));

	Character* ch = createChar(10 * level, 10 * (level-1), 5 * level, 0, 0, pos->x/PX_W, pos->y/PX_H, PX_W, PX_H, NULL);
	printf("%d %d\n", ch->pos->x, ch->pos->y);
	addChar(map->characters, ch);
}