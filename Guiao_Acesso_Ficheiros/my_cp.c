#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){
    int fd_origem = open(argv[1], O_RDONLY);
    int fd_destino = open(argv[2], O_CREAT | O_WRONLY, 0664);

    char *buffer = malloc(sizeof(char) * 1024);
    ssize_t byte_read;
    while ((byte_read = read(fd_origem, buffer, 1024)) > 0) {
            write(fd_destino, buffer, byte_read);
    }

    close(fd_origem);
    close(fd_destino);
    free(buffer);
    return 0;
}