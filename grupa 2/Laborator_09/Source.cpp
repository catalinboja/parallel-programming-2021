#include "sha1.h"
#include <string>
#include <fstream>
#include <omp.h>
using namespace std;

int main() {


	string hashCautat = "00c3cc7c9d684decd98721deaa0729d73faa9d9b";

	//exemplu utilizare hash
	string parola = "test";
	string hash = sha1(parola);
	cout << endl << "sha1('test'):" << hash;

	ifstream fisier("10-million-password-list-top-1000000.txt");
	string linie;
	fisier >> linie;

	cout << endl << "Prima parola din fisier este " << linie;

	fisier.eof();

	fisier.close();
}