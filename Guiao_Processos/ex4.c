#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t child;
    int status;

    for(int i = 0; i < 10; i++){
        child = fork();
        if(child == 0){
            printf("Filho: ID processo pai: %d ID processo filho: %d\n", getppid(), getpid());
            _exit(i);
        }
    }

    for(int i = 0; i < 10; i++){
        pid_t terminated_pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("O filho %d terminou: %d\n", WEXITSTATUS(status), terminated_pid);
        }
    }
}