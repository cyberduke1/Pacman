#include "pacman.cpp"
#include "Window.cpp"


SDL_Window *GameWindow = nullptr;
SDL_Renderer *MainRenderer = nullptr;
SDL_Event event;

void Init();
void DrawMap(SDL_Renderer *renderer, Map One,pacman Pacman,Window LoadMap);
void Update(pacman Pacman,Window LoadMaps);

int main(int argv,char *argc[]){

    Init();

    pacman Pacman(MainRenderer);
    Window LoadMaps;
    bool quit = false;
    int CurrentStage = 1;
    Map UpdatedState = LoadMaps.Stages(CurrentStage);
    DrawMap(MainRenderer,LoadMaps.Stages(CurrentStage),Pacman,LoadMaps);
    SDL_RenderPresent(MainRenderer);
    while(!quit){
        while(SDL_PollEvent(&event) != 0){

            if(event.type == SDL_QUIT){
                quit = true;
                break;
            }
        }
    }

    return 0;
}

void Init()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    GameWindow = SDL_CreateWindow("Pacman",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    MainRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED);
}

void DrawMap(SDL_Renderer *renderer, Map One,pacman Pacman,Window LoadMap)
{
    SDL_Rect Wall = {0, 0, 0, 0};
    bool FullyRan = false;
    SDL_Texture* PacmanTextures = nullptr;
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

            case '9':
                switch (Pacman.Direction)
                {
                    case Pacman.FIRST_SOUTH:
                        PacmanTextures = Pacman.LoadSprites(renderer, Pacman.SpriteCord[3].first, Pacman.SpriteCord[0].second, 4, 2);
                        break;
                    case Pacman.SECOND_SOUTH:
                        PacmanTextures = Pacman.LoadSprites(renderer, Pacman.SpriteCord[3].first, Pacman.SpriteCord[1].second, 4, 2);
                        break;
                    case Pacman.FIRST_EAST:
                        PacmanTextures = Pacman.LoadSprites(renderer, Pacman.SpriteCord[1].first, Pacman.SpriteCord[0].second, 4, 2);
                        break;
                    case Pacman.SECOND_EAST:
                        PacmanTextures = Pacman.LoadSprites(renderer, Pacman.SpriteCord[1].first, Pacman.SpriteCord[1].second, 4, 2);
                        break;
                    case Pacman.FIRST_NORTH:
                        PacmanTextures = Pacman.LoadSprites(renderer, Pacman.SpriteCord[3].first, Pacman.SpriteCord[0].second, 4, 2);
                        break;
                    case Pacman.SECOND_NORTH:
                        PacmanTextures = Pacman.LoadSprites(renderer, Pacman.SpriteCord[3].first, Pacman.SpriteCord[1].second, 4, 2);
                        break;
                    case Pacman.FIRST_WEST:
                        PacmanTextures = Pacman.LoadSprites(renderer, Pacman.SpriteCord[0].first, Pacman.SpriteCord[0].second, 4, 2);
                        break;
                    case Pacman.SECOND_WEST:
                        PacmanTextures = Pacman.LoadSprites(renderer, Pacman.SpriteCord[0].first, Pacman.SpriteCord[1].second, 4, 2);
                        break;
                    default:
                        break;
                }
                if (PacmanTextures != nullptr){

                    SDL_RenderCopy(renderer, PacmanTextures, nullptr, &Wall);
                    SDL_DestroyTexture(PacmanTextures);
                }
                break;
            case 'o':
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                SDL_RenderDrawPoint(renderer, Wall.x + CELL_SIZE / 2, Wall.y + CELL_SIZE / 2);
                LoadMap.DrawCircle(renderer, Wall.x + CELL_SIZE / 2, Wall.y + CELL_SIZE / 2,CELL_SIZE/6);
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
    
}

