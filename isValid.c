#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

char maze[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int nRows, nCols;

bool isValid(int x, int y) {
    return x >= 0 && x < nRows && y >= 0 && y < nCols && maze[x][y] != '#' && !visited[x][y];
}