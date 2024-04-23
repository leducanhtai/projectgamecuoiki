all:
    g++ -Isrc/include -Lsrc/lib -o game checkCollision.cpp randomFalling.cpp LoadBoss.cpp handleEvent.cpp game_functions.cpp gameLoop.cpp main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer
