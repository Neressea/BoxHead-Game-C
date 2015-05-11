#include "../header/Item.h"

void poseItem(ListItem *listitem, int x, int y){

	int hasard;

	Item *it = createItem(0,x,y);
	ListItem *cursor = listitem->next;
	ListItem *new = malloc(sizeof(ListItem));
	new->current = it;
	new->next = NULL;

	hasard = rand()%10;

	if (cursor == NULL){
		if(hasard <8){
			listitem->next=new;	
		}
	}else{
		while(cursor != NULL){
			if (cursor->next == NULL){
				if(hasard < 8){
					cursor->next=new;
				}

				break;
			} 
			cursor=cursor->next;
		}
	}
	
}

Item* createItem(int id, int x, int y){
	Item* b = (Item*) malloc(sizeof(Item));
	b->id = id;
	b->time = SDL_GetTicks();
	b->pitem = malloc(sizeof(SDL_Rect));
	b->pitem->h = ITEM_H;
	b->pitem->w = ITEM_W;
	b->pitem->x = x;
	b->pitem->y = y;

	return b;
}

void updateItem(ListItem *listitem, SDL_Renderer *rendu, SDL_Texture *tableau[]){
	ListItem *cursor = listitem->next;
	
	while(cursor != NULL){
		if (SDL_GetTicks() - cursor->current->time > LIFEEXPANC){
			listitem->next = cursor->next;
			free(cursor->current);			
			free(cursor);
			cursor = listitem;
		}
		cursor = cursor->next;		
	}

	cursor = listitem->next;
	
	while(cursor != NULL){
		                
		SDL_RenderCopy(rendu, tableau[cursor->current->id], NULL, cursor->current->pitem);		

		cursor = cursor->next;		

	}

	
}

ListItem* init_listItem(){
	ListItem *b = malloc(sizeof(ListItem));
	b->current = NULL;
	b->next = NULL;

	return b;

}
