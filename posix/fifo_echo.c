/**
 * This program will read from the pipe
 * org.unsigned.fifo and replys to it like
 * an echo server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_LINE 80

int main(int argc, char const *argv[]) {
	char *fifo_name = "./org.unsigned.fifo";
	char *line = (char *) calloc(MAX_LINE, MAX_LINE * sizeof(char));

	int fifo_server;

	/* create fifo */
	if(mkfifo(fifo_name, 0622) < 0){
		printf("Errore nella creazione della fifo");
		return -1;
	}

	/* infinite looping duplicate input to output */
	while(1){
		/* open fifo two times to avoid EOF */
		if((fifo_server = open(fifo_name, O_RDONLY)) < 0){
			printf("Errore nell'apertura della fifo");
			return -1;
		}

		if(read(fifo_server, line, MAX_LINE) > 0){
			printf("[+]Msg: %s\n", line);
		}
		else break;

		close(fifo_server);
	}

	printf("Sto uscendo\n");
	
	unlink(fifo_name);
	return 0;
}