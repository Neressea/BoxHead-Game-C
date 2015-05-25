#include "../header/IA.h"

void manageEnnemies(Map* map){

	int level = map->characters->current->level; //We get the level of the player to define the difficulty
	int numberOfEnnemies = size(map->characters) - 1;

	//If there is not enough ennemies, we add them
	if(numberOfEnnemies < level * 3){
		int numberToAdd = level * 3 - numberOfEnnemies;
		
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

	//We compute the position of the ennemy in function of the position of the hero.
	key[0] = (dist->y < 0) ? 1 : 0;
	key[1] = (dist->y != 0) ? !key[0] : 0;
	key[2] = (dist->x < 0) ? 1 : 0;
	key[3] = (dist->x != 0) ? !key[2] : 0;

	deplaceEnnemy(b, key, ennemy);
	free(dist);
}

void deplaceEnnemy(ListBuilding *b, int key[], Character *ennemy){
	SDL_Rect* position = ennemy->pos;
	int x = position->x, y = position->y;

	//A static variable to memorize the number of time we get in the function. Reinitialized after the tenth call.
	static int pool = 1; 

	//We change the position of the ennemy
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

	Building *build;
	//We check the collision with buildings.
	if((build = cantMove(b, position))){
		position->x = x;
		position->y = y;

		//We don't want the building to be destroyed too easily, so we give damages only all tenth call.
		if(build->hp > 0 && pool % 10 == 0){
			build->hp -= ennemy->attack;
			pool = 1;
			if(build->hp <=0) build->hp = 0;
		}else{
			pool++;
		}
	}
}

void createEnnemy(Map* map, int level){
	//We select the position where the ennemy will appear
	int width = map->width;
	int height = map->height;
	SDL_Rect *pos = malloc(sizeof(SDL_Rect));

	//We check that the position is free, that's to say there is no building and not the hero.
	do{
		pos->x = abs((rand() * PX_W)%width);
		pos->y = abs((rand() * PX_H)%height);
	}while(isFree(map, pos));

	//We create and add the ennemy to the map.
	Character* ch = createChar(100 + level * 20, 100 * (level-1), level, 0, 0, pos->x/PX_W, pos->y/PX_H, 50, 61, NULL);
	addChar(map->characters, ch);

	free(pos);
}

