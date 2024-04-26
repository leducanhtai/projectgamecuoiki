#include "game_functions.h"



void renderText(const std::string& text, int x, int y) 
{
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
    if (textSurface == nullptr) 
    {
        std::cerr << "Unable to render SDL_ttf Error: " << TTF_GetError() << std::endl;
    } 
    else 
    {
        SDL_Rect renderQuad = { x, y, textSurface->w, textSurface->h };
        SDL_BlitSurface(textSurface, nullptr, gScreenSurface, &renderQuad);
        SDL_FreeSurface(textSurface);
    }
}


void createLightImage(int bossX, int bossY) 
{
        LightImage lightImage;
        lightImage.x = bossX + (gBossImage->w  - gLightImage->w) / 2; 
        lightImage.y = bossY + gBossImage->h - 750;
        lightImages.push_back(lightImage);
    
}


void renderBloodBar(int currentBlood, int maxBlood, int x, int y, int width, int height) {
    
    int bloodBarWidth = (currentBlood * width) / maxBlood;
    SDL_Rect bloodBarRect = { x, y, width, height };
    SDL_FillRect(gScreenSurface, &bloodBarRect, SDL_MapRGB(gScreenSurface->format, 255, 0, 0));
    SDL_Rect remainingBloodhRect = { x, y, bloodBarWidth, height };
    SDL_FillRect(gScreenSurface, &remainingBloodhRect, SDL_MapRGB(gScreenSurface->format, 0, 255, 0));
}

