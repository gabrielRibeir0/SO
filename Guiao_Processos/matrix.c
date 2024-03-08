#include "matrix.h"


int **createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// ex.5
int valueExists(int **matrix, int value) {
    pid_t child;
    int status;
    for(int i = 0; i < ROWS; i++){
        child = fork();
        if(child == 0){
            for(int j = 0; j < COLUMNS; j++){
                if(matrix[i][j] == value){
                    _exit(i);
                }
            }
            _exit(-1);
        }
    }

    for(int i = 0; i < ROWS; i++){
        pid_t terminated_pid = wait(&status);
        if(WIFEXITED(status)){
            if(WEXITSTATUS(status) != 255){
                printf("O filho %d encontrou o valor %d na linha %d\n", terminated_pid, value, WEXITSTATUS(status));
            }
            else{
                printf("O filho %d não encontrou o valor %d\n", terminated_pid, value);
            }
        }
    }

    return 0;
}

// ex.6
void linesWithValue(int **matrix, int value) {
    pid_t child;
    pid_t pidsChild[ROWS];
    int status;
    for(int i = 0; i < ROWS; i++){
        child = fork();
        if(child == 0){
            for(int j = 0; j < COLUMNS; j++){
                if(matrix[i][j] == value){
                    _exit(i);
                }
            }
            _exit(-1);
        }
        else {
            pidsChild[i] = child;
        }
    }

    printf("\nPor ordem:\n");
    for(int i = 0; i < ROWS; i++){
        pid_t terminated_pid = waitpid(pidsChild[i], &status, 0);
        if(WIFEXITED(status)){
            if(WEXITSTATUS(status) != 255){
                printf("O filho %d encontrou o valor %d na linha %d\n", terminated_pid, value, WEXITSTATUS(status));
            }
            else{
                printf("O filho %d não encontrou o valor %d\n", terminated_pid, value);
            }
        }
    }
}