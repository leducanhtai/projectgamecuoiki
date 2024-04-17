#include <iostream>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_ttf.h"
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "checkCollision.h"
#include "randomFalling.h"
#include "game_functions.h"
#include "gameLoop.h"
#include "globals.h"
#include "LoadBoss.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 1067;
const int SPRITE_SPEED = 6;
const int BULLET_SPEED = 2;
const int FALLING_SPEED = 1;
const int NUM_FALLING_IMAGES = 4;
const int BULLET_WIDTH = 3;
const int BULLET_HEIGHT = 3;
const int HP_WIDTH = 30;
const int HP_HEIGHT = 30;
const int SHIELD_WIDTH = 30;
const int SHIELD_HEIGHT = 30;

const int WALKING_ANIMATION_FRAMES = 3;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
//SDL_Rect gBossClips[ WALKING_ANIMATION_FRAMES ];

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gBackground = NULL;
SDL_Surface* gSprite = NULL;
SDL_Surface* gBulletImage = NULL; 
SDL_Surface* gGameOverImage = NULL; 
SDL_Surface* gBossImage = NULL;
SDL_Surface* gBoss2Image = NULL;
SDL_Surface* gBoss3Image = NULL;
SDL_Surface* gLightImage = NULL;
SDL_Surface* gHPImage = NULL;
SDL_Surface* gMenu = NULL;
SDL_Surface* gGuide = NULL;
SDL_Surface* gShield = NULL;
SDL_Surface* gProtect = NULL;
SDL_Surface* gExplosionImage = NULL;
TTF_Font* gFont = nullptr;

int hpX = rand() % SCREEN_WIDTH;
int hpY = 0;
int shieldX = rand() % SCREEN_WIDTH;
int shieldY = 0;
int spriteX = SCREEN_WIDTH / 2;
int spriteY = SCREEN_HEIGHT - 100;
bool isMovingLeft = false;
bool isMovingRight = false;
bool isSpriteFacingRight = true;
bool isMouseClicked = false;
bool gameOver = false;
int Time = 0;
int Points = 0;
int Blood=500;
int Level = 1;


int backgroundY = 0;
int currentFrame = 0;
bool spawnHP = false;
bool isGuideVisible = true;
bool spawnShield = false;
bool immortal = false;
bool isProtectVisible = false;
Uint32 protectStartTime = 0;

