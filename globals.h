#ifndef GLOBALS_H
#define GLOBALS_H


#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_ttf.h"
#include <vector>
#include <string>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SPRITE_SPEED;
extern const int BULLET_SPEED;
extern const int FALLING_SPEED;

extern bool isMovingLeft;
extern bool isMovingRight;
extern bool isSpriteFacingRight;
extern bool gameOver;
extern bool isBossVisible;

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gBackground;
extern SDL_Surface* gSprite;
//extern SDL_Surface* gFallingImage;
extern SDL_Surface* gBulletImage;
extern SDL_Surface* gContinueImage;
extern SDL_Surface* gGameOverImage;
extern SDL_Surface* gBossImage;
extern SDL_Surface* gBoss2Image;
extern SDL_Surface* gBoss3Image;
extern TTF_Font* gFont; 

extern int spriteX;
extern int spriteY;
extern int Time;
extern int Points;
extern int Blood;
extern int bossX;
extern int bossY;
extern int bossDirection;
extern int boss2X;
extern int boss2Y;
extern int boss2Direction;
extern int boss3X;
extern int boss3Y;
extern int boss3Direction;

extern const int NUM_FALLING_IMAGES;
extern const int BULLET_WIDTH;
extern const int BULLET_HEIGHT;


struct FallingImage {
    int x, y;
    std::string imagePath;
};

struct Bullet {
    int x, y;
};

extern std::vector<FallingImage> fallingImages;
extern std::vector<Bullet> bullets;

#endif // GLOBALS_H