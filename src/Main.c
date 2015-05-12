#include "../header/Main.h"

int screen_h = SCREEN_H;
int screen_w = SCREEN_W;

int main(){
	
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}

	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1){
		fprintf(stderr, "Erreur d'initialisation de la SDL_IMG : %s\n", SDL_GetError()); // managing IMG loading error 
		exit(EXIT_FAILURE);
	}

	if (TTF_Init() == -1){
		fprintf(stderr, "Erreur d'initialisation de la SDL_TTF : %s\n", SDL_GetError()); // managing TTF loading error 
		exit(EXIT_FAILURE);
	}

	SDL_Window *main_screen = SDL_CreateWindow("Jeu de la mort qui tue",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_W,SCREEN_H, SDL_WINDOW_SHOWN| SDL_WINDOW_RESIZABLE);
	SDL_Renderer *rendu = SDL_CreateRenderer(main_screen, -1, SDL_RENDERER_SOFTWARE);

	SDL_Rect *title = malloc(sizeof(SDL_Rect));
	SDL_Rect *title2 = malloc(sizeof(SDL_Rect));
	SDL_Rect *point = malloc(sizeof(SDL_Rect));
	SDL_Color textColor = { 255, 255, 255, 255 }; 
	SDL_Event event;
	SDL_Event event1;

	TTF_Font* font = TTF_OpenFont("./images/polices/AmaticSC-Regular.ttf",100);
    	SDL_Surface *Surface_Title = TTF_RenderText_Solid (font, "The Game", textColor);
	SDL_Surface *Surface_Tsubtitle = TTF_RenderText_Solid (font, "Appuyez sur une touche", textColor);
	SDL_Texture* Text_title = SDL_CreateTextureFromSurface(rendu, Surface_Title);
	SDL_Texture* Text_subtitle = SDL_CreateTextureFromSurface(rendu, Surface_Tsubtitle);
	SDL_Texture* Pointeur = IMG_LoadTexture(rendu, "./images/sprites/ennemy.png");	

	int screen = 0;
	int quit = 0;
	int play = 0;
	int option = 0;
	int test = 0;

	while(screen == 0){
		SDL_PollEvent(&event);

		if (event.type == SDL_KEYDOWN){
			screen = 1;
		}

		if (event.type == SDL_QUIT){
			screen = 1;
			quit = 1;
		}

		SDL_GetWindowSize(main_screen,&screen_w,&screen_h);

		title->h = screen_h/1.2;
		title->w = screen_w/1.6;	
		title->x = screen_w/2 - title->w/2;
		title->y = screen_h/2 - title->h/2 - screen_h/4.8;

		SDL_RenderClear(rendu);

		SDL_RenderCopy(rendu, Text_title, NULL, title );

		title2->h = screen_h/4.8;
		title2->w = screen_w/2;	
		title2->x = screen_w/2 - title2->w/2;
		title2->y = screen_h/2 - title2->h/2 + screen_h/4.8;

		
		if(SDL_GetTicks() - test>100){
			if(SDL_GetTicks()- test>300){
				test = SDL_GetTicks();
			}
			SDL_RenderCopy(rendu, Text_subtitle, NULL, title2 );	
		}else{
	
		}

		SDL_RenderPresent(rendu);

	
	}

	Surface_Title = TTF_RenderText_Solid (font, "New Game", textColor);
	Surface_Tsubtitle = TTF_RenderText_Solid (font, "Options", textColor);
	SDL_Surface *Surface_Tsubtitle2 = TTF_RenderText_Solid (font, "Quit", textColor);
	Text_title = SDL_CreateTextureFromSurface(rendu, Surface_Title);
	Text_subtitle = SDL_CreateTextureFromSurface(rendu, Surface_Tsubtitle);

	SDL_Texture *Text_subtitle2 = SDL_CreateTextureFromSurface(rendu, Surface_Tsubtitle2);

	point->y = screen_h/2 - screen_h/3.2;

	while(quit == 0){
		SDL_PollEvent(&event1);
			switch(event1.type){
				case SDL_QUIT:
					quit = 1;
				break;
				case SDL_KEYDOWN:
					switch (event1.key.keysym.sym){
						case SDLK_UP:
							if (point->y > screen_h/2 - screen_h/3.2){
								point->y = point->y - screen_h/4;
							}
							SDL_Delay(70);							
						break;
						case SDLK_DOWN:
							if (point->y < screen_h/2 - screen_h/3.2 + 2*screen_h/4){
								point->y = point->y + screen_h/4;
							}
							SDL_Delay(70);
						break;
						case SDLK_SPACE:
							if (point->y == screen_h/2 - screen_h/3.2) 								{							
								play = 1;
							}else if (point->y == screen_h/2 - screen_h/3.2 + 2*screen_h/4){
							}else{
								option = 1;
							}
								quit = 1;
						break;
					}
				break;
			}

		SDL_GetWindowSize(main_screen,&screen_w,&screen_h);
		
		title->h = screen_h/4.8;
		title->w = screen_w/2;
		title->x = screen_w/2 - title->w/2;
		title->y = screen_h/2 - title->h/2 - screen_h/4;

		SDL_RenderClear(rendu);
		SDL_RenderCopy(rendu, Text_title, NULL, title );
		
		title->y = screen_h/2 - title->h/2;

		SDL_RenderCopy(rendu, Text_subtitle, NULL, title );

		title->y = screen_h/2 - title->h/2 + screen_h/4;

		SDL_RenderCopy(rendu, Text_subtitle2, NULL, title );

		point->h = screen_h/9.6;
		point->w = screen_w/12.8;	
		point->x = screen_w/2 - title->w/2 - screen_w/8;

		SDL_RenderCopy(rendu, Pointeur, NULL, point );
		SDL_RenderPresent(rendu);
		
	}

	if (option == 1){

	}

	if (play == 1){
		managing_event(main_screen,rendu);
	}
	
	free(title);
	free(title2);
	TTF_CloseFont(font);	
	IMG_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}

