#include <stdio.h>
#include <stdlib.h>

/*
[studenti.c]
Dichiarare una struttura studente composta da:
int matricola;
char nome[30];
float media;
Leggere da terminale un array di studenti e visualizzare (matricola e nome) tutti
gli studenti con una media >=27
Suggerimento: qui di seguito trovate alcune righe ciascuna delle quali rappresenta
uno studente, salvate queste righe in un file di testo e datelo come input al
vostro programma utilizzando le funzioni di input da file

uso: ./programma db.txt
 */

struct Studente{
	int   matricola;
	char  nome[30];
	float media;
} Studente;


int main(int argc, char const *argv[])
{
	FILE *fp;
	struct Studente tmp;

	if ((fp = fopen(argv[1], "r")) == NULL) exit(1);

	while (!feof(fp)) {
		fscanf(fp, "%4d %30s %f", &tmp.matricola, tmp.nome, &tmp.media);
		if(tmp.media >=27.0){
			printf("%d %s %f\n", tmp.matricola, tmp.nome, tmp.media);
		}
	}
	fclose(fp);
	return 0;
}