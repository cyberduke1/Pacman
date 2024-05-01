#include "headerfile/Inky.h"


Inky::Inky()
{
    //destination is the 2 position from the position of the pacman
    Direction = -1;
    State = CHILLED;
    SpeedX = SLOW;
    SpeedY = SLOW;
    ImgLoc = "C://Users//zulul//Documents//pacman//Pacman//source//resources//sprites//inky.png";
}