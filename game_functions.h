#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "src/include/SDL2/SDL.h"
#include "globals.h"

void handleEvent(SDL_Event &e);
void changeSpriteImage();
void renderGame();

#endif // GAME_FUNCTIONS_H