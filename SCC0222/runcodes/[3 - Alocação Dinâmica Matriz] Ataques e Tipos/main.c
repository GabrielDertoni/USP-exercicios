#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int damage;
	int type;
} attack_t;

int main(int argc, char *argv[]) {
	int m, n, enemy_type, max_idx;
	float max_dmg = 0;

	scanf("%d", &m);
	float **mat = (float **)malloc(sizeof(float *) * m);
	// Lê todas as entradas da matriz de tipos e multiplicadores.
	for (int i = 0; i < m; i++) {
		mat[i] = (float *)malloc(sizeof(float) * m);
		for (int j = 0; j < m; j++)
			scanf("%f", &mat[i][j]);
	}

	attack_t *attacks = NULL;
	int allocated, damage = 0, type;
	for (n = 0, allocated = 0; damage != -1; n++) {
		scanf("%d", &damage);
		if (damage != -1) {
			scanf("%d", &type);
			if (n >= allocated) {
				allocated *= 2;
				if (allocated == 0) allocated += 2;
				attacks = (attack_t *)realloc(attacks, allocated * sizeof(attack_t));
			}
			attacks[n].damage = damage;
			attacks[n].type = type;
		}
	}
	attacks = (attack_t *)realloc(attacks, --n * sizeof(attack_t));

	scanf("%d", &enemy_type);
	for (int i = 0; i < n; i++) {
		float full_damage = (float)attacks[i].damage * mat[attacks[i].type][enemy_type];
		if (full_damage > max_dmg) {
			max_dmg = full_damage;
			max_idx = i;
		}
	}

	printf("O melhor ataque possui indice %d e dano %.2f\n", max_idx, max_dmg);

	free(attacks);
	for (int i = 0; i < m; i++) free(mat[i]);
	free(mat);

	return 0;
}
