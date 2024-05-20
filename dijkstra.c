#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100
#define INF INT_MAX
int nRows, nCols;
char maze[MAX][MAX];

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point point;
    int distance;
} Node;

int isValid(int row, int col, int numRows, int numCols) {
    return (row >= 0) && (row < numRows) && (col >= 0) && (col < numCols);
}

int isDestination(int row, int col, Point dest) {
    return row == dest.x && col == dest.y;
}

void printPath(Point parent[MAX][MAX], Point dest) {
    Point path[MAX * MAX];
    int pathLen = 0;
    for (Point at = dest; at.x != -1 && at.y != -1; at = parent[at.x][at.y]) {
        path[pathLen++] = at;
    }
    printf("\n");
    printf("Shortest Path: ");
    for (int i = pathLen - 1; i >= 0; i--) {
        if (i == 0) {
            printf("(%d,%d)", (path[i].x + 1), (path[i].y + 1));
        }
        else {
            printf("(%d,%d) -> ", (path[i].x + 1), (path[i].y + 1));
        }
    }
}

void dijkstra(char maze[MAX][MAX], int numRows, int numCols, Point src, Point dest) {
    int dist[MAX][MAX];
    int visited[MAX][MAX];
    Point parent[MAX][MAX];

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            dist[i][j] = INF;
            visited[i][j] = 0;
            parent[i][j] = (Point){-1, -1};
        }
    }

    dist[src.x][src.y] = 0;
    Node minHeap[MAX * MAX];
    int heapSize = 0;

    minHeap[heapSize++] = (Node){src, 0};

    int rowNum[] = {-1, 1, 0, 0};
    int colNum[] = {0, 0, -1, 1};

    while (heapSize > 0) {
        Node node = minHeap[0];
        minHeap[0] = minHeap[--heapSize];

        for (int i = 0; i < heapSize; i++) {
            if (minHeap[i].distance < minHeap[0].distance) {
                Node temp = minHeap[0];
                minHeap[0] = minHeap[i];
                minHeap[i] = temp;
            }
        }

        int row = node.point.x;
        int col = node.point.y;

        if (visited[row][col]) continue;
        visited[row][col] = 1;

        for (int i = 0; i < 4; i++) {
            int newRow = row + rowNum[i];
            int newCol = col + colNum[i];

            if (isValid(newRow, newCol, numRows, numCols) && (maze[newRow][newCol] == '.' || maze[newRow][newCol] == 'E') && !visited[newRow][newCol]) {
                int newDist = dist[row][col] + 1;

                if (newDist < dist[newRow][newCol]) {
                    dist[newRow][newCol] = newDist;
                    parent[newRow][newCol] = (Point){row, col};
                    minHeap[heapSize++] = (Node){{newRow, newCol}, newDist};
                }
            }
        }
    }

    if (dist[dest.x][dest.y] == INF) {
        printf("No shortest path found\n");
    }
    else {
        printPath(parent, dest);
    }
}

void dfs(char maze[MAX][MAX], int numRows, int numCols, Point src, Point dest, int visited[MAX][MAX], Point path[], int pathLen, int *maxPathLen, Point longestPath[]) {
    if (src.x == dest.x && src.y == dest.y) {
        if (pathLen > *maxPathLen) {
            *maxPathLen = pathLen;
            for (int i = 0; i < pathLen; i++) {
                longestPath[i] = path[i];
            }
        }
        return;
    }

    int rowNum[] = {-1, 1, 0, 0};
    int colNum[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int newRow = src.x + rowNum[i];
        int newCol = src.y + colNum[i];

        if (isValid(newRow, newCol, numRows, numCols) && (maze[newRow][newCol] == '.' || maze[newRow][newCol] == 'E') && !visited[newRow][newCol]) {
            visited[newRow][newCol] = 1;
            path[pathLen] = (Point){newRow, newCol};
            dfs(maze, numRows, numCols, (Point){newRow, newCol}, dest, visited, path, pathLen + 1, maxPathLen, longestPath);
            visited[newRow][newCol] = 0;
        }
    }
}

void findLongestPath(char maze[MAX][MAX], int numRows, int numCols, Point src, Point dest) {
    int visited[MAX][MAX] = {0};
    Point longestPath[MAX * MAX];
    Point path[MAX * MAX];
    int maxPathLen = 0;

    visited[src.x][src.y] = 1;
    path[0] = src;

    dfs(maze, numRows, numCols, src, dest, visited, path, 1, &maxPathLen, longestPath);

    if (maxPathLen == 0) {
        printf("No longest path found\n");
    }
    else {
        printf("\n");
        printf("\n");
        printf("Longest Path: ");
        for (int i = 0; i < maxPathLen; i++) {
            if (i + 1 == maxPathLen) {
                printf("(%d,%d)", (longestPath[i].x + 1), (longestPath[i].y + 1));
            }
            else {
                printf("(%d,%d) -> ", (longestPath[i].x + 1), (longestPath[i].y + 1));
            }
        }
        printf("\n");
    }
}

void countAllPaths(char maze[MAX][MAX], int numRows, int numCols, Point src, Point dest, int visited[MAX][MAX], int* pathCount, Point path[], int pathLen) {
    path[pathLen] = src;
    pathLen++;

    if (src.x == dest.x && src.y == dest.y) {
        (*pathCount)++;
        printf("Path-%d: ", *pathCount);
        for (int i = 0; i < pathLen; i++) {
            printf("(%d,%d)", (path[i].x + 1), (path[i].y + 1));
            if (i < pathLen - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
        return;
    }

    int rowNum[] = {-1, 1, 0, 0};
    int colNum[] = {0, 0, -1, 1};

    visited[src.x][src.y] = 1;

    for (int i = 0; i < 4; i++) {
        int newRow = src.x + rowNum[i];
        int newCol = src.y + colNum[i];

        if (isValid(newRow, newCol, numRows, numCols) && (maze[newRow][newCol] == '.' || maze[newRow][newCol] == 'E') && !visited[newRow][newCol]) {
            countAllPaths(maze, numRows, numCols, (Point){newRow, newCol}, dest, visited, pathCount, path, pathLen);
        }
    }

    visited[src.x][src.y] = 0;
}

// Baca input file
void readMaze(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    nRows = 0;
    while (fgets(maze[nRows], MAX, file)) {
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

    Point src, dest;

    // Mencari titik S dan E
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            if (maze[i][j] == 'S') {
                src = (Point){i, j};
            }
            else if (maze[i][j] == 'E') {
                dest = (Point){i, j};
            }
        }
    }

    int visited[MAX][MAX] = {0};
    Point path[MAX * MAX];
    int pathCount = 0;
    countAllPaths(maze, nRows, nCols, src, dest, visited, &pathCount, path,0);

    dijkstra(maze, nRows, nCols, src, dest);

    findLongestPath(maze, nRows, nCols, src, dest);

    printf("\nTotal number of possible paths: %d\n", pathCount);

    return 0;
}