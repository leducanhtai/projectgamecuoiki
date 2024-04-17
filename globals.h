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
extern const int WALKING_ANIMATION_FRAMES;
extern const int HP_WIDTH;
extern const int HP_HEIGHT;
extern const int SHIELD_WIDTH;
extern const int SHIELD_HEIGHT;

extern SDL_Rect gSpriteClips[];//[ WALKING_ANIMATION_FRAMES ];
extern SDL_Rect gBossClips[];//[ WALKING_ANIMATION_FRAMES ];

extern bool isMovingLeft;
extern bool isMovingRight;
extern bool isSpriteFacingRight;
extern bool gameOver;
extern bool isBossVisible;
extern bool isMouseClicked;
extern bool spawnHP;
extern bool spawnShield;
extern bool immortal;
extern bool isProtectVisible;
extern Uint32 protectStartTime;

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
extern SDL_Surface* gLightImage;
extern SDL_Surface* gHPImage;
extern SDL_Surface* gShield;
extern SDL_Surface* gProtect;
extern SDL_Surface* gExplosionImage;

extern TTF_Font* gFont; 

extern int hpX;
extern int hpY;
extern int shieldX;
extern int shieldY;
extern int spriteX;
extern int spriteY;
extern int Time;
extern int Points;
extern int Level;
extern int currentFrame;
extern int backgroundY;

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

struct LightImage {
    int x, y;
};

struct Explosion {
    int x, y;
    Uint32 startTime;
};
extern std::vector<LightImage> lightImages;
extern std::vector<FallingImage> fallingImages;
extern std::vector<Bullet> bullets;
extern std::vector<Explosion> explosions;

#endif // GLOBALS_H