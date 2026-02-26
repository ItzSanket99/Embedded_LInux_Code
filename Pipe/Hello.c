#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){

	char msg[10];
	int fd[2];
	// fd[0] - read end
 	// fd[1] write end
 	
 	if(pipe(fd) == -1){
 		printf("failed to open pipe\n");
 		return 1;
 	}
 	
 	int id = fork();
 	
 	if(id == -1){
		printf("failed to fork\n");
		return 2;
	}
	
	
 	if(id == 0){
 		//child process reads data
 		close(fd[1]);
 		if(read(fd[0], msg, sizeof(msg)) == -1){
			printf("failed to read data from pipe\n");
			return 3;
		}
		close(fd[0]); 		
		printf("child recived : %s\n", msg);
		
 	}else{
		//parent process write data
		close(fd[0]);
		if(write(fd[1], "hello" , 6) == -1){
			printf("failed to write the data to pipe\n");
			return 4;
		}
		close(fd[1]);
		printf("parent write to pipe\n");
			
	}	
	return 0;
}
