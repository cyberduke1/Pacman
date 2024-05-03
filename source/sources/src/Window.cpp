#include "headerfile/Window.h"

Window::Window()
{
    Located = {
        "C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\blinky.png",
        "C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\inky.png",
        "C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\clyde.png",
        "C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\Pinky.png",
        "C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\pacman.png"};

    BlinkySprites.reserve(Located.size());
    InkySprites.reserve(Located.size());
    PinkySprites.reserve(Located.size());
    ClydeSprites.reserve(Located.size());
    PacmanSprites.reserve(Located.size());
}

void Window::InitialLoad(SDL_Renderer *renderer)
{
    for (int i = 0; i < Located.size(); i++)
    {
        SDL_Texture *texture = IMG_LoadTexture(renderer, Located[i].c_str());
        if (texture == nullptr)
        {
            std::cout << "Unable to load image " << Located[i] << "! SDL_image Error: " << IMG_GetError() << std::endl;
            continue;
        }

        switch (i)
        {
        case 0:
            BlinkySprites.push_back(texture);
            break;
        case 1:
            InkySprites.push_back(texture);
            break;
        case 2:
            PinkySprites.push_back(texture);
            break;
        case 3:
            ClydeSprites.push_back(texture);
            break;
        case 4:
            PacmanSprites.push_back(texture);
            break;
        }
    }
}

SDL_Texture *Window::LoadSprites(const std::string &location, SDL_Renderer *renderer, int rowIndex, int colIndex, int numRows, int numCols)
{
    SDL_Texture *texture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(location.c_str());
    if (loadedSurface == nullptr)
    {
        std::cout << "Unable to load image " << location << "! SDL_image Error: " << IMG_GetError() << std::endl;
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
            std::cout << "Unable to create surface for sprite from image " << location << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            SDL_BlitSurface(loadedSurface, &spriteRect, spriteSurface, nullptr);

            texture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
            if (texture == nullptr)
            {
                std::cout << "Unable to create texture from surface! SDL Error: " << SDL_GetError() << std::endl;
            }

            SDL_FreeSurface(spriteSurface);
        }

        SDL_FreeSurface(loadedSurface);
    }
    return texture;
}


SDL_Texture *Window::LoadSprite(const std::string &location, SDL_Renderer *renderer, int spriteIndex)
{
    SDL_Texture *texture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(location.c_str());
    if (loadedSurface == nullptr)
    {
        std::cout << "Unable to load image " << location << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {

        int spriteWidth = loadedSurface->w / NUM_SPRITES_PER_IMAGE;
        int spriteHeight = loadedSurface->h;

        SDL_Rect spriteRect = {spriteIndex * spriteWidth, 0, spriteWidth, spriteHeight};

        SDL_Surface *spriteSurface = SDL_CreateRGBSurfaceWithFormat(0, spriteWidth, spriteHeight, 32, SDL_PIXELFORMAT_RGBA32);
        if (spriteSurface == nullptr)
        {
            std::cout << "Unable to create surface for sprite from image " << location << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            SDL_BlitSurface(loadedSurface, &spriteRect, spriteSurface, nullptr);
            texture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
            if (texture == nullptr)
            {
                std::cout << "Unable to create texture from surface! SDL Error: " << SDL_GetError() << std::endl;
            }
            SDL_FreeSurface(spriteSurface);
        }
        SDL_FreeSurface(loadedSurface);
    }
    return texture;
}

bool Window::DrawMap(SDL_Renderer *renderer, Map One)
{
    SDL_Rect Wall = {0, 0, 0, 0};
    bool FullyRan = false;
    for (int y = 0; y < LIMIT; y++)
    {
        for (int x = 0; x < LIMIT; x++)
        {
            Wall = {(x + 13) * CELL_SIZE, (y + 13) * CELL_SIZE, CELL_SIZE, CELL_SIZE};

            switch (One[y][x])
            {
            case '#':
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_RenderFillRect(renderer, &Wall);
                break;
            case '.':
                
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawPoint(renderer, Wall.x + CELL_SIZE / 2, Wall.y + CELL_SIZE / 2);
                break;
            case '0':
                
                if (!BlinkySprites.empty())
                {
                    SDL_Texture *spriteTexture = LoadSprite(Located[0], renderer, 0); // Assuming Blinky is at index 0
                    if (spriteTexture != nullptr)
                    {
                        SDL_RenderCopy(renderer, spriteTexture, nullptr, &Wall);
                        SDL_DestroyTexture(spriteTexture);
                    }
                }
                break;
            case '1':
                
                if (!InkySprites.empty())
                {
                    SDL_Texture *spriteTexture = LoadSprite(Located[1], renderer, 0); // Assuming Inky is at index 1
                    if (spriteTexture != nullptr)
                    {
                        SDL_RenderCopy(renderer, spriteTexture, nullptr, &Wall);
                        SDL_DestroyTexture(spriteTexture);
                    }
                }
                break;
            case '2':
                
                if (!PinkySprites.empty())
                {
                    SDL_Texture *spriteTexture = LoadSprite(Located[2], renderer, 0); // Assuming Pinky is at index 2
                    if (spriteTexture != nullptr)
                    {
                        SDL_RenderCopy(renderer, spriteTexture, nullptr, &Wall);
                        SDL_DestroyTexture(spriteTexture);
                    }
                }
                break;
            case '3':
                
                if (!ClydeSprites.empty())
                {
                    SDL_Texture *spriteTexture = LoadSprite(Located[3], renderer, 0); // Assuming Clyde is at index 3
                    if (spriteTexture != nullptr)
                    {
                        SDL_RenderCopy(renderer, spriteTexture, nullptr, &Wall);
                        SDL_DestroyTexture(spriteTexture);
                    }
                }
                break;
            case '9':
                
                if (!PacmanSprites.empty()){

                
                    SDL_Texture *spriteTexture = LoadSprites(Located[4], renderer, 0, 0, 4, 2);
                    if (spriteTexture != nullptr){

                        SDL_RenderCopy(renderer, spriteTexture, nullptr, &Wall);
                        SDL_DestroyTexture(spriteTexture);
                    }
                }
                break;
            case 'o':
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                SDL_RenderDrawPoint(renderer, Wall.x + CELL_SIZE / 2, Wall.y + CELL_SIZE / 2);
                DrawCircle(renderer, Wall.x + CELL_SIZE / 2, Wall.y + CELL_SIZE / 2,CELL_SIZE/6);
                break;
            case '=':
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &Wall);
                break;

            default:
                break;
            }
        }
    }
    FullyRan = true;

    return FullyRan;
}

void Window::DrawCircle(SDL_Renderer * renderer, int32_t centerX, int32_t centerY, int32_t radius)
{
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }

}



Window::~Window()
{
    for (auto texture : BlinkySprites)
    {
        SDL_DestroyTexture(texture);
    }
    for (auto texture : InkySprites)
    {
        SDL_DestroyTexture(texture);
    }
    for (auto texture : PinkySprites)
    {
        SDL_DestroyTexture(texture);
    }
    for (auto texture : ClydeSprites)
    {
        SDL_DestroyTexture(texture);
    }
    for (auto texture : PacmanSprites)
    {
        SDL_DestroyTexture(texture);
    }
}
