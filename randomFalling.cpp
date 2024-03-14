#include <string>
#include <cstdlib>
#include <ctime>
#include "randomFalling.h"

std::string getRandomFallingImage() {
    int randomNum = rand() % 4 + 1;
    return "img/bom" + std::to_string(randomNum) + ".bmp";
}