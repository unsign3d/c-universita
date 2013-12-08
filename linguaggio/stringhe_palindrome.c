#include <stdio.h>
#include <string.h>

#define MAX 180

int palindroma(char *str);

int main(int argc, char const *argv[])
{
	char str[MAX];

	printf("Inserire una stringa: ");
	scanf("%180s", str);
	printf("\n %s\n", (palindroma(str) == 1)  ? "è palindroma" : "non è palindroma");
	return 0;
}

int palindroma(char *str){
	int len = strlen(str) 
	 ,  mid = (int) (len -1) /2
	// parto assumendo che la stringa sia palindroma
	 , res = 1;

	//trovo un caso in cui non lo sia
	for (int i = 0; (i < mid) && (res == 1) ; ++i){
		if(str[i] != str[len-i-1]) res = 0;
	}

	return res;
}