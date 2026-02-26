#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	
	int fd = shm_open("/myshm",  O_CREAT | O_RDWR, 0666);
	
	if(fd == -1){
		printf("failed to open shm\n");
	}
	
	ftruncate(fd, 1024);
	void *addr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	 
	int *data = (int*)addr;
	*data = 43;
	
	munmap(addr, 1024);
	return 0;
}
