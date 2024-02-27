#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t parent, child;

    if((child = fork()) == 0){
        printf("ID processo filho: %d\n", child);
        _exit(0);
    }
    else{
        parent = getpid();
        printf("ID processo pai: %d\nID processo filho (pai imprime): %d\n", parent, child);
    }

    return 0;
}