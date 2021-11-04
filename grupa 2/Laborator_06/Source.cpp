
#include <iostream>
#include <string>
#include <thread>
#include <omp.h>
#include <vector>
using namespace std;

bool testPrim(long valoare) {
	bool estePrim = true;
	for (long i = 2; i < valoare / 2; i++) {
		if (valoare % i == 0) {
			estePrim = false;
			break;
		}
	}
	return estePrim;
}

void testNrPrimeSecvential(long N, int& rezultat) {
	rezultat = 0;
	for (long i = 0; i < N; i++) {
		if (testPrim(i)) {
			rezultat += 1;
		}
	}
}

void verificaInterval(long limitaInferioara, long limitaSuperioara, int &rezultat) {
	rezultat = 0;
	for (long i = limitaInferioara; i < limitaSuperioara; i++) {
		if (testPrim(i)) {
			rezultat += 1;
		}
	}
}

void testNrPrimeParalelIntervaleEgale (long N, int& rezultat) {
	int nrProcesoare = omp_get_num_procs();
	printf("\n Numar procesoare = %d", nrProcesoare);
	vector<thread> threaduri;
	int* rezultate = new int[nrProcesoare];
	long dimInterval = N / nrProcesoare;
	for (int i = 0; i < nrProcesoare; i++) {
		long limitaI = i * dimInterval;
		long limitaS = (i == nrProcesoare - 1) ? N : (i + 1) * dimInterval;
		threaduri.push_back(thread(verificaInterval, limitaI, limitaS, ref(rezultate[i])));
	}
	for (int i = 0; i < nrProcesoare; i++) {
		threaduri[i].join();
	}
	rezultat = 0;
	for (int i = 0; i < nrProcesoare; i++) {
		rezultat += rezultate[i];
	}
}

void benchmarking(string descriere, void (*pf)(long, int&), long N) {
	cout << endl << "Test " << descriere;
	int rezultat = 0;
	double tStart = omp_get_wtime();
	pf(N, rezultat);
	double tFinal = omp_get_wtime();
	cout << endl << "Rezultat = " << rezultat;
	cout << endl << "Durata (secunde) = " << (tFinal - tStart);
}

int main() {
	const long N = 4e5;
	benchmarking("Implementare secventiala", testNrPrimeSecvential, N);
	benchmarking("Implementare paralela cu intervale egale", testNrPrimeParalelIntervaleEgale, N);
}