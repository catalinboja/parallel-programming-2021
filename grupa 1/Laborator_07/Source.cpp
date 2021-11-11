#include <iostream>
#include <string>
#include <thread>
#include <omp.h>
#include <vector>
using namespace std;

bool testPrim(long valoare) {
	bool estePrim = true;
	for (int i = 2; i <= valoare / 2; i++) {
		if (valoare % i == 0) {
			estePrim = false;
			break;
		}
	}
	return estePrim;
}

//contor numere prime
void implementareSecventiala(long N, int& rezultat) {
	rezultat = 0;
	for (int i = 0; i < N; i++) {
		if (testPrim(i)) {
			rezultat += 1;
		}
	}
}


void verificaInterval(long limitaInferioara, long limitaSuperioara, int& rezultat) {
	rezultat = 0;
	for (int i = limitaInferioara; i < limitaSuperioara; i++) {
		if (testPrim(i)) {
			rezultat += 1;
		}
	}
}

//solutie paralela cu mai multe intervale
void implementareParalelaIntervaleEgale(long N, int& rezultat) {
	int nrProcesoare = omp_get_num_procs();
	printf("\n Numar procesoare = %d", nrProcesoare);

	vector<thread> threaduri;
	int* rezultate = new int[nrProcesoare];

	long dimInterval = N / nrProcesoare;
	for (int i = 0; i < nrProcesoare; i++) {
		long limitaI = i * dimInterval;
		long limitaS = (i == nrProcesoare - 1) ? N : (i + 1) * dimInterval;
		rezultate[i] = 0;
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

void verificaIntervalCuPas(long indexStart, long N, int pas, int& rezultat) {
	rezultat = 0;
	for (long i = indexStart; i < N; i+=pas) {
		if (testPrim(i))
			rezultat += 1;
	}
}

//solutie cu un load balancing mai eficient - pentru numar par de thread-uri
void implementareParalelaLoadBalancing(long N, int& rezultat) {
	rezultat = 0;

	int nrProcesoare = omp_get_num_procs();
	if (nrProcesoare != 1 && nrProcesoare % 2 == 1) {
		nrProcesoare -= 1;
	}

	vector<thread> threaduri;
	int* rezultate = new int[nrProcesoare];
	for (int i = 0; i < nrProcesoare; i++) {
		threaduri.push_back(
			thread(verificaIntervalCuPas, (2 * i + 1), N, 2 * nrProcesoare, ref(rezultate[i])));
	}

	for (int i = 0; i < nrProcesoare; i++) {
		threaduri[i].join();
	}

	for (int i = 0; i < nrProcesoare; i++) {
		rezultat += rezultate[i];
	}
}

void benchmark(string mesaj, void (*pf)(long, int&), long N) {
	cout << endl << "Test pentru " << mesaj;
	int rezultat = 0;
	double tStart = omp_get_wtime();
	pf(N, rezultat);
	double tFinal = omp_get_wtime();
	cout << endl << "Rezultat obtinut = " << rezultat;
	cout << endl << "Durata (secunde): " << (tFinal - tStart);
}


void implementareParalelaOMP(long N, int& rezultat) {
	rezultat = 0;

	int nrProcesoare = omp_get_num_procs();
	if (nrProcesoare != 1 && nrProcesoare % 2 == 1) {
		nrProcesoare -= 1;
	}

	int* rezultate = new int[nrProcesoare];
	for (int i = 0; i < nrProcesoare; i++) {
		rezultate[i] = 0;
	}
	
#pragma omp parallel num_threads(nrProcesoare)
	{
		int idThread = omp_get_thread_num();
		for (long i = (idThread*2+1); i < N; i+= (2*nrProcesoare)) {
			if (testPrim(i)) {
				rezultate[idThread] += 1;
			}
		}
	}

	for (int i = 0; i < nrProcesoare; i++) {
		rezultat += rezultate[i];
	}
}

int main() {
	const long N = 5 * 1e5;

	//benchmark("Implementare secventiala", implementareSecventiala, N);
	benchmark("Implementare paralela cu intervale egale", implementareParalelaIntervaleEgale, N);
	benchmark("Implementare paralela cu numar par de thread-uri si eliminare valori pare", implementareParalelaLoadBalancing, N);
	benchmark("Implementare paralela cu OMP", implementareParalelaOMP, N);
}