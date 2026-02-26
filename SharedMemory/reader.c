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
	int fd = shm_open("/myshm",  O_RDONLY, 0666);
	
	if(fd == -1){
		printf("failed to open shm\n");
	}
	
	ftruncate(fd, sizeof(struct data));
	void *addr = mmap(NULL, sizeof(struct data), PROT_READ, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		perror("mmap failed");
	}
	struct data *shared_data = (struct data*) addr;
	
	while(1){
		sleep(1);
		printf("cpu_usage: %f\n", shared_data->cpu_usage);
		printf("ram_usage: %f\n", shared_data->ram_usage);
		printf("timestamp: %s\n", shared_data->timestamp);
	}
	return 0;
}
