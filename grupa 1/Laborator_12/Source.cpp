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


//Merge sort
//https://www.tutorialspoint.com/cplusplus-program-to-implement-merge-sort

void swapping(int& a, int& b) {     //swap the content of a and b
	int temp;
	temp = a;
	a = b;
	b = temp;
}
void display(int* array, int size) {
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}
void merge(int* array, int l, int m, int r) {
	int i, j, k;
	//size of left and right sub-arrays
	const int nl = m - l + 1; 
	const int nr = r - m;
	int* larr = new int[nl];
	int* rarr = new int[nr];
	//fill left and right sub-arrays
	for (i = 0; i < nl; i++)
		larr[i] = array[l + i];
	for (j = 0; j < nr; j++)
		rarr[j] = array[m + 1 + j];
	i = 0; j = 0; k = l;
	//marge temp arrays to real array
	while (i < nl && j < nr) {
		if (larr[i] <= rarr[j]) {
			array[k] = larr[i];
			i++;
		}
		else {
			array[k] = rarr[j];
			j++;
		}
		k++;
	}
	while (i < nl) {       //extra element in left array
		array[k] = larr[i];
		i++; k++;
	}
	while (j < nr) {     //extra element in right array
		array[k] = rarr[j];
		j++; k++;
	}

	delete[] larr;
	delete[] rarr;
}
void mergeSort(int* array, int l, int r) {
	int m;
	if (l < r) {
		int m = l + (r - l) / 2;
		// Sort first and second arrays
		mergeSort(array, l, m);
		mergeSort(array, m + 1, r);
		merge(array, l, m, r);
	}
}

void sortareMerge(int* valori, int N) {
	mergeSort(valori, 0, N - 1);
}

//bitonic sort - secvential
//https://people.cs.rutgers.edu/~venugopa/parallel_summer2012/bitonic_openmp.html

int m;
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MIN(A, B) (((A) > (B)) ? (B) : (A))
#define UP 0
#define DOWN 1

void bitonic_sort_seq(int start, int length, int* seq, int flag)
{
	int i;
	int split_length;

	if (length == 1)
		return;

	if (length % 2 != 0)
	{
		printf("error\n");
		exit(0);
	}

	split_length = length / 2;

	// bitonic split
	for (i = start; i < start + split_length; i++)
	{
		if (flag == UP)
		{
			if (seq[i] > seq[i + split_length])
				swap(seq[i], seq[i + split_length]);
		}
		else
		{
			if (seq[i] < seq[i + split_length])
				swap(seq[i], seq[i + split_length]);
		}
	}

	bitonic_sort_seq(start, split_length, seq, flag);
	bitonic_sort_seq(start + split_length, split_length, seq, flag);
}

void bitonic_sort_par(int start, int length, int* seq, int flag)
{
	int i;
	int split_length;

	if (length == 1)
		return;

	if (length % 2 != 0)
	{
		printf("The length of a (sub)sequence is not divided by 2.\n");
		exit(0);
	}

	split_length = length / 2;

	// bitonic split
#pragma omp parallel for shared(seq, flag, start, split_length) private(i)
	for (i = start; i < start + split_length; i++)
	{
		if (flag == UP)
		{
			if (seq[i] > seq[i + split_length])
				swap(seq[i], seq[i + split_length]);
		}
		else
		{
			if (seq[i] < seq[i + split_length])
				swap(seq[i], seq[i + split_length]);
		}
	}

	if (split_length > m)
	{
		// m is the size of sub part-> n/numThreads
		bitonic_sort_par(start, split_length, seq, flag);
		bitonic_sort_par(start + split_length, split_length, seq, flag);
	}

	return;
}

int main() {
	const int N = 2^17;		//avem nevoie pentru bitonic sort
	int* valori = generare(N);
	int* copie = copiere(valori, N);

	//Test pentru Bubble Sort
	//Durata sortare = 69.6267
	//benchmark(copie, N, sortareBubble, "Bubble Sort");

	//Test pentru Odd-Even Sort
	//Durata sortare = 53.0702
	//benchmark(copie, N, sortareOddEvenSecvential, "Odd-Even Sort");


	//Test pentru Odd - Even Parallel Sort
	//Durata sortare = 25.3927
	//benchmark(copie, N, sortareOddEvenParalel, "Odd-Even Parallel Sort");


	//Test pentru Merge Sort
	//Durata sortare = 0.164617
	benchmark(copie, N, sortareMerge, "Merge Sort");

}