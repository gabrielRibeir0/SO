#include <stdio.h>
#include "mysystem.h"

void controller(int N, char** commands) {
	pid_t child;
    pid_t pids[N];
    int status;

    for(int i = 0; i < N; i++){
        child = fork();
        if(child == 0){
            int ret = 1, counter = 0;
            while(ret > 0) {
                ret = mysystem(commands[i]);
                counter++;
            }
            _exit(counter);
        }
        else{
            pids[i] = child;
        }
    }

    for(int i = 0; i < N; i++){
        waitpid(pids[i], &status, 0);
        if(WIFEXITED(status)){
            printf("Comando %s executado %d vezes\n", commands[i], WEXITSTATUS(status));
        }
        else{
            printf("Erro ao executar o comando %s\n", commands[i]);
        }
    }
}

int main(int argc, char* argv[]) {

    char *commands[argc-1];
    int N = 0;
	for(int i=1; i < argc; i++){
		commands[N] = strdup(argv[i]);
		printf("command[%d] = %s\n", N, commands[N]);
        N++;
	}

    controller(N, commands);

	return 0;
}