#include "solveMaze.h"

bool isValid(int x, int y) {
    return y >= 0 && y < nRows && x >= 0 && x < nCols && maze[y][x] != '#' && !visited[y][x];
}