#include "headerfile/bfs.h"



bool node::isValid(vector<std::string> &maze, point &curr)
{
    if (curr.row < 0 || curr.row >= numRows || curr.col < 0 || curr.col >= numCols || maze[curr.row][curr.col] == 'x')
        return false;

    return true;
}

point node::getNextMove(point currentPos, std::vector<std::string>& map) {
        // Iterate through possible directions
        for (const auto& dir : directions) {
            int nextRow = currentPos.row + dir.row;
            int nextCol = currentPos.col + dir.col;

            // Check if the next position is valid and empty
            if (nextRow >= 0 && nextRow < map.size() &&
                nextCol >= 0 && nextCol < map[nextRow].size() &&
                map[nextRow][nextCol] != '#') {
                // Return the next valid position
                return point(nextRow, nextCol);
            }
        }
        // If no valid move found, return the current position
        return currentPos;
    }

void node::BFS(point &source, point &goal, vector<std::string> &maze)
{
    vector<vector<node>> nodes(numRows, vector<node>(numCols, node()));     // Will track our visits and update values as we go
    vector<pair<int, int>> neighbours = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}}; // Used to traverse cell neighbours

    queue<point> toVisit;
    toVisit.push(source);

    while (!toVisit.empty() && !nodes[goal.row][goal.col].visited)
    {
        point curr = toVisit.front();
        toVisit.pop();

        for (pair<int, int> &offset : neighbours)
        {
            point currCell = point(curr.row + offset.first, curr.col + offset.second);

            if (isValid(maze, currCell) && nodes[currCell.row][currCell.col].visited == false)
            {
                toVisit.push(currCell);
                nodes[currCell.row][currCell.col].parent = curr;
                nodes[currCell.row][currCell.col].visited = true;
            }
        }
    }

    if (toVisit.empty() && !nodes[goal.row][goal.col].visited)
        return;
    else
    {
        point curr = nodes[goal.row][goal.col].parent;

        while (curr != source)
        {
            maze[curr.row][curr.col] = '.';
            curr = nodes[curr.row][curr.col].parent;
        }

    }
}