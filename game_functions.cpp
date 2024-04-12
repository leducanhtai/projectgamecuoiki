#include "game_functions.h"
#include "globals.h"
#include "checkCollision.h"
#include "randomFalling.h"
#include "gameLoop.h"
#include <iostream>
#include <string>


void handleEvent(SDL_Event& e) 
{
    if (e.type == SDL_QUIT) 
    {
        SDL_Quit();
        exit(0);
    }
    else if (e.type == SDL_KEYDOWN) 
    {
        switch (e.key.keysym.sym) 
        {
        case SDLK_LEFT:
            isMovingLeft = true;
            isMovingRight = false;
            break;
        case SDLK_RIGHT:
            isMovingLeft = false;
            isMovingRight = true;
            break;
        //case SDLK_UP:
        //    spriteY -= SPRITE_SPEEDU;
        //    break;
       // case SDLK_DOWN: 
        //    spriteY += SPRITE_SPEEDU;
        //    break;
        case SDLK_f:
            Bullet bullet;
            bullet.x = spriteX + (gSprite->w - BULLET_WIDTH * 14);
            bullet.y = spriteY;
            bullets.push_back(bullet);
            break;
        }
    }
    else if (e.type == SDL_KEYUP) 
    {
        switch (e.key.keysym.sym) 
        {
        case SDLK_LEFT:
            isMovingLeft = false;
            break;
        case SDLK_RIGHT:
            isMovingRight = false;
            break;
        
        }
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN) 
    {
        if (gameOver) 
        {
            isMouseClicked = true;
        }
    }
}

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
        lightImage.x = bossX + (gBossImage->w - gLightImage->w) / 2; // Ensure light image is centered on boss
        lightImage.y = bossY + gBossImage->h - 100;
        lightImages.push_back(lightImage);
    
}

void renderGame(SDL_Surface* gScreenSurface, SDL_Surface* gBackground, SDL_Surface* gGameOverImage, SDL_Surface* gSprite, 
                SDL_Surface* gBulletImage,std::vector<FallingImage>& fallingImages, std::vector<Bullet>& bullets, int& spriteX, 
                int& spriteY, bool& isMovingLeft, bool& isMovingRight, bool& isSpriteFacingRight, bool& gameOver) 
{
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));
    SDL_BlitSurface(gBackground, NULL, gScreenSurface, NULL);

    LoadBoss();
    
    for (auto& bullet : bullets) 
    {
        bullet.y -= BULLET_SPEED;
        SDL_Rect bulletRect = { bullet.x, bullet.y, BULLET_WIDTH, BULLET_HEIGHT };
        SDL_BlitSurface(gBulletImage, NULL, gScreenSurface, &bulletRect);
    }
    for (auto lightIter = lightImages.begin(); lightIter != lightImages.end();) 
    {
        lightIter->y += 3;
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
            Blood --;
            if(Blood == 0)
            {
               gameOver = true;
               return;
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
        if (checkCollision(spriteX, spriteY, spriteW, spriteH, fallingImages[i].x, fallingImages[i].y, imageW, imageH)) 
        {
            Blood --;
            if(Blood == 0)
            {
               gameOver = true;
               return;
            }
        }
    }

    SDL_Rect spriteRect = { spriteX, spriteY, 0, 0 };
    SDL_Rect* currentClip = &gSpriteClips[currentFrame / 3];
    SDL_BlitSurface(gSprite, currentClip, gScreenSurface, &spriteRect);
    //SDL_BlitSurface(gSprite, NULL, gScreenSurface, &spriteRect);
    renderText("Time: " + std::to_string(Time), 10, 10);
    renderText("Points: " + std::to_string(Points), 200, 10);
    renderText("Blood : " + std::to_string(Blood), 400, 10);
    renderText("Level : " + std::to_string(Level), 400, 50);
    SDL_UpdateWindowSurface(gWindow);
}