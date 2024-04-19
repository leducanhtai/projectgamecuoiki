#include "LoadBoss.h"

int bossX = SCREEN_WIDTH / 2;
int bossY = SCREEN_HEIGHT / 10;

int boss2X = SCREEN_WIDTH / 2;
int boss2Y = SCREEN_HEIGHT / 5;

int boss3X = SCREEN_WIDTH / 2;
int boss3Y = SCREEN_HEIGHT / 5;

int bossDirection = 1;
int boss2Direction = 1;
int boss3Direction = 1;

int bossBlood = 20;
int boss2Blood = 40;
int boss3Blood = 50;

bool isBossVisible = false;

void LoadBoss()
{
    if (Points >= 50 && Points <= 70 && bossBlood > 0) 
    { 
       
        Level = 2;
        isBossVisible = true;
        SDL_Rect bossRect = { bossX, bossY, 0, 0 };
        SDL_Rect* currentClip = &gBossClips[currentFrame / 3];
        SDL_BlitSurface(gBossImage, currentClip, gScreenSurface, &bossRect);
        createLightImage(bossX, bossY);
    }
    else if(Points >= 200 && Points <= 250 && boss2Blood > 0)
    {
     
        Level = 3;
        isBossVisible = true;
        SDL_Rect boss2Rect = { boss2X, boss2Y, 0, 0 };
        SDL_Rect* currentClip = &gBoss2Clips[currentFrame / 3];
        SDL_BlitSurface(gBoss2Image, currentClip, gScreenSurface, &boss2Rect);
        //SDL_Rect boss2Rect = { boss2X, boss2Y, 0, 0 };
        //SDL_BlitSurface(gBoss2Image, NULL, gScreenSurface, &boss2Rect);
        createLightImage(boss2X, boss2Y);
    }
    else if(Points >=1000 && Points <= 1100 && boss3Blood > 0)
    {

        Level = 4;
        isBossVisible = true;
        SDL_Rect boss3Rect = { boss3X, boss3Y, 0, 0 };
        SDL_Rect* currentClip = &gBoss3Clips[currentFrame / 3];
        SDL_BlitSurface(gBoss3Image, currentClip, gScreenSurface, &boss3Rect);
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