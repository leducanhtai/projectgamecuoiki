
#ifndef CHECKCOLLISION_H
#define CHECKCOLLISION_H

#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"
#include "globals.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "game_functions.h"
#include "gameLoop.h"
#include "randomFalling.h"

bool checkCollision(int spriteX, int spriteY, int spriteW, int spriteH, int imageX, int imageY, int imageW, int imageH);

#endif //CHECKCOLLISION_H
