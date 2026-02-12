#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int sharedVar = 0;
pthread_mutex_t lock;

void * incremnetFunction(){
	while(1){
		pthread_mutex_lock(&lock);
		sharedVar += 5;
		pthread_mutex_unlock(&lock);
		printf("Increment : %d\n",sharedVar);
		sleep(1);
	}
	return NULL;
}

void * decrementFunction(){
	while(1){
		pthread_mutex_lock(&lock);
		sharedVar -= 10;
		pthread_mutex_unlock(&lock);
		printf("Decrement : %d\n",sharedVar);
		sleep(2);
	}
	return NULL;
	
}
int main(void){

	pthread_t thread_id1, thread_id2;
	pthread_mutex_init(&lock, NULL);
	pthread_create(&thread_id1, NULL, incremnetFunction, NULL);
	pthread_create(&thread_id2, NULL, decrementFunction, NULL);

	
	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
	
	pthread_mutex_destroy(&lock);

}
