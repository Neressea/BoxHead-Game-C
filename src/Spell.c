#include "../header/Spell.h"

int screen_h1 = SCREEN_H;
int screen_w1 = SCREEN_W;

Spell* createSpell(TypeSpell *type, int *direction, int x, int y){
	Spell *c = (Spell*) malloc(sizeof(Spell));
	c->type = type;
	c->direction = *direction;
	c->time = SDL_GetTicks();
	c->pspell = malloc(sizeof(SDL_Rect));
	if (*direction == 6 || *direction == 9){
		c->pspell->h = SPELL_W;
		c->pspell->w = SPELL_H;
		c->pspell->y = y + 20;
		c->pspell->x = x;
	}else{
		c->pspell->h = SPELL_H;
		c->pspell->w = SPELL_W;
		c->pspell->y = y;
		c->pspell->x = x + 10;
	}


	return c;

}



void deleteSpell(ListSpell *current_list){
	
	ListSpell *cursor = current_list->nextSpell;
	
	while(cursor != NULL){
		if (SDL_GetTicks() - cursor->currentSpell->time > LIFEEXPANC){
			current_list->nextSpell = cursor->nextSpell;
			free(cursor->currentSpell);			
			free(cursor);
			cursor = current_list;
		}
		
		cursor = cursor->nextSpell;		

	}
}

void updateSpell(ListSpell *current_list, Move* move, SDL_Window *main_screen){
	
	SDL_GetWindowSize(main_screen,&screen_w1,&screen_h1);	

	deleteSpell(current_list);

	ListSpell *cursor = current_list->nextSpell;

	int current_direction = 0;

	while(cursor != NULL){

		current_direction = cursor->currentSpell->direction;
		update_blitmap(move, cursor->currentSpell->pspell);

		if (current_direction == 0){
			cursor->currentSpell->pspell->y += 2*SPEED;		
		}
		if (current_direction == 3){
			cursor->currentSpell->pspell->y -= 2*SPEED;
		}
		if (current_direction == 6){
			cursor->currentSpell->pspell->x -= 2*SPEED;
		}
		if (current_direction == 9){
			cursor->currentSpell->pspell->x += 2*SPEED;
		}
		if (current_direction == 12){
			cursor->currentSpell->pspell->y += 2*SPEED;
			cursor->currentSpell->pspell->x += 2*SPEED;
		}
		if (current_direction == 15){
			cursor->currentSpell->pspell->y += 2*SPEED;
			cursor->currentSpell->pspell->x -= 2*SPEED;
		}
		if (current_direction == 18){
			cursor->currentSpell->pspell->y -= 2*SPEED;
			cursor->currentSpell->pspell->x += 2*SPEED;
		}
		if (current_direction == 21){
			cursor->currentSpell->pspell->y -= 2*SPEED;
			cursor->currentSpell->pspell->x -= 2*SPEED;
		}

		cursor = cursor->nextSpell;
	}

}


void lanceattack(ListSpell *current_list, int *f, TypeSpell *current_type, int key[], int x, int y){
	
	ListSpell *cursor = current_list->nextSpell;	

	if (key[4] && current_type->ammo != 0){
		
		Spell *new = createSpell(current_type, f, x, y);			
		ListSpell * newlist = malloc(sizeof(ListSpell));
		newlist->currentSpell = new;
		newlist->nextSpell = NULL; 

		unsigned int t = SDL_GetTicks() - current_type->time;
		unsigned int r = current_type->rate; 
		if ( t>r ){
			if (cursor == NULL){
			current_list->nextSpell = newlist;
			}
			else{
			cursor->nextSpell = newlist;
			}
			current_type->ammo --;
			current_type->time = SDL_GetTicks();
		}		
	}
}

TypeSpell *init_typeSpell(int attack, int id, int rate, int ammo){
	TypeSpell *t= malloc(sizeof(TypeSpell));

	t->id = id;
	t->attack = attack;
	t->ammo = ammo;
	t->rate = rate;

	return t;
}

void Blit_attack(ListSpell *current_list,SDL_Renderer *rendu, SDL_Texture *tableau[]){
        
        ListSpell *cursor = current_list->nextSpell;
	
	while(cursor != NULL){
		                
		SDL_RenderCopy(rendu, tableau[cursor->currentSpell->direction/3 + (NB_SPRITES_A*cursor->currentSpell->type->id)], NULL, cursor->currentSpell->pspell);
		
		
		cursor = cursor->nextSpell;		

	}

	SDL_RenderPresent(rendu);


}

ListSpell *init_listspell(){
	ListSpell *list = malloc(sizeof(ListSpell));	
	list->currentSpell = NULL;
	list->nextSpell = NULL;

	return list;
}

void update_blitmap (Move* move, SDL_Rect *position){
	position->x -= move ->x;
	position->y -= move ->y;


}

void manageSpellType(TypeSpell *current_type, SDL_Renderer *rendu, SDL_Texture *texture_type[], TTF_Font* font){
	SDL_Rect *pattack = malloc(sizeof(SDL_Rect));
	SDL_Color textColor = { 0, 0, 0, 0 };
	
	char nbAmmo[15] = "Inf";
	
	if (current_type->ammo >= 0){
		sprintf(nbAmmo, "%d", current_type->ammo);
	}

	SDL_Surface *Surface_Ammo = TTF_RenderText_Solid (font, nbAmmo, textColor);
	SDL_Texture* Text_Ammo = SDL_CreateTextureFromSurface(rendu, Surface_Ammo);

	pattack->h = PX_H;
	pattack->w = PX_W;
	pattack->x = 10;
	pattack->y = SCREEN_H - PX_W - 25;

	SDL_RenderCopy(rendu, texture_type[current_type->id], NULL, pattack);

	pattack->h = PX_H/2.5;
	pattack->w = PX_W/2.5;
	pattack->x = 75;
	pattack->y = SCREEN_H - PX_W + 30;
	
	SDL_RenderCopy(rendu, Text_Ammo, NULL, pattack );

	free(pattack);
	SDL_FreeSurface(Surface_Ammo);
	SDL_DestroyTexture(Text_Ammo);
}

void destroyListSpell(ListSpell* ls){
	ListSpell *succ;
	while(ls){
		succ = ls->nextSpell;
		destroySpell(ls->currentSpell);
		free(ls);
		ls = succ;
	}
}

void destroySpell(Spell* s){
	//free(s->pspell);
	free(s);
}


