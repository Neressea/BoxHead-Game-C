#include "../header/Item.h"

void poseItem(ListItem *listitem, int x, int y){

	int hasard;

	ListItem *cursor = listitem;
	ListItem *new = malloc(sizeof(ListItem));
	new->current = createItem(0,x,y);
	new->next = NULL;

	while(cursor != NULL){
		if (cursor->next == NULL){
			hasard = rand()%10;
			if(hasard < 8){
				cursor->next=new;
			}else{

			}
			break;
		} 
		cursor=cursor->next;
	}
}

Item* createItem(int id, int x, int y){
	Item* b = malloc(sizeof(Item));
	b->id = id;
	b->time = SDL_GetTicks();
	b->pitem->h = ITEM_H;
	b->pitem->w = ITEM_W;
	b->pitem->x = x;
	b->pitem->y = y;

	return b;
}

void updateItem(ListItem *listitem){
	ListItem *cursor = listitem;
	
	while(cursor != NULL){
		if (SDL_GetTicks() - cursor->current->time > LIFEEXPANC){
			listitem->next = cursor->next;
			free(cursor->current);			
			free(cursor);
			cursor = listitem;
		}
		
		cursor = cursor->next;		

	}
}

