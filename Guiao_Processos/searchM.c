#include "matrix.h"

int main(int argc, char *argv[]) {

    // generate random matrix
    int **matrix = createMatrix();

    // print matrix
    printMatrix(matrix);

    if(argc > 1) {
        int value = atoi(argv[1]);
        valueExists(matrix, value);
        linesWithValue(matrix, value);
    }

    // free matrix
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}