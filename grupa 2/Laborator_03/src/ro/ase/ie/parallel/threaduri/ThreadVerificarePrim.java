package ro.ase.ie.parallel.threaduri;

import ro.ase.ie.parallel.secvential.ContorNrPrime;

public class ThreadVerificarePrim extends Thread{
	
	long numar;
	int rezultat;

	public ThreadVerificarePrim(long numar) {
		super();
		this.numar = numar;
	}

	public int getRezultat() {
		return rezultat;
	}

	@Override
	public void run() {
		this.rezultat = (int) ContorNrPrime.getNrPrime(numar, numar+1);
	}
	
	

}
