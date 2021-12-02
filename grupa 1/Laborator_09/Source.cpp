#include "sha1.h"
#include <string>
#include <fstream>
#include <omp.h>
using namespace std;

int main() {
	//exemplu utilizare hash

	string hashPrimit = "00c3cc7c9d684decd98721deaa0729d73faa9d9b";

	string parola = "test";

	string hash = sha1(parola);

	cout << endl << "sha1('test'):" << hash;

	ifstream fisier("10-million-password-list-top-1000000.txt");

	double tSTart = omp_get_wtime();

	while (!fisier.eof()) {
		string linie;
		fisier >> linie;
		string valoareHash = sha1(sha1("parallel" + linie));

		if (valoareHash == hashPrimit) {
			cout << endl << "Parola cautata este " << linie;
			break;
		}
	}

	double tFinal = omp_get_wtime();
	cout << endl << "Timp solutie secventiala = " << tFinal - tSTart;

	fisier.close();

	fisier.open("10-million-password-list-top-1000000.txt");

	tSTart = omp_get_wtime();
	bool parolaGasita = false;

#pragma omp parallel num_threads(4) shared(parolaGasita)
	{
		while (!fisier.eof() && !parolaGasita) {
			string linie;
#pragma omp critical
			{
				fisier >> linie;
			}
			
			string valoareHash = sha1(sha1("parallel" + linie));

			if (valoareHash == hashPrimit) {
				cout << endl << "Parola cautata este " << linie;
				cout << endl << "A fost gasita de thread-ul " << omp_get_thread_num();
				parolaGasita = true;
			}
		}
	}

	tFinal = omp_get_wtime();
	cout << "Timp solutie paralela = " << tFinal - tSTart;
}