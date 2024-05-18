#include "pacman.h"



pacman::pacman(SDL_Renderer *renderer)
{
    Direction = SECOND_EAST;
    Position = {0,0,0,0};
    SpriteCord.push_back({0,0});//East 1
    SpriteCord.push_back({0,1});//East 2
    SpriteCord.push_back({1,0});//West 1
    SpriteCord.push_back({1,1});//West 2
    SpriteCord.push_back({2,0});//Up 1
    SpriteCord.push_back({2,1});//up 2
    SpriteCord.push_back({3,0});//Down 1
    SpriteCord.push_back({3,1});//Down 2

    Loc.push_back("C:\\Users\\zulul\\Documents\\pacman\\pacman\\files\\resources\\sprites\\pacmaneast1.png");
    Loc.push_back("C:\\Users\\zulul\\Documents\\pacman\\pacman\\files\\resources\\sprites\\pacmaneast2.png");
    Loc.push_back("C:\\Users\\zulul\\Documents\\pacman\\pacman\\files\\resources\\sprites\\pacmanwest1.png");
    Loc.push_back("C:\\Users\\zulul\\Documents\\pacman\\pacman\\files\\resources\\sprites\\pacmanwest2.png");
    Loc.push_back("C:\\Users\\zulul\\Documents\\pacman\\pacman\\files\\resources\\sprites\\pacmanup1.png");
    Loc.push_back("C:\\Users\\zulul\\Documents\\pacman\\pacman\\files\\resources\\sprites\\pacmanup2.png");
    Loc.push_back("C:\\Users\\zulul\\Documents\\pacman\\pacman\\files\\resources\\sprites\\pacmandown1.png");
    Loc.push_back("C:\\Users\\zulul\\Documents\\pacman\\pacman\\files\\resources\\sprites\\pacmandown2.png");
    Loc.push_back("C:\\Users\\zulul\\Documents\\pacman\\pacman\\files\\resources\\sprites\\pacmaninit.png");

    //PacmanSprites = LoadSprites;
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

SDL_Rect pacman::PacmanUpdate(Map &One)
{
    Position.y = getPacmanPos(One).first;
    Position.x = getPacmanPos(One).second;

    switch (Direction) {
        case FIRST_SOUTH:
        case SECOND_SOUTH:
            Position.y += static_cast<int>(PacmanSpeed * DeltaTime);
            break;
        case FIRST_EAST:
        case SECOND_EAST:
            Position.x += static_cast<int>(PacmanSpeed * DeltaTime);
            break;
        case FIRST_NORTH:
        case SECOND_NORTH:
            Position.y -= static_cast<int>(PacmanSpeed * DeltaTime);
            break;
        case FIRST_WEST:
        case SECOND_WEST:
            Position.x -= static_cast<int>(PacmanSpeed * DeltaTime);
            break;
        default:
            break;
    }

    
    One[Position.y][Position.x] = '9';
}

void pacman::PacmanMove(SDL_Event event, Map &One, pacman &Pacman)
{
    int pacmanY = getPacmanPos(One).first;
    int pacmanX = getPacmanPos(One).second;
    switch (event.key.keysym.sym) {
        case SDLK_UP:
            if (pacmanY > 0 && One[pacmanY - 1][pacmanX] != '#' && One[pacmanY - 1][pacmanX] != '=' && One[pacmanY - 1][pacmanX] != '0' && One[pacmanY - 1][pacmanX] != '1' && One[pacmanY - 1][pacmanX] != '2' && One[pacmanY - 1][pacmanX] != '3') {
                One[pacmanY][pacmanX] = ' ';
                PacmanUpdate(One);
            }
            Pacman.Direction = Pacman.FIRST_NORTH;
            break;
        case SDLK_DOWN:
            if (pacmanY < One.size() - 1 && One[pacmanY + 1][pacmanX] != '#' && One[pacmanY + 1][pacmanX] != '=' && One[pacmanY + 1][pacmanX] != '0' && One[pacmanY + 1][pacmanX] != '1' && One[pacmanY + 1][pacmanX] != '2' && One[pacmanY + 1][pacmanX] != '3') {
                One[pacmanY][pacmanX] = ' ';
                PacmanUpdate(One);
            }
            Pacman.Direction = Pacman.FIRST_SOUTH;
            break;
        case SDLK_LEFT:
            if (pacmanX > 0 && One[pacmanY][pacmanX - 1] != '#' && One[pacmanY][pacmanX - 1] != '=' && One[pacmanY][pacmanX - 1] != '0' && One[pacmanY][pacmanX - 1] != '1' && One[pacmanY][pacmanX - 1] != '2' && One[pacmanY][pacmanX - 1] != '3') {
                One[pacmanY][pacmanX] = ' ';
                PacmanUpdate(One);
            }
            Pacman.Direction = Pacman.FIRST_WEST;
            break;
        case SDLK_RIGHT:
            if (pacmanX < One[pacmanY].size() - 1 && One[pacmanY][pacmanX + 1] != '#' && One[pacmanY][pacmanX + 1] != '=' && One[pacmanY][pacmanX + 1] != '0' && One[pacmanY][pacmanX + 1] != '1' && One[pacmanY][pacmanX + 1] != '2' && One[pacmanY][pacmanX + 1] != '3') {
                One[pacmanY][pacmanX] = ' ';
                PacmanUpdate(One);
            }
            Pacman.Direction = Pacman.FIRST_EAST;
            break;
        default:
            break;
    }
    
}

SDL_Texture *pacman::LoadSprites(SDL_Renderer *renderer, int rowIndex, int colIndex, std::string pacLocation) const
{
    SDL_Texture *texture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(pacLocation.c_str());
    if (loadedSurface == nullptr) {
        std::cout << "Unable to load pacman image " << pacLocation << "! SDL_image Error: " << IMG_GetError() << std::endl;
    } else {
        int spriteWidth = rowIndex;
        int spriteHeight = colIndex;

        
        if (spriteWidth <= 0 || spriteHeight <= 0) {
            std::cout << "Invalid sprite dimensions for " << pacLocation << "!" << std::endl;
            SDL_FreeSurface(loadedSurface);
            return nullptr;
        }

        
        SDL_Rect spriteRect = {0, 0, spriteWidth, spriteHeight};

        
        SDL_Surface *spriteSurface = SDL_CreateRGBSurfaceWithFormat(0, spriteWidth, spriteHeight, 32, SDL_PIXELFORMAT_RGBA32);
        if (spriteSurface == nullptr) {
            std::cout << "Unable to create surface for sprite from pacman image " << pacLocation << "! SDL Error: " << SDL_GetError() << std::endl;
        } else {
            
            SDL_BlitSurface(loadedSurface, nullptr, spriteSurface, nullptr);

            
            texture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
            if (texture == nullptr) {
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
    SDL_DestroyTexture(PacmanSprites);
}
