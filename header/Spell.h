#ifndef spell_h
#define spell_h


/**
* Defines what a spell is.
* attack : points of attack
* ammo : number of ammo left
* rate : rate of fire if a gun, -1 else.
*/
typedef struct{
	int attack;
	int ammo;
	int rate; //?
}Spell;

#endif
