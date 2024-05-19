#ifndef SOLVE_MAZE_H
#define SOLVE_MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MAX_SIZE 100

char maze[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int nRows, nCols;
int totalPaths = 0;  // Variabel untuk menyimpan jumlah total jalur yang valid

typedef struct {
    int x, y;
} Point;

void readMaze(const char *filename);
void DFS(int x, int y, int endX, int endY, int path[][2], int pathIndex, int **shortestPath, int **longestPath, int *shortestLength, int *longestLength);
void printPath(int path[][2], int pathLength, int **shortestPath, int **longestPath, int *shortestLength, int *longestLength);
bool isValid(int x, int y);

#endif // SOLVE_MAZE_H
