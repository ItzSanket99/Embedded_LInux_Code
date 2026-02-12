#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<stdlib.h>
#include<signal.h>
#include<pthread.h>

void * childIncrement(){
	for(int i = 0; i < 5; i++){
		printf("thread: i = %d\n",i);
		sleep(1);
	}
	return NULL;
	
}

void * childDecrement(){
	for(int i = 5; i >= 0; i--){
		printf("thread: i = %d\n",i);
		sleep(1);
	}
	return NULL;
	
}


void * parentIncrement(){
	for(int i = 5; i < 10; i++){
		printf("thread: i = %d\n",i);
		sleep(1);
	}
	return NULL;
	
}

void * parentDecrement(){
	for(int i = 10; i >= 5; i--){
		printf("thread: i = %d\n",i);
		sleep(1);
	}
	return NULL;
	
}

int main(){
	
	
	pid_t id = fork();
	

	if(id == 0){
		printf("child process\n");
		pthread_t thread_id1, thread_id2;
		pthread_create(&thread_id1, NULL, childIncrement, NULL);
		pthread_create(&thread_id2, NULL, childDecrement, NULL);
		
		pthread_join(thread_id1,NULL);
		pthread_join(thread_id2,NULL);
	
	}else{
		printf("parent process\n");
		pthread_t thread_id1, thread_id2;
		pthread_create(&thread_id1, NULL, parentIncrement, NULL);
		pthread_create(&thread_id2, NULL, parentDecrement, NULL);
		
		pthread_join(thread_id1,NULL);
		pthread_join(thread_id2,NULL);
	}

	
	return 0;
}

