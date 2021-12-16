#include <iostream>
#include <string>
#include <omp.h>
using namespace std;


//generare vector random
int* generare(int N) {
	srand(1000);
	int* valori = new int[N];
	for (int i = 0; i < N; i++) {
		valori[i] = rand() % 10000;		//valorile random sunt in [0, 9999]
	}
	return valori;
}

int* copiere(int* valori, int N) {
	int* copie = new int[N];
	memcpy(copie, valori, N * sizeof(int));
	return copie;
}

bool esteSortatCrescator(int* valori, int N) {
	bool esteSortat = true;
	for (int i = 0; i < N - 1; i++) {
		if (valori[i] > valori[i + 1]) {
			esteSortat = false;
			break;
		}
	}
	return esteSortat;
}

void benchmark(int* valori, int N, void (*pf)(int*, int), string mesaj) {

	cout << endl << "Test pentru " << mesaj;

	double tStart = omp_get_wtime();
	pf(valori, N);
	double tFinal = omp_get_wtime();

	cout << endl << "Durata sortare = " << (tFinal - tStart);
	if (esteSortatCrescator(valori, N)) {
		cout << endl << "Sortare corecta";
	}
	else
	{
		cout << endl << "*** Sortare gresita";
	}
}


void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void sortareBubble(int* valori, int N) {
	bool isOver = true;
	do {
		isOver = true;
		for (int i = 1; i < N; i++)
			if (valori[i - 1] > valori[i])
			{
				swap(valori[i - 1], valori[i]);
				isOver = false;
			}
	} while (!isOver);

}

void sortareOddEvenSecvential(int* v, int N) {
	for (int it = 0; it < N; it++)
	{
		if (it % 2 == 1) {
			for (int i = 2; i < N; i += 2)
				if (v[i - 1] > v[i])
					swap(v[i - 1], v[i]);
		}
		else {
			for (int i = 1; i < N; i += 2)
				if (v[i - 1] > v[i])
					swap(v[i - 1], v[i]);
		}
	}
}

void sortareOddEvenParalel(int* v, int N) {

	for (int it = 0; it < N; it++) {
		if (it % 2 == 1) {
#pragma omp parallel for shared(v)
			for (int i = 2; i < N; i += 2)
				if (v[i - 1] > v[i])
					swap(v[i - 1], v[i]);
		}
		else {
#pragma omp parallel for shared(v)
			for (int i = 1; i < N; i += 2)
				if (v[i - 1] > v[i])
					swap(v[i - 1], v[i]);
		}
	}
}

int main() {
	const int N = 1e5;
	int* valori = generare(N);
	int* copie = copiere(valori, N);

	//Test pentru Bubble Sort
	//Durata sortare = 69.6267
	//benchmark(copie, N, sortareBubble, "Bubble Sort");

	//Test pentru Odd-Even Sort
	//Durata sortare = 53.0702
	//benchmark(copie, N, sortareOddEvenSecvential, "Odd-Even Sort");

	
}