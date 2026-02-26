#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define tempLimit 60

int main(){
	
	int tempValue;
	int fd[2];
	
	pid_t child1, child2;

	
	if(pipe(fd) == -1){
		printf("failed to open pipe\n");
		return 1;
	}
	
	child1 = fork(); // first child
	if(child1 == 0){
		close(fd[1]);
		int temp;
		while(1){
		
			if(read(fd[0], &temp, sizeof(temp)) == -1){
				printf("failed to read from pipe\n");
				return 3;
			}
			printf("child1: temp value: %d\n", temp);
			sleep(1);
			
		}
		close(fd[0]);	
		
	} else {
	
		child2 = fork(); // second child
		if(child2 == 0){
			close(fd[1]);
			int temp;
			while(1){
				if(read(fd[0], &temp, sizeof(temp)) == -1){
					printf("failed to read from pipe\n");
					return 4;
				}
				
				if(temp > tempLimit){
					printf("Warning %d\n", temp);
				}
				sleep(1);
				
			}
			close(fd[0]);	

		}else{
			// parent generate temp here 
			close(fd[0]);
			while(1){
				tempValue = rand() % 20 + 50;
				if(write(fd[1], &tempValue, sizeof(tempValue)) == -1){
					printf("failed to write into pipe\n");
					return 2;
				}
				sleep(2);
				
			}
			close(fd[1]);
		}
	}
	return 0;
}
	
	


