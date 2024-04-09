#include "gameLoop.h"

void changeSpriteImage(SDL_Surface* &gSprite, bool isSpriteFacingRight) 
{
    if (isSpriteFacingRight) 
    {
        gSprite = SDL_LoadBMP("img/maybayk11.bmp"); 
    } 
    else 
    {
        gSprite = SDL_LoadBMP("img/maybayk22.bmp"); 
    }
}
void moveBoss() {
    // Cập nhật vị trí của boss dựa trên hướng di chuyển
    bossX += bossDirection * SPRITE_SPEED;
    
    // Kiểm tra va chạm với biên giới trái và phải của màn hình
    if (bossX <= 0) {
        bossX = 0;
        bossDirection = 1; // Đổi hướng di chuyển sang phải
    } else if (bossX >= SCREEN_WIDTH - gBossImage->w) {
        bossX = SCREEN_WIDTH - gBossImage->w;
        bossDirection = -1; // Đổi hướng di chuyển sang trái
    }
}
void gameLoop() {
    SDL_Event e;
    Uint32 lastUpdate = SDL_GetTicks();
    Uint32 lastSecond = SDL_GetTicks();
    int frames = 0;
    const Uint32 FRAME_DELAY = 400 / 60;
    while (true) {
        while (SDL_PollEvent(&e) != 0) {
            handleEvent(e);
        }
        if (gameOver) {
            SDL_Rect gameOverRect = { (SCREEN_WIDTH - gGameOverImage->w) / 2, (SCREEN_HEIGHT - gGameOverImage->h) / 2, 0, 0 };
            SDL_BlitSurface(gGameOverImage, NULL, gScreenSurface, &gameOverRect);
            SDL_UpdateWindowSurface(gWindow);
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    return; 
                }
                else if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (mouseX >= gameOverRect.x && mouseX <= gameOverRect.x + gGameOverImage->w &&
                         mouseY >= gameOverRect.y && mouseY <= gameOverRect.y + gGameOverImage->h) {
                         gameOver = false;
                         Time = 0;
                         Points = 0;
                         Blood = 500;
                         bullets.clear();
                         fallingImages.clear();
                        for (int i = 0; i < NUM_FALLING_IMAGES; i++) {
                            FallingImage fallingImage;
                            fallingImage.x = rand() % SCREEN_WIDTH;
                            fallingImage.y = rand() % (SCREEN_HEIGHT / 10);
                            fallingImage.imagePath = getRandomFallingImage();
                            fallingImages.push_back(fallingImage);
                        }
                    }
                }
            }
        }
        else 
        {
            moveBoss();
            Uint32 currentTime = SDL_GetTicks();
            Uint32 deltaTime = currentTime - lastUpdate;
            Uint32 deltaSecond = currentTime - lastSecond;
            if (deltaTime >= FRAME_DELAY) {
                if (isMovingLeft && spriteX > 0) {
                    spriteX -= SPRITE_SPEED;
                    if (isSpriteFacingRight) {
                        isSpriteFacingRight = false;
                        changeSpriteImage(gSprite, isSpriteFacingRight);
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
}