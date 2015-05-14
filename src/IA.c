#include "../header/IA.h"

void manageEnnemies(Map* map){

	int level = map->characters->current->level; //We get the level of the player to define the difficulty
	int numberOfEnnemies = size(map->characters) - 1;

	//If there is not enough ennemies, we add them
	if(numberOfEnnemies < level * 2){
		int numberToAdd = level * 2 - numberOfEnnemies;
		
		int i;
		for(i = 0; i < numberToAdd; ++i){
			createEnnemy(map, level);
		}
	}

	moveEnnemies(map);
}

void moveEnnemies(Map* map){
	Character* heros = map->characters->current;
	ListChar* ennemy = map->characters->next;

	while(ennemy != NULL){
		moveEnnemy(heros, ennemy->current);
		ennemy = ennemy->next;
	}
}

void moveEnnemy(Character* heros, Character *ennemy){
	SDL_Rect *move = malloc(sizeof(SDL_Rect));
	move->x = heros->pos->x - ennemy->pos->x;
	move->y = heros->pos->y - ennemy->pos->y;
}

void createEnnemy(Map* map, int level){
	//We select the position where the ennemy will appear
	int width = map->width;
	int height = map->height;

	SDL_Rect *pos = malloc(sizeof(SDL_Rect));

	do{
		pos->x = abs((rand() * PX_W)%width);
		pos->y = abs((rand() * PX_H)%height);
	}while(isFree(map, pos));

	Character* ch = createChar(100 * level, 100 * (level-1), 5 * level, 0, 0, pos->x/PX_W, pos->y/PX_H, 50, 61, NULL);
	addChar(map->characters, ch);

	free(pos);
}

