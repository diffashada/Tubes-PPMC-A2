#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW 10
#define MAX_COL 10

char maze[MAX_ROW][MAX_COL];
int visited[MAX_ROW][MAX_COL];
int path_count = 0;
int shortest_path_len = MAX_ROW * MAX_COL;
int longest_path_len = 0;
char shortest_path[MAX_ROW * MAX_COL];
char longest_path[MAX_ROW * MAX_COL];

void findPaths(int x, int y, int dest_x, int dest_y, int len, char path[MAX_ROW * MAX_COL], int path_len) {
    if (x < 0 || x >= MAX_ROW || y < 0 || y >= MAX_COL || maze[x][y] == '#' || visited[x][y])
        return;

    if (x == dest_x && y == dest_y) {
        path[path_len] = '\0';
        printf("Path %d: %s\n", ++path_count, path);
        if (len > longest_path_len) {
            longest_path_len = len;
            strcpy(longest_path, path);
        }
        if (len < shortest_path_len) {
            shortest_path_len = len;
            strcpy(shortest_path, path);
        }
        return;
    }

    visited[x][y] = 1;

    path[path_len] = '(';
    path[path_len + 1] = x + '0';
    path[path_len + 2] = ',';
    path[path_len + 3] = y + '0';
    path[path_len + 4] = ')';
    path[path_len + 5] = '-';
    path[path_len + 6] = '>';

    findPaths(x + 1, y, dest_x, dest_y, len + 1, path, path_len + 7);
    findPaths(x - 1, y, dest_x, dest_y, len + 1, path, path_len + 7);
    findPaths(x, y + 1, dest_x, dest_y, len + 1, path, path_len + 7);
    findPaths(x, y - 1, dest_x, dest_y, len + 1, path, path_len + 7);

    visited[x][y] = 0;
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

    printf("All possible paths from start to end:\n");

    int start_x, start_y, end_x, end_y;

    for (int i = 0; i < MAX_ROW; i++) {
        char line[MAX_COL + 2];  // +2 for '\n' and '\0'
        if (fgets(line, MAX_COL + 2, fp) == NULL) {
            printf("Error reading maze from file.");
            return 1;
        }
        for (int j = 0; j < MAX_COL; j++) {
            maze[i][j] = line[j];
            visited[i][j] = 0;
            if (maze[i][j] == 'S') {
                start_x = i;
                start_y = j;
            }
            if (maze[i][j] == 'E') {
                end_x = i;
                end_y = j;
            }
        }
    }

    char path[MAX_ROW * MAX_COL];
    findPaths(start_x, start_y, end_x, end_y, 0, path, 0);

    printf("\nTotal number of paths: %d\n", path_count);

    printf("\nLongest path from start to end:\n");
    printf("Path: %s\n", longest_path);

    printf("\nShortest path from start to end:\n");
    printf("Path: %s\n", shortest_path);

    fclose(fp);

    return 0;
}
