#ifndef char_h
#define char_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Spell.h"
#include "Building.h"
#include "Globals.h"
#include "Main.h"


/**
* This struct defines what a character is, for the main char and ennemies.
* hp : points of life. When comes to 0, the char dies.
* defense : 
* attack : attack points
* level : the current level of the character
* xp : the experience of the char
* pos : the position of the character
* spells : the list of spells of the character.
*/
typedef struct{
	int hp;
	int defense;
	int attack;
	int level;
	int xp;
	SDL_Rect *pos;
	ListSpell* spells;
}Character;

/**
* Defines a list of characters.
* current : the current character in the list.
* next : the next character in ths list. NULL if it is the end.
*/
typedef struct ListChar ListChar;
struct ListChar{
	Character *current;
	struct ListChar* next;
};


/**
* Move the character.
* p : the character we want to move.
* key : an array to know the direction of the character.
*/
void move(Character *p, int key[]);

/**
* Create a new character.
*/
Character* createChar(int hp, int defense, int attack, int level, int xp, int pos_x, int pos_y, int w, int h, ListSpell *spell);

/**
* Compute the size of the list of characters.
* characters : the list we want to know the size.
*/
int size(ListChar *characters);

/**
* Add a new character at the end of the list.
*/
void addChar(ListChar *characters, Character* ch);

/**
* Show the characters (hero and ennemies) on the screen.
* rendu : the renderer we blit the textures on.
* characters : the list of characters we need to show.
* corner : the posicition of the corner of the map in the model.
* texture_chara : an array caontaining arrays of texture pointers for the hero and ennemies.
* key : the input on the keyboard.
* direction : we need to know the direction of the character for other treatments in other function
* b : the list of buildings we want to show. 
*/
void showCharacters(SDL_Renderer *rendu, ListChar* characters, SDL_Rect *corner, SDL_Texture*** texture_chara, int key[], int* direction, ListBuilding* b);

/**
* Update the texture of a character according to the direction and the current frame to simulate the movment.
*/
SDL_Texture* update_texture(int key[], SDL_Texture *tableau[], int *trame, int *f);

/**
* Compute the index in the texture array depending on the current trame.
*/
int text_move(int *trame);

/**
* Compute the current trame.
*/
void compute_tram(int *j, int *trame);

/**
* Remove all killed characters in the list. 
* The case of the hero is catched in the function managing_event()
*/
ListChar* removeKilled(ListChar* characters);

/**
* Add xp to the character.
*/
void add_xp(Character* ch, int dam);

/**
* Free the space allocated ti the character.
* Called by destroyListChara.
*/
void destroyChara(Character* c);

/**
* Free a list of characters.
*/
void destroyListChara(ListChar *lc);

#endif
