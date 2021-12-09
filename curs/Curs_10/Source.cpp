#include <string>
#include <iostream>
#include <omp.h>

using namespace std;

int main() {

	const int N = 100;
	int valori[N];

	for (int i = 0; i < N; i++) {
		valori[i] = i + 1;
	}

	for (int i = 1; i < N; i++) {
		valori[i] = valori[i - 1] + 2;
		//cout << endl << "Thread id = " << omp_get_thread_num();
	}

	cout << endl << "Valori: ";
	for (int i = 0; i < N; i++) {
		cout << " " << valori[i];
	}

	//atentie la dependentele dintre iteratii
#pragma omp parallel for
	for(int i = 1; i < N; i++) {
		valori[i] = valori[i - 1] + 2;
		//cout << endl << "Thread id = " << omp_get_thread_num();
	}

	cout << endl << "Valori: ";
	for(int i = 0; i < N; i++) {
		cout << " " << valori[i];
	}


	//directive omp
#pragma omp parallel 
	{
		//if (omp_get_thread_num() == 0) {
		//	printf("\n Start secventa paralela");
		//}


		//secventa este executata doar de thread-ul cu id-ul 0
#pragma omp master
		{
			if (omp_get_thread_num() == 0)
			{
				printf("\n Hello de la thread cu id 0");
			}
			printf("\n Start secventa paralela");
		}

		printf("\n Hello");

		//secventa este executata o singura data de oricare thread
#pragma omp single
		{
			int id = omp_get_thread_num();
			printf("\n Secventa single executata de thread %d", id);
		}

		//fiecare sectiune este executata o singura data de oricare thread
#pragma omp sections
		{
#pragma omp section
			{
				int id = omp_get_thread_num();
				printf("\n Sectiune 1 executata de thread %d", id);
			}
#pragma omp section
			{
				int id = omp_get_thread_num();
				printf("\n Sectiune 2 executata de thread %d", id);
			}
#pragma omp section
			{
				int id = omp_get_thread_num();
				printf("\n Sectiune 3 executata de thread %d", id);
			}
		}
	}

	cout << endl << "-----------------------------------------";
#pragma omp parallel
	{

		printf("\n Hello");

#pragma omp for nowait
		for (int i = 0; i < 4; i++) {
			printf("\n Hello pentru iteratia %d", i);
		}

		printf("\n Bye");

	}


}