#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

int main(){

	int bloque = 1;	

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // gestion erreur chargement SDL
		exit(EXIT_FAILURE);
	}

	SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);

	while(bloque){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_QUIT:
				bloque = 0;
			break;
		}

        }


	SDL_Quit();

	return EXIT_SUCCESS;
}
