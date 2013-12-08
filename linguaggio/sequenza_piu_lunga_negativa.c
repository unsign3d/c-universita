#include <stdio.h>
#include <stdlib.h>

/*
 * Stampa la sequenza negativa più lunga dato un array in input
 *
 * L'esercizio è svolto solo con l'uso di array e variabili, senza
 * strutture (quindi in maniera meno elegante)
 * 
 */

int main(int argc, char const *argv[])
{
	int n = 9, old_s, old_ind, new_s, i;
	int *arr;
	
	//chiedo il numero di elementi
	printf("Inserire il numero di elementi da inserire: ");
	scanf("%d", &n);
	printf("\n");

	//se è possibile alloco l'array, se no esco
	if (n > 0) {
		// in realtà potevo anche dichiarare qui
		// int arr[n] ma è più elegante così
		arr = (int*) malloc(n * sizeof(int));
	}
	else {
		exit(1);
	}

	//popolo l'array
	for (int i = 0; i < n; ++i) {
		printf("Inserire l'elemento %d ", i+1);
		scanf("%d", &arr[i]);
		printf("\n");
	}
	
	//cerco la sequenza negativa più lunga
	old_s = new_s = 0;
	for (i = 0; i < n; ++i) {
		//se l'elemento è negativo sono nella sequenza
		//di negativi
		if (arr[i] < 0) {
			++new_s;
		}
		else {
			//se l'elemento precedente era negativo, allora
			//faccio il backup della sequenza
			if( i > 0 && arr[i-1] < 0){
				//se la nuova sequenza è > di quella vecchia
				//faccio il backup
				if( new_s > old_s ) {
					old_s = new_s;
					old_ind = i -1;
				}
				//azzero la nuova sequenza
				new_s = 0;
			}
		}
		printf("%d\n", new_s);
	}
	if( new_s > old_s ) {
			old_s = new_s;
			old_ind = i;
		}
	printf("La sequenza più lunga ha %d elementi a partire da %d\n", old_s, old_ind - old_s +1);
	return 0;
}