#include "game_functions.h"
#include "globals.h"
#include "checkCollision.h"
#include "randomFalling.h"
#include "gameLoop.h"
#include <iostream>
#include <string>


void handleEvent(SDL_Event &e) 
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
            case SDLK_UP:
                Bullet bullet;
                bullet.x = spriteX + (gSprite->w - BULLET_WIDTH*14);
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
            case SDLK_UP:
                gSprite = SDL_LoadBMP("img/maybayk33.bmp");
                break;
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

void renderGame(SDL_Surface* gScreenSurface, SDL_Surface* gBackground, SDL_Surface* gGameOverImage, SDL_Surface* gSprite, SDL_Surface* gBulletImage,
    std::vector<FallingImage>& fallingImages, std::vector<Bullet>& bullets, int& spriteX, int& spriteY, bool& isMovingLeft, bool& isMovingRight, bool& isSpriteFacingRight, bool& gameOver) {
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0, 0, 0));
    SDL_BlitSurface(gBackground, NULL, gScreenSurface, NULL);
    
    if (Time>=10) {
                
        SDL_Rect bossRect = { (SCREEN_WIDTH - gBossImage->w) / 2, (SCREEN_HEIGHT - gBossImage->h) / 2, 0, 0 };
        SDL_BlitSurface(gBossImage, NULL, gScreenSurface, &bossRect);
    }
    
    for (auto& bullet : bullets) {
        bullet.y -= BULLET_SPEED;
        SDL_Rect bulletRect = { bullet.x, bullet.y, BULLET_WIDTH, BULLET_HEIGHT };
        SDL_BlitSurface(gBulletImage, NULL, gScreenSurface, &bulletRect);
    }

    for (int i = 0; i < NUM_FALLING_IMAGES; i++) {
        fallingImages[i].y += FALLING_SPEED;
        if (fallingImages[i].y > SCREEN_HEIGHT) {
            fallingImages[i].x = rand() % SCREEN_WIDTH;
            fallingImages[i].y = rand() % (SCREEN_HEIGHT / 10);
            fallingImages[i].imagePath = getRandomFallingImage();
        }
        SDL_Surface* fallingImage = SDL_LoadBMP(fallingImages[i].imagePath.c_str());
        if (fallingImage == NULL) {
            printf("Unable to load falling image! SDL Error: %s\n", SDL_GetError());
        }
        else {
            SDL_Rect fallingRect = { fallingImages[i].x, fallingImages[i].y, 0, 0 };
            SDL_BlitSurface(fallingImage, NULL, gScreenSurface, &fallingRect);
            SDL_FreeSurface(fallingImage);
        }
        int spriteW = gSprite->w;
        int spriteH = gSprite->h;
        int imageW = fallingImage->w;
        int imageH = fallingImage->h; 
        if (checkCollision(spriteX, spriteY, spriteW, spriteH, fallingImages[i].x, fallingImages[i].y, imageW, imageH)) {
            Blood --;
            if(Blood == 0)
            {
               gameOver = true;
               return;
            }
        }
    }

    SDL_Rect spriteRect = { spriteX, spriteY, 0, 0 };
    SDL_BlitSurface(gSprite, NULL, gScreenSurface, &spriteRect);
    renderText("Time: " + std::to_string(Time), 10, 10); // Render Time at top-left corner
    renderText("Points: " + std::to_string(Points), 200, 10); // Render Time at top-left corner
    renderText("Blood : " + std::to_string(Blood), 400, 10);
    SDL_UpdateWindowSurface(gWindow);
}
