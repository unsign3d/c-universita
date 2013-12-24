/*
 * Thanks to
 * http://bit.ly/1c2jDJS
 *
 * Simple program both server
 * and client who send and receve a
 * message
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SECRET_KEY 123

int main(int argc, char const *argv[])
{
	/* basically the same key used 
	 for the semaphore programs */
	key_t key;
	int msqid;
	struct msqid_ds buf;
	struct msg_buf {
	  long mtype;
	  int  length;
	  char *text;
	} msg;

	int size;

	/* create a token */
	if((key = ftok("/tmp", SECRET_KEY)) == -1) {
		printf("[-] Error on ftok\n");
		return 1;
	}

	/* create a set of msg */
	if((msqid = msgget(key, 0666|IPC_CREAT|IPC_EXCL)) == -1) {
		printf("[-] Error on msgid\n");
		return 1;
	}

	/* perform an operation in message q */
	if((msgctl(msqid, IPC_STAT, &buf)) == -1){
		printf("[-] Error on msgctl [1]\n");
		return 1;
	}

	/* set the message */
	msg.mtype = 1;
	msg.text = "Much messages, such IPC, so shibe, WOW";
	msg.length = strlen(msg.text);

	size = sizeof(struct msg_buf) - sizeof(long);

	if((msgsnd(msqid, &msg, size, 0)) == -1) {
		printf("[-] Error on msgsnd\n");
		return 1;
	}

	/* free the buffer */
	msg.text = "";
	msg.length = 0;

	/* receve the message */
	if((msgrcv(msqid, &msg, size, 1, 0)) == -1) {
		printf("[-] Error on msgrcv\n");
		return 1;
	}
	else {
		printf("%s \n", msg.text);
	}

	/* remove message q */
	if((msgctl(msqid, IPC_RMID, &buf)) == -1){
		printf("[-] Error on msgctl [2]\n");
		return 1;
	}
	return 0;
}
