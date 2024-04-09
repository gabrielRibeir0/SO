#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    int p[2];
    int pipe_return = pipe(p);
    if(pipe_return == -1){
        perror("Erro na criação de pipes");
    }

    const char *filename = argv[2];
    const char *word = argv[3];
    pid_t child;
    int status;
    char *line;
    size_t size;
    FILE *fp = fopen(filename, "r");
    while(getline(&line, &size, fp) != -1){
        child = fork();
        if(child == 0){
            if(strstr(line, word) != NULL){

            }
        }
    }
}