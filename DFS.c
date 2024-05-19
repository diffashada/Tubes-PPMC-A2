#include "solveMaze.h"
#include "isValid.c"
#include "printPath.c"
#include "readMaze.c"

// DFS untuk mencari semua jalur yang mungkin
void DFS(int x, int y, int endX, int endY, int path[][2], int pathIndex, int **shortestPath, int **longestPath, int *shortestLength, int *longestLength) {
    visited[y][x] = true;
    path[pathIndex][0] = x;
    path[pathIndex][1] = y;
    pathIndex++;

    if (x == endX && y == endY) {
        printPath(path, pathIndex, shortestPath, longestPath, shortestLength, longestLength);
    } else {
        // Explore all four directions
        if (isValid(x + 1, y)) DFS(x + 1, y, endX, endY, path, pathIndex, shortestPath, longestPath, shortestLength, longestLength);
        if (isValid(x - 1, y)) DFS(x - 1, y, endX, endY, path, pathIndex, shortestPath, longestPath, shortestLength, longestLength);
        if (isValid(x, y + 1)) DFS(x, y + 1, endX, endY, path, pathIndex, shortestPath, longestPath, shortestLength, longestLength);
        if (isValid(x, y - 1)) DFS(x, y - 1, endX, endY, path, pathIndex, shortestPath, longestPath, shortestLength, longestLength);
    }

    visited[y][x] = false;
    pathIndex--;
}