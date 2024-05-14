#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 10
#define MAX_COL 10

char maze[MAX_ROW][MAX_COL];

void findCoordinates(char target, int *x, int *y) {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            if (maze[i][j] == target) {
                *x = i;
                *y = j;
                return;
            }
        }
    }
    *x = -1;
    *y = -1;
}

int main() {
    FILE *fp;
    char filename[100];

    printf("Masukkan File Txt Struktur Maze: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("File tidak dapat dibuka.");
        return 1;
    }

    // Read the maze from file and print line by line
    printf("Maze structure:\n");
    char line[MAX_COL + 2]; // +2 for '\n' and '\0'
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
        // Copy the line to the maze array
        static int row = 0;
        strncpy(maze[row], line, MAX_COL);
        row++;
    }
    printf("\n");


    int start_x, start_y, end_x, end_y;

    // Find coordinates of 'S' (start)
    findCoordinates('S', &start_x, &start_y);

    // Find coordinates of 'E' (end)
    findCoordinates('E', &end_x, &end_y);

    if (start_x == -1 || start_y == -1) {
        printf("Start 'S' not found in the maze.\n");
    } else {
        printf("Coordinates of 'S' (start): (%d, %d)\n", start_x, start_y);
    }

    if (end_x == -1 || end_y == -1) {
        printf("End 'E' not found in the maze.\n");
    } else {
        printf("Coordinates of 'E' (end): (%d, %d)\n", end_x, end_y);
    }

    fclose(fp);

    return 0;
}
