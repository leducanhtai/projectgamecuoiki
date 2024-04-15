#ifndef LOADBOSS_H
#define LOADBOSS_H

#include <iostream>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_ttf.h"
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "globals.h"
#include "game_functions.h"
#include "checkCollision.h"
#include "randomFalling.h"


void LoadBoss();
void moveEntity(int& entityX, int& entityDirection, int entityWidth, int screenWidth);

#endif //LOADBOSS_H