// Tugas Besar EL2208 Praktikum Pemecahan Masalah dengan C
// Kelompok : A2
// Problem : Maze Problem
// Deskripsi program : Program ini akan menemukan semua kemungkinan jalur dari Start ke End, serta menemukan jalur terpendek dan jalur terpanjang dari file input labirin yang berukuran minimal 7x7

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 100

char maze[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int nRows, nCols;

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
    DFS(startX, startY, endX, endY, path, 0, &shortestPath, &longestPath, &shortestLength, &longestLength);
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
