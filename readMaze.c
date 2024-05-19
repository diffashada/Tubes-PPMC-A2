#include "solveMaze.h"

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
