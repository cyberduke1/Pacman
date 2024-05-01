#include "headerfile/Pinky.h"


Pinky::Pinky()
{
    //destination is the 3 position from the position of the pacman
    Direction = -1;
    State = CHILLED;
    SpeedX = SLOW;
    SpeedY = SLOW;
    ImgLoc = "C://Users//zulul//Documents//pacman//Pacman//source//resources//sprites//Pinky.png";
}