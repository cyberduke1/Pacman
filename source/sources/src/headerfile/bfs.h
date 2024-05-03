#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int numRows, numCols;

class point
{
public:
    int row = -1, col = -1; // Members of this structure

    point() {} // Default constructor

    point(int row, int col) // Additional constructor
    {
        this->row = row;
        this->col = col;
    }

    bool operator!=(point &other) // Used for comparisions
    {
        return row != other.row || col != other.col;
    }

    bool operator==(point &other)
    {
        return row == other.row && col == other.col;
    }
};

class node // Combines the two properties (parent array and visited array) into one type
{
public:
    point parent;
    bool visited = false;
     std::vector<point> directions = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    point getNextMove(point currentPos, std::vector<std::string>& map);
    bool isValid(vector<std::string> &maze, point &curr);
    void BFS(point &source, point &goal, vector<std::string> &maze);

    node(){};
};