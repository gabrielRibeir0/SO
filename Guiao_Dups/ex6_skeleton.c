#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


#define MAX_COMMANDS 10

// parse do argumento e execvp
// devolve o resultado do exec
int exec_command(char* arg){

	//Estamos a assumir numero maximo de argumentos
	char *exec_args[10];

	char *string;	
	int exec_ret = 0;
	int i=0;

	char* command = strdup(arg);

	string=strtok(command," ");
	
	while(string!=NULL){
		exec_args[i]=string;
		string=strtok(NULL," ");
		i++;
	}

	exec_args[i]=NULL;
	
	exec_ret=execvp(exec_args[0],exec_args);
	
	return exec_ret;
}


int main(int argc, char** argv){
	
	int number_of_commands=4;
	
	char * commands[] = {
		"grep -v ^# /etc/passwd",
		"cut -f7 -d:",
		"uniq",
		"wc -l"
	};

    int pipes[number_of_commands-1][2];
    /*for(int i=0;i<number_of_commands-1;i++){
        pipe(pipes[i]);
    }*/

    pid_t pid;
    for(int i = 0; i < number_of_commands; i++){
        if(i != number_of_commands-1) {
            pipe(pipes[i]);
        }
        pid = fork();
        if(pid == 0){
            int in_original = dup(0);
            int out_original = dup(1);
            if(i == 0){
                dup2(pipes[i][1],1);
            }
            else if(i == number_of_commands-1){
                dup2(pipes[i-1][0],0);
            }
            else{
                dup2(pipes[i-1][0],0);
                dup2(pipes[i][1],1);
            }
            for(int j = 0; j < number_of_commands-1; j++){
                close(pipes[j][0]);
                //close(pipes[j][1]);
            }
            //close(pipes[i][0]);
            exec_command(commands[i]);
            //close(pipes[i][1]);
            dup2(in_original,0);
            dup2(out_original,1);
            _exit(0);
        }
    }

    for(int i = 0; i < number_of_commands-1; i++){
        wait(NULL);
    }

	return 0;
}

