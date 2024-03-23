#include "gameLoop.h"


void gameLoop() {
    SDL_Event e;
    Uint32 lastUpdate = SDL_GetTicks();
    const Uint32 FRAME_DELAY = 400 / 60;
    while (!gameOver) {
        while (SDL_PollEvent(&e) != 0) {
            handleEvent(e);
        }
        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastUpdate;
        if (deltaTime >= FRAME_DELAY) {
            if (isMovingLeft && spriteX > 0) {
                spriteX -= SPRITE_SPEED;
                if (isSpriteFacingRight) {
                    isSpriteFacingRight = false;
                    changeSpriteImage();
                }
            }
            if (isMovingRight && spriteX < SCREEN_WIDTH - gSprite->w) {
                spriteX += SPRITE_SPEED;
                if (!isSpriteFacingRight) {
                    isSpriteFacingRight = true;
                    changeSpriteImage();
                }
            }
            for (auto& bullet : bullets) {
                bullet.y -= BULLET_SPEED;
            }
            lastUpdate = currentTime;
        }
        renderGame();
    }
}
