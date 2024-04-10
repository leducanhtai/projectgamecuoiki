
#ifndef CHECKCOLLISION_H
#define CHECKCOLLISION_H

#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_ttf.h"
#include "globals.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "game_functions.h"
#include "gameLoop.h"
#include "randomFalling.h"
#include "LoadBoss.h"

bool checkCollision(int X1, int Y1, int W1, int H1, int X2, int Y2, int W2, int H2);

#endif //CHECKCOLLISION_H
