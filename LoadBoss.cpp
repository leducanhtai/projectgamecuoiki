#include "LoadBoss.h"
void LoadBoss()
{
    if (Points >= 10 && Points <= 40) 
    { 
        isBossVisible = true;
        SDL_Rect bossRect = { bossX, bossY, 0, 0 };
        SDL_BlitSurface(gBossImage, NULL, gScreenSurface, &bossRect);
    }
    else if(Points >= 60 && Points <= 80 )
    {
        isBossVisible = true;
        SDL_Rect boss2Rect = { boss2X, boss2Y, 0, 0 };
        SDL_BlitSurface(gBoss2Image, NULL, gScreenSurface, &boss2Rect);
    }
    else if(Points >=100 && Points <= 150)
    {
        isBossVisible = true;
        SDL_Rect boss3Rect = { boss3X, boss3Y, 0, 0 };
        SDL_BlitSurface(gBoss3Image, NULL, gScreenSurface, &boss3Rect);
    }
    else
    {
        isBossVisible = false;
    }
}