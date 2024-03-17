#include "game_functions.h"
#include "globals.h"
#include "checkCollision.h"
#include "randomFalling.h"
#include "gameLoop.h"
#include <iostream>
#include <string>


void handleEvent(SDL_Event &e) {
    if (e.type == SDL_QUIT) {
        SDL_Quit();
        exit(0);
    } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                isMovingLeft = true;
                isMovingRight = false;
                break;
            case SDLK_RIGHT:
                isMovingLeft = false;
                isMovingRight = true;
                break;
            case SDLK_UP:
                Bullet bullet;
                bullet.x = spriteX + (gSprite->w - BULLET_WIDTH*11);
                bullet.y = spriteY;
                bullets.push_back(bullet);
                break;
        }
    } else if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                isMovingLeft = false;
                break;
            case SDLK_RIGHT:
                isMovingRight = false;
                break;
            case SDLK_UP:
                gSprite = SDL_LoadBMP("img/maybayk33.bmp");               
                break;
        }
    }
}
void changeSpriteImage() {
    if (isSpriteFacingRight) {
        gSprite = SDL_LoadBMP("img/maybayk11.bmp"); 
    } else {
        gSprite = SDL_LoadBMP("img/maybayk22.bmp"); 
    }
}

void renderGame() {
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));
    SDL_BlitSurface(gBackground, NULL, gScreenSurface, NULL);
    // Vẽ các viên đạn
    for (const auto& bullet : bullets) {
        SDL_Rect bulletRect = { bullet.x, bullet.y, BULLET_WIDTH, BULLET_HEIGHT };
        SDL_BlitSurface(gBulletImage, NULL, gScreenSurface, &bulletRect);
    }
    for (int i = 0; i < NUM_FALLING_IMAGES; ++i) {
        fallingImages[i].y += FALLING_SPEED;
        if (fallingImages[i].y > SCREEN_HEIGHT) {
            fallingImages[i].x = rand() % SCREEN_WIDTH;
            fallingImages[i].y = rand() % (SCREEN_HEIGHT / 10);
            fallingImages[i].imagePath = getRandomFallingImage();
        }
        SDL_Surface* fallingImage = SDL_LoadBMP(fallingImages[i].imagePath.c_str());
        if (fallingImage == NULL) {
            printf("Unable to load falling image! SDL Error: %s\n", SDL_GetError());
        } else {
            SDL_Rect fallingRect = { fallingImages[i].x, fallingImages[i].y, 0, 0 };
            SDL_BlitSurface(fallingImage, NULL, gScreenSurface, &fallingRect);
            SDL_FreeSurface(fallingImage);
        }
        int spriteW = gSprite->w;
        int spriteH = gSprite->h;
        int imageW = gFallingImage->w;
        int imageH = gFallingImage->h;
        if (checkCollision(spriteX, spriteY, spriteW, spriteH, fallingImages[i].x, fallingImages[i].y, imageW, imageH)) {
            SDL_Rect gameOverRect = { (SCREEN_WIDTH - gGameOverImage->w) / 2, (SCREEN_HEIGHT - gGameOverImage->h) / 2, 0, 0 };
            SDL_BlitSurface(gGameOverImage, NULL, gScreenSurface, &gameOverRect);
            SDL_UpdateWindowSurface(gWindow);
            gameOver = true;
            return; 
        }
    }

    SDL_Rect spriteRect = { spriteX, spriteY, 0, 0 };
    SDL_BlitSurface(gSprite, NULL, gScreenSurface, &spriteRect);
    SDL_UpdateWindowSurface(gWindow);
}