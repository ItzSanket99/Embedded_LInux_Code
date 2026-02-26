#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>


struct data {
  float cpu_usage;
  float ram_usage;
  char timestamp[32];
};

int main(){
	
	int cnt = 0;
	int fd = shm_open("/myshm",   O_CREAT | O_RDWR, 0666);
	
	if(fd == -1){
		printf("failed to open shm\n");
	}
	
	ftruncate(fd, sizeof(struct data));
	void *addr = mmap(NULL, sizeof(struct data), PROT_WRITE, MAP_SHARED, fd, 0);
	
	struct data *shared_data = (struct data*) addr;
	
	while(1){
		sleep(1);
		shared_data->cpu_usage = ((float)rand() / RAND_MAX) * 100.0f;
		shared_data->ram_usage = ((float)rand() / RAND_MAX) * 100.0f;
		sprintf(shared_data->timestamp, "%d", cnt++);
	}
	
	munmap(addr, 1024);
	return 0;
}
