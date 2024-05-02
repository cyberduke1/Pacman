#include "headerfile/Blinky.h"


Blinky::Blinky(int cell_size)
{
    Direction = -1;
    State = CHILLED;
    SpeedX = SLOW;
    SpeedY = SLOW;
    
}

Blinky::~Blinky()
{
    Direction = -1;
    State = CHILLED;
    SpeedX = SLOW;
    SpeedY = SLOW;
}
