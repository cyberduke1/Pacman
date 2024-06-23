#include "constants.h"
#pragma once

enum Direction { UP, DOWN, LEFT, RIGHT };

class pacman
{
public:
    pacman();
    ~pacman();
    std::pair<int, int> GetPacmanPos();
    bool CheckWall(Direction checkDir);
    void move();
    void setDirection(Direction newDir);
    void RenderPacman(SDL_Renderer *&Renderer);
    SDL_Rect PacmanRect;
    Direction dir;
    Direction queuedDir;
};



class Blinky {
public:
    Blinky();
    ~Blinky();

    void move(pacman& Pacman);
    std::pair<int, int> GetBlinkyPos();
private:
    std::pair<int, int> BlinkyPos;
    bool CheckWall(int y, int x);
    std::vector<std::pair<int, int>> BFS(std::pair<int, int> start, std::pair<int, int> goal);
};

class Inky {
public:
    Inky();
    ~Inky();

    void move(pacman& Pacman);
    std::pair<int, int> GetInkyPos();
private:
    std::pair<int, int> InkyPos;
    bool CheckWall(int y, int x);
    std::vector<std::pair<int, int>> BFS(std::pair<int, int> start, std::pair<int, int> goal);
};

class Pinky {
public:
    Pinky();
    ~Pinky();

    void move(pacman& Pacman);
    std::pair<int, int> GetPinkyPos();
private:
    std::pair<int, int> PinkyPos;
    bool CheckWall(int y, int x);
    std::vector<std::pair<int, int>> BFS(std::pair<int, int> start, std::pair<int, int> goal);
};



class BFS {
public:
    enum Direction { UP, DOWN, LEFT, RIGHT };
    static std::vector<int> find_path(std::pair<int, int> start, std::pair<int, int> goal, const std::list<std::pair<int, int>>& snake_segments) {
        // Sets and Queues for BFS from both directions
        std::unordered_set<std::pair<int, int>, hash_pair> visited_from_start, visited_from_goal;
        std::queue<std::pair<int, int>> queue_from_start, queue_from_goal;
        std::unordered_map<std::pair<int, int>, std::pair<int, int>, hash_pair> parent_from_start, parent_from_goal;

        queue_from_start.push(start);
        queue_from_goal.push(goal);
        visited_from_start.insert(start);
        visited_from_goal.insert(goal);
        parent_from_start[start] = start;
        parent_from_goal[goal] = goal;

        auto reconstruct_path = [](const std::unordered_map<std::pair<int, int>, std::pair<int, int>, hash_pair>& parents, std::pair<int, int> current) {
            std::vector<std::pair<int, int>> path;
            while (parents.at(current) != current) {
                path.push_back(current);
                current = parents.at(current);
            }
            path.push_back(current);
            std::reverse(path.begin(), path.end());
            return path;
        };

        // BFS loop
        while (!queue_from_start.empty() && !queue_from_goal.empty()) {
            // Process current nodes from start and goal
            std::pair<int, int> current_from_start = queue_from_start.front();
            std::pair<int, int> current_from_goal = queue_from_goal.front();
            queue_from_start.pop();
            queue_from_goal.pop();

            // Check for meeting point
            if (visited_from_goal.count(current_from_start)) {
                auto path_from_start = reconstruct_path(parent_from_start, current_from_start);
                auto path_from_goal = reconstruct_path(parent_from_goal, current_from_start);
                path_from_goal.erase(path_from_goal.begin());
                std::reverse(path_from_goal.begin(), path_from_goal.end());
                path_from_start.insert(path_from_start.end(), path_from_goal.begin(), path_from_goal.end());
                return directions_from_path(path_from_start);
            }

            if (visited_from_start.count(current_from_goal)) {
                auto path_from_start = reconstruct_path(parent_from_start, current_from_goal);
                auto path_from_goal = reconstruct_path(parent_from_goal, current_from_goal);
                path_from_goal.erase(path_from_goal.begin());
                std::reverse(path_from_goal.begin(), path_from_goal.end());
                path_from_start.insert(path_from_start.end(), path_from_goal.begin(), path_from_goal.end());
                return directions_from_path(path_from_start);
            }

            // Add neighbors
            add_neighbors(queue_from_start, visited_from_start, parent_from_start, current_from_start, snake_segments);
            add_neighbors(queue_from_goal, visited_from_goal, parent_from_goal, current_from_goal, snake_segments);
        }

        return std::vector<int>();  // No path found
    }

private:
    struct hash_pair {
        template <class T1, class T2>
        size_t operator()(const std::pair<T1, T2>& p) const {
            auto hash1 = std::hash<T1>{}(p.first);
            auto hash2 = std::hash<T2>{}(p.second);
            return hash1 ^ hash2;
        }
    };

    static void add_neighbors(std::queue<std::pair<int, int>>& queue, std::unordered_set<std::pair<int, int>, hash_pair>& visited, std::unordered_map<std::pair<int, int>, std::pair<int, int>, hash_pair>& parents, std::pair<int, int> current, const std::list<std::pair<int, int>>& snake_segments) {
        static const std::vector<std::pair<int, int>> neighbors = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        for (const auto& neighbor : neighbors) {
            int nx = current.first + neighbor.first;
            int ny = current.second + neighbor.second;

            if (nx >= 0 && ny >= 0 && nx < WIDTH && ny < WIDTH) {
                bool occupied = std::find(snake_segments.begin(), snake_segments.end(), std::make_pair(nx, ny)) != snake_segments.end();
                if (!occupied && !visited.count(std::make_pair(nx, ny))) {
                    queue.push({nx, ny});
                    visited.insert({nx, ny});
                    parents[{nx, ny}] = current;
                }
            }
        }
    }

    static std::vector<int> directions_from_path(const std::vector<std::pair<int, int>>& path) {
        std::vector<int> directions;
        for (size_t i = 1; i < path.size(); ++i) {
            std::pair<int, int> diff = {path[i].first - path[i - 1].first, path[i].second - path[i - 1].second};

            if (diff == std::make_pair(0, 1)) directions.push_back(DOWN);
            else if (diff == std::make_pair(0, -1)) directions.push_back(UP);
            else if (diff == std::make_pair(1, 0)) directions.push_back(RIGHT);
            else if (diff == std::make_pair(-1, 0)) directions.push_back(LEFT);
        }
        return directions;
    }
};