
#include <iostream>
#include <string>
#include <thread>
#include <omp.h>
#include <vector>
using namespace std;

bool testPrim(long valoare) {
	bool estePrim = true;
	for (long i = 2; i <= valoare / 2; i++) {
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

void verificaInterval(long limitaInferioara, long limitaSuperioara, int& rezultat) {
	rezultat = 0;
	for (long i = limitaInferioara; i < limitaSuperioara; i++) {
		if (testPrim(i)) {
			rezultat += 1;
		}
	}
}

void testNrPrimeParalelIntervaleEgale(long N, int& rezultat) {
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


void verificaValori(long indexStart, int pas, long N, int& rezultat) {
	rezultat = 0;
	for (int i = indexStart; i < N; i += pas) {
		if (testPrim(i)) {
			rezultat += 1;
		}
	}
}

void testNrPrimeParalelLoadBalancingFaraValoriPare(long N, int& rezultat) {

	rezultat = 0;
	int nrProcesoare = omp_get_num_procs();

	//ne asiguram ca folosim numar par de procesoare
	if (nrProcesoare != 1 && nrProcesoare % 2 == 1) {
		nrProcesoare -= 1;
	}

	vector<thread> threaduri;
	int* rezultate = new int[nrProcesoare];

	for (int i = 0; i < nrProcesoare; i ++ ) {
		long indexStart = (2 * i) + 1;
		int pas = 2 * nrProcesoare;
		threaduri.push_back(thread(verificaValori, indexStart, pas, N, ref(rezultate[i])));
	}

	for (int i = 0; i < nrProcesoare; i++) {
		threaduri[i].join();
	}

	for (int i = 0; i < nrProcesoare; i++) {
		rezultat += rezultate[i];
	}

}

void testNrPrimeParalelOMP(long N, int& rezultat) {
	rezultat = 0;
	int nrProcesoare = omp_get_num_procs();

	//ne asiguram ca folosim numar par de procesoare
	if (nrProcesoare != 1 && nrProcesoare % 2 == 1) {
		nrProcesoare -= 1;
	}

	int* rezultate = new int[nrProcesoare];
	for (int i = 0; i < nrProcesoare; i++) {
		rezultate[i] = 0;
	}

#pragma omp parallel num_threads(nrProcesoare)
	{
		int nrThreaduriExistente = omp_get_num_threads();
		int pas = 2 * nrThreaduriExistente;

		int idThread = omp_get_thread_num();

		int indexStart = (2 * idThread) + 1;

		for (long i = indexStart; i < N; i+= pas) {
			if (testPrim(i)) {
				rezultate[idThread] += 1;
			}
		}
	}

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
	//benchmarking("Implementare secventiala", testNrPrimeSecvential, N);
	benchmarking("Implementare paralela cu intervale egale", testNrPrimeParalelIntervaleEgale, N);
	benchmarking("Implementare paralela cu load balancing", testNrPrimeParalelLoadBalancingFaraValoriPare, N);
	benchmarking("Implementare paralela cu OMP", testNrPrimeParalelOMP, N);

}