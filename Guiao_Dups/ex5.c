#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    int pipe_fd[2];
    pipe(pipe_fd);

    pid_t pid = fork();
    if(pid == 0) {
        close(pipe_fd[1]);

        dup2(pipe_fd[0], 0);
        close(pipe_fd[0]);

        execlp("wc", "wc", "-l", NULL);

        _exit(0);
    }
    else {
        int fd1 = dup(1);
        dup2(pipe_fd[1], 1);

        close(pipe_fd[0]);
        execlp("ls", "ls", "/etc", NULL);
    }

    return 0;
}