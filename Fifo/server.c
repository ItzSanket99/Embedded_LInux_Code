#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int main(){
	int led_state;
	char msg[20];
	
	int fd = open("tmp/cmdfifo", O_RDONLY);
	if(fd == -1){
		printf("failed to open file\n");
		return 1;
	}
	
	while(1){
		if(read(fd, &led_state, sizeof(int)) == -1){
			printf("failed to read file\n");
			return 2;
		}
		
		if(led_state == 0){
			strcpy(msg, "LED_ON");
			printf("%s\n", msg);
			
		}else if(led_state == 1){
			strcpy(msg, "LED_OFF");	
			printf("%s\n", msg);
			
		}else if(led_state == 2){
			printf("%s\n", msg);
			
		}
	}
	return 0;
}
