#ifndef GHOST_H
#define GHOST_H
#include <string>
#include <stdio.h>


class Ghost{

public:
    Ghost();
    int Direction;
    int State;
    int SpeedX;
    int SpeedY;
    int PosX,PosY;
    std::string ImgLoc;
    enum DIRECTION{FIRST_SOUTH,SECOND_SOUTH,FIRST_EAST,SECOND_EAST,FIRST_NORTH,SECOND_NORTH,FIRST_WEST,SECOND_WEST}; //first and second entries are used to choose the eyes for the sprite at the time
    enum STATE{CHILLED,ANGRY,PISSED};
    enum SPEED{SLOW,MEDIUM,FAST};
    void Load_State_IMG();
    ~Ghost();
private:
    int Algorithm(std::string destination);
    int Change_State();
};

#endif