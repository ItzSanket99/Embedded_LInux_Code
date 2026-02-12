#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<fcntl.h>

int minimal_mode = 0;

void handler(int sig){
	
	minimal_mode = 1;	
}

int main(void){
	
	pid_t pid = getpid();

	printf("Worker PID : %d\n", pid);
	signal(SIGUSR1, handler);
	
	int fd = open("app.log", O_RDWR);
	//fseek(fd, 0, SEEK_END);
	if(fd == -1){
		printf("open() failed with error %d\n", errno);
		perror("ERROR");
	}else{
		printf("File discriptor of opneded file is %d\n", fd);
	}
	
	char *msg1 = "detailed log entry…\n";
	char *msg2 = "minimal log entry\n";
	while(1){
	
		if(minimal_mode == 0){
			ssize_t count = (ssize_t)strlen(msg1);
			ssize_t writtenBytes = write(fd, msg1, count);
		}else{
			ssize_t count = (ssize_t)strlen(msg2);
			ssize_t writtenBytes = write(fd, msg2, count);
		}
		
		sleep(1);
	
	}
	
    	
}
