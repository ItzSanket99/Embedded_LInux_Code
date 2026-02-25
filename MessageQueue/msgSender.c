#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgSender{
    long msg_type;
    int number;
};

int main(){

    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msgSender msg;
    msg.msg_type = 1;

    printf("Enter number: ");
    scanf("%d", &msg.number);

    msgsnd(msgid, &msg, sizeof(msg.number), 0);

    return 0;
}