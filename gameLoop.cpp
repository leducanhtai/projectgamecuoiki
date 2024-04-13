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
void moveEntity(int& entityX, int& entityDirection, int entityWidth, int screenWidth) 
{
    entityX += entityDirection * 1;
    if (entityX <= 0) 
    {
        entityX = 0;
        entityDirection = 1;
    } 
    else if (entityX >= screenWidth - entityWidth) 
    {
        entityX = screenWidth - entityWidth;
        entityDirection = -1;
    }
}
void gameLoop() 
{
    SDL_Event e;
    Uint32 lastUpdate = SDL_GetTicks();
    Uint32 lastSecond = SDL_GetTicks();
    int frames = 0;
    const Uint32 FRAME_DELAY = 500 / 60;
    while (true) 
    {
        while (SDL_PollEvent(&e) != 0) 
        {
            handleEvent(e);
        }
        if (gameOver) 
        {
            SDL_Rect gameOverRect = { (SCREEN_WIDTH - gGameOverImage->w) / 2, 
                                      (SCREEN_HEIGHT - gGameOverImage->h) / 2, 0, 0 };
            SDL_BlitSurface(gGameOverImage, NULL, gScreenSurface, &gameOverRect);
            SDL_UpdateWindowSurface(gWindow);
            while (SDL_PollEvent(&e) != 0) 
            {
                if (e.type == SDL_QUIT) 
                {
                    return; 
                }
                else if (e.type == SDL_MOUSEBUTTONDOWN) 
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (mouseX >= gameOverRect.x && mouseX <= gameOverRect.x + gGameOverImage->w &&
                         mouseY >= gameOverRect.y && mouseY <= gameOverRect.y + gGameOverImage->h) 
                    {
                         gameOver = false;
                         Time = 0;
                         Points = 0;
                         Blood = 1000;
                         Level =1;
                         bullets.clear();
                         fallingImages.clear();
                         lightImages.clear();

                        for (int i = 0; i < NUM_FALLING_IMAGES; i++) 
                        {
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
            Uint32 currentTime = SDL_GetTicks();
            Uint32 deltaTime = currentTime - lastUpdate;
            Uint32 deltaSecond = currentTime - lastSecond;
            if (deltaTime >= FRAME_DELAY) {
                if (isMovingLeft && spriteX > 0) 
                {
                    spriteX -= SPRITE_SPEED;
                }
                if (isMovingRight && spriteX < SCREEN_WIDTH - gSprite->w) 
                {
                    spriteX += SPRITE_SPEED;
                }
                ++currentFrame;			
			    if( currentFrame / 3 >= WALKING_ANIMATION_FRAMES )
			    {
					currentFrame = 0;
			    }
                lastUpdate = currentTime;
                frames++;
            }
            if (deltaSecond >= 1000) 
            {
                Time++;
                lastSecond = currentTime;
                frames = 0;
            }
            
            for (auto bulletIter = bullets.begin(); bulletIter != bullets.end();) 
            {
                bool bulletRemoved = false;
                for (auto& fallingImage : fallingImages) 
                {
                    if (checkCollision(bulletIter->x, bulletIter->y, BULLET_WIDTH, BULLET_HEIGHT,
                                       fallingImage.x, fallingImage.y, gSprite->w, gSprite->h))
                    {
                        
                        bulletIter = bullets.erase(bulletIter);
                        bulletRemoved = true;
                       // fallingImage = fallingImages.back();
                        //fallingImages.pop_back();
                        Points++;
                        break;
                    }
                }
                if(isBossVisible && checkCollision(bulletIter->x, bulletIter->y, BULLET_WIDTH, 
                                       BULLET_HEIGHT, bossX, bossY, gBossImage->w, gBossImage->h))
                {
                    bulletIter = bullets.erase(bulletIter);
                    bulletRemoved = true;
                    Points++;
                    
                }
            
                if (!bulletRemoved) 
                {
                    bulletIter++;
                }
            }
            if (spawnHP) {
                hpY += 1.2; 
                if (checkCollision(spriteX, spriteY, gSprite->w, gSprite->h, hpX, hpY, HP_WIDTH, HP_HEIGHT)) {
                    Blood ++;
                    // spawnHP = false;
                }
                if (hpY > SCREEN_HEIGHT){
                    hpX = rand() % SCREEN_WIDTH;
                    hpY = 0;
                    spawnHP = false; 
                }
            } else {
                if (Time % 5 == 0) { 
                    hpX = rand() % SCREEN_WIDTH;
                    hpY = 0;
                    spawnHP = true; 
                }
            }
            moveEntity(bossX, bossDirection, gBossImage->w, SCREEN_WIDTH);
            moveEntity(boss2X, boss2Direction, gBoss2Image->w, SCREEN_WIDTH);
            moveEntity(boss3X, boss3Direction, gBoss3Image->w, SCREEN_WIDTH);
            renderGame(gScreenSurface, gBackground, gGameOverImage, gSprite, gBulletImage, fallingImages,
                bullets, spriteX, spriteY, isMovingLeft, isMovingRight, isSpriteFacingRight, gameOver);
        }
    }
}