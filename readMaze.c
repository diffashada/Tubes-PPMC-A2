#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

char maze[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int nRows, nCols;
int totalPaths = 0;  // Variabel untuk menyimpan jumlah total jalur yang valid

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
