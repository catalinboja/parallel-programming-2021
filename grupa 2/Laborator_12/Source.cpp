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


//bitonic sort
//https://github.com/richursa/cpuBitonicSort/blob/master/bitonicSort.cpp


void ascendingSwap(int index1, int index2, int* ar)                                           //swap two values such that they appear in ascending order in the array
{
	if (ar[index2] < ar[index1])
	{
		int temp = ar[index2];
		ar[index2] = ar[index1];
		ar[index1] = temp;
	}
}
void decendingSwap(int index1, int index2, int* ar)                                           //swap two values such that they appear in decending order in the array
{
	if (ar[index1] < ar[index2])
	{
		int temp = ar[index2];
		ar[index2] = ar[index1];
		ar[index1] = temp;
	}
}
void bitonicSortFromBitonicSequence(int startIndex, int lastIndex, int dir, int* ar)     //form a increaseing or decreasing array when a bitonic input is given to the function
{
	if (dir == 1)
	{
		int counter = 0;                                                                    //counter to keep track of already swapped elements ,, parallelising this area results in poor performance due to overhead ,,need to fix
		int noOfElements = lastIndex - startIndex + 1;
		for (int j = noOfElements / 2; j > 0; j = j / 2)
		{
			counter = 0;
			for (int i = startIndex; i + j <= lastIndex; i++)
			{
				if (counter < j)
				{
					ascendingSwap(i, i + j, ar);
					counter++;

				}
				else
				{
					counter = 0;
					i = i + j - 1;

				}
			}
		}
	}
	else                                                                                    //decending sort
	{
		int counter = 0;
		int noOfElements = lastIndex - startIndex + 1;
		for (int j = noOfElements / 2; j > 0; j = j / 2)
		{
			counter = 0;
			for (int i = startIndex; i <= (lastIndex - j); i++)
			{
				if (counter < j)
				{
					decendingSwap(i, i + j, ar);
					counter++;

				}
				else
				{
					counter = 0;
					i = i + j - 1;

				}
			}
		}
	}

}
void bitonicSequenceGenerator(int startIndex, int lastIndex, int* ar)                         //generate a bitonic sequence  from a a random order
{
	int noOfElements = lastIndex - startIndex + 1;
	for (int j = 2; j <= noOfElements; j = j * 2)
	{
#pragma omp parallel for                                                         //parallel implementation results in most performance gains here
		for (int i = 0; i < noOfElements; i = i + j)
		{
			if (((i / j) % 2) == 0)                                                               //extra computation results in drastically lower performance ,need to fix
			{
				bitonicSortFromBitonicSequence(i, i + j - 1, 1, ar);
			}
			else
			{
				bitonicSortFromBitonicSequence(i, i + j - 1, 0, ar);
			}
		}
	}
}

void sortareBitonicParalel(int* valori, int N) {
	//bitonic_sort_par(0, N, valori, UP);
	bitonicSequenceGenerator(0, N - 1, valori);
}

int main() {
	const int N = pow(2, 25);		//avem nevoie pentru bitonic sort
	//const int N = 1e5;
	int* valori = generare(N);
	int* copie = copiere(valori, N);

	//Test pentru Bubble Sort
	//Durata sortare = 72.5686
	//benchmark(copie, N, sortareBubble, "Bubble Sort");

	//Test pentru Odd-Even Sort
	//Durata sortare = 52.893
	//benchmark(copie, N, sortareOddEvenSecvential, "Odd-Even Sort");

	//Test pentru Odd - Even Parallel Sort
	//Durata sortare = 26.8765
	//benchmark(copie, N, sortareOddEvenParalel, "Odd-Even Parallel Sort");

	//Test pentru Merge Sort
	//Durata sortare = 0.140404
	//Test pentru Merge Sort pentru 2^25 valori
	//Durata sortare = 31.7488
	benchmark(valori, N, sortareMerge, "Merge Sort");

	//Test pentru Bitonic Sort Paralel
	//Durata sortare = 0.158533
	//Test pentru Bitonic Sort Paralel pentru 2^25 valori
	//Durata sortare = 41.6421
	benchmark(copie, N, sortareBitonicParalel, "Bitonic Sort Paralel");

}