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
const int SPRITE_SPEED = 3;
const int BULLET_SPEED = 2;
const int FALLING_SPEED = 1;
const int NUM_FALLING_IMAGES = 2;
const int BULLET_WIDTH = 3;
const int BULLET_HEIGHT = 3;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gBackground = NULL;
SDL_Surface* gSprite = NULL;
SDL_Surface* gBulletImage = NULL; 
SDL_Surface* gGameOverImage = NULL; 
SDL_Surface* gBossImage = NULL;
SDL_Surface* gBoss2Image = NULL;
SDL_Surface* gBoss3Image = NULL;
TTF_Font* gFont = nullptr;

int spriteX = SCREEN_WIDTH / 2;
int spriteY = SCREEN_HEIGHT - 100;
bool isMovingLeft = false;
bool isMovingRight = false;
bool isSpriteFacingRight = true;
bool gameOver = false;
int Time = 0;
int Points = 0;
int Blood=500;

int bossX = SCREEN_WIDTH / 2;
int bossY = SCREEN_HEIGHT / 5;
int boss2X = SCREEN_WIDTH / 2;
int boss2Y = SCREEN_HEIGHT / 5;
int boss3X = SCREEN_WIDTH / 2;
int boss3Y = SCREEN_HEIGHT / 5;

int bossDirection = 1;
int boss2Direction = 1;
int boss3Direction = 1;

bool isBossVisible = false;

std::vector<FallingImage> fallingImages;
std::vector<Bullet> bullets;
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
    gBackground = SDL_LoadBMP("img/background1.bmp");
    if (gBackground == NULL) {
        printf("Unable to load background image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    gSprite = SDL_LoadBMP("img/maybayk11.bmp");
    if (gSprite == NULL) {
        printf("Unable to load sprite image! SDL Error: %s\n", SDL_GetError());
        success = false;
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
    SDL_Quit();
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