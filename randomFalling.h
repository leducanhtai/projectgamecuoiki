#ifndef RANDOMFALLING_H
#define RANDOMFALLING_H

#include <iostream>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_ttf.h"
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "globals.h"
#include "gameLoop.h"
#include "game_functions.h"
#include "checkCollision.h"
#include "LoadBoss.h"


std::string getRandomFallingImage();

#endif //RANDOMFALLING_H