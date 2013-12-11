#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

/**
 * semplice uso della fork
 * il processo crea un figlio, 
 * aspetta, stampa ed esce
 *
 * [unsigned.ultrabook] $ ./fork
 * Much parent, wow
 * Much children, such pid, so multiprog, wow
 * Such wait, so shibe, wow
 *
 */

void child_code();
void parent_code();


int main(int argc, char const *argv[]) {

	pid_t childPid;

	//creo un nuovo processo
	switch (childPid = fork()){
		case -1: //fork fallita
			return 1;
			break;
		case 0: // eseguo il codice del figlio
			child_code();
			break;
		default: // eseguo il codice del padre
			parent_code();
			break;
	}
	/* code */
	return 0;
}

void child_code() {
	printf("Much children, such pid, so multiprog, wow\n");

}

void parent_code() {
	int errno;
	printf("Much parent, wow\n");
	while ((errno = wait(NULL)) != -1) continue; //busy waiting
	//se non è un errore inatteso esco
	if(errno != ECHILD){
		//la stampa avviene sempre e solo dopo il figlio
		printf("Such wait, so shibe, wow\n"); 
		exit(EXIT_SUCCESS);
	}  
}