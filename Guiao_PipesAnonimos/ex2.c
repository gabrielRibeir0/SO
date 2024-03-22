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
    if(pid == 0){ //processo filho: escreve
        //int valores[5] = {1, 2, 3,4 , 5};
        //int valor = 400;
        close(p[0]);
        for(int i = 0; i < 100000; i++) {
            ssize_t written_bytes = write(p[1], &i, sizeof(int));
            printf("Filho: escreve o valor %d (%d bytes)\n", i, written_bytes);
        }
        close(p[1]);
        _exit(0);
    }
    else{ //processo pai: recebe
        close(p[1]);
        int res;
        sleep(5);
        ssize_t read_bytes;
        while((read_bytes = read(p[0], &res, sizeof(int))) > 0) {
            printf("Pai: recebe o valor %d (%d bytes)\n", res, read_bytes);
        }
        close(p[0]);

        pid_t terminated_pid = wait(&status);
        if(WIFEXITED(status)){
            printf("Pai: o filho %d terminou com status %d\n", terminated_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}