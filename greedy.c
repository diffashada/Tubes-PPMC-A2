#include "solveMaze.h"


void greedyAlg(int x, int y, int endX, int endY, int path[][2], int pathIndex, int **shortestPath, int **longestPath, int *shortestLength, int *longestLength) {
    if (!isValid(x, y) || visited[y][x]) return; // Return if position is not valid or already visited.

    visited[y][x] = true; // Mark current position as visited.
    path[pathIndex][0] = x;
    path[pathIndex][1] = y;
    pathIndex++;

    if (x == endX && y == endY) {
        printPath(path, pathIndex, shortestPath, longestPath, shortestLength, longestLength);
        totalPaths++; // Increment total path count on reaching the end.
    } else {
        int direction[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Directions: right, down, left, up
        int distance[4]; // Overall distances for each direction towards the end.

        // Calculate scores for each direction
        for (int i = 0; i < 4; i++) {
            int newX = x + direction[i][0];
            int newY = y + direction[i][1];
            distance[i] = abs(endX - newX) + abs(endY - newY); // Overall/Manhattan distance to end coords
        }

        // Sort directions based on overall distance using bubble sort
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3 - i; j++) {
                if (distance[j] > distance[j + 1]) {
                    // Swap distances
                    int temp = distance[j];
                    distance[j] = distance[j + 1];
                    distance[j + 1] = temp;
                    // Swap diections
                    int tempDir[2] = {direction[j][0], direction[j][1]};
                    direction[j][0] = direction[j + 1][0];
                    direction[j][1] = direction[j + 1][1];
                    direction[j + 1][0] = tempDir[0];
                    direction[j + 1][1] = tempDir[1];
                }
            }
        }

        // Explore based on sorted overall distance
        for (int i = 0; i < 4; i++) {
            int newX = x + direction[i][0];
            int newY = y + direction[i][1];
            greedyAlg(newX, newY, endX, endY, path, pathIndex, shortestPath, longestPath, shortestLength, longestLength);
        }
    }

    // Backtracking
    visited[y][x] = false;
    pathIndex--;
}