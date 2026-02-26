#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <mqueue.h>

int main(){
	
	mqd_t mqdes;	
	mqdes = mq_open("/myqueue", O_RDONLY, 0666, NULL);
	
	struct mq_attr attr;
	mq_getattr(mqdes, &attr);
	 
	if(mqdes == -1){
		printf("failed to open queue\n");
		return 1;	
   	}
   	
   	char msg[attr.mq_msgsize];
   	
   	if(mq_receive(mqdes, (char *)msg, sizeof(msg), 0) == -1){
   		printf("failed to recive from queue\n");
   		return 2;
   	}
   	
   	printf("recived : %s\n",msg);
   	mq_close(mqdes);
	return 0;
}
