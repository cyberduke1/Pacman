#include "pacman.cpp"
#include "Window.cpp"


SDL_Window *GameWindow = nullptr;
SDL_Renderer *MainRenderer = nullptr;
SDL_Event event;

void Init();
void DrawMap(SDL_Renderer *renderer, Map One,pacman Pacman,Window LoadMap);

int main(int argv,char *argc[]){

    Init();

    pacman Pacman(MainRenderer);
    Window LoadMaps;
    bool quit = false;
    int CurrentStage = 1;
    LoadMaps.Stages(CurrentStage);
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
                
                PacmanTextures = Pacman.LoadSprites(renderer, 0, 0, 4, 2);
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