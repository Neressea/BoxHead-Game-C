#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../header/Main.h"

int screen_h = SCREEN_H;
int screen_w = SCREEN_W;

int main(){

	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}

	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1){
		fprintf(stderr, "Erreur d'initialisation des images : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}

	managing_event();

	IMG_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}

void managing_event(){

	SDL_Window *main_screen = NULL;
	SDL_Renderer *rendu = NULL;
	SDL_Texture *texture_heros[NB_SPRITES_H] = {NULL};
	SDL_Texture *texture_attack[NB_SPRITES_A] = {NULL};
	SDL_Texture *current_texture = NULL;
	SDL_Rect *pheros = NULL;
	SDL_Rect *pattack = NULL;
	Map *map = malloc(sizeof(Map));
	
	int quit = 0;
	int key[5] = {0};
	int j = 0;
	int f = 0;
	int trame = 0;
	int limit = 0;
	int test = 0;
	
	main_screen = SDL_CreateWindow("Jeu de la mort qui tue",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_W,SCREEN_H, SDL_WINDOW_SHOWN|
SDL_WINDOW_RESIZABLE);
 			 // iniatializing screen

	rendu = SDL_CreateRenderer(main_screen, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(rendu, 0, 255, 255, 255);
	SDL_RenderClear(rendu);
	
	init_texture(rendu, texture_heros);
	init_texture_attack(rendu, texture_attack); 
	
	current_texture = texture_heros[0];

	if (current_texture == NULL){
		fprintf(stderr, "Erreur d'initialisation de sprite courant : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}

	load(rendu, map, "./maps/map1");

	pheros = malloc(sizeof(SDL_Rect));

	pheros->h = PXH_H;
	pheros->w = PXH_W;
	pheros->x = screen_w /2- PXH_W / 2;
	pheros->y = screen_h / 2 - PXH_H / 2;

	pattack = malloc(sizeof(SDL_Rect));
	
	pattack->h = PXH_H;
	pattack->w = PXH_W;
	pattack->x = screen_w /2- PXH_W / 2;
	pattack->y = screen_h / 2 - PXH_H / 2;

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
						}
				break;
								
			}

	

	SDL_RenderClear(rendu);
	show(rendu, map);
	
	j++;
	compute_tram(&j, &trame);

	SDL_GetWindowSize(main_screen,&screen_w,&screen_h);

	pheros->x = screen_w /2- PXH_W / 2;
	pheros->y = screen_h / 2 - PXH_H / 2;

	current_texture = update_heros(key, texture_heros, &trame, &f);
	SDL_RenderCopy(rendu, current_texture, NULL, pheros);	
	SDL_RenderPresent(rendu);

	attack_heros(pattack,&f, rendu, texture_attack, key);

	//test_key(key, pheros);
	moveMap(map, key);	

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
	
}

void init_texture_attack(SDL_Renderer *rendu, SDL_Texture *tableau[]){
	tableau[0] = IMG_LoadTexture(rendu, "./images/sprites/tower.png");
}

void destroy_texture(int taille, SDL_Texture *tableau[]){
	int i;

	for (i = 0; i < taille; i++){
		SDL_DestroyTexture(tableau[i]);
	}

}

SDL_Texture* update_heros(int key[], SDL_Texture *tableau[], int *trame, int *f){
	
	if (key[0] && key[2]){
		*f = 21;		
		return tableau[21 + text_move(trame)];
	}
	if (key[0] && key[3]){
		*f = 18;
		return tableau[18 + text_move(trame)];
	}
	if (key[0] && !key[3] && !key[2]){
		*f = 3;
		return tableau[3 + text_move(trame)];
	}
	
	if (key[1] && key[2]){
		*f = 15;
		return tableau[15 + text_move(trame)];
	}
	if (key[1] && key[3]){
		*f = 12;
		return tableau[12 + text_move(trame)];
	}
	if (key[1] && !key[3] && !key[2]){
		*f = 0;
		return tableau[0 + text_move(trame)];
	}
		
	if (key[2] && !key[0] && !key[1]){
		*f = 6;		
		return tableau[6 + text_move(trame)];
	}
	if (key[3] && !key[0] && !key[1]){
		*f = 9;
		return tableau[9 + text_move(trame)];
	}

	return tableau[*f];

}

void compute_tram(int *j, int *trame){
	if (*j > SPEED_TRAME * 4){
		*j = 0;
	}

	*trame = *j % SPEED_TRAME;

}

int text_move(int *trame){
	if (*trame == 0){
		return 0;
	}
	else if (*trame == 1){
		return 1;
	}
	else if (*trame == 2){
		return 0;
	}
	else {
		return 2;
	}

	return 0;

}

void attack_heros(SDL_Rect *pattack,int *f, SDL_Renderer *rendu, SDL_Texture *tableau[], int key[]){

	if (key[4]){
		pattack->y = screen_h / 2 - PXH_H / 2;
		printf("Remise zéro\n");
	}

	if(pattack->y < screen_h){
		SDL_RenderCopy(rendu, tableau[*f], NULL, pattack);
		SDL_RenderPresent(rendu);
		printf("Blit\n");
		pattack->y += SPEED;
	}

	
	

}


