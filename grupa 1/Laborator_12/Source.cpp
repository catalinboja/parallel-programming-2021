#include <iostream>
#include <string>
#include <omp.h>
using namespace std;


//generare vector random
int* generare(int N) {
	srand(1000);
	int* valori = new int[N];
	for (int i = 0; i < N; i++) {
		valori[i] = rand() % 10000;		//valorile random sunt in [0, 9999]
	}
	return valori;
}

int* copiere(int* valori, int N) {
	int* copie = new int[N];
	memcpy(copie, valori, N * sizeof(int));
	return copie;
}

bool esteSortatCrescator(int* valori, int N) {
	bool esteSortat = true;
	for (int i = 0; i < N - 1; i++) {
		if (valori[i] > valori[i + 1]) {
			esteSortat = false;
			break;
		}
	}
}

void benchmark(int* valori, int N, void (*pf)(int*, int), string mesaj) {

	cout << endl << "Test pentru " << mesaj;

	double tStart = omp_get_wtime();
	pf(valori, N);
	double tFinal = omp_get_wtime();

	cout << endl << "Durata sortare = " << (tFinal - tStart);
	if (esteSortatCrescator(valori, N)) {
		cout << endl << "Sortare corecta";
	}
	else
	{
		cout << endl << "*** Sortare gresita";
	}
}


int main() {

}