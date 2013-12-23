#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define SECRET_KEY 123

int main(int argc, char const *argv[])
{
	key_t key;
	int semid;
	/* setted to allocate the space */
	struct sembuf sb = {0,-1,0};

	/* create a token */
	if((key = ftok("/tmp", SECRET_KEY)) == -1) {
		printf("[-] Error on ftok\n");
		return 1;
	}

	/* grab the previously used sem */
	if((semid = semget(key, 1, 0)) == -1) {
		printf("[-] Error on semget\n");
		return 1;
	}

	printf("[+]Now I'll lock for 5 seconds the semaphore\n");

	if (semop(semid, &sb, 1) == -1) {
		printf("[-] Error on semget\n");
		return 1;
	}
	/* put in sleep */
	sleep(5);

	/* unlock */
	sb.sem_op = 1;
	if (semop(semid, &sb, 1) == -1) {
		printf("[-] Error on semget\n");
		return 1;
	}

	printf("[+]Unlocked\n");

	return 0;
}