std::vector<FallingImage> fallingImages;
std::vector<Bullet> bullets;
std::vector<LightImage> lightImages;
std::vector<Explosion> explosions;

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } 
    else 
    {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                                     SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) 
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } 
        else 
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    if (TTF_Init() == -1) 
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    } 
    else 
    {
        gFont = TTF_OpenFont("arial.ttf", 28); // Load font
        if (gFont == nullptr) 
        {
            printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
            success = false;
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;
    gBackground = SDL_LoadBMP("img/background.bmp");
    if (gBackground == NULL) {
        printf("Unable to load background image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    gSprite = SDL_LoadBMP("img/nv22.bmp");
    if (gSprite == NULL) {
        printf("Unable to load sprite image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else{
        gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  61;
		gSpriteClips[ 0 ].h = 75;

		gSpriteClips[ 1 ].x =  0;
		gSpriteClips[ 1 ].y =   75;
		gSpriteClips[ 1 ].w =  61;
		gSpriteClips[ 1 ].h = 75;
		
		gSpriteClips[ 2 ].x = 0;
		gSpriteClips[ 2 ].y =   150;
		gSpriteClips[ 2 ].w =  61;
		gSpriteClips[ 2 ].h = 75;

    }
    gBulletImage = SDL_LoadBMP("img/bullet.bmp");
    if (gBulletImage == NULL) {
        printf("Unable to load bullet image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    gGameOverImage = SDL_LoadBMP("img/gameover1.bmp");
    if (gGameOverImage == NULL) {
        printf("Unable to load game over image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    gBossImage = SDL_LoadBMP("img/boss.bmp");
    if (gBossImage == NULL) {
        printf("Unable to load boss image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    gBoss2Image = SDL_LoadBMP("img/boss2.bmp");
    if (gBoss2Image == NULL) {
        printf("Unable to load boss2 image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    gBoss3Image = SDL_LoadBMP("img/boss3.bmp");
    if (gBoss3Image == NULL) {
        printf("Unable to load boss3 image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    gLightImage = SDL_LoadBMP("img/light.bmp");
    if (gLightImage == NULL) {
    printf("Unable to load light image! SDL Error: %s\n", SDL_GetError());
    success = false;
    }
    gHPImage = SDL_LoadBMP("img/hp.bmp");
    if (gHPImage == NULL) {
    printf("Unable to load hp image! SDL Error: %s\n", SDL_GetError());
    success = false;
    }
    gMenu = SDL_LoadBMP("img/menu.bmp");
    if (gMenu == NULL) {
        printf("Unable to load menu image! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    gGuide = SDL_LoadBMP("img/hd.bmp");
    if (gGuide == NULL) {
        printf("Unable to load guide image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    gShield = SDL_LoadBMP("img/khien.bmp");
    if (gShield == NULL) {
        printf("Unable to load shield image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    gProtect = SDL_LoadBMP("img/lachan.bmp");
    if (gProtect == NULL) {
        printf("Unable to load protect image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    gExplosionImage = SDL_LoadBMP("img/explode.bmp");
    if (gExplosionImage == NULL) {
        printf("Unable to load explosion image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}

void close() {
    SDL_FreeSurface(gBackground);
    gBackground = NULL;
    SDL_FreeSurface(gSprite);
    gSprite = NULL;
    SDL_FreeSurface(gBulletImage);
    gBulletImage = NULL;
    SDL_FreeSurface(gGameOverImage);
    gGameOverImage = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_FreeSurface(gBossImage);
    gBossImage = NULL;
    SDL_FreeSurface(gBoss2Image);
    gBoss2Image = NULL;
    SDL_FreeSurface(gBoss3Image);
    gBoss3Image = NULL;
    SDL_FreeSurface(gMenu);
    gMenu = NULL;
    SDL_FreeSurface(gGuide);
    gGuide = NULL;
    SDL_FreeSurface(gLightImage);
    gLightImage = NULL;
    SDL_FreeSurface(gShield);
    gShield = NULL;
    SDL_FreeSurface(gProtect);
    gProtect = NULL;
    SDL_Quit();
}
void LoadMenu(bool startGame)
{
    SDL_Rect menuRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_BlitSurface(gMenu, NULL, gScreenSurface, &menuRect);
    SDL_UpdateWindowSurface(gWindow);
     while (!startGame) 
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {

            if (event.type == SDL_MOUSEBUTTONDOWN) 
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= 200 && mouseX <= 410 && 
                    mouseY >= 500 && mouseY <= 600) 
                {
                    startGame = true;
                }
                else if((mouseX >= 200 && mouseX <= 410 && 
                        mouseY >= 650 && mouseY <= 750)&&isGuideVisible)
                {
                    SDL_Rect guideRect = {50, 600, SCREEN_WIDTH, SCREEN_HEIGHT };
                    SDL_BlitSurface(gGuide, NULL, gScreenSurface, &guideRect);
                    SDL_UpdateWindowSurface(gWindow);
                    isGuideVisible=false;
                }
                //else if(mouseX >= 460 && mouseX <= 530 && 
                //        mouseY >= 610 && mouseY <= 660)
                //{
                //    isGuideVisible=false;
                //}
            }
        }
    }
}

int main(int argc, char* args[]) 
{
    srand(time(NULL));
    if (!init()) 
    {
        printf("Failed to initialize!\n");
        return 1;
    }
    if (!loadMedia()) 
    {
        printf("Failed to load media!\n");
        return 1;
    }
    bool startGame = false;
    LoadMenu(startGame);
    FallingImage fallingImage;
    for (int i = 0; i < NUM_FALLING_IMAGES; i++) 
    {
        fallingImage.x = rand() % SCREEN_WIDTH;
        fallingImage.y = rand() % (SCREEN_HEIGHT / 10);
        fallingImage.imagePath = getRandomFallingImage();
        fallingImages.push_back(fallingImage);
    }
    gameLoop();
    close();
    return 0;
}