void renderExplosion( int bossX, int bossY){

        SDL_Rect bigExplosionRect = { bossX, bossY, 0, 0 };
        SDL_Rect* currentClip = &gExplosionClips[currentFrame / 7];
        SDL_BlitSurface(gBigExplosionImage, currentClip, gScreenSurface, &bigExplosionRect);

}
void renderGame(SDL_Surface* gScreenSurface, SDL_Surface* gBackground, SDL_Surface* gGameOverImage, SDL_Surface* gSprite, 
                SDL_Surface* gBulletImage,std::vector<FallingImage>& fallingImages, std::vector<Bullet>& bullets, int& spriteX, 
                int& spriteY, bool& isMovingLeft, bool& isMovingRight, bool& isSpriteFacingRight, bool& gameOver) 
{
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));
    SDL_Rect backgroundRect = { 0, backgroundY, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_BlitSurface(gBackground, NULL, gScreenSurface, &backgroundRect);
    SDL_Rect nextBackgroundRect = { 0, backgroundY - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_BlitSurface(gBackground, NULL, gScreenSurface, &nextBackgroundRect);
    
    LoadBoss();
    
    if(spawnHP)
    {
       SDL_Rect hpRect = { hpX, hpY, HP_WIDTH, HP_HEIGHT };
       SDL_BlitSurface(gHPImage, NULL, gScreenSurface, &hpRect);
    }
    if (spawnShield) {
        SDL_Rect shieldRect = { shieldX, shieldY, SHIELD_WIDTH, SHIELD_HEIGHT };
        SDL_BlitSurface(gShield, NULL, gScreenSurface, &shieldRect);
    }
    if(spawnfire&& Points >= 500&&Points <= 600)
    {
       SDL_Rect fireBossRect = { fireBossX, fireBossY, FIRE_WIDTH, FIRE_HEIGHT };
       //SDL_BlitSurface(gfireBossImage, NULL, gScreenSurface, );
        //SDL_Rect fireBossRect = { spriteX, spriteY, 0, 0 };
        SDL_Rect* currentClip = &gfireBossClips[currentFrame / 3];
        SDL_BlitSurface(gfireBossImage, currentClip, gScreenSurface, &fireBossRect);

    }
    if (immortal) {
        if (!isProtectVisible) {
           isProtectVisible = true;
           protectStartTime = SDL_GetTicks();
        }
        if (SDL_GetTicks() - protectStartTime < 5000) {
            SDL_Rect protectRect = { spriteX - 20, spriteY- 20, 0, 0 };
            SDL_BlitSurface(gProtect, NULL, gScreenSurface, &protectRect);
        } else {
            immortal = false;
            isProtectVisible = false;
        }
    }
    for (auto& bullet : bullets) 
    {
        bullet.y -= BULLET_SPEED;
        SDL_Rect bulletRect = { bullet.x, bullet.y, BULLET_WIDTH, BULLET_HEIGHT };
        SDL_BlitSurface(gBulletImage, NULL, gScreenSurface, &bulletRect);
    }
    for (auto lightIter = lightImages.begin(); lightIter != lightImages.end();) 
    {
        lightIter->y += 2;
        if (lightIter->y > SCREEN_HEIGHT) 
        {
            lightIter = lightImages.erase(lightIter);
        } 
        else 
        {
            SDL_Rect lightRect = { lightIter->x, lightIter->y, 0, 0 };
            SDL_BlitSurface(gLightImage, NULL, gScreenSurface, &lightRect);
            ++lightIter;
        }
        int spriteW = gSprite->w;
        int spriteH = gSprite->h;
        int lightW = gLightImage->w;
        int lightH = gLightImage->h;
        if (checkCollision(spriteX, spriteY, spriteW, spriteH, lightIter->x, lightIter->y, lightW, lightH)) 
        {
            if(!immortal)
            {
               Blood -- ;
               if(Blood <= 0)
               {
                  gameOver = true;
                  return;
               }
            }
        } 
    }
    for (int i = 0; i < NUM_FALLING_IMAGES; i++) 
    {
        fallingImages[i].y += FALLING_SPEED;
        if (fallingImages[i].y > SCREEN_HEIGHT) 
        {
            fallingImages[i].x = rand() % SCREEN_WIDTH;
            fallingImages[i].y = rand() % (SCREEN_HEIGHT / 10);
            fallingImages[i].imagePath = getRandomFallingImage();
        }
        SDL_Surface* fallingImage = SDL_LoadBMP(fallingImages[i].imagePath.c_str());
        SDL_Rect fallingRect = { fallingImages[i].x, fallingImages[i].y, 0, 0 };
        SDL_BlitSurface(fallingImage, NULL, gScreenSurface, &fallingRect);
        SDL_FreeSurface(fallingImage);
        
        int spriteW = gSprite->w;
        int spriteH = gSprite->h;
        int imageW = fallingImage->w;
        int imageH = fallingImage->h;
        if ( checkCollision(spriteX, spriteY, spriteW, spriteH, fallingImages[i].x, fallingImages[i].y, imageW, imageH)) 
        {
            if(!immortal)
            {
               Blood --;
               if(Blood == 0)
               {
                  gameOver = true;
                  return;
               }
            }
        }
    }

    SDL_Rect spriteRect = { spriteX, spriteY, 0, 0 };
    SDL_Rect* currentClip = &gSpriteClips[currentFrame / 3];
    SDL_BlitSurface(gSprite, currentClip, gScreenSurface, &spriteRect);

    if(Points <= 70 && Points >=60) renderExplosion(bossX,bossY);
    if(Points <= 250 && Points >=230) renderExplosion(boss2X,boss2Y);
    if(Points <= 600 && Points >= 580) renderExplosion(boss3X,boss3Y);
    
    renderBloodBar(Blood, 500, spriteX + 50, spriteY - 10, gSprite->w, 5);
    for (auto& explosion : explosions) 
    {
        if (SDL_GetTicks() - explosion.startTime < 1000) 
        {                             
            SDL_Rect explosionRect = { explosion.x, explosion.y, 0, 0 };                  
            SDL_BlitSurface(gExplosionImage, NULL, gScreenSurface, &explosionRect);
        }    
    }
    renderText("Time: " + std::to_string(Time), 10, 10);
    renderText("Points: " + std::to_string(Points), 200, 10);
    renderText("Blood : " + std::to_string(Blood), 400, 10);
    renderText("Level : " + std::to_string(Level), 400, 50);
    SDL_UpdateWindowSurface(gWindow);
}