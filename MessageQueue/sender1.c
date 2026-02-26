#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 64;
    attr.mq_curmsgs = 0;

    mqd_t mqdes = mq_open("/queue", O_CREAT | O_WRONLY, 0666, &attr);
    if (mqdes == -1) {
        perror("mq_open failed");
        return 1;
    }

    char msg[] = "TASK_LOW_SENDER";

	while(1){	
		if (mq_send(mqdes, msg, strlen(msg) + 1, 0) == -1) {
		    perror("mq_send failed");
		    return 2;
		}
	}


    mq_close(mqdes);
    return 0;
}
