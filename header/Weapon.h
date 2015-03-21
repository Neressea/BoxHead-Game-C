#ifndef weapon_h
#define weapon_h


/**
* Defines what a weapon is.
* attack : points of attack
* ammo : number of ammo left
* rate : rate of fire if a gun, -1 else.
*/
typedef struct{
	int attack;
	int ammo;
	int rate; //?
}Weapon;

#endif