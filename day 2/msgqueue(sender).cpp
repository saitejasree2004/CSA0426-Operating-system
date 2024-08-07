#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSG_KEY 0x1234

// Define the message structure
struct msgbuf {
    long mtype;       // Message type
    char mtext[100];  // Message text
};

int main() {
    int msgid;
    struct msgbuf message;

    // Create a message queue
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    // Set the message type and text
    message.mtype = 1; // Message type
    strcpy(message.mtext, "Hello from sender!");

    // Send a message to the queue
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) < 0) {
        perror("msgsnd");
        exit(1);
    }

    printf("Sender: Message sent to the queue: %s\n", message.mtext);

    return 0;
}

