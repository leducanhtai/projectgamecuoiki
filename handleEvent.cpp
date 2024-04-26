#include "handleEvent.h"

bool isMovingLeft = false;
bool isMovingRight = false;
bool isMouseClicked = false;

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
        case SDLK_f:
            Bullet bullet;
            bullet.x = spriteX + (gSprite->w - BULLET_WIDTH - 15);
            bullet.y = spriteY;
            bullets.push_back(bullet);
            Mix_PlayChannel(-1, soundBullet, 0);
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