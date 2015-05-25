#include "../header/Map.h"

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
	loadSprite(file, rendu, map->textures, 0);
	loadSprite(file, rendu, map->textures, 1);
	loadSprite(file, rendu, map->textures, 2);

	char *line = malloc(sizeof(char) * 101); //We keep a char for the '\0'

	//Then we read the other lines that represents each "line" of the map
	int x=0, y=0;
	while(fgets(line, 100, file) != NULL){
		line[strlen(line)] = '\0';
		int i=0;
		x=0;

		//We add a wall at the first column
		addWall(map, -1, y);

		while(line[i] != '\0'){

			if(line[i] == '1'){
				addWall(map, x, y);
			}else if(line[i] == '2'){
				map->characters = malloc(sizeof(ListChar));
				map->characters->current = createChar(250, 100, 80, 1, 0, x, y, PXH_W, PXH_H, NULL);
				map->characters->next = NULL;
			}

			i++;
			x++;
		}

		//We add a wall at the last column
		addWall(map, x-1, y);
		y++;
	}

	map->width=PX_W * (x-1);
	map->height=PX_H * (y-1);

	encircleMap(map);

	//We set the left up corner of the map
	int pos_perso_px_x = map->characters->current->pos->x + PXH_W/2;
	int pos_perso_px_y = map->characters->current->pos->y + PXH_H/2;
	map->corner->x = pos_perso_px_x - SCREEN_W / 2;
	map->corner->y = pos_perso_px_y - SCREEN_H / 2;

	fclose(file);
	free(line);
}

void loadSprite(FILE *file, SDL_Renderer *rendu, SDL_Texture **text, int i){
	char* line = malloc(sizeof(char) * 100);
	fgets(line, 100, file);

	if(line == NULL){
		fprintf(stderr, "Non well-formated file (background)\n");
		exit(2);
	}

	//We load the texture of the background
	char path [120] = "./images/sprites/";
	strcat(path, line);
	path[strlen(path)-1] = '\0';
	text[i] = IMG_LoadTexture(rendu, path);

	if(text[i] == NULL){
		fprintf(stderr, "Error loading the background : %s\n", SDL_GetError());
		exit(2);
	}

	free(line);
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
	destroyListBuild(map->buildings);

	//We free the list of characters
	destroyListChara(map->characters);

	free(map);
}

