#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * incremnetFunction(){
	for(int i = 0; i < 5; i++){
		printf("thread: i = %d\n",i);
		sleep(1);
	}
	return NULL;
	
}

void * decrementFunction(){
	for(int i = 5; i >= 0; i--){
		printf("thread: i = %d\n",i);
		sleep(1);
	}
	return NULL;
	
}
int main(void){

	pthread_t thread_id1, thread_id2, thread_id3;
	pthread_create(&thread_id1, NULL, incremnetFunction, NULL);
	pthread_create(&thread_id2, NULL, incremnetFunction, NULL);
	pthread_create(&thread_id3, NULL, decrementFunction, NULL);
	
	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
	pthread_join(thread_id3, NULL);
}
