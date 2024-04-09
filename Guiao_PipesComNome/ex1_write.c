#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv){
    int fd = open("FIFO", O_WRONLY);
    if(fd == -1){
        perror("Erro na abertura do FIFO");
        return -1;
    }

    char buffer[1024];
    ssize_t read_bytes;
    while((read_bytes = read(0, &buffer, 1024)) > 0){
        write(fd, &buffer, read_bytes);
    }

    close(fd);

    return 0;
}