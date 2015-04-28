#include "./header/IA.h"

void manageEnnemies(Map* map){
	int level = map->characters->current->level; //We get the level of the player to define the difficulty

}

Character* createEnnemy(int level){

	//We select the position where the ennemy will appear
	int x = ;
	int y = ;

	Character* ch = createChar(10 * level, 10 * (level-1), 5 * level, 0, 0, int pos_x, int pos_y, NULL);

	return ch;
}
