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

    if(mkfifo(SERVER, 0666) == -1){
        perror("Erro ao criar o FIFO do servidor");
        return -1;
    }

    int server_fifo_read = open(SERVER, O_RDONLY);
    if(server_fifo_read == -1){
        perror("Erro na abertura do FIFO do servidor (leitura)");
        return -1;
    }

    //para manter o servidor sempre a ler de vários clientes, abrimos aqui em escrita para ter sempre alguém com a escrita aberta (não vai deixar o ciclo while terminar)
    int server_fifo_write = open(SERVER, O_WRONLY);
    if(server_fifo_write == -1){
        perror("Erro na abertura do FIFO do servidor (escrita)");
        return -1;
    }

    Msg message;
    ssize_t read_bytes;
    while ((read_bytes = read(server_fifo_read, &message, sizeof(Msg)))> 0){
        //se o valor de procura enviado para o cliente for -1, ver como código para encerrar o servidor
        if(message.needle == -1){
            printf("A fechar o servidor...\n");
            close(server_fifo_write);
        }
        else{
            message.occurrences = count_needle(message.needle);
        }

        char fifo_name[20];
        sprintf(fifo_name, "%s%d", CLIENT, message.pid);
        int client_fifo = open(fifo_name, O_WRONLY);
        if(client_fifo == -1){
            perror("Erro na abertura do FIFO do cliente");
            continue;
        }

        write(client_fifo, &message, sizeof(Msg));
        close(client_fifo);
    }

    close(server_fifo_read);
    unlink(SERVER);

	return 0;
}
