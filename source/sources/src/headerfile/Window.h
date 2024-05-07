#ifndef WINDOW_H
#define WINDOW_H
#include "constants.h"




using Map = std::vector<std::string>;

class Window
{

private:

    void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);

    std::vector<SDL_Texture *> BlinkySprites;
    std::vector<SDL_Texture *> InkySprites;
    std::vector<SDL_Texture *> PinkySprites;
    std::vector<SDL_Texture *> ClydeSprites;
    std::vector<SDL_Texture *> PacmanSprites;

public:
    //Methods
    void InitialLoad(SDL_Renderer *renderer);
    bool DrawMap(SDL_Renderer *renderer, Map map);
    SDL_Texture* LoadSprite(const std::string &location, SDL_Renderer *renderer, int spriteIndex);
    SDL_Texture* LoadSprites(const std::string &location, SDL_Renderer *renderer, int rowIndex, int colIndex, int numRows, int numCols);
    std::vector<std::string> Located;
    Window();
    ~Window();
};

#endif // WINDOW_H