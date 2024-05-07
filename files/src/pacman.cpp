#include "pacman.h"

void pacman::InitPacman(SDL_Renderer *renderer)
{
    pacLocation = "C:\\Users\\zulul\\Documents\\pacman\\mrs pacman\\files\\resources\\sprites\\pacman.png";
    SDL_Texture *texture = IMG_LoadTexture(renderer, pacLocation.c_str());
    if (texture == nullptr)
    {
        std::cout << "Unable to load pacman image " << pacLocation << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        PacmanSprites.push_back(texture);
    }
}

pacman::pacman(SDL_Renderer *renderer)
{
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

SDL_Texture *pacman::LoadSprites(SDL_Renderer *renderer, int rowIndex, int colIndex, int numRows, int numCols)
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
        int spriteWidth = loadedSurface->w / numCols;
        int spriteHeight = loadedSurface->h / numRows;

        SDL_Rect spriteRect = {
            colIndex * spriteWidth,
            rowIndex * spriteHeight,
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
