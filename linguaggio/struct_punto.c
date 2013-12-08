#include <stdio.h>

struct Punto {
	double x, y;
} Punto;

int main(int argc, char const *argv[]) {
	struct Punto p;
	printf("Inserire le coordinate in questo formato\n x.xxxx y.yyyyy: ");
	scanf("%lf %lf", &p.x, &p.y);
	printf("\n");
	printf("%lf [-] %lf", p.x, p.y);
	return 0;
}