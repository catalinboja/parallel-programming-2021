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
	for (long i = indexStart; i < N; i += pas) {
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
		for (long i = (idThread * 2 + 1); i < N; i += (2 * nrProcesoare)) {
			if (testPrim(i)) {
				rezultate[idThread] += 1;
			}
		}
	}

	for (int i = 0; i < nrProcesoare; i++) {
		rezultat += rezultate[i];
	}
}


void implementareParalelaOMPFaraCacheSharing(long N, int& rezultat) {
	rezultat = 0;

	int nrProcesoare = omp_get_num_procs();
	if (nrProcesoare != 1 && nrProcesoare % 2 == 1) {
		nrProcesoare -= 1;
	}

	int* rezultate = new int[nrProcesoare*100];
	for (int i = 0; i < nrProcesoare; i++) {
		rezultate[i*100] = 0;
	}

#pragma omp parallel num_threads(nrProcesoare)
	{
		int idThread = omp_get_thread_num();
		for (long i = (idThread * 2 + 1); i < N; i += (2 * nrProcesoare)) {
			if (testPrim(i)) {
				rezultate[idThread*100] += 1;
			}
		}
	}

	for (int i = 0; i < nrProcesoare; i++) {
		rezultat += rezultate[i*100];
	}
}

//atentie la race condition pe +=
void implementareParalelaOMPCuVariabilePrivate(long N, int& rezultat) {
	rezultat = 0;

	int nrProcesoare = omp_get_num_procs();
	if (nrProcesoare != 1 && nrProcesoare % 2 == 1) {
		nrProcesoare -= 1;
	}

	int rezultatLocal = 0;

#pragma omp parallel num_threads(nrProcesoare) shared(nrProcesoare, rezultat) firstprivate(rezultatLocal)
	{
		int idThread = omp_get_thread_num();
		for (long i = (idThread * 2 + 1); i < N; i += (2 * nrProcesoare)) {
			if (testPrim(i)) {
				rezultatLocal += 1;
			}
		}
		//race condition
		rezultat += rezultatLocal;
	}
}

//atentie la race condition pe +=
void implementareParalelaOMPCuVariabilePrivateFaraRaceCondition(long N, int& rezultat) {
	rezultat = 0;

	//generam un mutex prin omp
	omp_lock_t* mutex = new omp_lock_t();
	omp_init_lock(mutex);

	int nrProcesoare = omp_get_num_procs();
	if (nrProcesoare != 1 && nrProcesoare % 2 == 1) {
		nrProcesoare -= 1;
	}

	int rezultatLocal = 0;

#pragma omp parallel num_threads(nrProcesoare) shared(nrProcesoare, rezultat) firstprivate(rezultatLocal)
	{
		int idThread = omp_get_thread_num();
		for (long i = (idThread * 2 + 1); i < N; i += (2 * nrProcesoare)) {
			if (testPrim(i)) {
				rezultatLocal += 1;
			}
		}
		//race condition
		omp_set_lock(mutex);
		rezultat += rezultatLocal;
		omp_unset_lock(mutex);
	}
}

void implementareParalelaOMPCuAtomic(long N, int& rezultat) {
	rezultat = 0;

	int nrProcesoare = omp_get_num_procs();
	if (nrProcesoare != 1 && nrProcesoare % 2 == 1) {
		nrProcesoare -= 1;
	}

	int rezultatLocal = 0;

#pragma omp parallel num_threads(nrProcesoare) shared(nrProcesoare, rezultat) firstprivate(rezultatLocal)
	{
		int idThread = omp_get_thread_num();
		for (long i = (idThread * 2 + 1); i < N; i += (2 * nrProcesoare)) {
			if (testPrim(i)) {
				rezultatLocal += 1;
			}
		}
#pragma omp atomic
		rezultat += rezultatLocal;
	}
}

int minimVectorParalel(int valori[], long N) {
	int minim = valori[0];

	omp_set_num_threads(8);
	int minimLocal;

	omp_lock_t* mutex = new omp_lock_t();
	omp_init_lock(mutex);

#pragma omp parallel shared(minim) num_threads(4) private(minimLocal)
	{
		minimLocal = valori[0];
		int nrThreaduri = omp_get_num_threads();
		int dimInterval = N / nrThreaduri;
		int idThread = omp_get_thread_num();
		long start = (idThread * dimInterval);
		long final =  idThread == nrThreaduri-1 ? N : ((idThread + 1) * dimInterval);
		
		for (long i = start; i < final; i++) {
			if (minimLocal > valori[i]) {
				minimLocal = valori[i];
			}
		}

		omp_set_lock(mutex);
		minim = minimLocal < minim ? minimLocal : minim;
		omp_unset_lock(mutex);
	}
	return minim;
}


int main() {
	const long N = 7 * 1e5;

	//benchmark("Implementare secventiala", implementareSecventiala, N);
	//benchmark("Implementare paralela cu intervale egale", implementareParalelaIntervaleEgale, N);
	//benchmark("Implementare paralela cu numar par de thread-uri si eliminare valori pare", implementareParalelaLoadBalancing, N);
	//benchmark("Implementare paralela cu OMP", implementareParalelaOMP, N);
	benchmark("Implementare paralela cu OMP fara cache sharing", implementareParalelaOMPFaraCacheSharing, N);
	benchmark("Implementare paralela cu OMP cu variabile private", implementareParalelaOMPCuVariabilePrivate, N);
	benchmark("Implementare paralela cu OMP cu mutex", implementareParalelaOMPCuVariabilePrivateFaraRaceCondition, N);
	benchmark("Implementare paralela cu OMP cu atomic", implementareParalelaOMPCuAtomic, N);
}