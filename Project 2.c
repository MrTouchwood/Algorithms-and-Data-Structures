/*  Date: 12/05/2018
	Description: Project 2 - Sparse Matrices - Airports
	Version 3.0
	*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float apostasi(int xa, int ya, int xb, int yb) {
	return sqrt((xb - xa)^2 + (yb - ya)^2);
}

int main() {
	srand(1047028);

	/*katalogos aerodromiwn*/
	int i, j, x[1000], y[1000];
	for (i = 0; i < 1000; i++){
		start:
		y[i] = rand() % 3341000;
		x[i] = rand() % 2154000;
		for (j = 1; j < i; j++) if (apostasi(x[i], y[i], x[j], y[j]) < 100) goto start;
	}
	
	/*10.000 ptiseis*/
	int iloc[1000], jloc[10000], fperow; float distance[10000];
	for (i = 1; i<1000; i++) iloc[i] = -1;
	for (i = 0; i < 10000; i++) {
		jloc[i] = -1;
		distance[i] = 0;
	}
	iloc[0] = 0;

	i = -1;
	while(++i<1000 && jloc[9999] == -1){
		fperow = rand() % 20;
		if (iloc[i] + fperow > 9999) fperow = 9999 - iloc[i];

		for (j = iloc[i]; j < iloc[i] + fperow; j++){
			jloc[j] = rand() % 1000;
			distance[j] = apostasi(x[i], y[i], x[jloc[j]], y[jloc[j]]);
		}
		if (i < 999) iloc[i + 1] = iloc[i] + fperow;
	}
	
	//for (i = 0; i < 100; i++) printf("%d    %d\n", iloc[i], jloc[i]);!!!!!!!!!
	//for (i = 1000; i < 10000; i++) printf("%d\n", jloc[i]);
	
	//zitoumeno
	printf("Megistes apostaseis:\n");
	float maxdist;
	for (i = 0; i < 999; i++) {
		printf("%d   ", i + 1);
		maxdist = 0.0;
		for (j = iloc[i]; j < iloc[i + 1]; j++) if (distance[j] > maxdist) maxdist = distance[j];
		printf("%.2f\n", maxdist);
	}
	//last airport
	printf("%d  ", 1000);
	maxdist = 0.0;
	for (j = iloc[i]; j < 9999; j++) if (distance[j] > maxdist) maxdist = distance[j];
	printf("%.2f\n", maxdist);

	system("pause");
	return (0);
}