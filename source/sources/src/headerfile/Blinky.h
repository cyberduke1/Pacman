#ifndef BLINKY_H
#define BLINKY_H

#include "C:\Users\zulul\Documents\pacman\Pacman\source\sources\src\Ghost.cpp"


class Blinky : Ghost{
    public:
        SDL_Rect SpriteClips[8];
        Blinky(int cell_size); //Exact location of the pacman
        ~Blinky();
};

#endif