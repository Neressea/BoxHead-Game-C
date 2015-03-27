#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../header/Main.h"



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
	SDL_Texture *current_texture = NULL;
	SDL_Rect *pennemy = NULL;
	Map *map;
	
	
	main_screen = SDL_CreateWindow("Jeu de la mort qui tue",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_W,SCREEN_H, SDL_WINDOW_SHOWN); 			 // iniatializing screen

	rendu = SDL_CreateRenderer(main_screen, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(rendu, 0, 255, 255, 255);
	SDL_RenderClear(rendu);
	
	init_texture(rendu, texture_heros);
	
	current_texture = texture_heros[0];

	if (current_texture == NULL){
		fprintf(stderr, "Erreur d'initialisation de sprite courant : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}

	map = load(rendu, "./maps/map1");

	pennemy = malloc(sizeof(SDL_Rect));
	
	pennemy->h = PXH_H;
	pennemy->w = PXH_W;
	pennemy->x = 0;
	pennemy->y = 0;

	int quit = 0;
	int key[4] = {0};
	int i;
	int j = 0;
	int f = 0;
	int trame = 0;

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

						}
				break;
								
			}

	

	SDL_RenderClear(rendu);
	show(rendu, map);
	
	j++;
	compute_tram(&j, &trame);

	current_texture = update_heros(key, texture_heros, &trame, &f);
	SDL_RenderCopy(rendu, current_texture, NULL, pennemy);	
	SDL_RenderPresent(rendu);

	test_key(key, pennemy);	

	SDL_Delay(1);

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
	tableau[3] = IMG_LoadTexture(rendu, "./images/sprites/heros3.png");
	tableau[6] = IMG_LoadTexture(rendu, "./images/sprites/heros6.png");
	tableau[12] = IMG_LoadTexture(rendu, "./images/sprites/heros12.png");
	tableau[15] = IMG_LoadTexture(rendu, "./images/sprites/heros15.png");
	
}

void destroy_texture(int taille, SDL_Texture *tableau[]){
	int i;

	for (i = 0; i < taille; i++){
		SDL_DestroyTexture(tableau[i]);
	}

}

SDL_Texture* update_heros(int key[], SDL_Texture *tableau[], int *trame, int *f){
	
	if (key[0] && key[2]){
		return tableau[0];
	}
	if (key[0] && key[3]){
		return tableau[0];
	}
	if (key[0] && !key[3] && !key[2]){
		*f = 3;
		return tableau[3];
	}
	
	if (key[1] && key[2]){
		*f = 15;
		return tableau[15];
	}
	if (key[1] && key[3]){
		*f = 12;
		return tableau[12];
	}
	if (key[1] && !key[3] && !key[2]){
		*f = 0;
		if (*trame == 0){
			return tableau[0];
		}
		else if (*trame == 1){
			return tableau[1];
		}
		else if (*trame == 2){
			return tableau[0];
		}
		else {
			return tableau[1];
		}
	}
		
	if (key[2] && !key[0] && !key[1]){
		*f = 6;		
		return tableau[6];
	}
	if (key[3] && !key[0] && !key[1]){
		return tableau[0];
	}

	return tableau[*f];

}

void compute_tram(int *j, int *trame){
	if (*j > SPEED_TRAME * 4){
		*j = 0;
	}

	*trame = *j % SPEED_TRAME;

}