/**
* Print the map on the screen
*/
void showMap(SDL_Window* screen, SDL_Renderer *rendu, Map* map){

	//We check if the size of the screen has changed
	static int screen_h = SCREEN_H, screen_w = SCREEN_W;
	int new_w, new_h;

	//We compute the difference bewteen teh two. If there isn't, it's 0.
	SDL_GetWindowSize(screen,&new_w,&new_h);
	int diff_h = new_h - screen_h, diff_w = new_w - screen_w;

	//We update the left up corner and teh size of the screen for the view.
	screen_h = new_h;
	screen_w = new_w;
	
	map->corner->x -= (int) diff_w/2;
	map->corner->y -= (int) diff_h/2;

	//We compute the shift bewteen the map and the view
	int shift_x = map->corner->x % PX_W;
	int shift_y = map->corner->y % PX_H;

	//We compute the position of the first and lastb case in the map (the bounds)
	SDL_Rect* map_pos = malloc(sizeof(SDL_Rect));

	int begin_x = map->corner->x - shift_x - PX_W;
	int begin_y = map->corner->y - shift_y - PX_H;

	int end_x = begin_x + (screen_w - screen_w % PX_W) + NB_SPRITES_BLITTED * PX_W * 2;
	int end_y = begin_y + (screen_h - screen_h % PX_H) + NB_SPRITES_BLITTED * PX_H * 2;

	//We compute the position where we blit the surface
	SDL_Rect* blit_pos = malloc(sizeof(SDL_Rect));
	blit_pos->x = - (NB_SPRITES_BLITTED * PX_W) - shift_x;
	blit_pos->y = - (NB_SPRITES_BLITTED * PX_H) - shift_y;
	blit_pos->w = PX_W;
	blit_pos->h = PX_H;

	//We blit all the necessary textures
	int i=0, j=0;
	for (i = begin_x; i <= end_x; i+=PX_W){

		//We reinitialize y
		blit_pos->y=- (NB_SPRITES_BLITTED * PX_H) - shift_y;

	 	for (j = begin_y; j <= end_y; j+=PX_H){

	 		//We check the type of the case to blit
	 		Building* b = NULL;
	 		if((b = isBuilding(map->buildings, map_pos))){
	 			if(b->hp == -1)
	 				SDL_RenderCopy(rendu, map->textures[1], NULL, blit_pos);
	 			else
	 				SDL_RenderCopy(rendu, map->textures[2], NULL, blit_pos);
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

Building* isBuilding(ListBuilding* buildings, SDL_Rect* pos){
	int is = 0;
	ListBuilding* b = buildings;

	//We loop whilewe have not found if it is a building, or until we are to the end of the list 
	while(is==0 && b != NULL){

		if(b->current->x == pos->x && b->current->y == pos->y){
			is = 1;
		}else{
			b = b->next;
		}
	}

	Building *res = NULL;
	if(is) res = b->current;

	return res;
}

void saveMap(Map *map){
	map->corner = NULL; //temp
}

void moveMap(SDL_Window *screen, Map* map, int key[], Move* move){

	int prev_x=map->corner->x, prev_y=map->corner->y;

	if(!key[4]){

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

		int screen_h, screen_w;
		SDL_GetWindowSize(screen,&screen_w,&screen_h);
		SDL_Rect* chara = malloc(sizeof(SDL_Rect));
		chara->x = map->corner->x + screen_w/2 - PXH_W/2;
		chara->y = map->corner->y + screen_h/2 - PXH_H/2;
		chara->w = PXH_W;
		chara->h = PXH_H;

		int res = 0;
		if(cantMove(map->buildings, chara) || blockMonsters(map, chara)){
			map->corner->x=prev_x;
			map->corner->y=prev_y;
		}else{
			move->x = map->corner->x - prev_x;
			move->y = map->corner->y - prev_y;
			map->characters->current->pos->x += move->x;
			map->characters->current->pos->y += move->y;
		}

		free(chara);

	}

	
}

Building* cantMove(ListBuilding* b, SDL_Rect* pos){
	int cant = 0;
	Building *res = NULL;

	//We loop whilewe have not found if it is a building, or until we are to the end of the list 
	while(cant==0 && b != NULL){

		//If we are between the x position of the building
		if(pos->x + PXH_W >= b->current->x && pos->x <= b->current->x + PX_W){
			if(pos->y + PXH_H >= b->current->y && pos->y <= b->current->y + PX_H){
				cant=1;
			}else{
				b = b->next;
			}
		}else{
			b = b->next;
		}
	}

	res = (cant) ? b->current : NULL;

	return res;
}

int blockMonsters(Map* map, SDL_Rect* pos){
	int cant = 0;
	static int loop = 0;

	ListChar* characters = map->characters->next;

	while(cant==0 && characters != NULL){
		//If we are between the x position of the building
		SDL_Rect* pos_e = characters->current->pos;

		if(pos->x+ pos->w >= pos_e->x && pos->x <= pos_e->x + pos_e->w){
			if(pos->y + pos->h >= pos_e->y && pos->y <= pos_e->y + pos_e->h){
				cant=1;

				if(loop==10){
					map->characters->current->hp-=characters->current->attack;
					loop=0;
				}else{
					loop++;
				}
			}
		}

		characters = characters->next;
	}

	//Finally, we don't block the hero with ennemies, because it's too hard to play.
	return 0;
}

int isFree(Map* map, SDL_Rect* pos){
	int cant = 0;
	ListChar* characters = map->characters->next;

	while(cant==0 && characters != NULL){
		//If we are between the x position of the building
		SDL_Rect* pos_e = characters->current->pos;

		if(pos->x+ pos->w >= pos_e->x && pos->x <= pos_e->x + pos_e->w){
			if(pos->y + pos->h >= pos_e->y && pos->y <= pos_e->y + pos_e->h){
				cant=1;
			}
		}

		characters = characters->next;
	}

	if(!cant){
		cant = (cantMove(map->buildings, pos)) ? 1 : 0;
	}

	return cant;
}

int cantMoveSpell(ListBuilding* lb, SDL_Rect* pos, Spell *spell, ListItem *listitem, Map *map){
	int cant = 0;

	ListBuilding* b = lb;

	int h;
	int w;
	
	if (spell->direction == 6 || spell->direction == 9){
		h = SPELL_W;
		w = SPELL_H;
	}else{
		h = SPELL_H;
		w = SPELL_W;
	}

	//We loop while we have not found if it is a building, or until we are to the end of the list 
	while(cant==0 && b != NULL){

		//If we are between the x position of the building
		if(pos->x + w >= b->current->x && pos->x <= b->current->x + PX_W){
			if(pos->y + h >= b->current->y && pos->y <= b->current->y + PX_H){
				cant=1;
				if (b->current->hp > 0){
					b->current->hp -= spell->type->attack;
					if (b->current->hp <= 0){
						b->current->hp = 0;
						poseItem(listitem, b->current->x-map->corner->x - ITEM_W/2 + PX_W/2, b->current->y-map->corner->y + PX_H/2 - ITEM_H/2); 
					}
				}
			}
		}
		b = b->next;
	}

	return cant;
}

int cantMoveMonster(ListChar* lb, SDL_Rect* pos, Spell *spell, ListItem *listitem, Map *map){
	int cant = 0;

	ListChar* lc = lb->next;

	int h;
	int w;
	
	if (spell->direction == 6 || spell->direction == 9){
		h = SPELL_W;
		w = SPELL_H;
	}else{
		h = SPELL_H;
		w = SPELL_W;
	}

	//We loop whilewe have not found if it is a building, or until we are to the end of the list 
	while(cant==0 && lc != NULL){
		//If we are between the x position of the building
		if(pos->x + w >= lc->current->pos->x && pos->x <= lc->current->pos->x + lc->current->pos->w){
			if(pos->y + h >= lc->current->pos->y && pos->y <= lc->current->pos->y + lc->current->pos->h){
				cant=1;
				if (lc->current->hp > 0){
					int damage = spell->type->attack + lb->current->level * 10;
					lc->current->hp -= damage;

					if(lc->current->hp <= 0)
						poseItem(listitem, lc->current->pos->x-map->corner->x + PXH_W/2 - ITEM_W/2, lc->current->pos->y-map->corner->y+ PXH_H/2 - ITEM_H/2);
					add_xp(lb->current, damage);
				}
			}
		}
		lc = lc->next;
	}
	return cant;
}

void addWall(Map *map, int x, int y){
	Building* b = createBuilding(x * PX_W, y * PX_H, -1, -1, -1);
	ListBuilding* lb = malloc(sizeof(ListBuilding));
	lb->current=b;
	lb->next = map->buildings;
	map->buildings = lb;
}

void turret(Map *map, TypeSpell *current_type, int key[], int direction, int *last){
	
	int x = map->characters->current->pos->x;
	int y = map->characters->current->pos->y;
	int mur = 0;
	
	if (key[4] && current_type->ammo != 0 && SDL_GetTicks() - *last > current_type->rate && (direction == 0 || direction == 3 || direction == 6 || direction == 9)){
		
		if (direction == 0){
			y = y + PXH_H;
			x = x/100;
			y = y/100;
			y++;
		}

		if (direction == 3){
			x = x/100;
			y = y/100;
			y--;
		}

		if (direction == 6){
			x = x - PXH_W;
			y = y + PXH_H;
			x = x/100;
			y = y/100;
			x--;
		}

		if (direction == 9){
			x = x + PXH_W;
			y = y + PXH_H;
			x = x/100;
			y = y/100;
			x++;
		}

		ListBuilding* b = map->buildings;

		while(b != NULL){
			if (b->current->x/PX_W == x){
				if (b->current->y/PX_H == y){
					mur = 1;
					break;
				}
			}
		b = b->next;
		}

		if (mur == 0){
			Building* b = createBuilding(x * PX_W, y * PX_H, map->characters->current->level*100, 10, 10);
			ListBuilding* lb = malloc(sizeof(ListBuilding));
			lb->current=b;
			lb->next = map->buildings;
			map->buildings = lb;
			current_type->ammo --;
			*last = SDL_GetTicks();
		}
	}
}

void turret_shot(Map *map, ListSpell *current_list, TypeSpell *current_type){
	ListBuilding* b = map->buildings;
	int direction = rand()%4;
	SDL_Rect * ptest = malloc(sizeof(SDL_Rect));
	int key[5] = {0};
	key[4] = 1;
	int test = 0;

		while(b != NULL){
			if (b->current->hp > 0){
					
				direction *= 3;

				if (direction == 0){
					ptest->h = SPELL_H;
					ptest->w = SPELL_W;
					ptest->y = b->current->y - map->corner->y + PX_H;
					ptest->x = b->current->x - map->corner->x + PX_W/2;
				}
				if (direction == 3){
					ptest->h = SPELL_H;
					ptest->w = SPELL_W;
					ptest->y = b->current->y - map->corner->y - PX_H;
					ptest->x = b->current->x - map->corner->x + PX_W/3;
				}
				if (direction == 6){
					ptest->h = SPELL_W;
					ptest->w = SPELL_H;
					ptest->y = b->current->y - map->corner->y;
					ptest->x = b->current->x - map->corner->x - PX_W;
				}
				if (direction == 9){
					ptest->h = SPELL_W;
					ptest->w = SPELL_H;
					ptest->y = b->current->y - map->corner->y;
					ptest->x = b->current->x - map->corner->x + PX_W;
				}
				lanceattack(current_list, &direction, current_type, key, ptest->x, ptest->y);
			}
		b = b->next;
		}

	free(ptest);

}

int test_shot(SDL_Rect* pref, int direction, Map *map){
	int test = 0;
	int time = 0;
	int h;
	int w;

	ListBuilding* b = map->buildings;
	ListChar *c = map->characters;
	SDL_Rect *ptest = malloc(sizeof(SDL_Rect));
	ptest->x = pref->x;
	ptest->y = pref->y;
	ptest->w = pref->w;
	ptest->h = pref->h;

	while(time != 200){
		if (direction == 0){
			ptest->y += 2*SPEED;
			h = SPELL_H;
			w = SPELL_W;		
		}
		if (direction == 3){
			ptest->y -= 2*SPEED;
			h = SPELL_H;
			w = SPELL_W;
		}
		if (direction == 6){
			ptest->x -= 2*SPEED;
			h = SPELL_W;
			w = SPELL_H;
		}
		if (direction == 9){
			ptest->x += 2*SPEED;
			h = SPELL_W;
			w = SPELL_H;
		}

		while(c != NULL){

			if(ptest->x + w >= c->current->pos->x && ptest->x <= c->current->pos->x + PXH_W){
				if(ptest->y + h >= c->current->pos->y && ptest->y <= c->current->pos->y + PXH_H){
	 				test = 1;
					break;
					
				}
			}
		
			c = c->next;

		}

		time++;

	}

	free(ptest);

	return test;

}

void encircleMap(Map* map){
	int i;
	for (i = -1; i <= map->height/PX_H+1; ++i){
		addWall(map, -1, i);
		addWall(map, map->width/PX_W, i);
	}

	for (i = -1; i < map->width/PX_W; ++i){
		addWall(map, i, -1);
		addWall(map, i, map->height/PX_H+1);
	}
}

ListBuilding* updateWall(ListBuilding* lb){
	
	ListBuilding* c = lb;
	ListBuilding* d;
	Building *b;

	while(lb!= NULL && c->current->hp == 0){
		b = lb->current;
		lb = lb->next;
		free(b);
	}

	while(c->next != NULL){
		if (c->next->current->hp == 0){
			d = c->next;		
			
			if (c->next->next != NULL){
				c->next = c->next->next ;
				c = c->next;
			}else{
				c->next = NULL;
			}
	
			free(d);
		}else{
			c = c->next;
		}

	}

	return lb;
}
