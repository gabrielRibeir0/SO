#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    int fd_in = open("/etc/passwd", O_RDONLY);
    int fd_out = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC , 0666);
    int fd_err = open("erros.txt", O_WRONLY | O_CREAT | O_TRUNC , 0666);

    int fd0 = dup(0);
    int fd1 = dup(1);
    int fd2 = dup(2);

    dup2(fd_in, 0);
    dup2(fd_out, 1);
    dup2(fd_err, 2);

    close(fd_in);
    close(fd_out);
    close(fd_err);

    execl("wc", "wc", "-l", NULL);

    int pid = fork();
    if(pid == 0){
        ssize_t bytes_read;
        char buffer[1024];
        while((bytes_read = read(0, &buffer, 1024)) > 0){
            write(1, &buffer, bytes_read);
            write(2, &buffer, bytes_read);
        }
    }

    dup2(fd0, 0);
    dup2(fd1, 1);
    dup2(fd2, 2);
    close(fd0);
    close(fd1);
    close(fd2);

    wait(NULL);
    write(1, "terminei\n", 9);

    return 0;
}