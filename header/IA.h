#ifndef ia_h
#define ia_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Map.h"

void manageEnnemies(Map* map);
Character* createEnnemy(int level);
int numberOfEnnemies(Map* map);

#endif