#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"

int main (int argc, char * argv[]){

	if (argc < 2) {
		printf("Missing argument.\n");
		_exit(1);
	}

    int fd = open("FIFO_MATRIX", O_RDWR);
    if(fd == -1){
        perror("Erro na abertura do FIFO");
        return -1;
    }

    int count;
    int value = atoi(argv[1]);
    write(fd, &value, sizeof(int));

    ssize_t read_bytes;
    while ((read_bytes = read(fd, &count, sizeof(int)))> 0){
        printf("O valor %d foi encontrado %d vezes.\n", value, count);
    }
    unlink("FIFO_MATRIX");
	
	return 0;
}

