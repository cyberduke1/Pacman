#include "pacman.h"


pacman::pacman() {
    dir = RIGHT;
    queuedDir = RIGHT; // Initialize queued direction to the same as the current direction
    PacmanRect = {0, 0, CELL_SIZE, CELL_SIZE};
}

std::pair<int, int> pacman::GetPacmanPos() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (stageOneBoard[i][j] == '9') {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Return an invalid position if not found
}

bool pacman::CheckWall(Direction checkDir) {
    std::pair<int, int> pos = GetPacmanPos();
    int pacmanY = pos.first;
    int pacmanX = pos.second;

    switch (checkDir) {
    case DOWN:
        if (pacmanY < HEIGHT - 1 && stageOneBoard[pacmanY + 1][pacmanX] != '#' && stageOneBoard[pacmanY + 1][pacmanX] != '=') {
            return true;
        }
        break;
    case RIGHT:
        if (pacmanX < WIDTH - 1 && stageOneBoard[pacmanY][pacmanX + 1] != '#') {
            return true;
        }
        // Handle teleportation from right edge to left edge
        if (pacmanX == WIDTH - 1) {
            return true;
        }
        break;
    case UP:
        if (pacmanY > 0 && stageOneBoard[pacmanY - 1][pacmanX] != '#') {
            return true;
        }
        break;
    case LEFT:
        if (pacmanX > 0 && stageOneBoard[pacmanY][pacmanX - 1] != '#') {
            return true;
        }
        // Handle teleportation from left edge to right edge
        if (pacmanX == 0) {
            return true;
        }
        break;
    default:
        break;
    }
    return false;
}

void pacman::move() {
    std::pair<int, int> pos = GetPacmanPos();
    int x = pos.second;
    int y = pos.first;

    if (x == -1 || y == -1) return; // Ensure Pacman position is valid

    // Apply the queued direction if possible
    if (CheckWall(queuedDir)) {
        dir = queuedDir;
    }

    switch (dir) {
    case UP:
        if (CheckWall(UP)) {
            stageOneBoard[y][x] = ' ';
            stageOneBoard[y - 1][x] = '9';
            PacmanRect.y -= CELL_SIZE;
        }
        break;
    case DOWN:
        if (CheckWall(DOWN)) {
            stageOneBoard[y][x] = ' ';
            stageOneBoard[y + 1][x] = '9';
            PacmanRect.y += CELL_SIZE;
        }
        break;
    case LEFT:
        if (CheckWall(LEFT)) {
            stageOneBoard[y][x] = ' ';
            if (x == 0) {
                stageOneBoard[y][WIDTH - 1] = '9'; // Teleport to the right edge
                PacmanRect.x = (WIDTH - 1) * CELL_SIZE;
            } else {
                stageOneBoard[y][x - 1] = '9';
                PacmanRect.x -= CELL_SIZE;
            }
        }
        break;
    case RIGHT:
        if (CheckWall(RIGHT)) {
            stageOneBoard[y][x] = ' ';
            if (x == WIDTH - 1) {
                stageOneBoard[y][0] = '9'; // Teleport to the left edge
                PacmanRect.x = 0;
            } else {
                stageOneBoard[y][x + 1] = '9';
                PacmanRect.x += CELL_SIZE;
            }
        }
        break;
    }

    // Ensure Pacman stays within bounds vertically
    if (PacmanRect.y < 0)
        PacmanRect.y = 0;
    if (PacmanRect.y > WINDOW_HEIGHT - PacmanRect.h)
        PacmanRect.y = WINDOW_HEIGHT - PacmanRect.h;
}

void pacman::setDirection(Direction newDir) {
    // Queue the new direction
    queuedDir = newDir;
}

void pacman::RenderPacman(SDL_Renderer *&Renderer) {
    SDL_SetRenderDrawColor(Renderer, 0, 220, 150, 255);
    SDL_RenderFillRect(Renderer, &PacmanRect);
}

pacman::~pacman() {}

Blinky::Blinky() {
    BlinkyPos = {0, 0}; // Initialize the Blinky position
}

std::pair<int, int> Blinky::GetBlinkyPos() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (stageOneBoard[i][j] == '1') {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Return an invalid position if not found
}

bool Blinky::CheckWall(int y, int x) {
    if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH && stageOneBoard[y][x] != '#') {
        return true;
    }
    return false;
}

