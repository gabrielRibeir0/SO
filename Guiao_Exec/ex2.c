#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    pid_t child;
    int status;

    child = fork();
    if(child == 0) {
        execlp("ls", "ls", "-l", NULL);
        _exit(0);
    }
    else{
        pid_t terminated_pid = wait(&status);
        if(WIFEXITED(status)) {
            printf("O filho %d terminou com status %d\n", terminated_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}