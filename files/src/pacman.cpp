#include "pacman.h"



pacman::pacman(SDL_Renderer *renderer)
{
    Direction = SECOND_EAST;
    SpriteCord.push_back({0,0});//East 1
    SpriteCord.push_back({0,1});//East 2
    SpriteCord.push_back({1,0});//West 1
    SpriteCord.push_back({1,1});//West 2
    SpriteCord.push_back({2,0});//Up 1
    SpriteCord.push_back({2,1});//up 2
    SpriteCord.push_back({3,0});//Down 1
    SpriteCord.push_back({3,1});//Down 2
}

std::pair<int, int> pacman::getPacmanPos(std::vector<std::string> map)
{
    for (int row = 0; row < map.size(); row++)
    {
        for (int col = 0; col < map[row].size(); col++)
        {
            if (map[row][col] == '9')
            {
                return {row, col};
            }
        }
    }
}

SDL_Texture *pacman::LoadSprites(SDL_Renderer *renderer, int rowIndex, int colIndex, int numRows, int numCols) const
{
    SDL_Texture *texture = nullptr;

    std::string Location = "C:\\Users\\zulul\\Documents\\pacman\\mrs pacman\\files\\resources\\sprites\\pacman.png";
    SDL_Surface *loadedSurface = IMG_Load(Location.c_str());
    if (loadedSurface == nullptr)
    {
        std::cout << "Unable to load pacman image " << Location << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        int spriteWidth = (loadedSurface->w / numCols);
        int spriteHeight = (loadedSurface->h / numRows);

        
        
        SDL_Rect spriteRect = {
            colIndex * (spriteWidth),
            rowIndex * (spriteHeight),
            spriteWidth,
            spriteHeight};

        SDL_Surface *spriteSurface = SDL_CreateRGBSurfaceWithFormat(0, spriteWidth, spriteHeight, 32, SDL_PIXELFORMAT_RGBA32);
        if (spriteSurface == nullptr)
        {
            std::cout << "Unable to create surface for sprite from pacman image " << Location << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            SDL_BlitSurface(loadedSurface, &spriteRect, spriteSurface, nullptr);

            texture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
            if (texture == nullptr)
            {
                std::cout << "Unable to create texture from pacman surface! SDL Error: " << SDL_GetError() << std::endl;
                return texture;
            }

            SDL_FreeSurface(spriteSurface);
        }

        SDL_FreeSurface(loadedSurface);
    }
    return texture;
}


pacman::~pacman()
{
    for (auto texture : PacmanSprites)
    {
        SDL_DestroyTexture(texture);
    }
}
