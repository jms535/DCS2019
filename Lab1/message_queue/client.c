#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>
#define MAX_LEN 255

typedef struct{
    long type;
    char msgtxt[MAX_LEN];
}Msgbuf;

int MsgQInit(int key){
    int msgID;
    if((msgID = msgget(key, IPC_CREAT|0666) == -1)){
        perror("msgget error");
        return -1;
    }

    return msgID;
}

int MsgQSnd(int msgID, void* buf, int size, int type){
    Msgbuf sndbuf;
    sndbuf.type = type;
    memcpy(sndbuf.msgtxt, buf, size);

    if(msgsnd(msgID, &sndbuf, size, 0)){
        perror("MsgSnd");
        return -1;
    }
    return 0;
}

int main(){

    int MsgID;

    // pass same key value with server !
    MsgID = MsgQInit(788);
    printf("MsgID: %d\n", MsgID);

    for(int i = 0; i < 5; i++){
        printf("%dth Send\n", i);
        MsgQSnd(MsgID, "Test Msg", 9, 3);
    }
}
