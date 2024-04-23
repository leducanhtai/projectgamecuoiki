#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

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
#include "handleEvent.h"

void renderText(const std::string& text, int x, int y);
void createLightImage(int bossX, int bossY);
void renderGame(SDL_Surface* gScreenSurface, SDL_Surface* gBackground, SDL_Surface* gGameOverImage, SDL_Surface* gSprite, 
                SDL_Surface* gBulletImage,std::vector<FallingImage>& fallingImages, std::vector<Bullet>& bullets, int& spriteX, 
                int& spriteY, bool& isMovingLeft, bool& isMovingRight, bool& isSpriteFacingRight, bool& gameOver);

#endif // GAME_FUNCTIONS_H