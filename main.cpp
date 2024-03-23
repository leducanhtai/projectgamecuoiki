#include <iostream>
#include "src/include/SDL2/SDL.h"
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "checkCollision.h"
#include "randomFalling.h"
#include "game_functions.h"
#include "gameLoop.h"
#include "globals.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 1067;
const int SPRITE_SPEED = 3;
const int BULLET_SPEED = 5;
const int FALLING_SPEED = 1;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gBackground = NULL;
SDL_Surface* gSprite = NULL;
SDL_Surface* gFallingImage = NULL;
SDL_Surface* gBulletImage = NULL; 
SDL_Surface* gGameOverImage = NULL; 

int spriteX = SCREEN_WIDTH / 2;
int spriteY = SCREEN_HEIGHT - 100;
bool isMovingLeft = false;
bool isMovingRight = false;
bool isSpriteFacingRight = true;
bool gameOver = false;
const int NUM_FALLING_IMAGES = 1;
const int BULLET_WIDTH = 8;
const int BULLET_HEIGHT = 16;

std::vector<FallingImage> fallingImages;
std::vector<Bullet> bullets;
bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
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
    std::string fallingImageFile = getRandomFallingImage();
    gFallingImage = SDL_LoadBMP(fallingImageFile.c_str());
    if (gFallingImage == NULL) {
        printf("Unable to load falling image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }  
    gBulletImage = SDL_LoadBMP("img/bullet.bmp");
    if (gBulletImage == NULL) {
        printf("Unable to load bullet image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    gGameOverImage = SDL_LoadBMP("img/gameover.bmp");
    if (gGameOverImage == NULL) {
        printf("Unable to load game over image! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}

void close() {
    SDL_FreeSurface(gBackground);
    gBackground = NULL;
    SDL_FreeSurface(gSprite);
    gSprite = NULL;
    SDL_FreeSurface(gFallingImage);
    gFallingImage = NULL;
    SDL_FreeSurface(gGameOverImage);
    gGameOverImage = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}
int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
        return 1;
    }
    if (!loadMedia()) {
        printf("Failed to load media!\n");
        return 1;
    }
    FallingImage fallingImage;
    for (int i = 0; i < NUM_FALLING_IMAGES; i++) {
        fallingImage.x = rand() % SCREEN_WIDTH;
        fallingImage.y = rand() % SCREEN_HEIGHT / 10;
        fallingImage.imagePath = getRandomFallingImage();
        fallingImages.push_back(fallingImage);
    }
    gameLoop();
    close();
    return 0;
}