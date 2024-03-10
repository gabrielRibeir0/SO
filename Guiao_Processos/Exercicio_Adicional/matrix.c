#include "matrix.h"

void createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int fd = open("matrix", O_CREAT | O_WRONLY, 0664);
    int n;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            n = rand() % MAX_RAND;
            lseek(fd, 0, SEEK_END);
            write(fd, &n, sizeof(int));
        }
    }
    close(fd);
    printf("Done.\n");
}

void printMatrix() {
    int fd = open("matrix", O_RDONLY, 0664);
    int n;
    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            read(fd, &n, sizeof(int));
            printf("%7d ", n);
        }
        printf("\n");
    }

    close(fd);
}

// ex.5
int valueExists(int value) {
    pid_t child;
    int status;
    for(int i = 0; i < ROWS; i++){
        child = fork();
        if(child == 0){
            int n;
            int fd = open("matrix", O_RDONLY, 0664);
            lseek(fd, sizeof(int) * COLUMNS * i, SEEK_CUR);
            for(int j = 0; j < COLUMNS; j++){
                read(fd, &n, sizeof(int));
                if(n == value){
                    close(fd);
                    _exit(i);
                }
            }
            close(fd);
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
void linesWithValue(int value) {
    pid_t child;
    pid_t pidsChild[ROWS];
    int status;
    for(int i = 0; i < ROWS; i++){
        child = fork();
        if(child == 0){
            int n;
            int fd = open("matrix", O_RDONLY, 0664);
            lseek(fd, sizeof(int) * COLUMNS * i, SEEK_CUR);
            for(int j = 0; j < COLUMNS; j++){
                read(fd, &n, sizeof(int));
                if(n == value){
                    close(fd);
                    _exit(i);
                }
            }
            close(fd);
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