#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t pid;
	pid = fork();
	
	if(pid == 0){
		printf("I'm the child process\n");
	}
	else if (pid > 0){
		printf("I'm the parent process\n");
		sleep(2);
	}
	else{
		printf("wait for parent\n");
	}
	return 0;
}

