#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t parent = getppid();
    pid_t child = getpid();

    printf("ID processo pai: %d\nID processo filho: %d\n", parent, child);

    return 0;
}