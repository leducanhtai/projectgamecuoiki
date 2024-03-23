#include "checkCollision.h"

bool checkCollision(int spriteX, int spriteY, int spriteW, int spriteH, int imageX, int imageY, int imageW, int imageH) {
    if (spriteY + spriteH < imageY || imageY + imageH < spriteY) {
        return false;
    }
    if (spriteX + spriteW < imageX || imageX + imageW < spriteX) {
        return false;
    }
    return true;
}