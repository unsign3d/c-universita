#include <stdio.h>
#include <string.h>

/**
 * Controlla se 2 strinche sono uguali tramite una funzione
 * ritorna 1 se sono uguali, 0 altrimenti
 */

#define MAX 180

int confronta (char *str1, char *str2);

int main(int argc, char const *argv[])
{
	char str[MAX];
	char str2[MAX];

	printf("Inserire una stringa: ");
	scanf("%180s", str);
	printf("Inserire una stringa: ");
	scanf("%180s", str2);
	printf("\n %s\n", (confronta(str, str2) == 1)  ? "sono uguali" : "non sono uguali");
	return 0;
}

int confronta (char *str1, char *str2) {
	int len = strlen(str1);
	int res = 1;
	//se hanno lunghezze diverse ritorna 0
	if (len != strlen(str2)) return 0;

	for (int i = 0; i < len && res == 1; ++i){
		if(str1[i] != str2[i]) res = 0;
	}

	return res;

}