#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tempo em segundo da duração do dia em cada planeta e também das horas e minutos.
#define MINUTE 60
#define HOUR (60 * MINUTE)
#define EARTH_DAY (24 * HOUR)
#define JUPITER_DAY (9 * HOUR + 56 * MINUTE)
#define MERCURY_DAY (58 * EARTH_DAY + 16 * HOUR)
#define VENUS_DAY (243 * EARTH_DAY)

int main(int argc, char *argv[]) {
	long long total_seconds;
	scanf("%lld", &total_seconds);

	char planet[10];
	scanf(" %s", planet);

	int days, hours, minutes, seconds;
	if (!strcmp(planet, "Terra")) {
		days    =    total_seconds / EARTH_DAY;
		hours   =   (total_seconds % EARTH_DAY) / HOUR;
		minutes =  ((total_seconds % EARTH_DAY) % HOUR) / MINUTE;
		seconds = (((total_seconds % EARTH_DAY) % HOUR) % MINUTE);
	} else if (!strcmp(planet, "Venus")) {
		days    =    total_seconds / VENUS_DAY;
		hours   =   (total_seconds % VENUS_DAY) / HOUR;
		minutes =  ((total_seconds % VENUS_DAY) % HOUR) / MINUTE;
		seconds = (((total_seconds % VENUS_DAY) % HOUR) % MINUTE);
	} else if (!strcmp(planet, "Mercurio")) {
		days    =    total_seconds / MERCURY_DAY;
		hours   =   (total_seconds % MERCURY_DAY) / HOUR;
		minutes =  ((total_seconds % MERCURY_DAY) % HOUR) / MINUTE;
		seconds = (((total_seconds % MERCURY_DAY) % HOUR) % MINUTE);
	} else if (!strcmp(planet, "Jupiter")) {
		days    =    total_seconds / JUPITER_DAY;
		hours   =   (total_seconds % JUPITER_DAY) / HOUR;
		minutes =  ((total_seconds % JUPITER_DAY) % HOUR) / MINUTE;
		seconds = (((total_seconds % JUPITER_DAY) % HOUR) % MINUTE);
	} else {
		printf("Erro: Planeta tem que ser um de \"Terra\", \"Venus\", \"Mercurio\", \"Jupiter\"\n");
		return EXIT_FAILURE;
	}

	printf("%lld segundos no planeta %s equivalem a:\n", total_seconds, planet);
	printf("%d dias, %d horas, %d minutos e %d segundos\n", days, hours, minutes, seconds);

	return EXIT_SUCCESS;
}
