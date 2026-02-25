#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgReciver{
    long msg_type;
    int number;
};


int main(){

    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msgReciver msg;

    msgrcv(msgid, &msg, sizeof(msg.number), 1, 0);

    printf("Received from Message Queue: %d\n", msg.number);
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}