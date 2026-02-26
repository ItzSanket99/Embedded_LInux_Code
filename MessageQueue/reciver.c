#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	int totalCnt;
	int highCnt;
	int lowCnt;
	
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 64;
    attr.mq_curmsgs = 0;

    mqd_t mqdes = mq_open("/queue", O_CREAT | O_RDONLY, 0666, &attr);
    if (mqdes == -1) {
        printf("failed to open mq\n");
        return 1;
    }

    char msg[64];
    unsigned int prio;

    while (1) {
		sleep(1);
        ssize_t bytes = mq_receive(mqdes, msg, sizeof(msg), &prio);
        if (bytes == -1) {
            printf("mq receive failed");
            return 2;
        }
		if(bytes > 0) {
			totalCnt++;
			if(prio == 0){
				lowCnt++;
			}else{
				highCnt++;
			}
		}
		
        printf("Received: %s Priority: %u totalCnt %d highCnt %d lowCnt %d\n", msg, prio, totalCnt, highCnt, lowCnt);
    }

    mq_close(mqdes);
    mq_unlink("/queue");
    return 0;
}
