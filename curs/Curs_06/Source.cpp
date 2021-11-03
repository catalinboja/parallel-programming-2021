#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <omp.h>
#include <vector>

using namespace std;

std::mutex mutexGlobal;

void standardHello() {
	std::cout << std::endl << "Hello !";
}

void customHello(std::string mesaj) {
	std::cout << std::endl << mesaj;
}

void sumaNumere(int a, int b) {
	int rezultat = a + b;
	//std::cout << std::endl << "Suma este " << rezultat;
	printf("\nSuma este %d", rezultat);
}

void incrementValoare(int& valoare) {
	for (int i = 0; i < 10; i++) {
		mutexGlobal.lock();
		valoare += 1;
		mutexGlobal.unlock();
	}
}



int main() {

	std::vector<std::thread> threaduri;

	standardHello();
	customHello("Intro in C++ threads");
	
	int contor = 1;

	std::thread t1(standardHello);
	threaduri.push_back(t1);

	std::thread t2(standardHello);
	threaduri.push_back(t2);
	std::thread t3(standardHello);
	threaduri.push_back(t3);
	std::thread t4(customHello,"Hello din Custom thread");
	threaduri.push_back(t4);
	std::thread t5(sumaNumere, 2, 3);
	threaduri.push_back(t5);
	std::thread t6(incrementValoare, std::ref(contor));
	threaduri.push_back(t6);
	std::thread t7(incrementValoare, std::ref(contor));
	threaduri.push_back(t7);

	//for (std::thread &t : threaduri) {
	//	t.join();
	//}

	for (int i = 0; i < threaduri.size(); i++) {
		threaduri[i].join();
	}


	//t1.join();
	//t2.join();
	//t3.join();
	//t4.join();
	//t5.join();
	//t6.join();
	//t7.join();

	std::cout << std::endl << "Contor  = " << contor;
	std::cout << std::endl << "Sfarsit exemplu !";
}