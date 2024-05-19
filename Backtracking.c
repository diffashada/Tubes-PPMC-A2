#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 100

char maze[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int nRows, nCols;

// Menentukan apakah sel adalah valid untuk dilewati
bool isValid(int x, int y) {
    return x >= 0 && x < nRows && y >= 0 && y < nCols && maze[x][y] != '#' && !visited[x][y];
}

// Fungsi untuk mencetak path
void printPath(int path[][2], int pathLength, int **shortestPath, int **longestPath, int *shortestLength, int *longestLength) {
    printf("Path: ");
    for (int i = 0; i < pathLength; i++) {
        printf("(%d,%d)", path[i][0] + 1, path[i][1] + 1);
        if (i < pathLength - 1) printf(" -> ");
    }
    printf("\n");

    // Update shortest path
    if (*shortestLength == 0 || pathLength < *shortestLength) {
        *shortestLength = pathLength;
        memcpy(*shortestPath, path, pathLength * 2 * sizeof(int));
    }

    // Update longest path
    if (pathLength > *longestLength) {
        *longestLength = pathLength;
        memcpy(*longestPath, path, pathLength * 2 * sizeof(int));
    }
}

// Backtracking function to find all possible paths
void solveMazeBacktracking(int x, int y, int endX, int endY, int path[][2], int pathIndex, int **shortestPath, int **longestPath, int *shortestLength, int *longestLength) {
    visited[x][y] = true;
    path[pathIndex][0] = x;
    path[pathIndex][1] = y;
    pathIndex++;

    if (x == endX && y == endY) {
        printPath(path, pathIndex, shortestPath, longestPath, shortestLength, longestLength);
    } else {
        // Explore down, up, right, left
        if (isValid(x + 1, y)) solveMazeBacktracking(x + 1, y, endX, endY, path, pathIndex, shortestPath, longestPath, shortestLength, longestLength);
        if (isValid(x - 1, y)) solveMazeBacktracking(x - 1, y, endX, endY, path, pathIndex, shortestPath, longestPath, shortestLength, longestLength);
        if (isValid(x, y + 1)) solveMazeBacktracking(x, y + 1, endX, endY, path, pathIndex, shortestPath, longestPath, shortestLength, longestLength);
        if (isValid(x, y - 1)) solveMazeBacktracking(x, y - 1, endX, endY, path, pathIndex, shortestPath, longestPath, shortestLength, longestLength);
    }

    visited[x][y] = false;
    pathIndex--;
}

// Baca input file
void readMaze(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    nRows = 0;
    while (fgets(maze[nRows], MAX_SIZE, file)) {
        nCols = strlen(maze[nRows]) - 1; 
        maze[nRows][nCols] = '\0';  
        nRows++;
    }

    fclose(file);
}

int main() {
    char filename[100];
    printf("Enter the maze file name: ");
    scanf("%s", filename);
    readMaze(filename);

    int startX = -1, startY = -1, endX = -1, endY = -1;

     // Find start and end points
    for (int y = 0; y < nRows; y++) {
        for (int x = 0; x < nCols; x++) {
            if (maze[y][x] == 'S') {
                startX = x;
                startY = y;
            } else if (maze[y][x] == 'E') {
                endX = x;
                endY = y;
            }
        }
    }

    if (startX == -1 || startY == -1 || endX == -1 || endY == -1) {
        printf("Start or end not found in the maze.\n");
        return 1;
    }

    int path[MAX_SIZE * MAX_SIZE][2]; 
    int *shortestPath = malloc(MAX_SIZE * MAX_SIZE * 2 * sizeof(int));
    int *longestPath = malloc(MAX_SIZE * MAX_SIZE * 2 * sizeof(int));
    int shortestLength = 0, longestLength = 0;

    clock_t start_time = clock();
    solveMazeBacktracking(startX, startY, endX, endY, path, 0, &shortestPath, &longestPath, &shortestLength, &longestLength);
    clock_t end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Time spent: %f seconds\n", time_spent);

    printf("Shortest Path: ");
    for (int i = 0; i < shortestLength; i++) {
        printf("(%d,%d)", shortestPath[i*2] + 1, shortestPath[i*2 + 1] + 1);
        if (i < shortestLength - 1) printf(" -> ");
    }
    printf("\n");

    printf("Longest Path: ");
    for (int i = 0; i < longestLength; i++) {
        printf("(%d,%d)", longestPath[i*2] + 1, longestPath[i*2 + 1] + 1);
        if (i < longestLength - 1) printf(" -> ");
    }
    printf("\n");

    free(shortestPath);
    free(longestPath);

    return 0;
}
