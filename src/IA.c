#include "./header/IA.h"

void manageEnnemies(Map* map){
	int level = map->characters->current->level; //We get the level of the player to define the difficulty
	int numberOfEnnemies = size(map->characters) - 1;

	//If there is not enough ennemies, we add them
	if(numberOfEnnemies < level * level){
		int numberToAdd = level * level - numberOfEnnemies;
		
		for(int i = 0; i < numberToAdd; ++i){
			
		}
	}
}

Character* createEnnemy(Map* map, int level){

	//We select the position where the ennemy will appear
	int width = map->width/PX_W;
	int height = map->height/PX_H;

	SDL_Rect *pos = malloc(sizeof(SDL_Rect));

	do{

		pos->x = rand()%width;
		pos->y = rand()%height;

	}while(!isBuilding(map->buildings, pos));

	Character* ch = createChar(10 * level, 10 * (level-1), 5 * level, 0, 0, pos->x, pos->y, NULL);
	addChar(map->characters, ch);

	return ch;
}