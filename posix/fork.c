#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * semplice uso della fork
 * il processo crea un figlio, 
 * aspetta ed esce
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
		case 0:
			child_code();
			break;
		default:
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
	printf("Much parent, wow\n");
}