std::vector<std::pair<int, int>> Blinky::BFS(std::pair<int, int> start, std::pair<int, int> goal) {
    std::queue<std::pair<int, int>> q;
    std::unordered_map<int, std::pair<int, int>> parent;
    q.push(start);
    parent[start.first * WIDTH + start.second] = {-1, -1};

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // UP, DOWN, LEFT, RIGHT

    while (!q.empty()) {
        std::pair<int, int> current = q.front();
        q.pop();

        if (current == goal) {
            std::vector<std::pair<int, int>> path;
            for (std::pair<int, int> at = goal; at != std::make_pair(-1, -1); at = parent[at.first * WIDTH + at.second]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (auto& direction : directions) {
            int newY = current.first + direction[0];
            int newX = current.second + direction[1];

            if (CheckWall(newY, newX) && parent.find(newY * WIDTH + newX) == parent.end()) {
                q.push({newY, newX});
                parent[newY * WIDTH + newX] = current;
            }
        }
    }

    return {}; // Return an empty path if no path is found
}

void Blinky::move(pacman& Pacman) {
    std::pair<int, int> BlinkyPos = GetBlinkyPos();
    std::pair<int, int> pacmanPos = Pacman.GetPacmanPos();

    if (BlinkyPos.first == -1 || BlinkyPos.second == -1 || pacmanPos.first == -1 || pacmanPos.second == -1) return;

    std::vector<std::pair<int, int>> path = BFS(BlinkyPos, pacmanPos);

    if (path.size() > 1) {

        int nextY = path[1].first;
        int nextX = path[1].second;

        if (stageOneBoard[nextY][nextX] != '3' && stageOneBoard[nextY][nextX] != '2') {
            stageOneBoard[BlinkyPos.first][BlinkyPos.second] = ' ';
            stageOneBoard[path[1].first][path[1].second] = '1';
        }
        
    }
}

Blinky::~Blinky() {}



Inky::Inky() {
    InkyPos = {0, 0}; // Initialize the Inky position
}

std::pair<int, int> Inky::GetInkyPos() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (stageOneBoard[i][j] == '2') {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Return an invalid position if not found
}

bool Inky::CheckWall(int y, int x) {
    if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH && stageOneBoard[y][x] != '#') {
        return true;
    }
    return false;
}

std::vector<std::pair<int, int>> Inky::BFS(std::pair<int, int> start, std::pair<int, int> goal) {
    std::queue<std::pair<int, int>> q;
    std::unordered_map<int, std::pair<int, int>> parent;
    q.push(start);
    parent[start.first * WIDTH + start.second] = {-1, -1};

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // UP, DOWN, LEFT, RIGHT

    while (!q.empty()) {
        std::pair<int, int> current = q.front();
        q.pop();

        if (current == goal) {
            std::vector<std::pair<int, int>> path;
            for (std::pair<int, int> at = goal; at != std::make_pair(-1, -1); at = parent[at.first * WIDTH + at.second]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (auto& direction : directions) {
            int newY = current.first + direction[0];
            int newX = current.second + direction[1];

            if (CheckWall(newY, newX) && parent.find(newY * WIDTH + newX) == parent.end()) {
                q.push({newY, newX});
                parent[newY * WIDTH + newX] = current;
            }
        }
    }

    return {}; // Return an empty path if no path is found
}

void Inky::move(pacman& Pacman) {
    std::pair<int, int> InkyPos = GetInkyPos();
    std::pair<int, int> pacmanPos = Pacman.GetPacmanPos();

    if (InkyPos.first == -1 || InkyPos.second == -1 || pacmanPos.first == -1 || pacmanPos.second == -1) return;

    std::vector<std::pair<int, int>> path = BFS(InkyPos, pacmanPos);

    if (path.size() > 1) {
        int nextY = path[1].first;
        int nextX = path[1].second;

        // Ensure Blinky and Inky do not occupy the same cell
        if (stageOneBoard[nextY][nextX] != '1') {
            stageOneBoard[InkyPos.first][InkyPos.second] = ' ';
            stageOneBoard[nextY][nextX] = '2';
        }
    }
}

Inky::~Inky() {}


Pinky::Pinky() {
    PinkyPos = {0, 0}; // Initialize the Pinky position
}

std::pair<int, int> Pinky::GetPinkyPos() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (stageOneBoard[i][j] == '3') {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Return an invalid position if not found
}

bool Pinky::CheckWall(int y, int x) {
    if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH && stageOneBoard[y][x] != '#') {
        return true;
    }
    return false;
}

std::vector<std::pair<int, int>> Pinky::BFS(std::pair<int, int> start, std::pair<int, int> goal) {
    std::queue<std::pair<int, int>> q;
    std::unordered_map<int, std::pair<int, int>> parent;
    q.push(start);
    parent[start.first * WIDTH + start.second] = {-1, -1};

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // UP, DOWN, LEFT, RIGHT

    while (!q.empty()) {
        std::pair<int, int> current = q.front();
        q.pop();

        if (current == goal) {
            std::vector<std::pair<int, int>> path;
            for (std::pair<int, int> at = goal; at != std::make_pair(-1, -1); at = parent[at.first * WIDTH + at.second]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (auto& direction : directions) {
            int newY = current.first + direction[0];
            int newX = current.second + direction[1];

            if (CheckWall(newY, newX) && parent.find(newY * WIDTH + newX) == parent.end()) {
                q.push({newY, newX});
                parent[newY * WIDTH + newX] = current;
            }
        }
    }

    return {}; // Return an empty path if no path is found
}

void Pinky::move(pacman& Pacman) {
    std::pair<int, int> PinkyPos = GetPinkyPos();
    std::pair<int, int> pacmanPos = Pacman.GetPacmanPos();

    if (PinkyPos.first == -1 || PinkyPos.second == -1 || pacmanPos.first == -1 || pacmanPos.second == -1) return;

    std::vector<std::pair<int, int>> path = BFS(PinkyPos, pacmanPos);

    if (path.size() > 1) {
        int nextY = path[1].first;
        int nextX = path[1].second;

        // Ensure Blinky and Pinky do not occupy the same cell
        if (stageOneBoard[nextY][nextX] != '1' && stageOneBoard[nextY][nextX] != '2') {
            stageOneBoard[PinkyPos.first][PinkyPos.second] = ' ';
            stageOneBoard[nextY][nextX] = '3';
        }
    }
}

Pinky::~Pinky() {}
