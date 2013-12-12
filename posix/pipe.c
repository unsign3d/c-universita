#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	// il parametro del pipe chiede un array
	// di due elementi int, il primo è aperto
	// in lettura, il secondo in scrittura
	int fd[2];
	pid_t childPid; //per eseguire la fork
	//il messaggio che verrà trasferito
	char string[] = "Much pipe, such Mario, so Nintendo, WOW";
	char readbuffer[80];
	pipe(fd); //inizializzo il pipe

	//creo un nuovo processo
	switch (childPid = fork()){
		case -1: //fork fallita
			perror("fork"); //manda un errore in STDERR
			return 1;
			break;
		case 0: // eseguo il codice del figlio
			//il figlio chiude l'input (chiudo in scrittura)
			if(close(fd[0]) == -1) return 1 ; //gestisco l'eccezione
			//per scrivere sul pipe uso SYSCALL write
			write(fd[1], string, (strlen(string) +1));
			break;
		default: // eseguo il codice del padre
			//chiudo l'output
			if(close(fd[1]) == -1) return 1 ; 
			//uso la read (API) per leggere dal pipe
			read(fd[0], readbuffer, sizeof(readbuffer));
			//scrivo il messaggio
			printf("%s\n", readbuffer);
			break;
	}

	pipe(fd);


	return 0;
}