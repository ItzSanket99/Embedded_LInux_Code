#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <mqueue.h>

int main(){
	
	struct mq_attr attr;      
    attr.mq_msgsize = 10;     
	
	mqd_t mqdes;	
	mqdes = mq_open("/myqueue", O_CREAT | O_WRONLY, 0666, &attr);
	 
	if(mqdes == -1){
		printf("failed to open queue\n");
		return 1;	
   	}
   	
   	char msg[attr.mq_msgsize];
   	strcpy(msg, "hello");
   	 
   	if(mq_send(mqdes, (char*)msg, strlen(msg)+1, 0) == -1){
		printf("failed to send the message");
		return 2;
	}
    mq_close(mqdes);
	return 0;
}
