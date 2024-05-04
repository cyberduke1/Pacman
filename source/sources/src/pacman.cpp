#include "headerfile/pacman.h"


void pacman::updatePos(int dir)
{
    Direction = dir;
}

pacman::pacman()
{

    Direction = FIRST_WEST;
}

pacman::~pacman()
{

}