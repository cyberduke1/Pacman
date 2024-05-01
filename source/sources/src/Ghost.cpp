#include "headerfile/Ghost.h"
#include <SDL2/SDL.h>


void Ghost::Load_State_IMG()
{

}

Ghost::~Ghost()
{
    Direction = 0;
    State = 0;
    SpeedX = 0;
    SpeedY = 0;
}
Ghost::Ghost()
{
    Direction = -1;
    State = -1;
    SpeedX = 0;
    SpeedY = 0;
}

int Ghost::Algorithm(std::string destination)
{
    return 0;
}

int Ghost::Change_State()
{
    return 0;
}