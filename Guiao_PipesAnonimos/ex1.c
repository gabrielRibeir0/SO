#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    int p[2];
    int pipe_return = pipe(p);
    if(pipe_return == -1){
        perror("Erro na criação de pipes");
    }

    printf("Extremidade de escrita:%d\n Extremidade de leitura:%d\n", p[0], p[1]);
    pid_t pid = fork();
    int status;
    if(pid == 0){ //processo filho: consumidor
        close(p[1]);
        int res = 0;
        ssize_t read_bytes = read(p[0], &res, sizeof(int));
        printf("Filho: recebe o valor %d (%d bytes)\n", res, read_bytes);
        close(p[0]);
        _exit(0);
    }
    else{ //processo pai: produtor
        close(p[0]);
        int valor = 10;
        sleep(5);
        ssize_t written_bytes = write(p[1], &valor, sizeof(int));
        printf("Pai: escreve o valor %d (%d bytes)\n", valor, written_bytes);
        close(p[1]);

        pid_t terminated_pid = wait(&status);
        if(WIFEXITED(status)){
            printf("Pai: o filho %d terminou com status %d\n", terminated_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}