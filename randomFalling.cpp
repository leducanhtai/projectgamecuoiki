#include <string>
#include <cstdlib>
#include <ctime>

std::string getRandomFallingImage() {
    int randomNum = rand() % 4 + 1;
    return "img/appple" + std::to_string(randomNum) + ".bmp";
}