#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 1024

int main(){
    int fd_in = open("/etc/passwd", O_RDONLY);
    if(fd_in == -1){
        perror("erro no open do fd_in");
        return -1;
    }

    int res = dup2(fd_in,0);
    if(res == -1){
        perror("erro no dup2 do stdin");
        return -1;
    }

    printf("Dup2 stdin = %d\n", res);
    close(fd_in);

    int fd_out = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC , 0666);
    if(fd_out == -1){
        perror("erro no open do fd_out");
        return -1;
    }

    int fd_out_original = dup(1);

    res = dup2(fd_out,1);
    if(res == -1){
        perror("erro no dup2 do stdout");
        return -1;
    }

    printf("Dup2 stdin = %d\n", res);
    close(fd_out);

    int fd_err = open("erros.txt", O_WRONLY | O_CREAT | O_TRUNC , 0666);
    if(fd_err == -1){
        perror("erro no open do fd_out");
        return -1;
    }

    res = dup2(fd_err,2);
    if(res == -1){
        perror("erro no dup2 do stderr");
        return -1;
    }

    printf("Dup2 stdin = %d\n", res);
    close(fd_err);

    char BUF[BUFF_SIZE];
    int bytes_read;
    while(bytes_read = read(0, &BUF, BUFF_SIZE)){
        write(1, &BUF, BUFF_SIZE);
    }

    dup2(fd_out_original, 1);

    printf("terminei");

    return 0;
}
