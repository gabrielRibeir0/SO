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

void lookupNumber(int** matrix, int value, int* vector){
    int p[2];
    int pipe_return = pipe(p);
    if(pipe_return == -1){
        perror("Erro na criação de pipes");
    }

    pid_t child;
    int status;
    for(int i = 0; i < ROWS; i++){
        child = fork();
        if(child == 0){
            Minfo info;
            info.ocur_nr = 0;
            info.line_nr = i;
            for(int j = 0; j < COLUMNS; j++){
                if(matrix[i][j] == value){
                    info.ocur_nr++;
                }
            }
            close(p[0]);
            ssize_t written_bytes = write(p[1], &info, sizeof(Minfo));
            close(p[1]);
            _exit(0);
        }
    }

    close(p[1]);
    Minfo info;
    ssize_t read_bytes;
    while((read_bytes = read(p[0], &info, sizeof(Minfo))) > 0) {
        vector[info.line_nr] = info.ocur_nr;
        //printf("Pai: o filho encontrou o valor %d vezes na linha %d\n", info.ocur_nr, info.line_nr);
    }
    close(p[0]);


    for(int i = 0; i < ROWS; i++){
        pid_t terminated_pid = wait(&status);
        if(WIFEXITED(status)){
            printf("Pai: o filho %d terminou com status %d\n", terminated_pid, WEXITSTATUS(status));
        }
    }
}