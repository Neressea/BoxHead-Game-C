#include "../header/Spell.h"

int screen_h1 = SCREEN_H;
int screen_w1 = SCREEN_W;


/*void compute_attack(SDL_Rect *pattack[], int *f, int key[]){

	if(key[4]){
		if (*f == 0 && pattack[0]->y >= screen_h1){
			pattack[0]->y = screen_h1 / 2 - PXH_H / 2;
		}
		else if(*f == 3){
			pattack[1]->y = screen_h1 / 2 - PXH_H / 2;
		}
		else if(*f == 6){
			pattack[2]->x = screen_w1 / 2 - PXH_W / 2;
		}
	}

	
	

}

void blit_attack(SDL_Rect *pattack[], SDL_Renderer *rendu, SDL_Texture *tableau[]){
	
	if(pattack[0]->y < screen_h1){
		SDL_RenderCopy(rendu, tableau[0], NULL, pattack[0]);
		SDL_RenderPresent(rendu);
		pattack[0]->y += SPEED;
	}

	if(pattack[1]->y > 0){
		SDL_RenderCopy(rendu, tableau[0], NULL, pattack[1]);
		SDL_RenderPresent(rendu);
		pattack[1]->y -= SPEED;
	}

	if(pattack[2]->x > 0){
		SDL_RenderCopy(rendu, tableau[0], NULL, pattack[2]);
		SDL_RenderPresent(rendu);
		pattack[2]->x -= SPEED;
	}

}

void init_attack(SDL_Rect *pattack[]){
	int i;

	for (i=0; i < NB_SPRITES_A ;i++){
		pattack[i] = malloc(sizeof(SDL_Rect));

		pattack[i]->h = PXH_H;
		pattack[i]->w = PXH_W;
	}
	
	pattack[0]->x = screen_w1 /2 - PXH_W / 2;
	pattack[0]->y = screen_h1;
	pattack[1]->x = screen_w1 /2 - PXH_W / 2;
	pattack[1]->y = 0;
	pattack[2]->x = 0;
	pattack[2]->y = screen_h1 /2 - PXH_H / 2;
	

}*/

Spell* createSpell(TypeSpell *type, int direction, int x, int y){
	Spell *c = malloc(sizeof(Spell));
	c->type = type;
	c->direction = direction;
	c->pspell = malloc(sizeof(SDL_Rect));
	c->pspell->h = PX_H;
	c->pspell->w = PX_W;
	c->pspell->x = x;
	c->pspell->y = y;

	return c;

}

void updateSpell(ListSpell current_list){
	while(current_list.currentSpell != NULL){

	}
}



