/* Thanks to 
 * http://bit.ly/1c2jDJS
 * http://bit.ly/1e5sAFD
 * and other stuff on the internet
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SECRET_KEY 123
/* in linux is not defined */
union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};


int main(int argc, char const *argv[])
{
	key_t key;
	int semid;
	union semun sem_arg;

	/* create a token */
	if((key = ftok("/tmp", SECRET_KEY)) == -1) {
		printf("[-] Error on ftok\n");
		return 1;
	}

	/* create semaphore */
	if((semid = semget(key, 1, 0666 | IPC_CREAT)) == -1) {
		printf("[-] Error on semget\n");
		return 1;
	}

	/* set semaphore to 1 */
	sem_arg.val = 1;
	if(semctl(semid, 0, SETVAL, sem_arg) == -1) {
		printf("[-] Error on semctl\n");
		return 1;
	}

	return 0;
}
