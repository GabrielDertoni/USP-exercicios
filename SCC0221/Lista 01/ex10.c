#include <stdio.h>

int main(int argc, char *argv[]) {
	float kosten;
	printf("Schreiben die Herstellungskosten\n");
	scanf("%f", &kosten);

	float preis;
	if (kosten > 25000)
		preis = kosten * 1.35;
	else if (kosten > 12000)
		preis = kosten * 1.25;
	else
		preis = kosten * 1.05;

	printf("Der Preis des Autos wird R$ %.2f sein\n", preis);
	return 0;
}
