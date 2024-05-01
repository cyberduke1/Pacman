#include "headerfile/Blinky.h"


Blinky::Blinky(int cell_size)
{
    Direction = -1;
    State = CHILLED;
    SpeedX = SLOW;
    SpeedY = SLOW;
    ImgLoc = "C://Users//zulul//Documents//pacman//Pacman//source//resources//sprites//blinky.png";
    //destination is the exact position of the pacman

    //Set top left sprite
    SpriteClips[ 0 ].w = cell_size;
    SpriteClips[ 0 ].h = cell_size;

        //Set top right sprite
    SpriteClips[ 1 ].w = cell_size;
    SpriteClips[ 1 ].h = cell_size;
        
        //Set bottom left sprite
    SpriteClips[ 2 ].w = cell_size;
    SpriteClips[ 2 ].h = cell_size;

        //Set bottom right sprite
    SpriteClips[ 3 ].w = cell_size;
    SpriteClips[ 3 ].h = cell_size;    
}

Blinky::~Blinky()
{
    Direction = -1;
    State = CHILLED;
    SpeedX = SLOW;
    SpeedY = SLOW;
}
