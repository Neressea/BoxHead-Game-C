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

	 if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
	      	fprintf(stderr, "Erreur d'initialisation du la SDL_Mixer : %s\n", Mix_GetError()); //managing MIXER loading error
		exit(EXIT_FAILURE);
	   } 

	SDL_Window *main_screen = SDL_CreateWindow("Jeu de la mort qui tue",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_W,SCREEN_H, SDL_WINDOW_SHOWN| SDL_WINDOW_RESIZABLE);
	SDL_Renderer *rendu = SDL_CreateRenderer(main_screen, -1, SDL_RENDERER_SOFTWARE);

	SDL_Rect *title = malloc(sizeof(SDL_Rect));
	SDL_Rect *title2 = malloc(sizeof(SDL_Rect));
	SDL_Rect *point = malloc(sizeof(SDL_Rect));
	SDL_Color textColor = { 255, 255, 255, 255 }; 
	SDL_Event event;


	TTF_Font* font = TTF_OpenFont("./images/polices/AmaticSC-Regular.ttf",100); //!!0 création des textures 
    SDL_Surface *Surface_Title = TTF_RenderText_Solid (font, "The Game", textColor);
	SDL_Surface *Surface_Tsubtitle = TTF_RenderText_Solid (font, "Appuyez sur une touche", textColor);
	SDL_Texture* Text_title = SDL_CreateTextureFromSurface(rendu, Surface_Title);
	SDL_Texture* Text_subtitle = SDL_CreateTextureFromSurface(rendu, Surface_Tsubtitle);
	SDL_Texture* Pointeur = IMG_LoadTexture(rendu, "./images/sprites/cursor.png");	
	
	Mix_VolumeMusic(MIX_MAX_VOLUME); //On lance la musique d'écran titre
	Mix_Music *musique;
  	musique = Mix_LoadMUS("./sons/The Pyre.mp3"); 
  	Mix_PlayMusic(musique, -1); 

	int screen = 0;
	int quit = 0;
	int play = 0;
	int option = 0;
	int test = 0;

	int limit=0, test2=0;

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

		SDL_RenderClear(rendu); //!!1

		SDL_RenderCopy(rendu, Text_title, NULL, title ); //!!2

		title2->h = screen_h/4.8;  //definit la taille des textures
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

		SDL_RenderPresent(rendu); //!!3

		test2 = SDL_GetTicks();	

		if (limit > test){
			if (limit > test + FPS){
				SDL_Delay(FPS);
			}
			else {
				SDL_Delay(limit - test);
			}
		}

		limit = SDL_GetTicks() + FPS;
	}

	SDL_FreeSurface(Surface_Title);
	Surface_Title = TTF_RenderText_Solid (font, "New Game", textColor);

	SDL_FreeSurface(Surface_Tsubtitle);
	Surface_Tsubtitle = TTF_RenderText_Solid (font, "Keybindings", textColor);

	SDL_Surface *Surface_Tsubtitle2 = TTF_RenderText_Solid (font, "Quit", textColor);

	SDL_DestroyTexture(Text_title);
	Text_title = SDL_CreateTextureFromSurface(rendu, Surface_Title);
	SDL_FreeSurface(Surface_Title);

	SDL_DestroyTexture(Text_subtitle);
	Text_subtitle = SDL_CreateTextureFromSurface(rendu, Surface_Tsubtitle);
	SDL_FreeSurface(Surface_Tsubtitle);

	SDL_Texture *Text_subtitle2 = SDL_CreateTextureFromSurface(rendu, Surface_Tsubtitle2);
	SDL_FreeSurface(Surface_Tsubtitle2);

	point->y = screen_h/2 - screen_h/3.2;

	while(quit == 0){
		SDL_Event event1;
		event1.type = 0;
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
								quit=1;
							}else if (point->y == screen_h/2 - screen_h/3.2 + 2*screen_h/4){
								quit=1;
							}else{
								option = 1;
							}
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

		test2 = SDL_GetTicks();	

		if (limit > test){
			if (limit > test + FPS){
				SDL_Delay(FPS);
			}
			else {
				SDL_Delay(limit - test);
			}
		}

		limit = SDL_GetTicks() + FPS;

		if (option == 1){
			quit = managing_keybinds(main_screen,rendu);
			option=0;
			SDL_RenderClear(rendu);
		}

		if (play == 1){
			quit = managing_event(main_screen,rendu);
		}

		if(quit == 2){
			screen = 0;
			quit = 0;
			play = 0;
			option = 0;
			test = 0;
		}
	}

	SDL_DestroyRenderer(rendu);
	SDL_DestroyWindow(main_screen);
	free(title);
	free(title2);
	free(point);
	TTF_CloseFont(font);
	SDL_DestroyTexture(Text_title);
	SDL_DestroyTexture(Text_subtitle);
	SDL_DestroyTexture(Pointeur);	
	SDL_DestroyTexture(Text_subtitle2);
	IMG_Quit();
	SDL_VideoQuit();
	SDL_AudioQuit();
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}

