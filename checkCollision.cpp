#include "checkCollision.h"


bool checkCollision(int X1, int Y1, int W1, int H1, int X2, int Y2, int W2, int H2) {
    if (Y1 + H1 < Y2 || Y2 + H2 < Y1) {
        return false;
    }
    if (X1 + W1 < X2 || X2 + W2 < X1) {
        return false;
    }
    return true;
}