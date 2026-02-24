#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	
	if(mkfifo("myfifo1", 0777) == -1){
	
		if(errno != EEXIST){
			printf("could not able to create fifo file\n");
			return 1;
		}
	}
	
	int fd = open("myfifo1", O_RDWR);
	int x = 78;
	
	if(write(fd, &x, sizeof(x)) == -1){
		printf("Error writing file\n");
		return 2;	
	}
	close(fd);

	return 0;
}
