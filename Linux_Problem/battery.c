#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<fcntl.h>
#include<pthread.h>
#include <time.h>
int status = 0;
int battery_level = 100;
int low_battery = 0;
pthread_mutex_t lock;
int min = 1;
int max = 10;
int random_num;

void* decrement(){
printf("Hello world\n");
	while(1){
		random_num = (rand() % (max - min + 1)) + min;
		battery_level -= random_num;
		printf("Battery Level: %d\n",battery_level);
		sleep(1);
		
		if(battery_level < 20){
			pthread_mutex_lock(&lock);
			low_battery = 1;
			pthread_mutex_unlock(&lock);
			
			pid_t id = fork();
			
			if(id == 0){
				printf(" Low battery detected! Going to charging station...\n");
				
				char *argv[] = {"charger", NULL};
				execv("./runCharger", argv);
				
			}else{
				waitpid(0, &status, 0);
				printf("Charging completed!\n");
				battery_level = 100;
				low_battery = 0;
			}
		}
	}
	return NULL;
}

int main(void){
	printf("jf;sg\n");

	pthread_mutex_init(&lock, NULL);
	pthread_t battery_thread;
	pthread_create(&battery_thread, NULL, decrement, NULL);
	pthread_join(battery_thread,NULL);
	
	return 0;

}













