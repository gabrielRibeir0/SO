#include "matrix.h"

int main(int argc, char *argv[]) {

    // generate random matrix
    createMatrix();

    // print matrix
    printMatrix();

    if(argc > 1) {
        int value = atoi(argv[1]);
        valueExists(value);
        linesWithValue(value);
    }

    return 0;
}