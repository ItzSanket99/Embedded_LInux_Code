#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

sem_t semaphore;

void* routine(void* args){
    sem_wait(&semaphore);
    sleep(1);
    printf("hello from thread %d\n", *(int*)args);
    sem_post(&semaphore);
    free(args);
}

int main(){

    pthread_t th[4];
    sem_init(&semaphore, 0, 1);
    int i;
    for(i = 0; i < 4; i++){
        int* a = malloc(sizeof(int));
        *a = i;
        if(pthread_create(&th[i], 0, &routine, a) != 0){
            perror("failed to create thread\n");
        }
    }

    for(i = 0; i < 4; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("failed to join thread\n");
        }
    }


    sem_destroy(&semaphore);
    return 0;
}