#include "../header/Character.h"

/**
* Move the character
*/
void move(Character *p, int key[]){
	if (key[0] && key[2]){
		p->pos->y -= SPEED;
		p->pos->x -= SPEED;
	}
	if (key[0] && key[3]){
		p->pos->y -= SPEED;
		p->pos->x += SPEED;
	}
	if (key[0] && !key[3] && !key[2]){
		p->pos->y -= SPEED;
	}
	
	if (key[1] && key[2]){
		p->pos->y += SPEED;
		p->pos->x -= SPEED;
	}
	if (key[1] && key[3]){
		p->pos->y += SPEED;
		p->pos->x += SPEED;
	}
	if (key[1] && !key[3] && !key[2]){
		p->pos->y += SPEED;
	}
		
	if (key[2] && !key[0] && !key[1]){
		p->pos->x -= SPEED;
	}
	if (key[3] && !key[0] && !key[1]){
		p->pos->x += SPEED;
	}
}

/**
* p1 attacks p2
*/
void attackCharacter(Character p1, Character p2){
	p1.hp = 0;
	p2.hp = 0;

	int hh = p1.hp + p2.hp;
	p1.hp = hh;
}

/**
* p attacks the building b
*/
void attackBuilding(Character p, Building b){
	p.hp = 0;
	b.hp = 0;

	int hh = p.hp + b.hp;
	p.hp = hh;
}

Character *createChar(int hp, int defense, int attack, int level, int xp, int pos_x, int pos_y, int w, int h, ListSpell *spells){
	Character *c = malloc(sizeof(Character));
	c->hp = hp;
	c->defense = defense;
	c->attack = attack;
	c->level = level;
	c->xp = xp;
	c->pos = malloc(sizeof(SDL_Rect));
	c->pos->x = pos_x * PX_W;
	c->pos->y = pos_y * PX_H;
	c->pos->w = w;
	c->pos->h = h;
	c->spells = spells;

	return c;
}

int size(ListChar *characters){
	int nb=0;

	ListChar* ch = characters;
	while(ch != NULL){
		ch = ch->next;
		nb++;
	}

	return nb;
}

void addChar(ListChar *characters, Character* ch){

	ListChar *ennemy = malloc(sizeof(ListChar));

	while(characters->next != NULL) characters = characters->next;

	ennemy->current = ch;
	ennemy->next = NULL;

	characters->next = ennemy;
}

void showCharacters(SDL_Renderer *rendu, ListChar* characters, SDL_Rect* corner, SDL_Texture*** texture_chara, int key[], int* direction, ListBuilding* b){

	SDL_Texture** texture_heros = texture_chara[0];
	SDL_Texture** texture_ennemy = texture_chara[1];
	SDL_Texture* current_texture = texture_heros[0];

	SDL_Rect *blit = malloc(sizeof(SDL_Rect));
	blit->x = characters->current->pos->x - corner->x;
	blit->y = characters->current->pos->y - corner->y;
	blit->w = characters->current->pos->w;
	blit->h = characters->current->pos->h;

	static int trame = 0;
	static int j = 0;
	current_texture = update_texture(key, texture_heros, &trame, direction);
	compute_tram(&j, &trame);

	SDL_RenderCopy(rendu, current_texture, NULL, blit);

	//WE MOVE THE ENNEMIES
	Character* heros = characters->current;
	characters = characters->next;
	int key2[5]={0, 0, 0, 0, 0};
	int direction2 = 0;

	int i=0;

	while(characters != NULL){

		moveEnnemy(b, heros, characters->current, key2);
		current_texture = update_texture(key2, texture_ennemy, &trame, &direction2);

		blit->x= characters->current->pos->x - corner->x;
		blit->y= characters->current->pos->y - corner->y;

		SDL_RenderCopy(rendu, current_texture, NULL, blit);

		characters = characters->next;
	}


	free(blit);
}

SDL_Texture* update_texture(int key[], SDL_Texture *tableau[], int *trame, int *f){
	
	if (key[4]){
		return tableau[*f/3 + 24];
	}	

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
		return tableau[*f + text_move(trame)];
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

void compute_tram(int *j, int *trame){
	if (*j > SPEED_TRAME * 4){
		*j = 0;
	}

	*trame = (*j /SPEED_TRAME) % 4;
	(*j)++;
}

ListChar* removeKilled(ListChar* characters){

	//We delete the killed monsters in the head of the list
	ListChar *head = characters;
	while(head != NULL && head->current->hp <= 0)head = head->next;

	ListChar* previous = head;
	ListChar* cur = (head) ? head->next : NULL;

	while(cur != NULL){
		if(cur->current->hp<=0){
			previous->next = cur->next;
			ListChar* tmp = cur->next;
			free(cur);
			cur = tmp;
		}else{
			previous = cur;
			cur = cur->next;
		}
	}

	return head;
}

void add_xp(Character* ch, int dam){
	ch->xp+=dam;

	if(ch->xp >= (ch->level * 100)){
		ch->level++;
		ch->xp = 0;
	}
	
} 

void destroyChara(Character *c){
	free(c->pos);
	destroyListSpell(c->spells);
	free(c);
}

void destroyListChara(ListChar *lc){
	ListChar* nextC = NULL;

	while(lc != NULL){
		nextC = lc->next;
		destroyChara(lc->current);
		free(lc);
		lc = nextC;
	}	
}