void managing_event(SDL_Window * main_screen, SDL_Renderer *rendu){

	SDL_Texture *texture_heros[NB_SPRITES_H + NB_SPRITES_A] = {NULL};
	SDL_Texture *texture_ennemy[NB_SPRITES_H] = {NULL};	
	SDL_Texture *texture_attack[NB_TYP_SPELL*NB_SPRITES_A] = {NULL};
	SDL_Texture *texture_type[NB_TYP_SPELL] = {NULL};
	SDL_Texture *texture_item[NB_ITEM] = {NULL};
	SDL_Texture *current_texture = NULL;
	TTF_Font* font = TTF_OpenFont("./images/polices/Capture_it.ttf",100);
	Map *map = malloc(sizeof(Map));
	ListItem * listitem = init_listItem();
	ListSpell *liste_spell = init_listspell();
	
	TypeSpell **tab_typeSpell = malloc(NB_TYP_SPELL*sizeof(TypeSpell));
	tab_typeSpell[0] = init_typeSpell(100,0,500,-1);
	tab_typeSpell[1] = init_typeSpell(100,1,500,20);
	TypeSpell *current_type = tab_typeSpell[0];
	
	Move *move = malloc(sizeof(Move));
	SDL_Texture** texture_chara[] = {texture_heros, texture_ennemy};

	int quit = 0;
	int key[7] = {0};
	int direction = 0;
	int limit = 0;
	int test = 0;

	SDL_SetRenderDrawColor(rendu, 0, 255, 255, 255);
	SDL_RenderClear(rendu);
	
	init_texture(rendu, texture_heros);
	init_texture_ennemy(rendu, texture_ennemy);
	init_texture_attack(rendu, texture_attack);
	init_type_attack(rendu, texture_type);
	texture_item[0] = IMG_LoadTexture(rendu, "./images/sprites/item0.png");
	
	current_texture = texture_heros[0];

	if (current_texture == NULL){
		fprintf(stderr, "Erreur d'initialisation de sprite courant : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}

	load(rendu, map, "./maps/map1");	

	SDL_Event event;
		
	SDL_ShowCursor(SDL_DISABLE);
	
	while(quit == 0){

		SDL_PollEvent(&event);
			switch(event.type){
				case SDL_QUIT:
					quit = 1;
				break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym){	//openclassrooms.com/uploads/fr/ftp/mateo21/sdlkeysym.html
						case SDLK_ESCAPE:
							quit = 1;
        					break;
						case SDLK_UP:
							key[0] = 1;
						break;
						case SDLK_DOWN:
							key[1] = 1;
						break;
						case SDLK_LEFT:
							key[2] = 1;
						break;
						case SDLK_RIGHT:
							key[3] = 1;
						break;
						case SDLK_SPACE:
							key[4] = 1;
						break;
						case SDLK_a:
							key[5] = 1;
						break;
						case SDLK_z:
							key[6] = 1;
						break;
						}
				break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym){
						case SDLK_ESCAPE:
        					break;
						case SDLK_UP:
							key[0] = 0;
						break;
						case SDLK_DOWN:
							key[1] = 0;
						break;
						case SDLK_LEFT:
							key[2] = 0;
						break;
						case SDLK_RIGHT:
							key[3] = 0;
						break;
						case SDLK_SPACE:
							key[4] = 0;
						break;
						case SDLK_a:
							key[5] = 0;
						break;
						case SDLK_z:
							key[6] = 0;
						break;
						}
				break;
							
			}


	SDL_RenderClear(rendu);

	SDL_GetWindowSize(main_screen,&screen_w,&screen_h);

	showMap(main_screen, rendu, map);

	updateWall(map->buildings);

	//addChar(map->characters, createChar(100, 10, 10, 1, 1, 200, 200, 50, 50, liste_spell));
	manageEnnemies(map);

	showCharacters(rendu, map->characters, map->corner, texture_chara, key, &direction);
	
	changeTypeSpell(key, tab_typeSpell,&current_type);
	lanceattack(liste_spell, &direction, current_type, key);
	
	move->x = 0;
	move->y = 0;

	moveMap(main_screen, map, key, move);

	manageSpellType(current_type, rendu, texture_type, font);

	updateSpell(liste_spell, move, main_screen);

	deleteSpell2(liste_spell, map, listitem);

	updateItem(listitem, rendu, texture_item, move);
	
	Blit_attack(liste_spell,rendu, texture_attack);
		
	SDL_RenderPresent(rendu);

	//We manage the FPS
	
	test = SDL_GetTicks();	

	if (limit > test){
		if (limit > test + FPS){
			SDL_Delay(FPS);
		}
		else {
			SDL_Delay(limit - test);
		}
	}

		limit = SDL_GetTicks() + FPS;
	
		if (current_texture == NULL){
			fprintf(stderr, "Erreur de récupération des textures : %s\n", SDL_GetError()); // managing SDL loading error 
			exit(EXIT_FAILURE);
		}

	}
	
	SDL_DestroyTexture(current_texture);
	destroy_texture(NB_SPRITES_H, texture_heros);
	destroyMap(map);
	SDL_DestroyRenderer(rendu);
	SDL_DestroyWindow(main_screen);
	
}

