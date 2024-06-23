#include "Map.cpp"

class window
{
public:
    window(SDL_Renderer* &Renderer,SDL_Window* &Window);
    void Screen();
    pair<int,int> GetPacmanPos();
    void Screen(SDL_Renderer* &Renderer,Map& map,Blinky &blinky,Inky &inky,Pinky &pinky,pacman &pacman);
    void close(SDL_Renderer* &Renderer,SDL_Window* &Window);
    void ResetPositions(pacman &Pacman, Blinky &Blinky, Inky &Inky);
    bool CheckCollision(pacman &Pacman, Blinky &Blinky, Inky &Inky);
    ~window();
private:
    int initialPacmanPosX;
    int initialPacmanPosY;
    int initialBlinkyPosX;
    int initialBlinkyPosY;
    int initialInkyPosX;
    int initialInkyPosY;
    void StartWindow(SDL_Renderer* &Renderer,SDL_Window* &Window);
};