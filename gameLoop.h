#ifndef GAMELOOP_H
#define GAMELOOP_H

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
#include "LoadBoss.h"
#include "handleEvent.h"

void gameLoop() ;

#endif //GAMELOOP_H