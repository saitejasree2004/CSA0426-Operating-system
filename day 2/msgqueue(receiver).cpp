#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 0x1234

// Define the message structure
struct msgbuf {
    long mtype;       // Message type
    char mtext[100];  // Message text
};

int main() {
    int msgid;
    struct msgbuf message;

    // Locate the message queue
    msgid = msgget(MSG_KEY, 0666);
    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    // Receive a message from the queue
    if (msgrcv(msgid, &message, sizeof(message.mtext), 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    printf("Receiver: Message received from the queue: %s\n", message.mtext);

    // Delete the message queue
    if (msgctl(msgid, IPC_RMID, NULL) < 0) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}

