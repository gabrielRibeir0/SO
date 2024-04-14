#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include <time.h>

int main (int argc, char * argv[]){

	if (argc < 2) {
		printf("Missing argument.\n");
		_exit(1);
	}
    Msg message;
    message.needle = atoi(argv[1]);
    message.pid = getpid();
    message.occurrences = 0;

    char fifo_name[20];
    pid_t pid_child = getpid();
    sprintf(fifo_name, "%s%d", CLIENT, pid_child);

    if (mkfifo(fifo_name, 0666) == -1) {
        perror("Erro ao criar o FIFO do cliente");
        return -1;
    }

    int server_fifo = open(SERVER, O_WRONLY);
    if(server_fifo == -1){
        perror("Erro na abertura do FIFO do servidor");
        return -1;
    }

    printf("CLIENT: procura valor %d -> PID:%d\n", message.needle, message.pid);

    if(write(server_fifo, &message, sizeof(Msg)) == -1){
        perror("Erro no write para o FIFO do servidor");
        return -1;
    }
    close(server_fifo);

    int client_fifo = open(fifo_name, O_RDONLY);
    if (client_fifo == -1) {
        perror("Erro na abertura do FIFO do cliente");
        return -1;
    }

    ssize_t read_bytes;
    while ((read_bytes = read(client_fifo, &message, sizeof(Msg))) > 0) {
        printf("O valor %d foi encontrado %d vezes. -> PID:%d\n", message.needle, message.occurrences, message.pid);
    }

    close(client_fifo);
    unlink(CLIENT);
	return 0;
}

