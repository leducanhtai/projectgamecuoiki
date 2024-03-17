#include "gameLoop.h"
#include "game_functions.h"
#include "globals.h"
#include "checkCollision.h"
#include "randomFalling.h"
#include <iostream>
#include <string>



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
                    changeSpriteImage(); // Thay đổi hình ảnh khi đổi hướng
                }
            }
            if (isMovingRight && spriteX < SCREEN_WIDTH - gSprite->w) {
                spriteX += SPRITE_SPEED;
                if (!isSpriteFacingRight) {
                    isSpriteFacingRight = true;
                    changeSpriteImage(); // Thay đổi hình ảnh khi đổi hướng
                }
            }
            // Di chuyển các viên đạn lên trên màn hình
            for (auto& bullet : bullets) {
                bullet.y -= BULLET_SPEED;
            }
            lastUpdate = currentTime;
        }
        renderGame(); // Gọi hàm vẽ trò chơi
    }
}
