#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#define MAX_LEN 255

// Define structure for Message 
typedef struct{
    long type;
    char msgtxt[MAX_LEN];
}Msgbuf;

// Initialize Message Queue
int MsgQInit(int key){
    int msgID;
    if((msgID = msgget(key, IPC_CREAT|0666)) == -1){
        perror("msgget error");
        return -1;
    }
    return msgID;
}

// Message Queue Receiving function
int MsgQRcv(int msgID, void* buf, int size, int type){

    Msgbuf rcvbuf;
    int len;
    
    if((len = msgrcv(msgID, &rcvbuf, MAX_LEN, type, MSG_NOERROR | IPC_NOWAIT))== -1)
        return -1;

    memcpy(buf, rcvbuf.msgtxt, size);
    return len;
}

int main(){

    Msgbuf buf;
    int MsgID;
    int ret;

    MsgID = MsgQInit(788);
    printf("MsgID: %d\n", MsgID);
    buf.type = 3;
    while(1){
        ret = MsgQRcv(MsgID, buf.msgtxt, MAX_LEN, buf.type);
        if(ret != -1 && buf.type == 3){
            printf("msg = %s \n", buf.msgtxt);
        }
    }

    return 0;
}
