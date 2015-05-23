#ifndef globals_h
#define globals_h

	//Globals for the main
	#define main_h
	#define SPEED 8
	#define SPEED_TRAME 8
	#define SCREEN_W 640
	#define SCREEN_H 480
	#define PX_H 100
	#define PX_W 100
	#define PXH_H 80
	#define PXH_W 40
	#define NB_SPRITES_H 24
	#define NB_SPRITES_A 8
	#define FPS 18
	#define NB_ITEM 2

	//GLobals for the map
	#define NB_TEXTS_MAP 3
	#define NB_SPRITES_BLITTED 2
	

	//Globals for the spell
	#define LIFEEXPANC 10000
	#define NB_TYP_SPELL 4
	#define SPELL_H 70
	#define SPELL_W 20 

	//Globals for the items
	#define ITEM_H 30
	#define ITEM_W 30

	//Globals for the keybinds
	#define ESCAPE 0
	#define UP 1
	#define DOWN 2
	#define LEFT 3
	#define RIGHT 4
	#define ATTACK 5
	#define FIRE 6
	#define ICE 7
	#define TOWER 8

	//Autres variables
	#define LGR_MAX 30
	#define NB_TOUCHES 9


typedef struct {
	int x, y;
}Move;

#endif
