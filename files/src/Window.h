#ifndef WINDOW_H
#define WINDOW_H
#include "constants.h"

class Window
{
private:
    
public:
    Window();
    Map Stages(int Stage);
    void DrawCircle(SDL_Renderer * renderer, int32_t centerX, int32_t centerY, int32_t radius);
    ~Window();
};
#endif

