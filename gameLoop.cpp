#include "gameLoop.h"


void gameLoop() 
{
     Mix_PlayMusic(backgroundMusic, -1);
    SDL_Event e;
    Uint32 lastUpdate = SDL_GetTicks();
    Uint32 lastSecond = SDL_GetTicks();
    int frames = 0;
    const Uint32 FRAME_DELAY = 1000 / 60;   
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return;
        } 
    }
    while (true) 
    {
        
       
        while (SDL_PollEvent(&e) != 0) 
        {
            handleEvent(e);
        }
        if(Points == 601) win=true;
        if(win) 
        {
            
            SDL_Rect winRect = { (SCREEN_WIDTH - gwinImage->w) / 2, 
                                  (SCREEN_HEIGHT - gwinImage->h) / 2, 0, 0 };
            SDL_BlitSurface(gwinImage, NULL, gScreenSurface, &winRect);
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
                    if (mouseX >= 70 && mouseX <= 270 &&
                        mouseY >= 620 && mouseY <= 670) 
                    {
                        gameOver = false;
                        win = false;
                        Time = 0;
                        Points = 0;
                        Blood = 500;
                        Level =1;
                        bullets.clear();
                        fallingImages.clear();
                        lightImages.clear();
                        spawnHP=false;
                        spawnShield = false;
                        for (int i = 0; i < NUM_FALLING_IMAGES; i++) 
                        {
                            FallingImage fallingImage;
                            fallingImage.x = rand() % SCREEN_WIDTH;
                            fallingImage.y = rand() % (SCREEN_HEIGHT / 10);
                            fallingImage.imagePath = getRandomFallingImage();
                            fallingImages.push_back(fallingImage);
                        }
                    }
                    else if(mouseX >= 450 && mouseX <= 550 &&
                            mouseY >= 620 && mouseY <= 670)
                    {
                         SDL_Quit();
                    }
                }
            }
        }
        else if(gameOver) 
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
                        Blood = 500;
                        Level =1;
                        bullets.clear();
                        fallingImages.clear();
                        lightImages.clear();
                        spawnHP=false;
                        spawnShield = false;
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
            backgroundY += 1 ;
            if (backgroundY >= SCREEN_HEIGHT) 
            {
                backgroundY = 0;
            }
            
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
                if (bulletIter->y < 0 || bulletIter->y > SCREEN_HEIGHT) 
                {
                   bulletIter = bullets.erase(bulletIter);
                } 
                else
                {
                    bool bulletRemoved = false;
                    for (auto& fallingImage : fallingImages) 
                    {
                        if (checkCollision(bulletIter->x, bulletIter->y, BULLET_WIDTH, BULLET_HEIGHT,
                                   fallingImage.x, fallingImage.y, gSprite->w, gSprite->h))
                        {
                            Explosion explosion;
                            explosion.x = fallingImage.x;
                            explosion.y = fallingImage.y;
                            explosion.startTime = SDL_GetTicks();
                            explosions.push_back(explosion);
                            Mix_PlayChannel(-1, soundExplosionSmall, 0);
                    
                            bulletIter = bullets.erase(bulletIter);
                            bulletRemoved = true;
                            fallingImage.x = rand() % SCREEN_WIDTH;
                            fallingImage.y = rand() % (SCREEN_HEIGHT / 10);
                            fallingImage.imagePath = getRandomFallingImage();
                            Points++;
                            break;
                        }
                    }
                    if (Points >= 50 && Points <= 70 ){
                        if(isBossVisible && checkCollision(bulletIter->x, bulletIter->y, BULLET_WIDTH, 
                                       BULLET_HEIGHT, bossX, bossY, gBossImage->w, gBossImage->h-700))
                        {
                            bulletIter = bullets.erase(bulletIter);
                            bulletRemoved = true;
                            Points++;
                    
                        }
                    }
                    if (Points >= 200 && Points <= 250 ){
                        if(isBossVisible && checkCollision(bulletIter->x, bulletIter->y, BULLET_WIDTH, 
                                       BULLET_HEIGHT, boss2X, boss2Y, gBoss2Image->w, gBoss2Image->h-1300))
                        {
                            bulletIter = bullets.erase(bulletIter);
                            bulletRemoved = true;
                            Points++;
                    
                        }
                    }
                    if (Points >= 500 && Points <= 600 ){
                        if(isBossVisible && checkCollision(bulletIter->x, bulletIter->y, BULLET_WIDTH, 
                                       BULLET_HEIGHT, boss3X, boss3Y, gBoss3Image->w, gBoss3Image->h-1000))
                        {
                            bulletIter = bullets.erase(bulletIter);
                            bulletRemoved = true;
                            Points++;
                    
                        }
                    }
                    if (!bulletRemoved) 
                    {
                       bulletIter++;
                    }
                }
            }
            for (auto fallingImageIter = fallingImages.begin(); fallingImageIter != fallingImages.end();) 
            {
                if (fallingImageIter->y > SCREEN_HEIGHT) 
                {
                    fallingImageIter = fallingImages.erase(fallingImageIter);
                } 
                else 
                {
                    fallingImageIter++;
                }
            }

            if (spawnHP) 
            {
                hpY += 1; 
                if (checkCollision(spriteX, spriteY, gSprite->w, gSprite->h, hpX, hpY, HP_WIDTH, HP_HEIGHT)) {
                   if(Blood <= 500)
                   {
                       Blood ++;
                   }
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
            if (spawnShield) 
            {
                shieldY += 1.2; 
                if (!immortal &&checkCollision(spriteX, spriteY, gSprite->w, gSprite->h, shieldX, shieldY, SHIELD_WIDTH, SHIELD_HEIGHT)) 
                {
                     immortal = true;
                }
                if (shieldY > SCREEN_HEIGHT){
                    shieldX = rand() % SCREEN_WIDTH;
                    shieldY = 0;
                    spawnShield = false; 
                }
            } else {
                if (Time % 7 == 0) { 
                    shieldX = rand() % SCREEN_WIDTH;
                    shieldY = 0;
                    spawnShield = true; 
                 }
            }
            if (spawnfire) 
            {
                fireBossY += 2;
                if (checkCollision(spriteX, spriteY, gSprite->w, gSprite->h, fireBossX, fireBossY, FIRE_WIDTH , FIRE_HEIGHT)) 
                {           
                      if(!immortal)  Blood -- ;    
                      //gameOver=true;  
                         
                }                
                if (fireBossY > SCREEN_HEIGHT){
                    fireBossX = bossX + 300;
                    fireBossY = bossY + 100;
                    spawnfire = false; 
                }
            } else {
                if (Time % 1 == 0 && Points >= 500 && Points <= 600 ) { 
                    fireBossX = bossY + 300;
                    fireBossY = bossX + 100;
                    spawnfire = true; 
                 }
            }
            if (Points >= 50 && Points <= 70 ) moveEntity(bossX, bossDirection, gBossImage->w, SCREEN_WIDTH);
            if (Points >= 200 && Points <= 250 ) moveEntity(boss2X, boss2Direction, gBoss2Image->w, SCREEN_WIDTH);
            if (Points >= 500 && Points <= 600 ) moveEntity(boss3X, boss3Direction, gBoss3Image->w, SCREEN_WIDTH);
            renderGame(gScreenSurface, gBackground, gGameOverImage, gSprite, gBulletImage, fallingImages,
                bullets, spriteX, spriteY, isMovingLeft, isMovingRight, isSpriteFacingRight, gameOver);
        }
    }

} 