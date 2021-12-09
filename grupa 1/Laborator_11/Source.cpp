#include <iostream>
#include <string>
#include <omp.h>

using namespace std;

int main() {

	printf("\n Zona nowait");

#pragma omp parallel
	{
		printf("\n Hello !");

#pragma omp for nowait
		for (int i = 0; i < 4; i++) {
			printf("\n Procesare iteratie %d de catre thread %d", i, omp_get_thread_num());
		}

		printf("\n Bye");

	}

	printf("\n ------------------ Zona sectiuni");

#pragma omp parallel 
	{

		printf("\n Hello");

#pragma omp master
		{
			printf("\n Hello de la master thread, cu id-ul %d", omp_get_thread_num());
		}

#pragma omp single
		{
			printf("\n Hello de la thread-ul, cu id-ul %d", omp_get_thread_num());
		}

#pragma omp sections
		{
#pragma omp section
			{
				printf("\n Hi de le thread-ul cu id-ul %d", omp_get_thread_num());
			}
#pragma omp section
			{
				printf("\n Hola de le thread-ul cu id-ul %d", omp_get_thread_num());
			}
		}
		printf("\n Bye");
	}

	printf("\n ------------------ Exemplu sectiuni");

	const int N = 20;
	int a[N], b[N], suma[N], produs[N];

	for (int i = 0; i < N; i++) {
		a[i] = i;
		b[i] = i + 1;
		suma[i] = produs[i] = 0;
	}

	int threadId;

#pragma omp parallel shared(a,b,suma,produs) private(threadId)
	{
		threadId = omp_get_thread_num();

#pragma omp master
		{
			if (omp_in_parallel() != 0) {
				printf("\n Executie paralela cu %d thread-uri", omp_get_num_threads());
			}
		}

		printf("\n Thread-ul cu id %d a pornit", threadId);

#pragma omp sections
		{
#pragma omp section 
			{
				printf("\n Suma executata de thread-ul %d", threadId);
				for (int i = 0; i < N; i++) {
					suma[i] = a[i] + b[i];
					printf("\n suma[%d] = %d de catre %d", i, suma[i], threadId);
				}
			}

#pragma omp section 
			{
				printf("\n Produs executat de thread-ul %d", threadId);
				for (int i = 0; i < N; i++) {
					produs[i] = a[i] * b[i];
					printf("\n produs[%d] = %d de catre %d", i, produs[i], threadId);
				}
			}
		}
	}


	//o alta varianta
	printf("\n --------- O alta varianta");
#pragma omp parallel shared(a,b,suma,produs) private(threadId)
	{
		threadId = omp_get_thread_num();

#pragma omp master
		{
			if (omp_in_parallel() != 0) {
				printf("\n Executie paralela cu %d thread-uri", omp_get_num_threads());
			}
		}

		printf("\n Thread-ul cu id %d a pornit", threadId);

		for (int i = 0; i < N; i++) {
#pragma omp single
			{
				suma[i] = a[i] + b[i];
				printf("\n suma[%d] = %d de catre %d", i, suma[i], threadId);
			}
		}
	}
}