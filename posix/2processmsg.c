#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define SECRET_KEY 123

struct msg_buf {
	long mtype;
	int  length;
	char *text;
};
void child_code(int msqid);
void parent_code(int msqid);

int main(int argc, char const *argv[])
{
	/* basically the same key used 
	 for the semaphore programs */
	key_t key;
	pid_t childPid;
	int msqid;

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

	/* now use the fork */
	switch (childPid = fork()){
		case -1: //fork fallita
			return 1;
			break;
		case 0: // eseguo il codice del figlio
			child_code(msqid);
			break;
		default: // eseguo il codice del padre
			parent_code(msqid);
			break;
	}

	return 0;
}

void parent_code(int msqid){
	struct msqid_ds buf;
	struct msg_buf msg;
	int size = 0;

	/* perform an operation in message q */
	if((msgctl(msqid, IPC_STAT, &buf)) == -1){
		printf("[-] Error on msgctl [1]\n");
		exit(1);
	}

	/* set the message */
	msg.mtype = 1;
	msg.text = "Much messages, such IPC, so shibe, WOW";
	msg.length = strlen(msg.text);

	size = sizeof(struct msg_buf) - sizeof(long);


	if((msgsnd(msqid, &msg, size, 0)) == -1) {
		printf("[-] Error on msgsnd\n");
	  exit(1);
	}
}

void child_code(int msqid){
	struct msqid_ds buf;
	struct msg_buf msg;
	int size = sizeof(struct msg_buf) - sizeof(long);

	/* perform an operation in message q */
	if((msgctl(msqid, IPC_STAT, &buf)) == -1){
		printf("[-] Error on msgctl [1]\n");
		exit(1);
	}

	/* receve the message */
	if((msgrcv(msqid, &msg, size, 1, 0)) == -1) {
		printf("[-] Error on msgrcv\n");
		exit(1);
	}
	else {
		printf("%s \n", msg.text);
	}
  
  /* remove message q */
	if((msgctl(msqid, IPC_RMID, &buf)) == -1){
		printf("[-] Error on msgctl [2]\n");
		exit(1);
	}
  
}

