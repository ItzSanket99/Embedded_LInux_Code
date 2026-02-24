#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char* argv[]){

	int arr[5];
	
	int fd = open("sum", O_RDONLY);
	if(fd == -1){
		printf("failed to open file\n");
		return 1;
	}
	
	int i;
	for(i = 0; i < 5; i++){
		if(read(fd, &arr[i], sizeof(int)) == -1){
			printf("failed to read file\n");
			return 2;
		}
		printf("recived %d\n",arr[i]);
	}
	
	close(fd);
	
	return 0;
}
