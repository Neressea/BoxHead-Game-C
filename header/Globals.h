#ifndef globals_h
#define globals_h

	//Globals for the main
	#define main_h
	#define SPEED 4
	#define SPEED_TRAME 8
	#define SCREEN_W 640
	#define SCREEN_H 480
	#define PX_H 100
	#define PX_W 100
	#define PXH_H 80
	#define PXH_W 40
	#define NB_SPRITES_H 24
	#define NB_SPRITES_A 8
	#define FPS 20
	#define NB_ITEM 2

	//GLobals for the map
	#define NB_TEXTS_MAP 2
	#define NB_SPRITES_BLITTED 2
	

	//Globals for the spell
	#define LIFEEXPANC 10000
	#define NB_TYP_SPELL 2
	#define SPELL_H 70
	#define SPELL_W 20 

	//Globals for the items
	#define ITEM_H 30
	#define ITEM_W 30


typedef struct {
	int x, y;
}Move;

#endif