void test_key(int key[], SDL_Rect *position){
		
	if (key[0] && key[2]){
		position->y -= SPEED;
		position->x -= SPEED;
	}
	if (key[0] && key[3]){
		position->y -= SPEED;
		position->x += SPEED;
	}
	if (key[0] && !key[3] && !key[2]){
		position->y -= SPEED;
	}
	
	if (key[1] && key[2]){
		position->y += SPEED;
		position->x -= SPEED;
	}
	if (key[1] && key[3]){
		position->y += SPEED;
		position->x += SPEED;
	}
	if (key[1] && !key[3] && !key[2]){
		position->y += SPEED;
	}
		
	if (key[2] && !key[0] && !key[1]){
		position->x -= SPEED;
	}
	if (key[3] && !key[0] && !key[1]){
		position->x += SPEED;
	}

}

void init_texture(SDL_Renderer *rendu, SDL_Texture *tableau[]){
	tableau[0] = IMG_LoadTexture(rendu, "./images/sprites/heros0.png");
	tableau[1] = IMG_LoadTexture(rendu, "./images/sprites/heros1.png");
	tableau[2] = IMG_LoadTexture(rendu, "./images/sprites/heros2.png");
	tableau[3] = IMG_LoadTexture(rendu, "./images/sprites/heros3.png");
	tableau[4] = IMG_LoadTexture(rendu, "./images/sprites/heros4.png");
	tableau[5] = IMG_LoadTexture(rendu, "./images/sprites/heros5.png");
	tableau[6] = IMG_LoadTexture(rendu, "./images/sprites/heros6.png");
	tableau[7] = IMG_LoadTexture(rendu, "./images/sprites/heros7.png");
	tableau[8] = IMG_LoadTexture(rendu, "./images/sprites/heros8.png");
	tableau[9] = IMG_LoadTexture(rendu, "./images/sprites/heros9.png");
	tableau[10] = IMG_LoadTexture(rendu, "./images/sprites/heros10.png");
	tableau[11] = IMG_LoadTexture(rendu, "./images/sprites/heros11.png");
	tableau[12] = IMG_LoadTexture(rendu, "./images/sprites/heros12.png");
	tableau[13] = IMG_LoadTexture(rendu, "./images/sprites/heros13.png");
	tableau[14] = IMG_LoadTexture(rendu, "./images/sprites/heros14.png");
	tableau[15] = IMG_LoadTexture(rendu, "./images/sprites/heros15.png");
	tableau[16] = IMG_LoadTexture(rendu, "./images/sprites/heros16.png");
	tableau[17] = IMG_LoadTexture(rendu, "./images/sprites/heros17.png");
	tableau[18] = IMG_LoadTexture(rendu, "./images/sprites/heros18.png");
	tableau[19] = IMG_LoadTexture(rendu, "./images/sprites/heros19.png");
	tableau[20] = IMG_LoadTexture(rendu, "./images/sprites/heros20.png");
	tableau[21] = IMG_LoadTexture(rendu, "./images/sprites/heros21.png");
	tableau[22] = IMG_LoadTexture(rendu, "./images/sprites/heros22.png");
	tableau[23] = IMG_LoadTexture(rendu, "./images/sprites/heros23.png");
	tableau[24] = IMG_LoadTexture(rendu, "./images/sprites/heros24.png");
	tableau[25] = IMG_LoadTexture(rendu, "./images/sprites/heros25.png");
	tableau[26] = IMG_LoadTexture(rendu, "./images/sprites/heros26.png");
	tableau[27] = IMG_LoadTexture(rendu, "./images/sprites/heros27.png");
	tableau[28] = IMG_LoadTexture(rendu, "./images/sprites/heros28.png");
	tableau[29] = IMG_LoadTexture(rendu, "./images/sprites/heros29.png");
	tableau[30] = IMG_LoadTexture(rendu, "./images/sprites/heros30.png");
	tableau[31] = IMG_LoadTexture(rendu, "./images/sprites/heros31.png");
}

