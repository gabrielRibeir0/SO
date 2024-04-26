#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int pipe_fd[2];
    pipe(pipe_fd);

    pid_t pid = fork();
    if(pid == 0) {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], 0);
        close(pipe_fd[0]);
        execlp("wc", "wc", NULL);
        _exit(0);
    }
    else {
        close(pipe_fd[0]);
        ssize_t bytes_read;
        char buffer[1024];
        while ((bytes_read = read(0, &buffer, 1024)) > 0) {
            write(pipe_fd[1], &buffer, bytes_read);
        }
        close(pipe_fd[1]);
        wait(NULL);
    }

    return 0;
}