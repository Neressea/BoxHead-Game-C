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
}

void moveEnnemy(ListBuilding* b, Character* heros, Character *ennemy, int key[]){
	SDL_Rect *dist = malloc(sizeof(SDL_Rect));
	dist->x = heros->pos->x - ennemy->pos->x;
	dist->y = heros->pos->y - ennemy->pos->y;

	key[0] = (dist->y < 0) ? 1 : 0;
	key[1] = (dist->y != 0) ? !key[0] : 0;
	key[2] = (dist->x < 0) ? 1 : 0;
	key[3] = (dist->x != 0) ? !key[2] : 0;

	deplaceEnnemy(b, key, ennemy->pos);
	free(dist);
}

void deplaceEnnemy(ListBuilding *b, int key[], SDL_Rect* position){
	int x = position->x, y = position->y;

	if (key[0] && key[2]){
		position->y -= SPEED / 3;
		position->x -= SPEED / 3;
	}
	if (key[0] && key[3]){
		position->y -= SPEED / 3;
		position->x += SPEED / 3;
	}
	if (key[0] && !key[3] && !key[2]){
		position->y -= SPEED / 3;
	}
	
	if (key[1] && key[2]){
		position->y += SPEED / 3;
		position->x -= SPEED / 3;
	}
	if (key[1] && key[3]){
		position->y += SPEED / 3;
		position->x += SPEED / 3;
	}
	if (key[1] && !key[3] && !key[2]){
		position->y += SPEED / 3;
	}
		
	if (key[2] && !key[0] && !key[1]){
		position->x -= SPEED / 3;
	}
	if (key[3] && !key[0] && !key[1]){
		position->x += SPEED / 3;
	}

	if(cantMove(b, position)){
		position->x = x;
		position->y = y;
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
	}while(isFree(map, pos));

	Character* ch = createChar(100 * level, 100 * (level-1), 5 * level, 0, 0, pos->x/PX_W, pos->y/PX_H, 50, 61, NULL);
	addChar(map->characters, ch);

	free(pos);
}

