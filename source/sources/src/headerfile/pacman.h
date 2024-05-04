#include <iostream>
#ifndef PACMAN_H
#define PACMAN_H


class pacman{
    public:
        pacman();
        ~pacman();
        enum DIRECTION{
            FIRST_SOUTH, SECOND_SOUTH, 
            FIRST_EAST, SECOND_EAST,
            FIRST_NORTH, SECOND_NORTH,
            FIRST_WEST, SECOND_WEST
        };
        int Direction;

        void updatePos(int dir);
    //private:
        
};
#endif