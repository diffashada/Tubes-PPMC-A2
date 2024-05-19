#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

char maze[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int nRows, nCols;

void printPath(int path[][2], int pathLength, int **shortestPath, int **longestPath, int *shortestLength, int *longestLength) {
    printf("Path: ");
    for (int i = 0; i < pathLength; i++) {
        printf("(%d,%d)", path[i][0] + 1, path[i][1] + 1);  // Memperbaiki urutan x dan y
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