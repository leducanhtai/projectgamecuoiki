#include "gameLoop.h"

void changeSpriteImage(SDL_Surface* &gSprite, bool isSpriteFacingRight) {
    if (isSpriteFacingRight) {
        gSprite = SDL_LoadBMP("img/maybayk11.bmp"); 
    } else {
        gSprite = SDL_LoadBMP("img/maybayk22.bmp"); 
    }
}

void gameLoop() {
    SDL_Event e;
    Uint32 lastUpdate = SDL_GetTicks();
    Uint32 lastSecond = SDL_GetTicks();
    int frames=0;
    const Uint32 FRAME_DELAY = 400 / 60;
    while (!gameOver) {
        while (SDL_PollEvent(&e) != 0) {
            handleEvent(e);
        }
        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastUpdate;
        Uint32 deltaSecond = currentTime - lastSecond;
        if (deltaTime >= FRAME_DELAY) {
            if (isMovingLeft && spriteX > 0) {
                spriteX -= SPRITE_SPEED;
                if (isSpriteFacingRight) {
                    isSpriteFacingRight = false;
                    changeSpriteImage(gSprite, isSpriteFacingRight );
                }
            }
            if (isMovingRight && spriteX < SCREEN_WIDTH - gSprite->w) {
                spriteX += SPRITE_SPEED;
                if (!isSpriteFacingRight) {
                    isSpriteFacingRight = true;
                    changeSpriteImage(gSprite, isSpriteFacingRight);
                }
            }
            lastUpdate = currentTime;
            frames++;
        }
        if (deltaSecond >= 1000) {
            Time++;
            lastSecond = currentTime;
            frames = 0; 
        }
         for (auto bulletIter = bullets.begin(); bulletIter != bullets.end();) {
            bool bulletRemoved = false;
            for (auto& fallingImage : fallingImages) {
                if (checkCollision(bulletIter->x, bulletIter->y, BULLET_WIDTH, BULLET_HEIGHT,
                                   fallingImage.x, fallingImage.y, gSprite->w, gSprite->h)) {
                    bulletIter = bullets.erase(bulletIter);
                    bulletRemoved = true;
                    Points++;
                    break;
                }
            }
            if (!bulletRemoved) {
                bulletIter++;
            }
        }
        renderGame(gScreenSurface, gBackground, gGameOverImage, gSprite, gBulletImage, fallingImages, 
                   bullets, spriteX, spriteY, isMovingLeft, isMovingRight, isSpriteFacingRight, gameOver);
        
    }
}
