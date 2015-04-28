#ifndef ia_h
#define ia_h

#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#include "Character.h"

void manageEnnemies(Map* map);
Character* createEnnemy(int level);
int numberOfEnnemies(Map* map);

#endif