#include "LoadBoss.h"
void LoadBoss()
{
    if (Points >= 10 && Points <= 40) 
    { 
        Level = 2;
        isBossVisible = true;
        SDL_Rect bossRect = { bossX, bossY, 0, 0 };
        //SDL_Rect* currentClip = &gBossClips[currentFrame / 3];
        //SDL_BlitSurface(gBossImage, currentClip, gScreenSurface, &bossRect);
        SDL_BlitSurface(gBossImage, NULL, gScreenSurface, &bossRect);
        createLightImage(bossX, bossY);
    }
    else if(Points >= 60 && Points <= 80 )
    {
        Level = 3;
        isBossVisible = true;
        SDL_Rect boss2Rect = { boss2X, boss2Y, 0, 0 };
        SDL_BlitSurface(gBoss2Image, NULL, gScreenSurface, &boss2Rect);
        createLightImage(boss2X, boss2Y);
    }
    else if(Points >=100 && Points <= 150)
    {
        Level = 4;
        isBossVisible = true;
        SDL_Rect boss3Rect = { boss3X, boss3Y, 0, 0 };
        SDL_BlitSurface(gBoss3Image, NULL, gScreenSurface, &boss3Rect);\
        createLightImage(boss3X, boss3Y);
    }
    else
    {
        isBossVisible = false;
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