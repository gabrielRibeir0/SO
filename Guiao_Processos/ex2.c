#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t child;
    int status;

    if((child = fork()) == 0){
        printf("Filho: ID processo pai: %d ID processo filho: %d\n", getppid(), getpid());
        _exit(0);
    }
    else{
        pid_t terminated_pid = wait(&status);
        if(WIFEXITED(status)) {
            printf("Pai: ID processo pai: %d ID processo filho: %d Status:%d\n", getppid(), getpid(), WEXITSTATUS(status));
        }
    }

    return 0;
}