int managing_event(SDL_Window * main_screen, SDL_Renderer *rendu){

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
	tab_typeSpell[1] = init_typeSpell(1000,1,500,20);
	tab_typeSpell[2] = init_typeSpell(100,2,500,10);
	tab_typeSpell[3] = init_typeSpell(100,0,500,-1);
	TypeSpell *current_type = tab_typeSpell[0];

	Move *move = malloc(sizeof(Move));
	SDL_Texture** texture_chara[] = {texture_heros, texture_ennemy};
	
	int Itemcaught[NB_ITEM]= {0};
	int quit = 0;
	int key[8] = {0};
	int direction = 0;
	int limit = 0;
	int test = 0;
	int last = 0;

	SDL_RenderClear(rendu);
	
	init_texture(rendu, texture_heros);
	init_texture_ennemy(rendu, texture_ennemy);
	init_texture_attack(rendu, texture_attack);
	init_type_attack(rendu, texture_type);
	texture_item[0] = IMG_LoadTexture(rendu, "./images/sprites/item0.png");
	texture_item[1] = IMG_LoadTexture(rendu, "./images/sprites/item1.png");
	
	current_texture = texture_heros[0];

	if (current_texture == NULL){
		fprintf(stderr, "Erreur d'initialisation de sprite courant : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}
	
	Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
	Mix_Music *musique;
	musique = Mix_LoadMUS("./sons/The Complex.mp3"); //Chargement de la musique
   	Mix_PlayMusic(musique, -1);
	Mix_AllocateChannels(32); //Effets sonores
	Mix_Chunk *feu;
	feu = Mix_LoadWAV("./sons/fire.wav");
	Mix_Chunk *glace;
	glace = Mix_LoadWAV("./sons/ice.wav");
	Mix_Chunk *mort;
	mort = Mix_LoadWAV("./sons/death.wav");
	Mix_Chunk *tour;
	tour = Mix_LoadWAV("./sons/hammer.wav");

	load(rendu, map, "./maps/map1");

	int keyBindings[NB_TOUCHES]={0}; //On génère les raccourcis clavier
	initialise_keybinds(keyBindings);


	SDL_Event event;
		
	SDL_ShowCursor(SDL_DISABLE);

	while(quit == 0){

		SDL_PollEvent(&event);
			switch(event.type){
				case SDL_QUIT:
					quit = 1;
				break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == keyBindings[ESCAPE]) {
						quit = 2;
					break; 
					} else if (event.key.keysym.sym == keyBindings[UP]) {
						key[0] = 1;
					break;
					} else if (event.key.keysym.sym == keyBindings[DOWN]) {
						key[1] = 1;
					break;
					} else if (event.key.keysym.sym == keyBindings[LEFT]) {
						key[2] = 1;
					break;
					} else if (event.key.keysym.sym == keyBindings[RIGHT]) {
						key[3] = 1;
					break;
					} else if (event.key.keysym.sym == keyBindings[ATTACK]) {
						key[4] = 1;
						if(current_type == tab_typeSpell[0] && Mix_Playing(1) == 0) {
							Mix_PlayChannel(1, feu, 0);
						} else if (current_type == tab_typeSpell[1] && Mix_Playing(1) == 0) {
							Mix_PlayChannel(1, glace, 0);
						} else if (current_type == tab_typeSpell[2] && Mix_Playing(1) == 0) {
							Mix_PlayChannel(1, tour, 0);
						}
					break;
					} else if (event.key.keysym.sym == keyBindings[FIRE]) {
						key[5] = 1;
						Mix_PlayChannel(1, feu, 0);
					break;
					} else if (event.key.keysym.sym == keyBindings[ICE]) {
						key[6] = 1;
						Mix_PlayChannel(1, glace, 0);
					break;
					} else if (event.key.keysym.sym == keyBindings[TOWER]) {
						key[7] = 1;
						Mix_PlayChannel(1, tour, 0);
					break;
					}
				break;
				case SDL_KEYUP:
					if (event.key.keysym.sym == keyBindings[ESCAPE]) {
					break; 
					} else if (event.key.keysym.sym == keyBindings[UP]) {
						key[0] = 0;
					break;
					} else if (event.key.keysym.sym == keyBindings[DOWN]) {
						key[1] = 0;
					break;
					} else if (event.key.keysym.sym == keyBindings[LEFT]) {
						key[2] = 0;
					break;
					} else if (event.key.keysym.sym == keyBindings[RIGHT]) {
						key[3] = 0;
					break;
					} else if (event.key.keysym.sym == keyBindings[ATTACK]) {
						key[4] = 0;
					break;
					} else if (event.key.keysym.sym == keyBindings[FIRE]) {
						key[5] = 0;
					break;
					} else if (event.key.keysym.sym == keyBindings[ICE]) {
						key[6] = 0;
					break;
					} else if (event.key.keysym.sym == keyBindings[TOWER]) {
						key[7] = 0;
					break;
					}
				break;
							
			}


	SDL_RenderClear(rendu);

	SDL_GetWindowSize(main_screen,&screen_w,&screen_h);

	showMap(main_screen, rendu, map);

	map->buildings = updateWall(map->buildings);

	manageEnnemies(map);

	showCharacters(rendu, map->characters, map->corner, texture_chara, key, &direction, map->buildings);
	
	changeTypeSpell(key, tab_typeSpell,&current_type);

	if (current_type->id == 2){
		turret(map, current_type, key, direction, &last);
	}else{
		lanceattack(liste_spell, &direction, current_type, key,screen_w /2- PXH_W / 2, screen_h /2 - PXH_H / 2);
		turret_shot(map, liste_spell, tab_typeSpell[3]);
	}

	

	move->x = 0;
	move->y = 0;

	moveMap(main_screen, map, key, move);

	manageSpellType(current_type, rendu, texture_type, font);

	updateSpell(liste_spell, move, main_screen);

	deleteSpell2(liste_spell, map, listitem);

	removeKilled(map->characters->next);

	updateItem(listitem, rendu, texture_item, move);
	
	catchItem(map->characters->current->pos, listitem, map->corner, Itemcaught);

	effect_item(Itemcaught, tab_typeSpell, map->characters->current);

	hero_stat(rendu, font, map);

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

		if(map->characters->current->hp<=0){
			SDL_Rect pos;
			pos.x = 0;
			pos.y = 0;
			SDL_Texture* end_screen = IMG_LoadTexture(rendu, "./images/sprites/game_over.jpeg");
			SDL_RenderClear(rendu);
			Mix_PlayChannel(2, mort, 0);

			SDL_RenderCopy(rendu, end_screen, NULL, &pos);
			int t=0;
			while(t++ < 5000) SDL_RenderPresent(rendu);

			SDL_DestroyTexture(end_screen);
			quit = 2;	
		}
	}

	int i=0;
	for (i = 0; i < 2; ++i)
	{
		free(tab_typeSpell[i]);
	}

	for (i = 0; i < NB_SPRITES_H + NB_SPRITES_A; ++i)
	{
		SDL_DestroyTexture(texture_heros[i]);
	}

	for (i = 0; i < NB_SPRITES_H; ++i)
	{
		SDL_DestroyTexture(texture_ennemy[i]);
	}

	for (i = 0; i < NB_TYP_SPELL*NB_SPRITES_A; ++i)
	{
		SDL_DestroyTexture(texture_attack[i]);
	}

	for (i = 0; i < NB_TYP_SPELL; ++i)
	{
		SDL_DestroyTexture(texture_type[i]);
	}

	for (i = 0; i < NB_ITEM; ++i)
	{
		SDL_DestroyTexture(texture_item[i]);
	}
	
	destroyListItem(listitem);
	destroyListSpell(liste_spell);
	SDL_DestroyTexture(current_texture);
	destroy_texture(NB_SPRITES_H, texture_heros);
	destroyMap(map);
	free(tab_typeSpell);
	free(move);
	Mix_FreeChunk(feu);
	Mix_FreeChunk(glace);
	Mix_FreeChunk(mort);
	Mix_FreeChunk(tour);
	TTF_CloseFont(font);
	Mix_FreeMusic(musique);

	return quit;
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

void init_texture_ennemy(SDL_Renderer *rendu, SDL_Texture *tableau[]){
	tableau[0] = IMG_LoadTexture(rendu, "./images/sprites/monstre0.png");
	tableau[1] = IMG_LoadTexture(rendu, "./images/sprites/monstre1.png");
	tableau[2] = IMG_LoadTexture(rendu, "./images/sprites/monstre2.png");
	tableau[3] = IMG_LoadTexture(rendu, "./images/sprites/monstre3.png");
	tableau[4] = IMG_LoadTexture(rendu, "./images/sprites/monstre4.png");
	tableau[5] = IMG_LoadTexture(rendu, "./images/sprites/monstre5.png");
	tableau[6] = IMG_LoadTexture(rendu, "./images/sprites/monstre6.png");
	tableau[7] = IMG_LoadTexture(rendu, "./images/sprites/monstre7.png");
	tableau[8] = IMG_LoadTexture(rendu, "./images/sprites/monstre8.png");
	tableau[9] = IMG_LoadTexture(rendu, "./images/sprites/monstre9.png");
	tableau[10] = IMG_LoadTexture(rendu, "./images/sprites/monstre10.png");
	tableau[11] = IMG_LoadTexture(rendu, "./images/sprites/monstre11.png");
	tableau[12] = IMG_LoadTexture(rendu, "./images/sprites/monstre12.png");
	tableau[13] = IMG_LoadTexture(rendu, "./images/sprites/monstre13.png");
	tableau[14] = IMG_LoadTexture(rendu, "./images/sprites/monstre14.png");
	tableau[15] = IMG_LoadTexture(rendu, "./images/sprites/monstre15.png");
	tableau[16] = IMG_LoadTexture(rendu, "./images/sprites/monstre16.png");
	tableau[17] = IMG_LoadTexture(rendu, "./images/sprites/monstre17.png");
	tableau[18] = IMG_LoadTexture(rendu, "./images/sprites/monstre18.png");
	tableau[19] = IMG_LoadTexture(rendu, "./images/sprites/monstre19.png");
	tableau[20] = IMG_LoadTexture(rendu, "./images/sprites/monstre20.png");
	tableau[21] = IMG_LoadTexture(rendu, "./images/sprites/monstre21.png");
	tableau[22] = IMG_LoadTexture(rendu, "./images/sprites/monstre22.png");
	tableau[23] = IMG_LoadTexture(rendu, "./images/sprites/monstre23.png");
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
	tableau[2] = IMG_LoadTexture(rendu, "./images/sprites/typespell2.png");
}

void destroy_texture(int taille, SDL_Texture *tableau[]){
	int i;

	for (i = 0; i < taille; i++){
		SDL_DestroyTexture(tableau[i]);
	}

}

void changeTypeSpell (int key[], TypeSpell **tab_typeSpell, TypeSpell **current_type){
	int i;

	for (i = 5 ; i < NB_TYP_SPELL + 4; i ++){
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
		
		if(cantMoveMonster(map->characters, test, cursor->currentSpell,listitem,map)){
			current_list->nextSpell = cursor->nextSpell;
			free(cursor);
			cursor = current_list;
		}else if (cantMoveSpell(map->buildings, test, cursor->currentSpell,listitem,map)){
			current_list->nextSpell = cursor->nextSpell;
			free(cursor);
			cursor = current_list;
		}

		map->characters->next = removeKilled(map->characters->next);

		cursor = cursor->nextSpell;
	}

	free(test);

}

void hero_stat(SDL_Renderer *rendu, TTF_Font* font, Map *map){
	
	SDL_Rect *phealth = malloc(sizeof(SDL_Rect));
	SDL_Rect *plevel = malloc(sizeof(SDL_Rect));
	SDL_Color textColor = { 0, 0, 0, 0 };
	
	char hp[15] = "100";
	char level[15] = "1";

	sprintf(hp, "%d", map->characters->current->hp);

	SDL_Surface *Surface_health = TTF_RenderText_Solid (font, "Health:", textColor);
	SDL_Texture* Text_health = SDL_CreateTextureFromSurface(rendu, Surface_health);	

	SDL_Surface *Surface_hp = TTF_RenderText_Solid (font, hp, textColor);
	SDL_Texture* Text_hp = SDL_CreateTextureFromSurface(rendu, Surface_hp);

	phealth->h = 50;
	phealth->w = 100;
	phealth->x = 10;
	phealth->y = 10;

	SDL_RenderCopy(rendu,Text_health, NULL, phealth);

	phealth->y = phealth->y + 40;

	SDL_RenderCopy(rendu,Text_hp, NULL, phealth);

	sprintf(level, "%d", map->characters->current->level);

	SDL_Surface *Surface_level = TTF_RenderText_Solid (font, "Level:", textColor);
	SDL_Texture* Text_level = SDL_CreateTextureFromSurface(rendu, Surface_level);	

	SDL_Surface *Surface_le = TTF_RenderText_Solid (font, level, textColor);
	SDL_Texture* Text_le = SDL_CreateTextureFromSurface(rendu, Surface_le);

	plevel->h = 50;
	plevel->w = 100;
	plevel->x = SCREEN_W - 150;
	plevel->y = 10;

	SDL_RenderCopy(rendu,Text_level, NULL, plevel);

	plevel->w = 50;
	plevel->y = plevel->y + 40;

	SDL_RenderCopy(rendu,Text_le, NULL, plevel);


	SDL_DestroyTexture(Text_level);
	SDL_DestroyTexture(Text_le);
	SDL_DestroyTexture(Text_health);
	SDL_DestroyTexture(Text_hp);
	SDL_FreeSurface(Surface_health);
	SDL_FreeSurface(Surface_hp);
	SDL_FreeSurface(Surface_level);
	SDL_FreeSurface(Surface_le);

	free(phealth);
	free(plevel);

}

int managing_keybinds(SDL_Window * main_screen, SDL_Renderer *rendu){ //Non terminée

	int keyBindings[NB_TOUCHES]={0}; //On génère les raccourcis clavier
	initialise_keybinds(keyBindings);

	int quit=0;
	int test = 0;
	int limit=0, test2=0;
	int mess=0;
	char* instruction[11] = {"Choisissez la touche a Configurer", "Touche pour se deplacer vers le haut", "Touche pour se deplacer vers le bas", "Touche pour se deplacer vers la gauche", "Touche pour se deplacer vers la droite", "Touche d'attaque", "Touche pour selectionner le feu", "Touche pour selectionner la glace", "Touche pour selectionner les tours", "Touche deja liee a une action"};
	int i;

	char t1 = keyBindings[1];
	char t2 = keyBindings[2];
	char t3 = keyBindings[3];
	char t4 = keyBindings[4];
	char t5 = keyBindings[5];
	char t6 = keyBindings[6];
	char t7 = keyBindings[7];
	char t8 = keyBindings[8];

	SDL_Rect *title3 = malloc(sizeof(SDL_Rect));

	SDL_Rect *point1 = malloc(sizeof(SDL_Rect));
	SDL_GetWindowSize(main_screen,&screen_w,&screen_h);
	
	point1->h = screen_h/9.6;
	point1->w = screen_w/12.8;	
	point1->x = screen_w/2 - screen_w/6 - screen_w/8;
	point1->y = screen_h/2 - screen_h/2.25;
	
	int pas=screen_h/11;

	TTF_Font* font1 = TTF_OpenFont("./images/polices/AmaticSC-Regular.ttf",100); //!!0 création des textures
	SDL_Color textColor1 = { 255, 255, 255, 255 }; 
 
	
SDL_Event event;

while(quit == 0) {

	SDL_PollEvent(&event);	
	switch(event.type){
			case SDL_QUIT:
				quit = 1;
			break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
						case SDLK_ESCAPE:
							quit = 2;
						break;
						case SDLK_UP:
							if (point1->y > screen_h/2 - screen_h/2.25) {
								point1->y = point1->y - pas;
							}
							SDL_Delay(70);							
						break;
						case SDLK_DOWN:
							if (point1->y < screen_h/2 - screen_h/2.25 + 7*pas) {
								point1->y = point1->y + pas;
							}
							SDL_Delay(70);
						break;
						case SDLK_SPACE: ;
							for (i = 1; i < NB_TOUCHES; ++i) {
								if (point1->y <= screen_h/2 - screen_h/2.25 + i*pas && point1->y > screen_h/2 - screen_h/2.25) {
									SDL_RenderClear(rendu); //On affiche l'instruction d'appuyer sur une touche
									mess=i;
									title3->h = screen_h/5; 
									title3->w = screen_w/1.5;	
									title3->x = screen_w/2 - title3->w/2;
									title3->y = screen_h/2 - title3->h/2;
									SDL_Surface *Surface_Tinstruction = TTF_RenderText_Solid (font1, instruction[mess], textColor1);
									SDL_Texture *Text_instruction = SDL_CreateTextureFromSurface(rendu, Surface_Tinstruction);
									SDL_FreeSurface(Surface_Tinstruction);
									SDL_RenderCopy(rendu, Text_instruction, NULL, title3 ); 
									SDL_RenderPresent(rendu);
									SDL_DestroyTexture(Text_instruction);

									SDL_Delay(70);
									SDL_Event event;
									mess=0;
									int reussi=0;							
									while( reussi==0) {
										SDL_PollEvent(&event);
										if(event.type==SDL_KEYDOWN){
											if(event.key.keysym.sym == SDLK_ESCAPE) {
												reussi = 1;
												break;
											} else {
												int test=2;
												test = configureKeybind(i, keyBindings, event.key.keysym.sym);
												//On vérifie qu'on peut attribuer cette touche
												if (test == 1) {
													mess=9;
													SDL_RenderClear(rendu);
													SDL_Surface *Surface_Tinstruction = TTF_RenderText_Solid (font1, instruction[mess], textColor1);
													SDL_Texture *Text_instruction = SDL_CreateTextureFromSurface(rendu, Surface_Tinstruction);
													SDL_FreeSurface(Surface_Tinstruction);
													SDL_RenderCopy(rendu, Text_instruction, NULL, title3 ); 
													SDL_RenderPresent(rendu);
													SDL_DestroyTexture(Text_instruction);
													mess=0;
												} else {
													if (test == 0) {
														reussi = 1;
													}
												}
											}
										}
									}
								break;
								}
								
							}
							if (point1->y <= screen_h/2 - screen_h/2.25) {
								createCustomKeybinds();
								
							}
						break;
				break;
			}
			
	}
	SDL_RenderClear(rendu); //!!1

	SDL_Surface *Surface_Ttitle0 = TTF_RenderText_Solid (font1, "Reinitialiser", textColor1);
	SDL_Texture *Text_title0 = SDL_CreateTextureFromSurface(rendu, Surface_Ttitle0);
	SDL_FreeSurface(Surface_Ttitle0);

	SDL_Surface *Surface_Tkeytitle1 = TTF_RenderText_Solid (font1, "Haut", textColor1);
	SDL_Texture *Text_keytitle1 = SDL_CreateTextureFromSurface(rendu, Surface_Tkeytitle1);
	SDL_FreeSurface(Surface_Tkeytitle1);

	SDL_Surface *Surface_Tkeytitle2 = TTF_RenderText_Solid (font1, "Bas", textColor1);
	SDL_Texture *Text_keytitle2 = SDL_CreateTextureFromSurface(rendu, Surface_Tkeytitle2);
	SDL_FreeSurface(Surface_Tkeytitle2);

	SDL_Surface *Surface_Tkeytitle3 = TTF_RenderText_Solid (font1, "Gauche", textColor1);
	SDL_Texture *Text_keytitle3 = SDL_CreateTextureFromSurface(rendu, Surface_Tkeytitle3);
	SDL_FreeSurface(Surface_Tkeytitle3);

	SDL_Surface *Surface_Tkeytitle4 = TTF_RenderText_Solid (font1, "Droite", textColor1);
	SDL_Texture *Text_keytitle4 = SDL_CreateTextureFromSurface(rendu, Surface_Tkeytitle4);
	SDL_FreeSurface(Surface_Tkeytitle4);

	SDL_Surface *Surface_Tkeytitle5 = TTF_RenderText_Solid (font1, "Attaque", textColor1);
	SDL_Texture *Text_keytitle5 = SDL_CreateTextureFromSurface(rendu, Surface_Tkeytitle5);
	SDL_FreeSurface(Surface_Tkeytitle5);

	SDL_Surface *Surface_Tkeytitle6 = TTF_RenderText_Solid (font1, "Feu", textColor1);
	SDL_Texture *Text_keytitle6 = SDL_CreateTextureFromSurface(rendu, Surface_Tkeytitle6);
	SDL_FreeSurface(Surface_Tkeytitle6);

	SDL_Surface *Surface_Tkeytitle7 = TTF_RenderText_Solid (font1, "Glace", textColor1);
	SDL_Texture *Text_keytitle7 = SDL_CreateTextureFromSurface(rendu, Surface_Tkeytitle7);
	SDL_FreeSurface(Surface_Tkeytitle7);

	SDL_Surface *Surface_Tkeytitle8 = TTF_RenderText_Solid (font1, "Tour", textColor1);
	SDL_Texture *Text_keytitle8 = SDL_CreateTextureFromSurface(rendu, Surface_Tkeytitle8);
	SDL_FreeSurface(Surface_Tkeytitle8);

	SDL_Surface *Surface_Tinstruction = TTF_RenderText_Solid (font1, instruction[mess], textColor1);
	SDL_Texture *Text_instruction = SDL_CreateTextureFromSurface(rendu, Surface_Tinstruction);
	SDL_FreeSurface(Surface_Tinstruction);
		
		title3->h = screen_h/10;  //definit la taille des textures
		title3->w = screen_w/3;	
		title3->x = screen_w/2 - title3->w/2;
		title3->y = screen_h/2 - title3->h/2 - 4*screen_h/10;


	SDL_RenderCopy(rendu, Text_title0, NULL, title3 ); //!!2
	title3->y += pas;
	SDL_RenderCopy(rendu, Text_keytitle1, NULL, title3 ); //!!2
	title3->y += pas;
	SDL_RenderCopy(rendu, Text_keytitle2, NULL, title3 );
	title3->y += pas;
	SDL_RenderCopy(rendu, Text_keytitle3, NULL, title3 );
	title3->y += pas;
	SDL_RenderCopy(rendu, Text_keytitle4, NULL, title3 ); 
	title3->y += pas;
	SDL_RenderCopy(rendu, Text_keytitle5, NULL, title3 );
	title3->y += pas;
	SDL_RenderCopy(rendu, Text_keytitle6, NULL, title3 );
	title3->y += pas;
	SDL_RenderCopy(rendu, Text_keytitle7, NULL, title3 );
	title3->y += pas;
	SDL_RenderCopy(rendu, Text_keytitle8, NULL, title3 ); 
	title3->y += pas;
	title3->w = title3->w*2;
	title3->x = screen_w/2 - title3->w/2;
	SDL_RenderCopy(rendu, Text_instruction, NULL, title3 ); 

	SDL_Texture* Pointeur = IMG_LoadTexture(rendu, "./images/sprites/cursor.png");	
	SDL_RenderCopy(rendu, Pointeur, NULL, point1 );
	
	SDL_RenderPresent(rendu); //!!3
	SDL_DestroyTexture(Text_keytitle1);
	SDL_DestroyTexture(Text_keytitle2);
	SDL_DestroyTexture(Text_keytitle3);
	SDL_DestroyTexture(Text_keytitle4);
	SDL_DestroyTexture(Text_keytitle5);
	SDL_DestroyTexture(Text_keytitle6);
	SDL_DestroyTexture(Text_keytitle7);
	SDL_DestroyTexture(Text_keytitle8);
	SDL_DestroyTexture(Pointeur);
	SDL_DestroyTexture(Text_title0);
	SDL_DestroyTexture(Text_instruction);



	test2 = SDL_GetTicks();	

		if (limit > test){
			if (limit > test + FPS){
				SDL_Delay(FPS);
			}
			else {
				SDL_Delay(limit - test);
			}
		}

		limit = SDL_GetTicks() + FPS;

}
SDL_RenderClear(rendu);
return quit;
}