void init_texture_ennemy(SDL_Renderer *rendu, SDL_Texture *tabl[]){
	tabl[0] = IMG_LoadTexture(rendu, "./images/sprites/monstre0.png");
}

void init_texture_attack(SDL_Renderer *rendu, SDL_Texture *tabl[]){
	tabl[0] = IMG_LoadTexture(rendu, "./images/sprites/attck0_fireball.png");
	tabl[1] = IMG_LoadTexture(rendu, "./images/sprites/attck1_fireball.png");
	tabl[2] = IMG_LoadTexture(rendu, "./images/sprites/attck2_fireball.png");
	tabl[3] = IMG_LoadTexture(rendu, "./images/sprites/attck3_fireball.png");
	tabl[4] = IMG_LoadTexture(rendu, "./images/sprites/attck4_fireball.png");
	tabl[5] = IMG_LoadTexture(rendu, "./images/sprites/attck5_fireball.png");
	tabl[6] = IMG_LoadTexture(rendu, "./images/sprites/attck6_fireball.png");
	tabl[7] = IMG_LoadTexture(rendu, "./images/sprites/attck7_fireball.png");
	tabl[8] = IMG_LoadTexture(rendu, "./images/sprites/attck0_frost.png");
	tabl[9] = IMG_LoadTexture(rendu, "./images/sprites/attck1_frost.png");
	tabl[10] = IMG_LoadTexture(rendu, "./images/sprites/attck2_frost.png");
	tabl[11] = IMG_LoadTexture(rendu, "./images/sprites/attck3_frost.png");
	tabl[12] = IMG_LoadTexture(rendu, "./images/sprites/attck4_frost.png");
	tabl[13] = IMG_LoadTexture(rendu, "./images/sprites/attck5_frost.png");
	tabl[14] = IMG_LoadTexture(rendu, "./images/sprites/attck6_frost.png");
	tabl[15] = IMG_LoadTexture(rendu, "./images/sprites/attck7_frost.png");

}

void init_type_attack(SDL_Renderer *rendu, SDL_Texture *tableau[]){
	tableau[0] = IMG_LoadTexture(rendu, "./images/sprites/typespell0.png");
	tableau[1] = IMG_LoadTexture(rendu, "./images/sprites/typespell1.png");
}

void destroy_texture(int taille, SDL_Texture *tableau[]){
	int i;

	for (i = 0; i < taille; i++){
		SDL_DestroyTexture(tableau[i]);
	}

}

void changeTypeSpell (int key[], TypeSpell **tab_typeSpell, TypeSpell **current_type){
	int i;

	for (i = 5 ; i < NB_TYP_SPELL + 5; i ++){
		if (key[i] == 1){			
			*current_type = tab_typeSpell[i-5];
		}
	}
}

void deleteSpell2(ListSpell *current_list, Map *map, ListItem *listitem){
	
	SDL_Rect *test = malloc(sizeof(SDL_Rect));

	ListSpell *cursor = current_list->nextSpell;	

	while(cursor != NULL){

		test->x = cursor->currentSpell->pspell->x + map->corner->x;
		test->y = cursor->currentSpell->pspell->y + map->corner->y;
		

		if (cantMoveSpell(map->buildings, test, cursor->currentSpell,listitem,map)){
			
			current_list->nextSpell = cursor->nextSpell;
			free(cursor);
			cursor = current_list;
		}

		cursor = cursor->nextSpell;
	}

	free(test);

}


