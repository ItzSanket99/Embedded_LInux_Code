#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	
	int fd = shm_open("/myshm", O_RDONLY, 0666);
	
	if(fd == -1){
		printf("failed to open shm\n");
	}
	
	void *addr = mmap(NULL, 1024, PROT_READ, MAP_SHARED, fd, 0);
	
	printf("%d\n", *(int*)addr);
	return 0;
}
