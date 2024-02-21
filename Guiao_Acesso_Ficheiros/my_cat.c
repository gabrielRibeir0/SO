#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    char *buffer = malloc(sizeof(char) * 1024);

    ssize_t byted_read;
    while((byted_read = read(0, buffer, 1024)) > 0) {
        ssize_t bytes_written = write(1, buffer, byted_read);
    }

    free(buffer);
    return 0;
}