#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv){
    int fd = mkfifo("FIFO", 0666);
    if(fd == -1){
        perror("Erro ao criar o FIFO");
        return -1;
    }

    return 0;
}