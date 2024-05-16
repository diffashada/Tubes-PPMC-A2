


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

char maze[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int nRows, nCols;
int shortestLength = 0, longestLength = 0;
int shortestPath[MAX_SIZE * MAX_SIZE][2], longestPath[MAX_SIZE * MAX_SIZE][2];

// Menentukan apakah sel adalah valid untuk dilewati
bool isValid(int x, int y) {
    return x >= 0 && x < nRows && y >= 0 && y < nCols && maze[x][y] != '#' && !visited[x][y];
}

// Backtracking untuk mencari semua jalur yang mungkin
void backtracking(int x, int y, int endX, int endY, int path[][2], int pathIndex) {
    visited[x][y] = true;
    path[pathIndex][0] = x;
    path[pathIndex][1] = y;
    pathIndex++;

    if (x == endX && y == endY) {
        // Update shortest path
        if (shortestLength == 0 || pathIndex < shortestLength) {
            shortestLength = pathIndex;
            memcpy(shortestPath, path, pathIndex * 2 * sizeof(int));
        }
        // Update longest path
        if (pathIndex > longestLength) {
            longestLength = pathIndex;
            memcpy(longestPath, path, pathIndex * 2 * sizeof(int));
        }
    } else {
        // Explore atas, bawah, kiri, kanan
        if (isValid(x + 1, y)) backtracking(x + 1, y, endX, endY, path, pathIndex);
        if (isValid(x - 1, y)) backtracking(x - 1, y, endX, endY, path, pathIndex);
        if (isValid(x, y + 1)) backtracking(x, y + 1, endX, endY, path, pathIndex);
        if (isValid(x, y - 1)) backtracking(x, y - 1, endX, endY, path, pathIndex);
    }

    visited[x][y] = false;
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

    // Mencari titik S dan E
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            if (maze[i][j] == 'S') {
                startX = i;
                startY = j;
            } else if (maze[i][j] == 'E') {
                endX = i;
                endY = j;
            }
        }
    }

    if (startX == -1 || startY == -1 || endX == -1 || endY == -1) {
        printf("Start or end not found in the maze.\n");
        return 1;
    }

    int path[MAX_SIZE * MAX_SIZE][2]; 

    backtracking(startX, startY, endX, endY, path, 0);

    printf("Shortest Path: ");
    for (int i = 0; i < shortestLength; i++) {
        printf("(%d,%d)", shortestPath[i][0] + 1, shortestPath[i][1] + 1);
        if (i < shortestLength - 1) printf(" -> ");
    }
    printf("\n");

    printf("Longest Path: ");
    for (int i = 0; i < longestLength; i++) {
        printf("(%d,%d)", longestPath[i][0] + 1, longestPath[i][1] + 1);
        if (i < longestLength - 1) printf(" -> ");
    }
    printf("\n");

    return 0;
}
