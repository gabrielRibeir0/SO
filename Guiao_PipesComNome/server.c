#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "vector.h"

//FIFO criado pelo servidor
//Cliente pode receber um sigpipe (concorrência!)

int main (int argc, char * argv[]){
	init_vector();
	print_vector();

    int fd = mkfifo("FIFO_MATRIX", 0666);
    if(fd == -1){
        perror("Erro ao criar o FIFO");
        return -1;
    }

    fd = open("FIFO_MATRIX", O_RDWR);
    if(fd == -1){
        perror("Erro na abertura do FIFO");
        return -1;
    }

    int value, count;
    ssize_t read_bytes;
    while ((read_bytes = read(fd, &value, sizeof(int)))> 0){
        count = count_needle(value);
        write(fd, &count, sizeof(int));
    }
	
	return 0;
}
