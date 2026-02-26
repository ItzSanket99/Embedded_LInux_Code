#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <mqueue.h>

int main(){
	
	mqd_t mqdes;	
	mqdes = mq_open("/myqueue", O_CREAT | O_WRONLY, 0666, NULL);
	 
	if(mqdes == -1){
		printf("failed to open queue\n");
		return 1;	
   	}
   	
   	char msg[10] = "hello"; 
   	if(mq_send(mqdes, (char *)msg, sizeof(msg), 0) == -1){
		printf("failed to send the message");
		return 2;
	}
    mq_close(mqdes);
	return 0;
}
