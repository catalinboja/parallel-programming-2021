#include <iostream>
#include <thread>
#include <stdio.h>
#include "omp.h"
using namespace std;

void mesaj() {
	printf("\n Hello din thread-ul secundar");
}

int main() {

	//macrodefinitie
	#define NMAX 100;

	//secventa paralela clasica cu thread-uri explicite
	printf("\n Hello din thread-ul principal");

	thread  t1(mesaj);
	thread  t2(mesaj);

	t1.join();
	t2.join();

	int nrThreaduri = omp_get_num_threads();
	printf("\n Nr thread-uri = %d", nrThreaduri);

	int idThreadPrincipal = omp_get_thread_num();
	printf("\n Thread principal id = %d", idThreadPrincipal);

	unsigned int nrProcesoare = omp_get_num_procs();
	printf("\n Nr core-uri: %d", nrProcesoare);

	//secventa paralela cu openmp
#pragma omp parallel num_threads(nrProcesoare/2)
	{
		int idThread = omp_get_thread_num();
		printf("\n Id-ul thread-ului este %d", idThread);

		if (idThread == 0) {
			int nrThreaduriCreate = omp_get_num_threads();
			printf("\n Nr thread-uri = %d", nrThreaduriCreate);
		}

		printf("\n Hello");
	}

	printf("\n Sfarsit exemplu");

}