void Update(pacman Pacman,Map map)
{
    SDL_Texture* PacmanTextures = nullptr;
    int pacmanY = Pacman.getPacmanPos(map).second;
    int pacmanX = Pacman.getPacmanPos(map).first;
    switch (Pacman.Direction)
    {
        case Pacman.FIRST_SOUTH:
            if (pacmanY > 0 && map[pacmanY + 1][pacmanX] != '#' && map[pacmanY + 1][pacmanX] != '='  && map[pacmanY + 1][pacmanX] != '0'  && map[pacmanY + 1][pacmanX] != '1' && map[pacmanY + 1][pacmanX] != '2' && map[pacmanY + 1][pacmanX] != '3'){
                pacmanY++;
                map[pacmanY][pacmanX] = '9';
            }
            break;
        case Pacman.SECOND_SOUTH:
            if (pacmanY > 0 && map[pacmanY + 1][pacmanX] != '#' && map[pacmanY + 1][pacmanX] != '='  && map[pacmanY + 1][pacmanX] != '0'  && map[pacmanY + 1][pacmanX] != '1' && map[pacmanY + 1][pacmanX] != '2' && map[pacmanY + 1][pacmanX] != '3'){
                pacmanY++;
                map[pacmanY][pacmanX] = '9';
            }
            break;
        case Pacman.FIRST_EAST:
            if (pacmanX > 0 && map[pacmanY][pacmanX - 1] != '#' && map[pacmanY][pacmanX - 1] != '=' &&map[pacmanY][pacmanX - 1] != '0' && map[pacmanY][pacmanX - 1] != '1' && map[pacmanY][pacmanX - 1] != '2' && map[pacmanY][pacmanX - 1] != '3')
            {
                --pacmanX;
                map[pacmanY][pacmanX] = '9';
                
            }
            break;
        case Pacman.SECOND_EAST:
            if (pacmanX > 0 && map[pacmanY][pacmanX - 1] != '#' && map[pacmanY][pacmanX - 1] != '=' &&map[pacmanY][pacmanX - 1] != '0' && map[pacmanY][pacmanX - 1] != '1' && map[pacmanY][pacmanX - 1] != '2' && map[pacmanY][pacmanX - 1] != '3')
            {
                --pacmanX;
                map[pacmanY][pacmanX] = '9';   
            }
            break;
        case Pacman.FIRST_NORTH:
            if (pacmanY > 0 && map[pacmanY - 1][pacmanX] != '#' && map[pacmanY - 1][pacmanX] != '='  && map[pacmanY - 1][pacmanX] != '0'  && map[pacmanY - 1][pacmanX] != '1' && map[pacmanY - 1][pacmanX] != '2' && map[pacmanY - 1][pacmanX] != '3')
            {
                --pacmanY;
                map[pacmanY][pacmanX] = '9';
            }
            break;
        case Pacman.SECOND_NORTH:
            if (pacmanY > 0 && map[pacmanY - 1][pacmanX] != '#' && map[pacmanY - 1][pacmanX] != '='  && map[pacmanY - 1][pacmanX] != '0'  && map[pacmanY - 1][pacmanX] != '1' && map[pacmanY - 1][pacmanX] != '2' && map[pacmanY - 1][pacmanX] != '3')
            {
                --pacmanY;
                map[pacmanY][pacmanX] = '9';
            }
            break;
        case Pacman.FIRST_WEST:
            if (pacmanX < map[pacmanY].size() - 1 && map[pacmanY][pacmanX + 1] != '#' && map[pacmanY][pacmanX + 1] != '=' && map[pacmanY][pacmanX + 1] != '0' && map[pacmanY][pacmanX + 1] != '1' && map[pacmanY][pacmanX + 1] != '2' && map[pacmanY][pacmanX + 1] != '3')
            {
                ++pacmanX;
                map[pacmanY][pacmanX] = '9';
            }
            break;
        case Pacman.SECOND_WEST:
            if (pacmanX < map[pacmanY].size() - 1 && map[pacmanY][pacmanX + 1] != '#' && map[pacmanY][pacmanX + 1] != '=' && map[pacmanY][pacmanX + 1] != '0' && map[pacmanY][pacmanX + 1] != '1' && map[pacmanY][pacmanX + 1] != '2' && map[pacmanY][pacmanX + 1] != '3')
            {
                ++pacmanX;
                map[pacmanY][pacmanX] = '9';
            }
            break;
        default:
            break;
    }
                
}


/*case '0':
                
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
                break;*/