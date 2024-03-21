#include "mysystem.h"


// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem(const char* command) {

	int fork_ret, exec_ret, status;
	int res = -1;

	//estamos a assumir um nr maximo de argumentos, isso teria de ser melhorado com realloc
	char* exec_args[20];
	char* string;
	char* cmd;
	int i=0;

	cmd = strdup(command);
	while((string = strsep(&cmd, " ")) != NULL){
		exec_args[i] = string;
		i++;
	}
	exec_args[i] = NULL;

	fork_ret = fork();

	switch(fork_ret){
		case -1:
			res=-1;
			break;
		
		case 0: //processo filho
			exec_ret = execvp(exec_args[0], exec_args);
			perror("erro no exec");
			_exit(exec_ret);
			break;
		
		default:
			wait(&status);
			if(WIFEXITED(status)==255){
				res=-1;
			}
			else{
				res = WEXITSTATUS(status);
			}
			break;
	}
	

	return res;
}