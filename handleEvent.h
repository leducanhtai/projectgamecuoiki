#ifndef HANDLEEVENT_H
#define HANDLEEVENT_H

#include <iostream>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_ttf.h"
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "globals.h"
#include "checkCollision.h"
#include "randomFalling.h"
#include "gameLoop.h"
#include "LoadBoss.h"
#include "game_functions.h"

void handleEvent(SDL_Event &e);


#endif // HANDLEEVENT_H