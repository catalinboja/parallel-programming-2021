#include <stdio.h>
#include <omp.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <math.h>

using namespace std;

const long N = 1e11;
const int NR_THREAD = 8;
const long LIMITA_SUP = (long)1e9;

alignas(1024) int vb;


//versiune secventiala calcul numar divizori pentru valoare primita
//metoda calculeaza cate valori sunt divizibile cu 10
void calculSecventialNumarDivizori(long n, long& nrDivizori) {
	for (long valoare = 1; valoare <= n; valoare++) {
		if (valoare % 10 == 0) {
			nrDivizori += 1;
		}
	}
}

void calculSecventialNumarDivizoriInterval(long limitaInf, long limitaSup, long n, long& nrDivizori) {
	for (long valoare = limitaInf; valoare <= limitaSup; valoare++) {
		if (valoare % 10 == 0) {
			nrDivizori += 1;
		}
	}
}


//versiune paralela pe un numar de thread-uri dat prin NR_THREAD cu rezultate partiale
void calculParalelNumarDivizoriRezultatePartiale(long n, long& nrDivizori) {
	long dimensiuneInterval = n / NR_THREAD;
	long rezultate[NR_THREAD];
	for (int i = 0; i < NR_THREAD; i++)
		rezultate[i] = 0;
	vector<thread> fireExecutie;
	for (int i = 0; i < NR_THREAD; i++) {
		long limitaInf = (i == 0) ? 1 : (i * dimensiuneInterval);
		long limitaSup = (i == NR_THREAD - 1) ? n : (i + 1) * dimensiuneInterval - 1;
		fireExecutie.push_back(
			thread(calculSecventialNumarDivizoriInterval,
				limitaInf,
				limitaSup,
				n,
				ref(rezultate[i])));
	}
	for (int i = 0; i < NR_THREAD; i++) {
		fireExecutie[i].join();
	}
	for (int i = 0; i < NR_THREAD; i++) {
		nrDivizori += rezultate[i];
	}
}

//versiune paralela pe un numar de thread-uri dat prin NR_THREAD cu rezultate partiale
void calculParalelNumarDivizoriRezultatePartialeCuDistantaControlata(long n, long& nrDivizori) {
	long dimensiuneInterval = n / NR_THREAD;

	//pentru a indeparta valorile din rezultate - pentru a nu intra pe aceeasi linie de cache
	// simulam o matrice

	long rezultate[NR_THREAD][1000];
	for (int i = 0; i < NR_THREAD; i++)
		rezultate[i][0] = 0;
	vector<thread> fireExecutie;
	for (int i = 0; i < NR_THREAD; i++) {
		long limitaInf = (i == 0) ? 1 : (i * dimensiuneInterval);
		long limitaSup = (i == NR_THREAD - 1) ? n : (i + 1) * dimensiuneInterval - 1;
		fireExecutie.push_back(
			thread(calculSecventialNumarDivizoriInterval,
				limitaInf,
				limitaSup,
				n,
				ref(rezultate[i][0])));
	}
	for (int i = 0; i < NR_THREAD; i++) {
		fireExecutie[i].join();
	}
	for (int i = 0; i < NR_THREAD; i++) {
		nrDivizori += rezultate[i][0];
	}
}

//functie benchmarking
void benchmark(void (*pf)(long, long&), long n, string info) {
	printf("\n Test pentru %s ", info.c_str());

	double tStart = omp_get_wtime();
	long rezultat = 0;
	pf(n, rezultat);
	double tFinal = omp_get_wtime();

	printf("\n Rezultat = %d", rezultat);
	printf("\n Durata = %f secunde", (tFinal - tStart));
}

int main() {

	//benchmark(calculSecventialNumarDivizori, N, "Test secvential ");
	//benchmark(calculParalelNumarDivizoriMutex, N, "Test paralel cu mutex ");
	//benchmark(calculParalelNumarDivizoriRezultatePartiale, N, "Test paralel cu rezultate partiale ");
	//benchmark(calculParalelNumarDivizoriRezultatePartialeCuDistantaControlata, N, "Test paralel cu rezultate partiale distantate in memorie ");

	int contor = 150;
	int variabilaLocala = 500;
	int variabilaPartajata = 0;
	int variabila = 200;
	string mesaj = "Hello ";
	int nrProcesoare = omp_get_num_procs();

	printf("\n Numarul maxim de thread-uri ce pot fi obtinute este %d", omp_get_max_threads());

#pragma omp parallel if(nrProcesoare > 4) \
	private(contor) firstprivate(variabilaLocala) shared(variabilaPartajata) default(shared)
	{
		contor = 0;
		for (int i = 0; i < 100; i++) {
			contor += 1;
			variabilaLocala += 1;
			variabilaPartajata += 1;
			variabila += 1;
		}
		
		printf("\n%s de la thread-ul cu id-ul %d", mesaj.c_str(), omp_get_thread_num());
		printf("\n Valoare contor = %d", contor);
		printf("\n Valoare locala = %d", variabilaLocala);
	}

	printf("\n Valoare contor = %d", contor);
	printf("\n Valoare partajata = %d", variabilaPartajata);

	omp_set_num_threads(4);

	printf("\n ------------------- Zona cu 4 thread-uri");

#pragma omp parallel 
	{
		printf("\n%s de la thread-ul cu id-ul %d", mesaj.c_str(), omp_get_thread_num());
	}

#pragma omp parallel 
	{
		printf("\n%s de la thread-ul cu id-ul %d", mesaj.c_str(), omp_get_thread_num());
	}

	printf("\n ------------------- Zona paralela cu 2 thread-uri");

#pragma omp parallel num_threads(2)
	{
		printf("\n%s de la thread-ul cu id-ul %d", mesaj.c_str(), omp_get_thread_num());
	}

	printf("\n Numarul maxim de thread-uri ce pot fi obtinute este %d", omp_get_max_threads());

}