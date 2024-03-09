#include <iostream>
#include "src/include/SDL2/SDL.h"

using std::cin;
using std::cout;
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 900;
SDL_Window* gwindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* BackGround = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO)<0) {
        cout<<"SDL Could not Initialize, SDL Error:\n"<<SDL_GetError();
        return false;
    }
    else {
        gwindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gwindow == NULL) {
            cout<<"Window could not be created\nSDL Error:\n"<<SDL_GetError();
            return false;
        }
        else {
            gScreenSurface = SDL_GetWindowSurface(gwindow);
        }
    }
    return true;
}
bool loadmedia(const char path[], SDL_Surface*& Carry_Surface) {
    Carry_Surface = SDL_LoadBMP(path);
    return Carry_Surface != NULL;
}
void stay_window() {
    SDL_Event e;
    bool quit = false;
    while(!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } 
        }
    }
}
int main(int argc, char* args[]) {
    if (init()) {
        BackGround = SDL_LoadBMP("img/farm.bmp");
        if (BackGround != NULL) {
            SDL_BlitSurface(BackGround, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gwindow);
        }
        else {
            cout<<"Error:\n"<<SDL_GetError();
        }
        stay_window();
    }
    return 0;
}