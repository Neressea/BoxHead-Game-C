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
		if(hasard <5){
			listitem->next=new;	
		}
	}else{
		while(cursor != NULL){
			if (cursor->next == NULL){
				if(hasard <5){
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

void updateItem(ListItem *listitem, SDL_Renderer *rendu, SDL_Texture *tableau[], Move *move){
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
		                
		update_blitmap(move, cursor->current->pitem);

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

int catchItem(SDL_Rect* pos, ListItem *listitem, SDL_Rect *corner){
	int cant = 0;

	ListItem* b = listitem->next;

	while(cant==0 && b != NULL){

		//If we are between the x position of the building
		if(pos->x + PXH_W >= b->current->pitem->x + corner->x && pos->x <= b->current->pitem->x + corner->x + ITEM_W){
			if(pos->y + PXH_H >= b->current->pitem->y + corner ->y && pos->y <= b->current->pitem->y + corner -> y + ITEM_W){
				cant=1;

				printf("atteint\n");				


			}
		}
		b = b->next;
	}
	return cant;
}

