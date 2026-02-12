
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<errno.h>
#include<signal.h>
#include<stdlib.h>

int main(int argc, char* argv[]){

	int pid = atoi(argv[1]);
	long size = atoi(argv[2]);
	
	struct stat file_stat;
	
		
		
		
		
		while(1)
		{
		if(stat("app.log",&file_stat) == 0){
		long currSize = file_stat.st_size;
			printf("currSize: %ld\n",currSize);
			if(currSize > size){
			
			printf("app.log is out of memory");
			kill(pid, SIGUSR1);
			}
		}
			sleep(2);
	
	
	}
}
