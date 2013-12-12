/* questo file non può essere compilato come -std=c99 */

#include <stdio.h>
#define MAX_S 1024

int main(int argc, char const *argv[])
{	
	/* la popen si usa come un file */
	FILE *fp;
	char buff[MAX_S]; //un buffer per fgets
	
	/* apro il comando ls */
	if ((fp = popen("ls", "r")) == NULL) {
		return -1;
	}

	/* stampo l'output di ls */
	while(fgets(buff, MAX_S, fp) != NULL) {
		printf("%s\n", buff );
	}

	if(pclose(fp) == -1){
		printf("Error on closing pipe\n");
		return -1;
	}

	return 0;
}