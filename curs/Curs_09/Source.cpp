#include <iostream>
#include <omp.h>
#include <string>
#include <vector>
using namespace std;

int main() {


#pragma omp parallel num_threads(4)
	{
		printf("\n Hello");
		int idThread = omp_get_thread_num();
		for (int i = 0; i < 4; i++) {
			if(i == idThread)
				printf("\n Hello pentru iteratia %d", i);
		}
	}


	printf("\n--------------- Utilizare omp for - work sharing");

#pragma omp parallel num_threads(4)
	{
		int idThread = omp_get_thread_num();
#pragma omp for
		for (int i = 0; i < 10; i++) {
				printf("\n Hello pentru iteratia %d de la thread-ul %d", i, idThread);
		}
	}

	printf("\n Exemplu minim folosind omp for");

	//determinam minim dintr-un vector
	vector<int> valori;
	srand(100);
	for (int i = 0; i < 100; i++) {
		valori.push_back(rand());
	}

	int minim = valori[0];

#pragma omp parallel num_threads(4)
	{
		int idThread = omp_get_thread_num();
		int minimLocal = valori[0];
#pragma omp for
		for (int i = 0; i < 100; i++) {
			if (minimLocal > valori[i])
			{
				minimLocal = valori[i];
			}
		}
		printf("\n Minim local este %d obtinut de thread %d", minimLocal, idThread);
#pragma omp critical
		{
			if (minim > minimLocal)
				minim = minimLocal;
		}

	}

	printf("\n Minimul este %d", minim);

	printf("\n Exemplu barrier - join");

#pragma omp parallel num_threads(4)
	{
		printf("\n Hello");
#pragma omp barrier
		printf("\n Bye");
	}

	printf("\n Exemplu suma folosind omp for cu reduction");

	int suma = 0;

	for (int i = 0; i < 100; i++) {
		suma += valori[i];
	}

	printf("\n Suma calculata secvential este %d", suma);

	suma = 0;

	//varianta 1
//#pragma omp parallel num_threads(4) shared(suma)
//	{
//#pragma omp for reduction(+: suma)
//		for (int i = 0; i < 100; i++) {
//			suma += valori[i];
//			if (i > 50) {
//				printf("\n Suma partiala pe thread cu id %d este %d", omp_get_thread_num(), suma);
//			}
//		}
//
//		printf("\n Suma calculata paralel este %d", suma);
//	}


	//varianta 2
//#pragma omp parallel num_threads(4) shared(suma)
//	{
//#pragma omp for reduction(+: suma)
//		for (int i = 0; i < 100; i++) {
//			suma += valori[i];
//		}
//	}
//
//	printf("\n Suma calculata paralel este %d", suma);


#pragma omp parallel for num_threads(4) reduction(+: suma)
	for (int i = 0; i < 100; i++) {
			suma += valori[i];
	}
	

	printf("\n Suma calculata paralel este %d", suma);


	printf("\n ---------- Exemplu schedule static pentru for ");

#pragma omp parallel num_threads(4)
	{
#pragma omp for schedule(static)
		for (int i = 0; i < 10; i++) {
			printf("\n Thread-ul %d a primit iteratia %d", omp_get_thread_num(), i);
		}
	}

	printf("\n ---------- Exemplu schedule dynamic pentru for ");

#pragma omp parallel num_threads(4)
	{
#pragma omp for schedule(dynamic)
		for (int i = 0; i < 10; i++) {
			printf("\n Thread-ul %d a primit iteratia %d", omp_get_thread_num(), i);
		}
	}
}