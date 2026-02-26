#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(){
	
	int n;
	// 0 - led_off
	// 1 - led_on
	// 2 - status
	
	int fd = open("tmp/cmdfifo", O_WRONLY);
	if(fd == -1){
		printf("failed to open fifo\n");
		return 1;
	}
	
	while(1){
		scanf("%d",&n);
		
		if(write(fd, &n, sizeof(int)) == -1){
			printf("failed to write fifo\n");
			return 2;
		}
		printf("Wrote %d\n", n);
		sleep(1);
	}
	
	
	return 0;
}
