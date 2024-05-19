#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

char maze[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int nRows, nCols;
int totalPaths = 0;  // Variabel untuk menyimpan jumlah total jalur yang valid

bool isValid(int x, int y) {
    return y >= 0 && y < nRows && x >= 0 && x < nCols && maze[y][x] != '#' && !visited[y][x];
}