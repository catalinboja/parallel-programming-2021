#include <iostream>
#include <string>
#include <omp.h>
using namespace std;

int main() {

	printf("\n -------------------- Test nowait --------------");

#pragma omp parallel 
	{
		printf("\n Hello");

#pragma omp for nowait
		for (int i = 0; i < 4; i++) {
			printf("\n Iteratia %d executata de thread-ul %d", i, omp_get_thread_num());
		}

		printf("\n Bye");
	}

	printf("\n -------------------- Test sectiuni --------------");

#pragma omp parallel
	{
		printf("\n Hello");

#pragma omp master
		{
			printf("\n Hello master de la thread-ul cu id-ul %d", omp_get_thread_num());
		}

#pragma omp single
		{
			printf("\n Hello special de la thread-ul cu id-ul %d", omp_get_thread_num());
		}
#pragma omp sections nowait
		{
#pragma omp section
			{
				printf("\n Hi de la thread-ul cu id-ul %d", omp_get_thread_num());
			}
#pragma omp section 
			{
				printf("\n Hola de la thread-ul cu id-ul %d", omp_get_thread_num());
			}
		}

		printf("\n Bye");
	}

	printf("\n -------------------- Exemplu sectiuni --------------");

	const int N = 20000;
	int a[N], b[N], suma[N], produs[N];

#pragma omp parallel 
	{

		int threadId = omp_get_thread_num();
		printf("\n Thread-ul %d a pornit", threadId);

#pragma omp master
		{
			if (omp_in_parallel() != 0) {
				printf("\n Solutia se executa in paralel");
			}
			else {
				printf("\n Solutia se executa secvential");
			}
		}


#pragma omp for 
		for (int i = 0; i < N; i++) {
			a[i] = i;
			b[i] = i * 3;
		}//bariera implicita

#pragma omp sections nowait
		{
#pragma omp section 
			{
				printf("\n Thread-ul %d va calcula suma vectorilor", threadId);
				for (int i = 0; i < N; i++) {
					suma[i] = a[i] + b[i];
				}
			}
#pragma omp section
			{
				printf("\n Thread-ul %d va calcula produsul vectorilor", threadId);
				for (int i = 0; i < N; i++) {
					produs[i] = a[i] * b[i];
				}
			}
		}

		printf("\n Thread-ul %d a terminat", threadId);

	}

}
