#include <vector>
#include <string>
#include <iostream>
#include <omp.h>
using namespace std;

//varianta secventiala suma elemente vector
long sumaElementeVector(int valori[], int n) {
	long suma = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 100; j++) {
			int temp = j / 3;
		}
		suma += valori[i];
	}
	return suma;
}

long sumaElementeVectorParalela(int valori[], int n) {
	long suma = 0;

#pragma omp parallel for num_threads(8) reduction(+: suma)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 100; j++) {
			int temp = j / 3;
		}
		suma += valori[i];
	}

	return suma;
}

long sumaElementeVectorParalelaCuSchedule(int valori[], int n) {
	long suma = 0;
	int nrIteratii = 0;
#pragma omp parallel num_threads(8)  firstprivate(nrIteratii)
	{
#pragma omp for reduction(+: suma) schedule(guided, 1000)
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 100; j++) {
				int temp = j / 3;
			}
			suma += valori[i];
			nrIteratii += 1;
		}
		cout << endl << "Nr iteratii = " << nrIteratii << " pentru thread " << omp_get_thread_num();
	}

	return suma;
}

void benchmark(long (*pf)(int[], int), int* valori, int n) {
	double tStart = omp_get_wtime();
	long rezultat = pf(valori,n);
	double tFinal = omp_get_wtime();
	cout << endl << "Rezultat: " << rezultat;
	cout << endl << "Durata: " << tFinal - tStart;
}


int main() {

	const int N = 1e8;
	int * valori = new int[N];
	for (int i = 0; i < N; i++) {
		valori[i] = i+1;
	}

	cout << endl << "Start teste";

	///benchmark(sumaElementeVector, valori, N);
	benchmark(sumaElementeVectorParalela, valori, N);
	benchmark(sumaElementeVectorParalelaCuSchedule, valori, N);

	cout << endl << "Final teste";

}