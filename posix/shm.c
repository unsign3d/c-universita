/** 
 *  WARNING
 *  due to semplicity the shared memory
 *  is not treated like a critic session.
 *  In this toy case the same process will
 *  read and write on the shared memory 
 *  segment.
 *
 * 	Thanks to gapil for the awesome guide.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SECRET_KEY 123
#define MSG_LENGTH 160

int main(int argc, char const *argv[])
{
	key_t key;
	int shmid;
	struct shmseg *shmp;
	char *msg = "SUCH CAT, MUCH SWAG, SO NEKO, WOW";

	/* create a token */
	if((key = ftok("/tmp", SECRET_KEY)) == -1) {
		printf("[-] Error on ftok\n");
		return 1;
	}

	/* create a set of msg */
	if((shmid = shmget(key, MSG_LENGTH * sizeof(char), 0666|IPC_CREAT|IPC_EXCL)) == -1) {
		printf("[-] Error on shmget\n");
		return 1;
	}

	/* attach a segment to the process */
	if ((shmp = (struct shmseg *) shmat(shmid, NULL, 0)) == (void *) -1) {
		printf("[-] Error on shmat\n");
		return 1;
	}
	/* attach a segment to the process */
	if (shmctl(shmid, IPC_RMID, 0) == -1) {
		printf("[-] Error on shmctl \n");
		return 1;
	}

	/* write on the shared memory */
	snprintf((char *)shmp, strlen(msg) +1, "%s", (char * )msg);

	/* write shared memory on STDOUT */
	puts((char *) shmp);

	/* detach a segment to the process */
	if (shmdt(shmp) == -1) {
		printf("[-] Error on shmdt\n");
		return 1;
	}
	return 0;
}
