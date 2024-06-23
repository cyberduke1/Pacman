#include "Window.cpp"


int main(int argc, char** argv) {
    auto start = std::chrono::high_resolution_clock::now();
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer* Renderer = nullptr;
    SDL_Window* Window = nullptr;
    pacman Pacman;
    Blinky blinky;
    Inky inky;
    Pinky pinky;
    Map Boards;

    window ScreenWindow(Renderer, Window);
    ScreenWindow.Screen(Renderer, Boards, blinky, inky,pinky, Pacman);

    ScreenWindow.close(Renderer, Window);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    // Print the duration in seconds
    std::cout << "Execution time: " << duration.count() << " seconds." << std::endl;
    return 0;
}