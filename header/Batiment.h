#ifndef batiment_h
#define batiment_h
#endif

typedef struct
{
	int pv;
	int pos_x, pos_y;
	int attack;
	int defense;
}Batiment;

void attack(Batiment b, Perso p);