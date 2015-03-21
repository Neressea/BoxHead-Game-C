#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../header/Main.h"

int main(){

	

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // managing SDL loading error 
		exit(EXIT_FAILURE);
	}

	SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE || SDL_DOUBLEBUF); // iniatializing screen
	SDL_WM_SetCaption("Jeu de la mort qui tue", NULL); // set name to this screen
	
	managing_event();

	SDL_Quit();

	return EXIT_SUCCESS;
}


void managing_event(){
	
	SDL_Surface *main_screen, *ennemy = NULL;
	SDL_Rect pennemy;
	

	main_screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE || SDL_DOUBLEBUF);
	ennemy = SDL_LoadBMP("../images/sprites/ennemy.bmp");
	SDL_FillRect(main_screen, NULL, SDL_MapRGB(main_screen->format, 255, 255, 255));

	pennemy.x = main_screen->w / 2 - ennemy->w / 2;
	pennemy.y = main_screen->h / 2 - ennemy->h / 2;

	int bloque = 1;
	int up = 0;
	int down = 0; 
	int le = 0; 
	int ri = 0;

	SDL_Event event;

	SDL_EnableKeyRepeat(10, 10);

	while(bloque){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				bloque = 0;
			break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){	//openclassrooms.com/uploads/fr/ftp/mateo21/sdlkeysym.html
					case SDLK_ESCAPE:
        				break;
					case SDLK_UP:
						up = 1;
					break;
					case SDLK_DOWN:
						down = 1;
					break;
					case SDLK_LEFT:
						le = 1;
					break;
					case SDLK_RIGHT:
						ri = 1;
					break;

					}
			break;
		}
	
	if (up){		
		pennemy.y --;
		up = 0;		
	}
	else if (down){
		pennemy.y ++;
		down = 0;
	
	}

	if (le){
		pennemy.x --;
		le = 0;
	}
	else if (ri){
		pennemy.x ++;
		ri = 0;
	}

	
	SDL_FillRect(main_screen, NULL, SDL_MapRGB(main_screen->format, 255, 255, 255));
	SDL_BlitSurface(ennemy,NULL, main_screen,&pennemy);
	SDL_Flip(main_screen);

	}


}

void key_event(SDL_Event *event,SDL_Rect *pennemy){
	
	int up, down, le, ri = 0;
	
	switch ((*event).key.keysym.sym){	//openclassrooms.com/uploads/fr/ftp/mateo21/sdlkeysym.html
		case SDLK_ESCAPE:
        	break;
		case SDLK_UP:
			up = 1;
		break;
		case SDLK_DOWN:
			down = 1;
		break;
		case SDLK_LEFT:
			le = 1;
		break;
		case SDLK_RIGHT:
			ri = 1;
		break;

	}

	if (up){		
		pennemy->y --;
		up = 0;		
	}
	else if (down){
		pennemy->y ++;
		down = 0;
	
	}

	if (le){
		pennemy->x --;
		le = 0;
	}
	else if (ri){
		pennemy->x ++;
		ri = 0;
	}


	


}


