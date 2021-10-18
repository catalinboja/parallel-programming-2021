package ro.ase.ie.parallel.threaduri;

import ro.ase.ie.parallel.Util;
import ro.ase.ie.parallel.secvential.ContorNrPrime;

public class ThreadVerificareNumar extends Thread {
	
	long valoare;
	long rezultat;
	
	public ThreadVerificareNumar(long valoare) {
		super();
		this.valoare = valoare;
	}

	@Override
	public void run() {
		this.rezultat = ContorNrPrime.getNrPrime(valoare, valoare + 1);
	}

	public long getRezultat() {
		return rezultat;
	}
	
}
