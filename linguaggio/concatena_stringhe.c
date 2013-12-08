#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 180

/*
int concatena (char a[], char b[], char ab[], int max)
- a e b sono le due stringhe da concatenare.
- ab è la stringa contenente il risultato della concatenazione
- max rappresenta il numero di caratteri allocati in memoria perla stringa ab.
Se la lunghezza di a + lunghezza di b è minore di max, la funzione crea nella
stringa ab la concatenazione di a + b.La funzione restituisce la lunghezza della
nuova stringa ab. Altrimenti, la funzione restituisce -1 e ab non ha significato.
 */

int concatena (char a[], char b[], char ab[], int max);

int main(int argc, char const *argv[])
{
	char str[MAX];
	char str2[MAX];
	char res[2*MAX];

	printf("Inserire una stringa: ");
	scanf("%180s", str);
	printf("Inserire una stringa: ");
	scanf("%180s", str2);

	if(concatena(str, str2, res, 2*MAX) == 0){
		printf("%s\n", res);
	}
	else {
		printf("Errore\n");
	}
	
	return 0;
}

int concatena (char *a, char *b, char *ab, int max){
	int l1 = strlen(a);
	int l2 = strlen(b);
	int i = 0, lab = l1+l2;
	
	if(lab > max) return -1;

	//copio il primo
	for (; i < l1; ++i) {
		ab[i] = a[i];
	}

	//copio il secondo
	for (; i < lab; ++i) {
		ab[i] = b[i - l1];
	}
	//faccio finire la stringa
	ab[i] = '\0';

	return 0;
}