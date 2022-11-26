#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int i =0;
void phandler (int);
void chandler (int);

int main(){
	pid_t pid, p_pid;
	struct sigaction sat;
	
	pid = fork();
	
	if (pid == 0){
		sat.sa_handler = chandler;
		sigaction (SIGUSR1, &sat, NULL);
		p_pid = getppid();
		
		while(1){
			sleep(1);
			kill(p_pid, SIGUSR1);
			pause();
		}
	}
	else if(pid > 0){
		sat.sa_handler = phandler;
		sigaction(SIGUSR1, &sat, NULL);
		while(1){
			pause();
			sleep(1);
			kill(pid, SIGUSR1);
		}
	}
	else{
		perror("Error");
	}
	return 0;
}

void phandler(int signo){
	printf("Parent : %d time.\n", ++i);
}
void chandler(int signo){
	printf("Child : %d time.\n", ++i);
}

