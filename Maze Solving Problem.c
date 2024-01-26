#include <stdio.h>
#include<stdbool.h>
#define MAX_ROWS 20
#define MAX_COLS 20

typedef struct {
    int row, col;
} Cell;

bool isValid(int row, int col, int numRows, int numCols, int maze[MAX_ROWS][MAX_COLS]) {
    return (row >= 0 && row < numRows && col >= 0 && col < numCols && maze[row][col] == 1);
}

void printPath(Cell path[], int length) {
    printf("Minimal Path: ");
    for (int i = 0; i < length; i++) {
        printf("(%d, %d) -> ", path[i].row, path[i].col);
    }
    printf("Cheese\n");
}

bool findMinimalPath(int maze[MAX_ROWS][MAX_COLS], int numRows, int numCols, Cell current, Cell end, Cell path[], int length) {
    if (current.row == end.row && current.col == end.col) {
        printPath(path, length);
        return true;
    }

    int directions[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

    for (int i = 0; i < 4; i++) {
        int newRow = current.row + directions[i][0];
        int newCol = current.col + directions[i][1];
        Cell nextCell = {newRow, newCol};

        if (isValid(newRow, newCol, numRows, numCols, maze)) {
            path[length] = nextCell;
            if (findMinimalPath(maze, numRows, numCols, nextCell, end, path, length + 1)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int numRows, numCols;
    int maze[MAX_ROWS][MAX_COLS];

    printf("Enter the number of rows and columns for the maze: ");
    scanf("%d %d", &numRows, &numCols);

    printf("Enter the maze (0 for wall, 1 for open path):\n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    printf("Initial maze:\n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }

    Cell start = {0, 0};
    Cell end = {numRows - 1, numCols - 1};
    Cell path[MAX_ROWS * MAX_COLS];
    path[0] = start;

    if (!findMinimalPath(maze, numRows, numCols, start, end, path, 1)) {
        printf("No minimal path found from Rat to Cheese.\n");
    }

    return 0;
}
