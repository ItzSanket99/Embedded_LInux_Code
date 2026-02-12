#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<stdlib.h>
#include<signal.h>
void handle_signal(int sig){
	
	printf("parent recived signal: %d from child\n",sig);
}

int main(){
	
	
	pid_t id = fork();
	printf("After fork id %d\n",id);
	signal(SIGUSR1, handle_signal);

	if(id == 0){
	
		printf("its child process\n");
		printf("Pid of child process : %d\n",getpid());
		printf("PPid of child process : %d\n",getppid());
		sleep(2);
		kill(getppid(),	SIGUSR1);
		exit(0);
	}else{
		printf("its parent process\n");
		printf("Pid of parent process : %d\n",getpid());
		printf("PPid of parent process : %d\n",getppid());
		pause();
		printf("parent exit\n");
	}

	
	return 0;
}

